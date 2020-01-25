#ifndef Vehicle_H

#define Vehicle_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingLotPrinter.h"

using namespace ParkingLotUtils;
using std::ostream;
/**
 * This is the class that holds all of our vehicle's information and performs
 * all the required actions and a number of actions.
 * to alleviate certain requirements.
 */
class Vehicle {
    /**
     * This is the information that we receive in the income of a vehicle,
     * as well as the location where the vehicle is parked,
     * and information if it enters.
     */
	VehicleType type;
	LicensePlate plate;
	Time entrance;
	ParkingSpot spot;
	bool was_fined;

public:

    /**
     * This is the function of the inspector,
     * if the inspector arrived gives a report to the vehicle if necessary.
     * @param inspection_time The time the inspector arrived.
     * @return Value to whether the inspector gave report (true) or not (false).
     */
	bool inspect(Time inspection_time);

    /**
     * The builder of the vehicle that puts the type of vehicle,
     * license plate and time of entry into their places.
     * @param type of the vehicle.
     * @param plate of the vehicle.
     * @param entrance of the vehicle.
     */
	Vehicle(VehicleType type, LicensePlate plate, Time entrance);

	/**
	 * It's a copy constructor.
	 * @param other This is the vehicle we copy.
	 */
	Vehicle(const Vehicle& other);

	/**
	 * @return the type of vehicle.
	 */
	VehicleType typeOfVehicle() const;

	/**
	 * Given current time, returns how much hours the vehicle parked.
	 * @param exit_time current time.
	 * @return much hours the vehicle parked.
	 */
	Time::Hour timeParking(Time exit_time) const;

    /**
     * Put our vehicle in where it is parked.
     * @param parkingSpot.
     */
	void setParkingSpot(ParkingSpot& parkings_spot);

	/**
	 * @return where is the vehicle parked.
	 */
	ParkingSpot getParkingSpot() const;

    /**
     * @return whether the vehicle received a report.
     */
	bool wasFined() const;

	/**
	 * Overrides the action "==" to match vehicles.
	 * @param vehicleA.
	 * @param vehicleB.
	 * @return boolean value if the vehicles have the same plate.
	 */
	friend bool operator==(const Vehicle& vehicleA, const Vehicle& vehicleB);

	/**
	 * Performs vehicle printing as required.
	 * @param os where to print.
	 * @param are vehicle.
	 * @return where to print.
	 */
	friend ostream& operator<<(ostream& os, const Vehicle& vehicle);

private:
    /**
     * If there is a report, do nothing (returns false).
     * Otherwise gives a report (and returns true).
     */
	bool fine();
};

#endif