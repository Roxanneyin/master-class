project4.exe: project4.o LinkedNodeClass.o SortedListClass.o FIFOQueueClass.o LIFOStackClass.o
	g++ project4.o LinkedNodeClass.o SortedListClass.o FIFOQueueClass.o LIFOStackClass.o -o project4.exe

project4.o: project4.cpp
	g++ -c project4.cpp -o project4.o

LinkedNodeClass.o: LinkedNodeClass.h LinkedNodeClass.cpp
	g++ -c LinkedNodeClass.cpp -o LinkedNodeClass.o

SortedListClass.o: SortedListClass.h SortedListClass.cpp
	g++ -c SortedListClass.cpp -o SortedListClass.o

FIFOQueueClass.o: FIFOQueueClass.h FIFOQueueClass.cpp
	g++ -c FIFOQueueClass.cpp -o FIFOQueueClass.o

LIFOStackClass.o: LIFOStackClass.h LIFOStackClass.cpp
	g++ -c LIFOStackClass.cpp -o LIFOStackClass.o

clean:
	rm -rf project4.exe project4.o LinkedNodeClass.o SortedListClass.o FIFOQueueClass.o LIFOStackClass.o
