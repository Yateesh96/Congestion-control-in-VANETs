#include "veins_inet/VeinsInetSampleApplication.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include "veins_inet/VeinsInetSampleMessage_m.h"
using namespace inet;
Define_Module(VeinsInetSampleApplication);
VeinsInetSampleApplication::VeinsInetSampleApplication()
{
}

void VeinsInetSampleApplication::broadcast()
{
 	cnt+=1
 	auto payload = makeShared<VeinsInetSampleMessage>();
 	timestampPayload(payload);
 	payload->setChunkLength(B(100));
 	payload->setRoadId(traciVehicle->getRoadId().c_str());

 	auto packet = createPacket(std::to_string(conglvl));
 	packet->insertAtBack(payload);
 	sendPacket(std::move(packet));
}
double VeinsInetSampleApplication::updateCongestionLevel()
//double updateCongestionLevel()
{
	 conglvl_before = conglvl;
 	if(congested)
 	{
 		if(mobility->getCurrentVelocity().length() <= vthreshold)
 		{
 		   lastChangeAt = 0;
		   currentTimestamp = simTime().dbl()*1000 ;
 		   if(maxconglvl >= (1+(( simTime().dbl()*1000 - lastChangeCongAt)/tcong)))
		   {
 			conglvl = 1+(( simTime().dbl()*1000 -lastChangeCongAt)/tcong);
 		   }
 		    else
 		   {
 			conglvl = maxconglvl;
		   }
 		}
		else if(lastChangeCongAt == 0)
 		{
			currentTimestamp = simTime().dbl()*1000;
 			lastChangeAt = currentTimestamp;
 		}
 		else if(simTime().dbl()*1000-lastChangeAt >= tfree)
		{
 			congested = false;
 			conglvl = 1;
 			lastChangeAt = 0;
		 }
 	}
 	else if(mobility->getCurrentVelocity().length() <= vthreshold)
 	{
 		if(lastChangeAt == 0)
 		{
 			lastChangeAt = simTime().dbl()*1000;
 		}
		else if((simTime().dbl()*1000 - lastChangeAt) >= tcong)
		{
 			congested = true;
 			lastChangeCongAt = lastChangeAt;
 			lastChangeAt = 0;
 			currentTimestamp = simTime().dbl()*1000;
 			if(maxconglvl >= (1+((currentTimestamp-lastChangeCongAt)/tcong)))
 			{
			       conglvl = 1+(( simTime().dbl()*1000 - lastChangeCongAt)/tcong);
 			}
 			else
			{
 				conglvl = maxconglvl;
			}
 		}
 	}
 else
{
 	lastChangeAt = 0;
}
return conglvl;
}

bool VeinsInetSampleApplication::startApplication()
{
 
 if(getParentModule()->getIndex()>=0)
 {
 	traciVehicle->setMaxSpeed(13.89);
 	congested=false;
 	vthreshold=4.63;
 	tfree=20000;
 	conglvl=1;
 	maxconglvl=9999;
 	lastChangeAt=0;
 	lastChangeCongAt=0;
 	tcong=10000;
 	cnt=0;
 	auto call=[this]()
 	{
 		EV_INFO<<getParentModule()->getIndex()<<":"<<
 		this->updateCongestionLevel();
 		/* if(this->conglvl_before!=this->conglvl)
 		{
 			this->broadcast();
		}*/
	};
		auto Timerspec=veins::TimerSpecification(call).interval(0.1);
 		timerManager.create(Timerspec,"update");
 	auto call2=[this]()
 	{ 
 		this->broadcast(); 
 	};
 		auto Timerspec=veins::TimerSpecification(call2).interval(1);
 		timerManager.create(Timerspec,"broadcast");
 	}
 
 	return true;
}

bool VeinsInetSampleApplication::stopApplication()
{
	return true;
}

VeinsInetSampleApplication::~VeinsInetSampleApplication()
{}
void VeinsInetSampleApplication::processPacket(std::shared_ptr<inet::Packet> pk)
{
 	auto payload = pk->peekAtFront<VeinsInetSampleMessage>();
	EV_INFO << "Received packet: " << payload << endl;
 	getParentModule()->getDisplayString().setTagArg("i", 1, "green");
 	traciVehicle->changeRoute(payload->getRoadId(), 999.9);

 	if (haveForwarded) return;

 	auto packet = createPacket("relay");
	packet->insertAtBack(payload);
 	sendPacket(std::move(packet));

 	haveForwarded = true;
}
