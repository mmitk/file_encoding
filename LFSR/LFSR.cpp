#include<stdio.h>
#include "LFSR.hpp"

//constructor
LFSR::LFSR(string _seed, int t):tap(t){
   if(t>int(_seed.length()))
	throw std::runtime_error("Tap Out Of Bounds Error");
   if(_seed.length()>32)
	throw std::runtime_error("seed Out Of Bounds Error");
   
   this->seed=new Bit_flags(_seed.length());
   int index = 0;
   //initialize the this->seed member variable to reflect the passed string seed
   for(int i = _seed.length(); i>0;--i){
	/*if(_seed[i]!='1'&&_seed[i]!='0'&&i<int(_seed.length())){
	   throw std::runtime_error("Invalid Seed Exception");
	   break;
	}*/
	//if seed[i] is one add 1 to bitflags
       if(_seed[i]=='1'){
            this->seed->set_flag(index);
       }
       index +=1;
   }

}

//destructor
LFSR::~LFSR(){
	this->seed->~Bit_flags();
}


int LFSR::step(){
    //representations of bits at position 8 and 10, and new bit
    unsigned int l_bit;
    unsigned int _tap;
    unsigned int new_bit;
    l_bit = (unsigned int) this->seed->check_flag(this->seed->get_size()-1);
    if(tap>=8){
        _tap = (unsigned int) this->seed->check_flag(this->tap);}
    else{
         _tap = (unsigned int) this->seed->check_flag(this->tap-1);
    }
    new_bit = l_bit^_tap;
    this->seed->shift_left(1);
    if(new_bit==1)
        this->seed->set_flag(1);
    //this->print();
    //cout<<" ";
    return new_bit;
}

void LFSR::print(){
    int counter = 0;

    for(int i = this->seed->get_size();i>0;--i){
        cout<<this->seed->check_flag(i-1);
		    /*if ((counter+1) % 4 == 0) {
			    cout<<" ";
		    }
		    if ((counter + 1) % 32 == 0) {
			    cout<<endl;
		    }*/
            ++counter;
    }
}

int LFSR::generate(int k){
    int bit_tracker=0;
    for(int i =0; i<k;++i){
        bit_tracker *=2;
        bit_tracker+=this->step();
        //cout<<bit_tracker<<endl;
    }
    return bit_tracker;
}




