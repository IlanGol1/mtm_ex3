#ifndef Vehicle_H

#define Vehicle_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingLotPrinter.h"

using namespace ParkingLotUtils;

class Vehicle {
	VehicleType type;
	LicensePlate plate;
	Time entrance;
	ParkingSpot spot;
	bool was_fined;
	
public:
    bool inspect(Time inspection_time);
    Vehicle (VehicleType type, LicensePlate plate, Time entrance);
    Vehicle(const Vehicle& other);
    VehicleType typeOfVehicle();
    double timeParking(Time exit_time);
	void setParkingSpot(ParkingSpot& p);
	ParkingSpot getParkingSpot();
	bool wasFined();

	friend bool operator==(const Vehicle& vehicleA, const Vehicle& vehicleB);
	friend ostream& operator<<(ostream& os, Vehicle& vehicle);

private:
	bool fine();
};

#endif