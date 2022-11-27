# Project: Project2
# Makefile created by Dev-C++ 5.11

CPP      = g++.exe 
CC       = gcc.exe
WINDRES  = windres.exe
RES      = Project2_private.res
OBJ      = Gaming.o MineSweeper.o Themap.o $(RES)
LINKOBJ  = Gaming.o MineSweeper.o Themap.o $(RES)
LIBS     = -static-libgcc -municode -mwindows -g3
INCS     = 
CXXINCS  = 
BIN      = Project2.exe
CXXFLAGS = $(CXXINCS)
CFLAGS   = $(INCS)
RM       = rm.exe -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)

Gaming.o: Gaming.cpp
	$(CPP) -c Gaming.cpp -o Gaming.o $(CXXFLAGS)

MineSweeper.o: MineSweeper.cpp
	$(CPP) -c MineSweeper.cpp -o MineSweeper.o $(CXXFLAGS)

Themap.o: Themap.cpp
	$(CPP) -c Themap.cpp -o Themap.o $(CXXFLAGS)

Project2_private.res: Project2_private.rc MineSweeper.rc
	$(WINDRES) -i Project2_private.rc --input-format=rc -o Project2_private.res -O coff 
	
.PHONY : clean
clean:
	rm.exe -f *.o *.exe

