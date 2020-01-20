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
    VehicleType typeOfVehicle() const;
    double timeParking(Time exit_time) const;
	void setParkingSpot(ParkingSpot& p);
	ParkingSpot getParkingSpot() const;
	bool wasFined() const;

	bool operator==(const Vehicle& vehicleB) const;
	std::ostream& operator<<(std::ostream& os) const;

private:
	bool fine();
};

#endif