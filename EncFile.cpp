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
	_imsize=_image.getSize();
	_outimage.create(_imsize.x, _imsize.y, sf::Color::White);
}  // end constructor


// load image from file
void EncFile::loadImage(){
	if (!_image.loadFromFile(_filename))
		throw std::runtime_error("could not load image from file");
}//  end loadImage

void EncFile::softEncrypt(){
	sf::Color p;
	for (unsigned int i = 0; i<_imsize.x; i++) {
		for (unsigned int j = 0; j<_imsize.y; j++) {
			p = _image.getPixel(i, j);
			p.r = p.r^lin_feed->generate(32);
			p.g = p.g^lin_feed->generate(32);
			p.b = p.b^lin_feed->generate(32);
			_outimage.setPixel(i, j, p);
		}
	}
}
