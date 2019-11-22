

// g++ PhotoMagic.o LFSR.o bit_flags.o -o encrypt -lsfml-graphics -lsfml-window -lsfml-system

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream> 
#include <map>
#include <bitset>
#include "LFSR/LFSR.hpp"


int main(int argc, char** argv)
{
	int tap;
	std::string seed;
	//if a password argument was given (only 4 arguments)
	//sum integer value of every element in password
	//convert to string representation of binary value
	//and initialize lfsr with this seedand default tap of 2
	if(argc==4){
		std::string password = argv[3];
		int sum = 0;
		tap = 12;
		for(const char &c: password){

			sum+=int(c);
		}
		seed=std::bitset<8>(sum).to_string();
		seed = seed + seed;
		
	}
	//else initialize tap and seed as given tap and seed
	else{
		stringstream s_to_int(argv[4]);//converting tap to int value
		s_to_int>>tap;  //set tap
		seed = argv[3];//set seed
	}

	//initialize LFSR with given seed and tap
	LFSR lfsr(seed, tap);
	
	std::string input = argv[1];//set name of input file
	std::string output = argv[2];//set name of output file
	
	//declaring size and pixel variables
	sf::Vector2u size;
	sf::Color p;
	
	//declaring variables for input image, input texture, and input sprite
	sf::Image inImage;
	sf::Texture inTexture;
	sf::Sprite inSprite;

	//declaring variables for output image, output texture, and output sprite
	sf::Image outImage;
	sf::Texture outTexture;
	sf::Sprite outSprite;
	
	//load image from input file into variable for input image
	if (!inImage.loadFromFile(input))
		return -1;
	//set size of image
	size = inImage.getSize();
	
	std::string title = input + "\t\t\t\t\t\t\t\t" +output;
	//initialize window
	sf::RenderWindow window(sf::VideoMode(size.x*2, size.y), title);
	//create empty image to represent output image
	outImage.create(size.x, size.y, sf::Color::White);
	
	//load input image into sprite
	inTexture.loadFromImage(inImage);
	inSprite.setTexture(inTexture);
	inSprite.setPosition(0, 0);

	
	//For each pixel from input image, XOR with generated integer
	//and set corresponding pixel of output image
	for (unsigned int i = 0; i<size.x; i++) {
		for (unsigned int j = 0; j<size.y; j++) {
			p = inImage.getPixel(i, j);
			p.r = p.r^lfsr.generate(32);
			p.g = p.g^lfsr.generate(32);
			p.b = p.b^lfsr.generate(32);
			outImage.setPixel(i, j, p);
		}
	}
	
	
	//loud output image into sprite
	outTexture.loadFromImage(outImage);
	outSprite.setTexture(outTexture);
	outSprite.setPosition(size.x,0);

	//display window (and sprites)
	/*while (window.isOpen()) {
 		sf::Event event;
 		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
 				window.close();
 		}
 		
 		window.clear();
 		window.draw(inSprite);
		window.draw(outSprite);
 		window.display();
 		
 	}
	
	//write XOR'd image to output filename
	if (!outImage.saveToFile(output))
		return -1;*/
	return 0;
}
