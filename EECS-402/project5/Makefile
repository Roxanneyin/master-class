project5.exe: project5.o random.o EventClass.o SimulationClass.o
	g++ project5.o random.o EventClass.o SimulationClass.o -o project5.exe

project5.o: project5.cpp random.h SimulationClass.h constants.h
	g++ -c project5.cpp -o project5.o

random.o: random.cpp random.h
	g++ -c random.cpp -o random.o

SimulationClass.o: SimulationClass.h SimulationClass.cpp SortedListClass.h FIFOQueueClass.h random.h EventClass.h constants.h
	g++ -c SimulationClass.cpp -o SimulationClass.o

EventClass.o: EventClass.h EventClass.cpp
	g++ -c EventClass.cpp -o EventClass.o

clean:
	rm -rf project5.exe project5.o random.o SimulationClass.o EventClass.o
