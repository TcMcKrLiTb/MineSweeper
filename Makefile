MineSweeper : MineSweeper.o Gaming.o Themap.o Minerc.o
	g++ Gaming.o Themap.o MineSweeper.o  Minerc.o -o MineSweeper.exe -municode -lgdi32 -static-libgcc
	
MineSweeper.o : MineSweeper\MineSweeper.cpp
	g++ -c "MineSweeper\MineSweeper.cpp" -o MineSweeper.o
	
Gaming.o : MineSweeper\Gaming.cpp
	g++ -c "MineSweeper\Gaming.cpp" -o  Gaming.o
	
Themap.o : MineSweeper\Themap.cpp
	g++ -c "MineSweeper\Themap.cpp" -o  Themap.o
	
Minerc.o : MineSweeper\MineSweeper.rc
	windres -i "MineSweeper\MineSweeper.rc" -o Minerc.o
	
.PHONY : clean
clean:
	rm.exe -f *.o MineSweeper.exe