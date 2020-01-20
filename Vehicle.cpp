#include "Vehicle.h"
#include "ParkingLotTypes.h"
#include "ParkingLotPrinter.h"
#include "assert.h"

Vehicle::Vehicle(VehicleType type_sand,
                 LicensePlate plate_sand,
                 Time entrance_sand) :
                 type(type_sand),
                 plate(plate_sand),
	entrance(entrance_sand),
	spot(), was_fined(false){
}

Vehicle::Vehicle(const Vehicle& other) :
        type(other.type),
        plate(other.plate),
		entrance(other.entrance),
		spot(other.spot.getParkingBlock(), other.spot.getParkingNumber()),
		was_fined(other.was_fined){
}

VehicleType Vehicle::typeOfVehicle() const{
    return type;
}

bool Vehicle::operator==(const Vehicle& vehicleB) const{
    return this->plate == vehicleB.plate;
}

ostream& Vehicle::operator<<(ostream& os) const{
	return ParkingLotUtils::ParkingLotPrinter::printVehicle(os, this->type, this->plate, this->entrance);
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

bool Vehicle::wasFined() const{
	return was_fined;
}

//returns true upon a successful fine
bool Vehicle::fine(){
	if (was_fined) {
		return false;
	}
	was_fined = true;
	return true;
}

double Vehicle::timeParking(Time exit_time) const{
	Time tmp = exit_time - entrance;
	return tmp.toHours();
}

bool Vehicle::inspect(Time inspection_time){
	if (timeParking(inspection_time) > 24) return fine();
	return false;
}