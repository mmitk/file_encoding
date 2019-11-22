#include "bit_flags.hpp"
//constructor (initialized with capacity of 32) initializes array of bits (0)
Bit_flags::Bit_flags() {
	this->size = 32;
	this->capacity = 0;
	while (this->capacity <= 32)
	{
		this->capacity = this->capacity + 32;
	}
	this->index = this->capacity / 32;


    this->data = new unsigned int[this->index];

	for (int i = 0; i < this->index; i++) {
		this->data[i] = 0;
	}

}

//non-default constructor initializes array of bits (0) with a given size
Bit_flags::Bit_flags(int num_bits) {
	this->size = num_bits;
	this->capacity = 0;
	while (this->capacity <= num_bits)
	{
		this->capacity = this->capacity + 32;
	}
	this->index = this->capacity / 32;


    this->data = new unsigned int[this->index];

	for (int i = 0; i <= this->index; i++) {
		this->data[i] = 0;
	}

}

Bit_flags::Bit_flags(const Bit_flags &b, bool flip){
    this->size = b.size;
    this->capacity=b.capacity;
    this->index = b.index;
    this-> data = new unsigned int[this->index];
    for(int i = 0; i <= this->index;++i){
        if(flip){
            this->data[i]=~b.data[i];
        }
        else{
            this->data[i]=b.data[i];
            }
        
    }
    cout<<"copy constructor called"<<endl;
}

//destructor
Bit_flags::~Bit_flags() {

   delete[] this->data;
    
}

//sets bit(flag) at specified position to 1
void Bit_flags::set_flag(int flag_position){
    flag_position = flag_position - 1;

	if (flag_position >= this->capacity) {
		while (this->capacity <= flag_position)
		{
			this->capacity = this->capacity + 32;
		}//end while loop
		this->index = this->capacity / 32;
		unsigned int* temp_int = new unsigned int[this->index];
		int x = 0;
		for (int i=x; i <= this->size / 32; i++) {
			temp_int[i] = this->data[i];
			++x;
		}//end for loop

		for (int i=x; i < this->index; i++) {
			temp_int[i] = 0;
		}
        delete [] this->data;
		this->data = temp_int;
		this->size = flag_position + 1;
	}//end else if

	unsigned int temp = 1;
	int fposition = flag_position % 32;
	int index = flag_position / 32;
	//int size = sizeof(flag_holder) / (sizeof(unsigned int)));
	temp = temp << fposition;
	this->data[index] = this->data[index] | temp;
	//return SUCCESS;
}


void Bit_flags::unset_flag(int flag_position){
    flag_position = flag_position - 1;
	
	if (flag_position >= this->capacity) {
		
        //TODO add allocation of additional memory
        return;
	}
    else if (flag_position >= this->size) {
		//this->size = flag_position + 1;
        return;
	}

	//unsigned int temp;
	//int fposition = (flag_position + 1) % 32;
	//int index = (flag_position + 1) / 32;


    Bit_flags temp_bflags(*this, true);


	//flags all remaining positions in temp except for at the flag_position
	for (int i = 0; i < this->size; i++) {
		if (!this->check_flag(i) && i != flag_position + 1) {
			temp_bflags.set_flag(i);
		}
	}
	
	for (int i = 0; i < (this->capacity) / 32; i++) {
		if (flag_position / 32 == i)
		{
			this->data[i] = this->data[i] & temp_bflags.get_data(i);
		}
	}
    temp_bflags.~Bit_flags();
}

int Bit_flags::check_flag(int flag_position){
    unsigned int *tempnum = this->data;
	unsigned int temp;
	int fposition = flag_position % 32;
	int index = flag_position / 32;
	temp = 0;
	if(flag_position>=8)
		tempnum = tempnum + index;
	temp = *tempnum | temp;
	temp = temp >> fposition;
	temp = temp & 1;
	return temp;
}
void Bit_flags::shift_left(int num_shifts){
    for(int i = 0; i<this->index; ++i){
        this->data[i]=this->data[i]<<num_shifts;
    }

}

