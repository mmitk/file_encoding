#include "LFSR/LFSR.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
enum filetype{image, sound, text};
class EncFile{
   public:
	explicit EncFile(std::string filename, filetype f, std::string password, std::string outfile);
	void softEncrypt();
	
   private:
	std::string _filename;
	filetype _f;
	std::string _password;
	std::string _outfile;
	std::unique_ptr<LFSR> lin_feed;
	sf::Image _image;

	void loadImage();

};
