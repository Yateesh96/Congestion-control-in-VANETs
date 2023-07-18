#pragma once
#include "veins_inet/veins_inet.h"
#include "veins_inet/VeinsInetApplicationBase.h"
class VEINS_INET_API VeinsInetSampleApplication : public
veins::VeinsInetApplicationBase {
protected:
 	bool haveForwarded = false;
protected:
 	bool congested;
 	double vthreshold;
 	double vinst;
 	double conglvl;
 	double conglvl_before;
 	double maxconglvl;
 	double lastChangeAt;
 	double lastChangeCongAt;
 	double currentTimestamp;
 	int tcong;
 	int tfree;
 	int cnt;
protected:
 	double updateCongestionLevel();
 	void broadcast();
protected:
 	virtual bool startApplication() override;
 	virtual bool stopApplication() override;
 	virtual void processPacket(std::shared_ptr<inet::Packet> pk) override;
public:
 	VeinsInetSampleApplication();
 	~VeinsInetSampleApplication();
};
