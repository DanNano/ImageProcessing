#pragma once
#include <vector>
using namespace::std;

class Pixel //For RGB values
{
private:
	//Sets up unsigned chars for each color type
	unsigned char red;
	unsigned char green;
	unsigned char blue;

public:
	Pixel(unsigned char r, unsigned char g, unsigned char b); //Main function used from this class
	const unsigned char RGB(int rgb) const;
};


//Pixel.h file used for Project 2
//by Daniel Laforce
//Completed 3/24/2022
