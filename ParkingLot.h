#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "Vehicle.h"
#include "UniqueArray.h"
#include <map>
#include <algorithm>
#include <functional>
#include <vector>


using namespace ParkingLotUtils;
using std::ostream;
typedef std::equal_to<Vehicle> equal_to;

namespace MtmParkingLot {

	class ParkingLot {
	public:
        /**
         * We hold 3 different UniqueArray parking spaces,
         * for each vehicle type
         */
		UniqueArray<Vehicle, equal_to> motorbikes; 
		UniqueArray<Vehicle, equal_to> handicapped_cars;
		UniqueArray<Vehicle, equal_to> private_cars;
		
		ParkingLot(unsigned int parkingBlockSizes[]);

		~ParkingLot() = default;

		ParkingResult enterParking(VehicleType vehicleType,
		                           LicensePlate licensePlate,
		                           Time entranceTime);

		ParkingResult exitParking(LicensePlate licensePlate,
		                          Time exitTime);

		ParkingResult getParkingSpot(LicensePlate licensePlate,
		                             ParkingSpot& parkingSpot) const;

		void inspectParkingLot(Time inspectionTime);

		friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);
	};
}
#endif //MTMPARKINGLOT_PARKINGLOT_H
