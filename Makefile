CC = g++
CFLAGS = -std=c++11 -c -g -Og -Wall -Werror -pedantic
OBJ = LFSR.o bit_flags.o main.o
DEPS = LFSR/LFSR.hpp LFSR/bit_flags.hpp 
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
EXE = softEncrypt 

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<
	
LFSR.o: LFSR/LFSR.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

bit_flags.o: LFSR/bit_flags.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<
clean:
	rm $(OBJ) $(EXE) 
