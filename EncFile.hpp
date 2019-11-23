#include "LFSR/LFSR.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include<fstream>
#include<iostream>
#include<sstream>
enum filetype{image, sound, text, none};
class EncFile{
   public:
	EncFile(std::string filename, filetype f, std::string password, std::string outfile);
	void softEncrypt();  // encrypt infile
	void writeFile();  // save encrypted file
	
   private:
	std::string _filename;
	filetype _f;
	std::string _password;
	std::string _outfile;
	std::unique_ptr<LFSR> lin_feed;
	sf::Image _image;
	sf::Image _outimage;
	sf::Vector2u _imsize;
	std::string _intext;
	std::string _outtext;
	void writeImage();
	void writeText();
	void loadImage();
	void loadText();
	void softEncryptImage();
	void softEncryptText();

};
