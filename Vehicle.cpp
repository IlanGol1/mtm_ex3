#include "Vehicle.h"
#include "Time.h"
#include "ParkingLotTypes.h"
#include "ParkingLotPrinter.h"

Vehicle::Vehicle(VehicleType type_sand,
                 LicensePlate plate_sand,
                 Time entrance_sand) :
                 was_fined(false),
                 type(type_sand),
                 plate(plate_sand){
	entrance(entrance_sand.day, entrance_sand.hour, entrance_sand.minute);
}

Vehicle::Vehicle(const Vehicle& other) :
        was_fined(other.was_fined),
        type(other.type),
        plate(other.plate) {
    entrance(other.entrance.day, other.entrance.hour ,other.entrance.minute);
}

VehicleType Vehicle::typeOfVehicle(){
    return type;
}

bool operator==(const Vehicle& vehicleA, const Vehicle& vehicleB){
    return vehicleA.plate == vehicleB.plate;
}

ostream& operator<<(ostream& os, const Vehicle& vehicle) {
	return ParkingLotUtils::ParkingLotPrinter::printVehicle(os, vehicle.type, vehicle.plate, vehicle.entrance);
}

//it's faulty and I know it, but we(I) also need it
void Vehicle::setParkingSpot(ParkingSpot& p) {
	spot = p;
}

ParkingSpot Vehicle::getParkingSpot() {
	return spot;
}

bool Vehicle::wasFined() {
	return was_fined;
}

//returns true upon a successful fine
bool Vehicle::fine() {
	if (was_fined) {
		return false;
	}
	was_fined = true;
	return true;
}

Time::Hour Vehicle::timeParking(Time exit_time) {
	Time tmp = exit_time - entrance;
	return tmp.toHours();
}

bool Vehicle::inspect(Time inspection_time) {
	if (timeParking(inspection_time) > 24) return fine();
	return false;
}