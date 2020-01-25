#include "Vehicle.h"
#include "ParkingLotTypes.h"
#include "ParkingLotPrinter.h"

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

ostream& operator<<(ostream& os, const Vehicle& vehicle) {
	return ParkingLotPrinter::printVehicle(os,
		    						    	vehicle.type,
		    						    	vehicle.plate,
		    						    	vehicle.entrance);
}

bool operator==(const Vehicle& vehicleA, const Vehicle& vehicleB) {
	return vehicleA.plate == vehicleB.plate;
}


void Vehicle::setParkingSpot(ParkingSpot& parkings_spot) {
	
	spot = ParkingSpot(parkings_spot.getParkingBlock(),
		 				parkings_spot.getParkingNumber());
}

ParkingSpot Vehicle::getParkingSpot() const {
	return spot;
}

bool Vehicle::wasFined() const{
	return was_fined;
}

bool Vehicle::fine(){
	if (was_fined) {
		return false;
	}
	was_fined = true;
	return true;
}

Time::Hour Vehicle::timeParking(Time exit_time) const{
	Time tmp = exit_time - entrance;
	return tmp.toHours();
}

bool Vehicle::inspect(Time inspection_time){
	if (timeParking(inspection_time) > 24) return fine();
	return false;
}