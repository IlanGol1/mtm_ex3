FLAGS = -std=c++11 -Wall -Werror -pedantic-errors –DNDEBUG

MtmFilesH = Time.h ParkingLotPrinter.h ParkingSpot.h ParkingLotTypes.h
MtmFilesO = Time.o ParkingLotPrinter.o ParkingSpot.o 

MtmParkingLot: MtmParkingLot.o ParkingLot.o Vehicle.o $(MtmFilesO)
	g++ $(FLAGS) -o MtmParkingLot MtmParkingLot.o ParkingLot.o Vehicle.o $(MtmFilesO)

ParkingLot.o: ParkingLot.cpp ParkingLot.h $(MtmFilesH) UniqueArray.h UniqueArrayImp.h
	g++ $(FLAGS) -c ParkingLot.cpp

Vehicle.o: Vehicle.cpp Vehicle.h $(MtmFilesH)
	g++ $(FLAGS) -c Vehicle.cpp

Time.o: Time.cpp Time.h
	g++ $(FLAGS) -c Time.cpp

ParkingSpot.o: ParkingSpot.cpp ParkingSpot.h ParkingLotTypes.h
	g++ $(FLAGS) -c ParkingSpot.cpp

ParkingLotPrinter.o: ParkingLotPrinter.cpp ParkingLotPrinter.h ParkingSpot.h
	g++ $(FLAGS) -c ParkingLotPrinter.cpp

clean:
	$(RM) *.o *~

