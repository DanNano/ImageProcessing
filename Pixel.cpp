#include "Pixel.h"
#include <iostream>
#include <vector>
#include <string>
using namespace::std;

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b) //Constructor for this class
{
	red = r;
	green = g;
	blue = b;
}

const unsigned char Pixel::RGB(int rgb) const //RGB Function for this class
{
	if (rgb == 0)
	{
		return red;
	}

	if (rgb == 1)
	{
		return green;
	}

	if (rgb == 2)
	{
		return blue;
	}
	
	return 0;
}

//Pixel.cpp file used in Project 2
//by Daniel Laforce
//Completed 3/24/2022