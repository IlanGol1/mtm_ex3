#include "ParkingLot.h"
#include "UniqueArray.h"
#include <map>

using namespace MtmParkingLot;
using namespace ParkingLotUtils;

ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]) {

	motorobikes = UniqueArray<Vehicle, std::equal_to>(parkingBlockSizes[0]);
	private_cars = UniqueArray<Vehicle, std::equal_to>(parkingBlockSizes[1]);
	handicapped_cars = UniqueArray<Vehicle, std::equal_to>(parkingBlockSizes[2]);
}

ParkingLot::~ParkingLot() {
	motorbikes.~UniqueArray();
	private_cars.~UniqueArray();
	handicapped_cars.~UniqueArray();
}

inline void entry_attempt(UniqueArray& unique, Vehicle& vehicle) {

	unsigned int i = unique.insert(vehicle);

	ParkingSpot spot = ParkingSpot(vehicle.typeOfVehicle(), i);
	vehicle.setParkingSpot(spot);

	std::cout << vehicle;
	ParkingLotPrinter::printEntrySuccess(std::cout, spot);
}

inline ParkingResult already_parked(ParkingSpot& spot) {

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
	catch (ArrayIsFullException& exception) {

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
	catch (ArrayIsFullException & exception) {
		
		ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
		return NO_EMPTY_SPOT;
	}
}

inline unsigned int max(unsigned int first, unsigned int second) {

	if (first >= second) return first;
	return second;
}

inline unsigned int howMuchMoney(VehicleType type, bool was_fined) {
	
	//I used a map because I don't like using enums like chars or ints. this is totally unnecessary however. (for my partner - they used maps at MtmParkingLot.cpp).
	static take<VehicleType, int> = { {MOTORBIKE, 0}, {HANDICAPPED, 1}, {CAR, 2} }
	static int[3] initial_pay = { 10, 15, 20 };
	static int[3] extra_pay = { 5, 0, 10 }

	unsigned int sum = 0;
	
	if(hour > 0) sum += initial_pay[take.to(type)];
	if (hour > 1) sum += extra_charge[take.to(type)] * ( max(hour,6) - 1);
	if (was_fined) sum += 250;

	return sum;
}

ParkingResult ParkingLot::exitParking(LicensePlate licensePlate, Time exitTime) {
	
	Vehicle dud = Vehicle(HANDICAPPED, licensePlate, Time());
	Vehicle* vehicle = NULL;
	
	UniqueArray<Vehicle>* temp;

	if (vehicle = motorbikes[dud]) {

		temp = &motorbikes;
	}
	else if(vehicle = private_cars[dud]){

		temp = &private_cars;
	}
	else if (vehicle = handicapped_cars[dud]) {

		temp = &handicapped_cars;
	}else {

		ParkingLotPrinter::printExitFailure(std::cout, licensePlate);
		return VEHICLE_NOT_FOUND;
	}
	
	unsigned int price = howMuchMoney(vehicle->typeOfVehicle(), vehicle->wasFined());
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
	Vehicle* res = NULL;

	if (res = handicapped_cars[dud]);
	else if (res = motorbikes[dud]);
	else if (res = private_cars[dud]);
	else {
		return VEHICLE_NOT_FOUND;
	}

	parkingSpot = res->getParkingSpot();
	return SUCCESS;
}


class inspect_filter : UniqueArray<Vehicle, std::equal_to>::Filter {
	
	Time inspection_t;

public:
	
	inspect_filter(Time inspection) {

		inspection_t = inspection;
	}

	virtual bool operator() (const Vehicle& vehicle) const {
		
		return vehicle.inspect(time);
	}
};

inline unsigned int copy_and_inspect(inspect_filter& filter, UniqueArray<Vehicle, std::equal_to>& unique) {

	UniqueArray copy = unique.filter(inspect_filter());
	return copy.getCount();
}

void ParkingLot::inspectParkingLot(Time inspectionTime) {

	unsigned int count = 0;

	Filter filter = inspect_filter(inspectionTime);
	count += copy_and_inspect(filter, motorbikes);
	count += copy_and_inspect(filter, private_cars);
	count += copy_and_inspect(filter, handicapped_cars);

	ParkingLotPrinter::printInspectionResult(std::cout, inspectionTime, count);
}

//our array is sorted, but we're supposed to sort it. idk dude.
class print_filter : UniqueArray<Vehicle, std::equal_to>::filter {

	ostream& os;
	
public:

	print_filter(ostream& ref) {

		os = ref
	}
	virtual bool operator() (const Vehicle& vehicle) const {

		os << vehicle;
		ParkingLotPrinter::printParkingSpot(os, vehicle.getParkingSpot());
		return true;
	}
};

ostream& ParkingLot::operator<<(ostream& os, const ParkingLot& parkingLot) {

	ParkingLotPrinter::printParkingLotTitle(os);

	print_filter mfilter = print_filter(os);
	
	motorbikes.filter(mfilter);
	handicapped_cars.filter(mfilter);
	private_cars.filter(mfilter);
}