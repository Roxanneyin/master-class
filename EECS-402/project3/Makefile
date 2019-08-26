project3.exe: project3.o ColorClass.o RowColumnClass.o ColorImageClass.o StegaClass.o constants.h isEven.o inFileValid.o
	g++ project3.o ColorClass.o RowColumnClass.o ColorImageClass.o StegaClass.o isEven.o inFileValid.o -o project3.exe

project3.o: project3.cpp constants.h
	g++ -c project3.cpp -o project3.o

ColorClass.o: ColorClass.cpp ColorClass.h constants.h
	g++ -c ColorClass.cpp -o ColorClass.o

RowColumnClass.o: RowColumnClass.cpp RowColumnClass.h constants.h
	g++ -c RowColumnClass.cpp -o RowColumnClass.o

ColorImageClass.o: ColorImageClass.cpp ColorImageClass.h constants.h
	g++ -c ColorImageClass.cpp -o ColorImageClass.o

StegaClass.o: StegaClass.cpp StegaClass.h constants.h
	g++ -c StegaClass.cpp -o StegaClass.o

isEven.o: isEven.cpp isEven.h constants.h
	g++ -c isEven.cpp -o isEven.o

inFileValid.o: inFileValid.cpp inFileValid.h constants.h
	g++ -c inFileValid.cpp -o inFileValid.o

clean:
	rm -rf project3.exe project3.o ColorClass.o RowColumnClass.o ColorImageClass.o StegaClass.o isEven.o inFileValid.o

