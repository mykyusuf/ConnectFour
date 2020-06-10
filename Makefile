all: myk

myk:
	g++ -c ConnectFour.cpp -std=c++11 -o ConnectFour.o
	g++ -c main.cpp -std=c++11 -o main.o
	g++ -c ConnectFourPlus.cpp -std=c++11 -o ConnectFourPlus.o
	g++ -c ConnectFourDiag.cpp -std=c++11 -o ConnectFourDiag.o
	g++ -c ConnectFourUndo.cpp -std=c++11 -o ConnectFourUndo.o
	g++ ConnectFour.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourUndo.o main.o -o exe
	./exe
clean:
	rm *.o