

// g++ PhotoMagic.o LFSR.o bit_flags.o -o encrypt -lsfml-graphics -lsfml-window -lsfml-system

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream> 
#include <map>
#include <bitset>
#include "EncFile.hpp"


int main(int argc, char** argv)
{
	std::string password;
	//if a password argument was given (only 4 arguments)
	//sum integer value of every element in password
	//convert to string representation of binary value
	//and initialize lfsr with this seedand default tap of 2
	if(argc==4){
		password = argv[3];	
	}
	//else initialize tap and seed as given tap and seed
	else{
		cout<<"Correct Format: ./Encrypt infile outfile password"<<endl;
		return -1;
	}

	
	std::string input = argv[1];//set name of input file
	std::string output = argv[2];//set name of output file
	
	EncFile file(input,image,password,output);
	file.softEncrypt();
	try{
		file.writeFile();
	}
	catch(std::runtime_error e){
		cout<<e.what()<<endl;
	}
	return 0;
}
