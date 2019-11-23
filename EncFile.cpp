#include "EncFile.hpp"
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
			break;
		case sound: break;
		case text: 
			loadText();
			break;
		case none: throw std::runtime_error("invalid filetype");
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
	_imsize=_image.getSize();
	_outimage.create(_imsize.x, _imsize.y, sf::Color::White);
}//  end loadImage

void EncFile::softEncrypt(){
	// choose correct private function to use
	// to encrypt file based on filetype
	cout<<_f<<endl;
	switch(_f){
		case image:
			softEncryptImage();
			break;
		case sound: 
			break;
		case text: softEncryptText();
			break;
		default: break;
	}  // end switch
}

// encrypt image
void EncFile::softEncryptImage(){
	//use LFSR to scramble each pixel value of image
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

void EncFile::softEncryptText(){
	cout<<"encrypting......"<<endl;
	std::ostringstream fullstr;
	for(const char &c: _intext){
			//int newVal = c;
			int newVal = c ^ lin_feed->generate(32);
			char newc = (char)newVal;
			fullstr<<newc;

		}
	cout<<"instring: "<<_intext<<endl;
	cout<<"outtext: "<<_outtext<<endl;
	_outtext=fullstr.str();
}

void EncFile::writeFile(){
	// choose correct private function to use
	// to write file based on filetype
	switch(_f){
		case image:
			writeImage();
			break;
		case sound: break;
		case text:writeText();
			 break;
		default: break;
	}  // end switch
}

void EncFile::writeText(){
	ofstream outfile;
	outfile.open(_outfile);
	outfile<<_outtext;
	outfile.close();
}

void EncFile::writeImage(){
	if (!_outimage.saveToFile(_outfile))
		throw std::runtime_error("could not write encrypted image to file");
}

void EncFile::loadText(){
	std::ostringstream fullstr;
	string str;
	ifstream infile;
	infile.open (_filename);
        while(true) 
        {
	        if(!getline(infile,str)) // Saves the line in str
			break;
		else
			fullstr<<str<<endl;
        }
	//cout<<fullstr.str();
	infile.close();
	_intext= fullstr.str();
}
