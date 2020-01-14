#include "ParkingLotTypes.h"
#include "Time.h"
class Vehicle {
public:
	virtual bool fine();
	virtual bool exit_parking();
protected:
	bool was_fined;
	VehicleType type;
	LicensePlate plate;
	Time entrence;
};

Vehicle::fine() {
	if (was_fined) return false;
	was_fined = true;
	return true;
}