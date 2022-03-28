#pragma once
#include <vector>
#include "Pixel.h"
using namespace::std;

class TGA
{

public:
	struct Header //Header struct as first seen in the pdf file for project
	{
		char idLength;
		char colorMapType;
		char dataTypeCode;
		short colorMapOrigin;
		short colorMapLength;
		char colorMapDepth;
		short xOrigin;
		short yOrigin;
		short width;
		short height;
		char bitsPerPixel;
		char imageDescriptor;
	};


	//---------------------------------------------------Constructors----------------------------//
	TGA();
	TGA(Header x);
	//~TGA();

	//-------------------------------------Get Functions-------------------------------//
	void HeaderPrint();
	const Header GetHeader() const;
	Header GetHeader();
	const Pixel GetPixel(int x) const;
	Pixel GetPixel(int x);
	const int GetPixelCount() const;
	int GetPixelCount();
	const short GetWidth() const;
	const short GetHeight() const;


	//---------------------------------Set Function---------------------------//
	void Add(Pixel& RGB);

private:
	Header header;
	short width;
	short height;
	vector<Pixel> Pics;
};

//TGA.h file for Project 2
//File used to store informatin about the .tga files, mainly the header
//By Daniel Laforce
//Completed 3/24/2022
