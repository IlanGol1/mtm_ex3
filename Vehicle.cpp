#include "Vehicle.h"
#include "Time.h"
#include "ParkingLotTypes.h"
#include "ParkingLotPrinter.h"
#include "assert.h"

Vehicle::Vehicle(VehicleType type_sand,
                 LicensePlate plate_sand,
                 Time entrance_sand) :
                 was_fined(false),
                 type(type_sand),
                 plate(plate_sand),
	entrance(entrance_sand.day, entrance_sand.hour, entrance_sand.minute),
	spot(){
}

Vehicle::Vehicle(const Vehicle& other) :
        was_fined(other.was_fined),
        type(other.type),
        plate(other.plate),
		entrance(other.entrance.day, other.entrance.hour ,other.entrance.minute){
	
	if (other.spot) this->spot = ParkingSpot(other.spot.getParkingBlock(), other.spot.getParkingNumber());
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

//it's a bit faulty but I haven't found a way around it, since we first need to initialize the Vehicle and then put it in the unique array and give it a spot.
//so you can potentially assume that spot is empty to prevent any mistakes (not easy to do).
//an option is to declare the insert functions as friends but that is too much and unnecessary.
void Vehicle::setParkingSpot(ParkingSpot& p) {
	
	spot = ParkingSpot(p.getParkingBlock(), p.getParkingNumber());
}

ParkingSpot Vehicle::getParkingSpot() const {
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