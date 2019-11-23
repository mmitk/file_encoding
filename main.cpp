

// g++ PhotoMagic.o LFSR.o bit_flags.o -o encrypt -lsfml-graphics -lsfml-window -lsfml-system

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream> 
#include <map>
#include <bitset>
#include <algorithm>
#include<iterator>
#include "EncFile.hpp"

void split(const std::string& str,std::vector<std::string>& cont, char delim = ' ');
filetype findFileType(std::string ext);
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
	
	// create vector of tokens
	// to extract filetype
	std::vector<std::string> tokens;
	std::string input = argv[1];//set name of input file
	std::string output = argv[2];//set name of output file
	
	split(input, tokens, '.');
	string ext = tokens.back();
	filetype ftype;
	ftype=findFileType(ext);


	EncFile file(input,ftype,password,output);
	file.softEncrypt();
	try{
		file.writeFile();
	}
	catch(std::runtime_error e){
		cout<<e.what()<<endl;
	}
	return 0;
}


// function to split string
// works similar to (no default delimeter) string.split() in python
void split(const std::string& str,std::vector<std::string>& cont, char delim)
{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        cont.push_back(token);
    }
}

filetype findFileType(std::string ext){
	if(ext == "jpg"||ext=="jpeg"||ext=="png"||ext=="pdf")
		return filetype::image;
	else if(ext=="txt")
		return filetype::text;
	else
		throw std::runtime_error("invalid file extension");
	return none;
	
} 
