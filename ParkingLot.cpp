#include "ParkingLot.h"

using namespace MtmParkingLot;
using namespace ParkingLotUtils;

ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]):
	motorbikes(parkingBlockSizes[0]),
	private_cars(parkingBlockSizes[1]),
	handicapped_cars(parkingBlockSizes[2]){
}

ParkingLot::~ParkingLot() {
	motorbikes.~UniqueArray();
	private_cars.~UniqueArray();
	handicapped_cars.~UniqueArray();
}

inline void entry_attempt(UniqueArray<Vehicle, equal_to>& unique, Vehicle vehicle) {

	unsigned int i = unique.insert(vehicle);

	ParkingSpot spot = ParkingSpot(vehicle.typeOfVehicle(), i);
	vehicle.setParkingSpot(spot);

	std::cout << vehicle;
	ParkingLotPrinter::printEntrySuccess(std::cout, spot);
}

inline ParkingResult already_parked(ParkingSpot spot) {

	ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout, spot);
	return VEHICLE_ALREADY_PARKED;
}

ParkingResult ParkingLot::enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime) {
	
	Vehicle vehicle = Vehicle(vehicleType, licensePlate, entranceTime);
	unsigned int index = 0;

	try {
		if (vehicleType == HANDICAPPED) {
			
			if (handicapped_cars.getIndex(vehicle, index)) 
				return already_parked(ParkingSpot(HANDICAPPED, index));
			
			if (private_cars.getIndex(vehicle, index))
				return already_parked(ParkingSpot(CAR, index));

			entry_attempt(handicapped_cars, vehicle);
			return SUCCESS;
		}
	}
	catch (UniqueArray<Vehicle, equal_to>::UniqueArrayIsFullException& exception) {

		//do nothing...
	}
	try {
		if (vehicleType == MOTORBIKE) {

			if (motorbikes.getIndex(vehicle, index))
				return already_parked(ParkingSpot(MOTORBIKE, index));
	
			entry_attempt(motorbikes, vehicle);
			return SUCCESS;
		}
		else {
			if(vehicleType == CAR) if (private_cars.getIndex(vehicle, index)) 
				return already_parked(ParkingSpot(CAR, index));
	
			entry_attempt(private_cars, vehicle);
			return SUCCESS;
		}
	}
	catch (UniqueArray<Vehicle, equal_to>::UniqueArrayIsFullException& exception) {
		
		ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
		return NO_EMPTY_SPOT;
	}
}

inline unsigned int min(unsigned int first, unsigned int second) {

	if (first <= second) return first;
	return second;
}

unsigned int howMuchMoney(const Vehicle vehicle, Time exit) {
	
	//I used a map because I don't like using enums like chars or ints. this is totally unnecessary however.
	static std::map<VehicleType, int> take = { {MOTORBIKE, 0}, {HANDICAPPED, 1}, {CAR, 2} };
	static int initial_pay[3] = { 10, 15, 20 };
	static int extra_pay[3] = { 5, 0, 10 };

	VehicleType type = vehicle.typeOfVehicle();
	Time::Hour hour = vehicle.timeParking(exit);
	unsigned int sum = 0;

	if(hour > 0) sum += initial_pay[take.at(type)];
	if (hour > 1) sum += extra_pay[take.at(type)] * ( min(hour,6) - 1);
	if (vehicle.wasFined()) sum += 250;

	return sum;
}

ParkingResult ParkingLot::exitParking(LicensePlate licensePlate, Time exitTime) {
	
	Vehicle dud = Vehicle(HANDICAPPED, licensePlate, Time());
	const Vehicle* vehicle = NULL;
	
	UniqueArray<Vehicle, equal_to>* temp;

	if (vehicle = motorbikes[dud] != NULL) { //compilation problems : suggests parenthesis.

		temp = &motorbikes;
	}
	else if(vehicle = private_cars[dud] != NULL){

		temp = &private_cars;
	}
	else if (vehicle = handicapped_cars[dud] != NULL) {

		temp = &handicapped_cars;
	}else {

		ParkingLotPrinter::printExitFailure(std::cout, licensePlate);
		return VEHICLE_NOT_FOUND;
	}
	
	unsigned int price = howMuchMoney(vehicle, exitTime);
	ParkingLotPrinter::printExitSuccess(std::cout, vehicle->getParkingSpot(), exitTime, price);

	temp->remove(*vehicle);
	return SUCCESS;
}

