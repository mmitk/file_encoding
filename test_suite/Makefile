CC = g++
CFLAGS = -std=c++14 -c -g -Og -Wall -Werror -pedantic
OBJ = LFSR.o bit_flags.o EncFile.o test.o
DEPS = ../LFSR/LFSR.hpp ../LFSR/bit_flags.hpp ../EncFile.hpp
LIBS = -lboost_unit_test_framework -lsfml-graphics -lsfml-window -lsfml-system
EXE = encr_test_suite 

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

EncFile.o: ../EncFile.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<
	
LFSR.o: ../LFSR/LFSR.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

bit_flags.o: ../LFSR/bit_flags.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<
test.o: test.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<
clean:
	rm $(OBJ) $(EXE) 
