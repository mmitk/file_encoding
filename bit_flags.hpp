#ifndef BIT_FLAGS_CPP
#define BIT_FLAGS_CPP
#include <iostream>
using namespace std;
class Bit_flags {
    public:
        //constructors
        Bit_flags();
        Bit_flags(int num_bits);
        Bit_flags(const Bit_flags &b, bool flip);

        //destructor
        ~Bit_flags(){delete data;}

        //bit flags functions
        void set_flag(int flag_position);
        void unset_flag(int flag_position);
        int check_flag(int flag_position);
        void shift_left(int num_shifts);

        //accessors
        unsigned int get_data(int _index){return this->data[_index];}
        int get_size(){return this->size;}
        int get_capacity(){return this->capacity;}

    private:
	    int size;
	    int capacity;
	    int index;
	    //an integer of bits is kept within an array of unsigned integers
	    //pointer to array is stored as member variable, memory is allocated in constructor
	    unsigned int* data;
};

#endif