//first:
/*
ParkingResult ParkingLot::getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const {

	unsigned int index = 0;
	Vehicle dud = Vehicle(HANDICAPPED, licensePlate, Time());

	if (motorbikes.getIndex(dud, index)) {
		parkingSpot = ParkingSpot(MOTORBIKE, index);
		return SUCCESS;
	}
	if (handicapped_cars.getIndex(dud, index)) {
		parkingSpot = ParkingSpot(HANDICAPPED, index);
		return SUCCESS;
	}
	if (private_cars.getIndex(dud, index) {
		parkingSpot = ParkingSpot(CAR, index);
		return SUCCESS;
	}

	return VEHICLE_NOT_FOUND;
}
*/
//second

ParkingResult ParkingLot::getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const{

	Vehicle dud = Vehicle(HANDICAPPED, licensePlate, Time());
	const Vehicle* res = NULL;

	if (res = handicapped_cars[dud] != NULL);
	else if (res = motorbikes[dud] != NULL);
	else if (res = private_cars[dud] != NULL);
	else {
		return VEHICLE_NOT_FOUND;
	}

	parkingSpot = res->getParkingSpot();
	return SUCCESS;
}


class inspect_filter : UniqueArray<Vehicle, equal_to>::Filter {
	
	Time inspection_t;

public:
	
	inspect_filter(Time inspection) {

		inspection_t = inspection;
	}

	virtual bool operator() (const Vehicle& vehicle) const {
		
		return vehicle.inspect(inspection_t);
	}
};

inline unsigned int copy_and_inspect(inspect_filter& filter, UniqueArray<Vehicle, equal_to>& unique) {

	UniqueArray<Vehicle, equal_to> copy = unique.filter((UniqueArray<Vehicle, equal_to>::Filter)filter);
	return copy.getCount();
}

void ParkingLot::inspectParkingLot(Time inspectionTime) {

	unsigned int count = 0;

	inspect_filter filter(inspectionTime);
	count += copy_and_inspect(filter, motorbikes);
	count += copy_and_inspect(filter, private_cars);
	count += copy_and_inspect(filter, handicapped_cars);

	ParkingLotPrinter::printInspectionResult(std::cout, inspectionTime, count);
}

class CompareVehiclePointers {
	
	bool less (const Vehicle first, const Vehicle second) const{
		return first.getParkingSpot() < second.getParkingSpot();
	}

public:
	bool operator() (const Vehicle * first, const Vehicle * second)  const {
		
		if (second == NULL) return true;
		else if (first == NULL) return false;

		return less(*first, *second);
	};
};

inline void copy_and_print(ostream& os, UniqueArray<Vehicle, equal_to>& arr) {

	UniqueArray<Vehicle, equal_to> copy = UniqueArray<Vehicle, equal_to>(arr);
	std::sort(copy.begin(), copy.end(), CompareVehiclePointers());
	
	for (Vehicle* vehicle : copy) {
		if (!vehicle) break;
		os << *vehicle;
		ParkingLotPrinter::printParkingSpot(os, vehicle->getParkingSpot());
	}
}

ostream& operator<<(ostream& os, const ParkingLot& parkingLot) {

	ParkingLotPrinter::printParkingLotTitle(os);

	copy_and_print(os, parkingLot.motorbikes);
	copy_and_print(os, parkingLot.handicapped_cars);
	copy_and_print(os, parkingLot.private_cars);
}