# Congestion-control-in-VANETs
Vehicular Ad-hoc Network (VANET) is a fast-emerging technology derived from ad-hoc networks that provide intelligent communication between vehicles and other external devices. The fact that the VANET deals with high velocity movements of vehicles and the unpredictability of vehicles makes VANET unique from the rest of networks. The primary objective of VANET is to provide on road safety for the vehicles. These safety measures are achieved by making use of two types of message passing techniques viz.,

	i) Periodic safety messages

	ii) Event-driven messages

Periodic messages are used in order to exchange status information of the vehicle e.g., coordinates, velocity etc. whereas Event-driven messages are broadcasted whilst emergency situations e.g., accidents, harsh braking etc. These two types of messages are broadcasted over same channel. In case of heavy traffic conditions, these techniques are at a risk of failure since the periodic messages might consume the entire channel bandwidth leading to a congested channel. Hence, there is an absolute need for establishing a congestion control algorithm. In addition to that, using external infrastructure is an expensive process. In order to make it cost efficient, we need to reduce the usage of external infrastructure. In this project, we enhance the regular VANET’s by making use of only vehicle to vehicle(V2V) communication and reducing vehicle to Infrastructure communication(V2I), thereby reducing the cost.

In this model, we mainly focus on the following:

	a) Calculating congestion level of road by each vehicle.

	b) Transmitting obtained values to other vehicles 
