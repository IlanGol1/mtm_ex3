#include "ParkingLot.h"


using namespace ParkingLotUtils;

namespace MtmParkingLot {

	
	ParkingLot::ParkingLot(unsigned int parkingBlockSizes[]) :
		motorbikes(parkingBlockSizes[0]),
		handicapped_cars(parkingBlockSizes[1]),
		private_cars(parkingBlockSizes[2]) {
	}

	/**
	 * This function tries to insert a vehicle into unique and initialize its
	 * given spot.
	 * if fails to insert unique.insert throws an exception.
	 *
	 * @param unique This is the parking lot we are trying to park the vehicle.
	 * @param vehicle The vehicle we are trying to park.
	 * @param parkingType The type of car park.
	 */
	inline void entry_attempt(UniqueArray<Vehicle,
	                          equal_to>& unique,
	                          Vehicle vehicle,
	                          VehicleType parkingType) {

		unsigned int i = unique.insert(vehicle);

		ParkingSpot spot = ParkingSpot(parkingType, i);
        UniqueArrayIterator<Vehicle, equal_to> it(unique,i);
        (*it)->setParkingSpot(spot);
		std::cout << vehicle;
		ParkingLotPrinter::printEntrySuccess(std::cout, spot);
	}

	/**
	 * In case the vehicle is already parked,
	 * the function will print its parking spot.
	 *
	 * @param spot The parking spot in which the vehicle is parking.
	 * @return define from ParkinglotTypes which says
	 * he vehicle is already parked
	 */
	inline ParkingResult already_parked(ParkingSpot spot) {

		ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout, spot);
		return VEHICLE_ALREADY_PARKED;
	}

	ParkingResult ParkingLot::enterParking(VehicleType vehicleType,
	                                       LicensePlate licensePlate,
	                                       Time entranceTime) {

		Vehicle vehicle = Vehicle(vehicleType, licensePlate, entranceTime);
		unsigned int index = 0;

		try {
			if (vehicleType == HANDICAPPED) {

                if (handicapped_cars.getIndex(vehicle, index)) {
                    std::cout << *handicapped_cars[vehicle];
                    return already_parked(
                            ParkingSpot(HANDICAPPED, index));
                }

                if (private_cars.getIndex(vehicle, index)) {
                    std::cout<< *private_cars[vehicle];
                    return already_parked(
                            ParkingSpot(CAR, index));
                }

				entry_attempt(handicapped_cars,
				                  vehicle,
				                  HANDICAPPED);
				return SUCCESS;
			}
		}
		// In case the parking lot is full an exception will be thrown
		catch (UniqueArray<Vehicle,
		        equal_to>::UniqueArrayIsFullException& exception) {

			//do nothing because I will have another attempt to
			// put the car in parking for regular vehicles.
		}
		try {
			if (vehicleType == MOTORBIKE) {

                if (motorbikes.getIndex(vehicle, index)){
                    std::cout<< *motorbikes[vehicle];
                    return already_parked(
                            ParkingSpot(MOTORBIKE, index));
                }

				entry_attempt(motorbikes,
				                  vehicle,
				                  MOTORBIKE);
				return SUCCESS;
			}
			else {
                if (vehicleType == CAR) {
                    if (private_cars.getIndex(vehicle, index)) {
                        std::cout << *private_cars[vehicle];
                        return already_parked(ParkingSpot(CAR, index));
                    }
                }
            }

				entry_attempt(private_cars, vehicle, CAR);
				return SUCCESS;
			}
		// In case the parking lot is full an exception will be thrown
		catch (UniqueArray<Vehicle,
		        equal_to>::UniqueArrayIsFullException& exception) {
            std::cout << vehicle;
			ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
			return NO_EMPTY_SPOT;
		}
	}

    /**
     * Returns the minimum number between the two
    */
	inline unsigned int min(unsigned int first, unsigned int second) {

		if (first <= second) return first;
		return second;
	}

	/**
	 * The function calculates how much money a vehicle must pay at the exit,
	 * depending on the type of vehicle.
	 *
	 * @param vehicle
	 * @param exit time of the vehicle from the parking spot.
	 * @return How much money should the car owner pay.
	 */
	unsigned int howMuchMoney(const Vehicle vehicle, Time exit) {

		//I used a map because I don't like using enums like chars or ints.
		// this is totally unnecessary however.
		static std::map<VehicleType, int> take = { {MOTORBIKE, 0},
                                                   {HANDICAPPED, 1},
                                                   {CAR, 2} };
		static int initial_pay[3] = { 10, 15, 20 };
		static int extra_pay[3] = { 5, 0, 10 };

		VehicleType type = vehicle.typeOfVehicle();
		Time::Hour hour = vehicle.timeParking(exit);
		unsigned int sum = 0;

		if (hour > 0) sum += initial_pay[take.at(type)];
		if (hour > 1) sum += extra_pay[take.at(type)] *
		                     (min(hour, 6) - 1);
		if (vehicle.wasFined()) sum += 250;

		return sum;
	}

	ParkingResult ParkingLot::exitParking(LicensePlate licensePlate,
	                                      Time exitTime) {

		Vehicle tmp_vehicle = Vehicle(HANDICAPPED,
		                              licensePlate,
		                              Time());
		const Vehicle* vehicle = NULL;

		UniqueArray<Vehicle, equal_to>* tmp_parking;

		if ((vehicle = motorbikes[tmp_vehicle]) != NULL) {

			tmp_parking = &motorbikes;
		}
		else if ((vehicle = private_cars[tmp_vehicle]) != NULL) {

			tmp_parking = &private_cars;
		}
		else if ((vehicle = handicapped_cars[tmp_vehicle]) != NULL) {

			tmp_parking = &handicapped_cars;
		}
		else {

			ParkingLotPrinter::printExitFailure(std::cout, licensePlate);
			return VEHICLE_NOT_FOUND;
		}

		unsigned int price = howMuchMoney(*vehicle, exitTime);
		std::cout << *vehicle;
		ParkingLotPrinter::printExitSuccess(std::cout,
		                                     vehicle->getParkingSpot(),
		                                     exitTime, price);

		tmp_parking->remove(*vehicle);
		return SUCCESS;
	}

	ParkingResult ParkingLot::getParkingSpot(LicensePlate licensePlate,
	                                         ParkingSpot& parkingSpot) const {

		Vehicle tmp_vehicle = Vehicle(HANDICAPPED,
		                              licensePlate, Time());
		const Vehicle* true_vehicle = NULL;

		if ((true_vehicle = handicapped_cars[tmp_vehicle]) != NULL);
		else if ((true_vehicle = motorbikes[tmp_vehicle]) != NULL);
		else if ((true_vehicle = private_cars[tmp_vehicle]) != NULL);
		else {
			return VEHICLE_NOT_FOUND;
		}

		parkingSpot = true_vehicle->getParkingSpot();
		return SUCCESS;
	}

	/**
	 * function attempts inspecting every vehicle on a given uniquearray by iterating over it.
	 * it also counts how many were fined as a result of the inspection and returns the result.
	 * @param inspection_time
	 * @param unique
	 * @return
	 */
	inline unsigned int inspect(Time inspection_time,
	                            UniqueArray<Vehicle,
	                            equal_to>& unique) {
		unsigned int count = 0;
		for (UniqueArrayIterator<Vehicle, equal_to> it = unique.begin();
		     it != unique.end()  ;
		     ++it) {
            Vehicle * vehicle = *it;
            if (vehicle == NULL){
                continue;
            }
            if (vehicle->inspect(inspection_time)) count++;
		}
		return count;
	}

	void ParkingLot::inspectParkingLot(Time inspectionTime) {

		unsigned int count = 0;

		count += inspect(inspectionTime, motorbikes);
		count += inspect(inspectionTime, private_cars);
		count += inspect(inspectionTime, handicapped_cars);

		ParkingLotPrinter::printInspectionResult(std::cout,
		                                             inspectionTime,
		                                             count);
	}

	/**
	 * this class compares pointers to vehicles. if a pointer is NULL it's always bigger. otherwise it compares according to the'<'
	 * operator in 'ParkingSpot'
	 */
	class CompareVehiclePointers {

		bool less(const Vehicle first, const Vehicle second) const {
			return first.getParkingSpot() < second.getParkingSpot();
		}

	public:
		bool operator() (const Vehicle* first, const Vehicle* second)  const {

			if (second == NULL) return true;
			else if (first == NULL) return false;

			return less(*first, *second);
		};
	};

	/**
	 * the function copies and then sorts a unique array according to the '<' operator in ParkingSpot.
	 * afterwhich it prints the sorted result.
	 * @param os Where to print the list of sorted vehicles.
	 * @param arr the patking lot
	 * @return the printing
	 */
	inline ostream& print(ostream& os,
	                      const UniqueArray<Vehicle,
	                      equal_to>& arr){
		std::vector<Vehicle * > copy;
        for (UniqueArrayIterator<Vehicle,equal_to> it (arr.begin());
             it != arr.end();
             ++it) {
            copy.push_back(*it);
        }

        std::sort(copy.begin(), copy.end(), CompareVehiclePointers());

		for (Vehicle* vehicle : copy) {
			if (vehicle == NULL) break;
			os << (*vehicle);
			ParkingLotPrinter::printParkingSpot(os,
			                                    vehicle->getParkingSpot());
		}
		return os;
	}

	ostream& operator<<(ostream& os, const ParkingLot& parkingLot) {

		ParkingLotPrinter::printParkingLotTitle(os);

		print(os, parkingLot.motorbikes);
        print(os, parkingLot.handicapped_cars);
        print(os, parkingLot.private_cars);

		return os;
	}
}