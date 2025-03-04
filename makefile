FLAGS=-g -std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG
MtmFilesH=Time.h ParkingLotPrinter.h ParkingSpot.h ParkingLotTypes.h
MtmFilesO=Time.o ParkingLotPrinter.o ParkingSpot.o
UniqueArrayFiles=UniqueArray.h UniqueArrayImp.h UniqueArrayIterator.h UniqueArrayIteratorImp.h

MtmParkingLot: MtmParkingLot.o ParkingLot.o Vehicle.o $(MtmFilesO)
	g++ $(FLAGS) -o MtmParkingLot MtmParkingLot.o ParkingLot.o Vehicle.o $(MtmFilesO)

UniqueArray: tests/UniqueArrayTest.cpp $(UniqueArrayFiles)
	g++ $(FLAGS) -o UniqueArray tests/UniqueArrayTest.cpp

MtmParkingLot.o: MtmParkingLot.cpp $(MtmFilesH)
	g++ $(FLAGS) -c MtmParkingLot.cpp

ParkingLot.o: ParkingLot.cpp ParkingLot.h $(MtmFilesH) $(UniqueArrayFiles)
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

