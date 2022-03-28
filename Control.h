#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "TGA.h"
using namespace::std;

namespace Control
{

	//---------------------------------------File Functions----------------------------------------//
	TGA Read(string path);
	bool Write(string path, TGA& tga);

	//------------------------------------Basic info functions such as compare and Printing------------------------//
	void Print(TGA& tga);
	float CharChar(unsigned char t, unsigned char ttop, unsigned char tbottom);

	//----------------------------------Functions for TGA creation-----------------------------------//
	TGA Multiply(const TGA& ttop, const TGA& tbottom);
	TGA Subtract(const TGA& ttop, const TGA& tbottom);
	TGA Screen(const TGA& ttop, const TGA& tbottom, const TGA& S);
	TGA Overlay(const TGA& ttop, const TGA& tbottom);
	TGA RGB(const TGA& ttop, unsigned char red, unsigned char green, unsigned char blue);
	TGA Scale(const TGA& ttop, bool red, float x, bool green, float y, bool blue, float z);
	TGA Combine(const TGA& red, const TGA& green, const TGA& blue);
	TGA Rotate(const TGA& ttop);
	TGA Quad(const TGA& first, const TGA& second, const TGA& third, const TGA& fourth);

	//-------------------------------Vector functions-----------------------------//
	vector<TGA> NewRGB(const TGA& ttop);

};

//Control.h file for Project 2 - Control is what will actually move/make the files
//By Daniel Laforce
//Changed this to a namespace from a class, modifying it like this(with other changes) seems to have fixed errors in Control.cpp
//Completed 3/24/2022
