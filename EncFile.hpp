#include "LFSR/LFSR.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
enum filetype{image, sound, text};
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

	void loadImage();
	void softEncryptImage();

};
