#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

// #include <stdint.h>
#include <iostream>
#include<vector>
#include "../EncFile.hpp"

// Test constructor
BOOST_AUTO_TEST_CASE(EncFilecontructor) {
    //  normal constructor
    //  should throw exceptions when loading files (no other exceptions)
    BOOST_REQUIRE_NO_THROW(EncFile("somefile.txt",text,"somepassword","otherfile.txt"));
    BOOST_REQUIRE_THROW(EncFile("somefile.png",image,"somepassword","otherfile.png"),std::runtime_error);
    BOOST_REQUIRE_THROW(EncFile("somefile.jpeg",image,"somepassword","otherfile.jpeg"),std::runtime_error);
    BOOST_REQUIRE_THROW(EncFile("somefile.jpg",image,"somepassword","otherfile.jpg"),std::runtime_error);

    //  should throw invalid argument exception
    BOOST_REQUIRE_THROW(EncFile("somefile.txt",none,"somepassword","otherfile.txt"), std::invalid_argument);
    //BOOST_REQUIRE_THROWEncFile("somefile.txt",other,"somepassword","otherfile.txt"), std::invalid_argument);
}


/*BOOST_AUTO_TEST_CASE(EncFileloadImage) {
	// check if attempting to load image 
	// from non existing file raises an exception
	EncFile file("non-existant.png",image,"password","output.png");
	BOOST_REQUIRE_THROW(file.softEncrypt(),std::runtime_error);
}*/
