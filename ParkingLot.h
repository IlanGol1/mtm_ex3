#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "Vehicle.h"
#include "UniqueArray.h"

using namespace ParkingLotUtils;
using std::ostream;

namespace MtmParkingLot {

	class ParkingLot {
	public:

		UniqueArray<Vehicle> motorbikes;
		UniqueArray<Vehicle> private_cars;
		UniqueArray<Vehicle> handicapped_cars;

		ParkingLot(unsigned int parkingBlockSizes[]);
		~ParkingLot();
		ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
		ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
		ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
		void inspectParkingLot(Time inspectionTime);
		friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);

	};
}
#endif //MTMPARKINGLOT_PARKINGLOT_H
