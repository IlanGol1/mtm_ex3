#ifndef Vehicle_H

#define Vehicle_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingLotPrinter.h"

using namespace ParkingLotUtils;
using std::ostream;

class Vehicle {

	VehicleType type;
	LicensePlate plate;
	Time entrance;
	ParkingSpot spot;
	bool was_fined;

public:
	bool inspect(Time inspection_time);
	Vehicle(VehicleType type, LicensePlate plate, Time entrance);
	Vehicle(const Vehicle& other);
	VehicleType typeOfVehicle() const;
	double timeParking(Time exit_time) const;
	void setParkingSpot(ParkingSpot& p);
	ParkingSpot getParkingSpot() const;
	bool wasFined() const;
	friend bool operator==(const Vehicle& vehicleA, const Vehicle& vehicleB) const;
	friend ostream& operator<<(ostream& os, const Vehicle v) const;

private:
	bool fine();
};

ostream& operator<<(ostream& os, const Vehicle v) const{
	ParkingLotPrinter::printVehicle(os, v.type, v.plate, v.entrance);
}

bool operator==(const Vehicle& vehicleA, const Vehicle& vehicleB) const {
	return vehicleA.plate == vehicleB.plate;
}

#endif