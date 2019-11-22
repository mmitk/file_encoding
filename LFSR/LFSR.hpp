#include <string>
#include "bit_flags.hpp"
using namespace std;
class LFSR {
    public:
	LFSR(){this->seed = new Bit_flags;}
        LFSR(string _seed, int t); // constructor to create LFSR with
                                // the given initial seed and tap
        //destructor
       ~LFSR();
        int step(); // simulate one step and return the
                    // new bit as 0 or 1
        int generate(int k); // simulate k steps and return
                             // k-bit integer
        void print();
        int get_size(){return this->seed->get_size();}
        int get_last_flag(){return this->seed->check_flag(this->seed->get_size()-1);}
        int get_tap(){return this->seed->check_flag(tap);}
    private:
	//seed is kept as a bit flags object (implementation in bit_flags.cpp, interface in bit_flags.hpp)
	//an object that stores an array of bits up to a designated length
        Bit_flags* seed;
        int tap;

};
