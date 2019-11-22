#include "EncObj.hpp"
#include<stdexcept>
#include<exception>
#include <iostream>
#include <bitset>

EncFile::EncFile(std::string filename, filetype f,std::string password, std::string outfile):_filename(filename),_f(f), _password(password),_outfile(outfile){
	// call appropriate function
	// to load file based on filetype
	switch(f){
		case image:
			try{
				loadImage();
			}
			catch(std::runtime_error& e){
				std::cout<<e.what()<<std::endl;
			}
		case sound: break;
		case text: break;
		default: break;
	}  // end switch
	// initialize LFSR with password
	int sum = 0;
	int tap = 12;
	std::string seed;
	for(const char &c: password){
		sum+=int(c);
	}
	seed=std::bitset<8>(sum).to_string();
	seed = seed + seed;
	lin_feed = std::make_unique<LFSR>(seed,tap);
}  // end constructor


// load image from file
void EncFile::loadImage(){
	if (!_image.loadFromFile(_filename))
		throw std::runtime_error("could not load image from file");
}//  end loadImage
