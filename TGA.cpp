#include "TGA.h"
#include <string>
#include <iostream>
#include <vector>
using namespace::std;

TGA::TGA() //Defalut constructor when the image is not found, partial information
{
	header.idLength = 0;
	width = 0;
	height = 0;
}

TGA::TGA(Header x) //Constructor
{
	header = x;
	width = x.width;
	height = x.height;
}

//TGA::~TGA() //Destructor
//{
	//Created in case it's needed
//}

void TGA::HeaderPrint() //Print the header information, such as the sample from the file.
{
	cout << header.idLength << " ";
	cout << header.colorMapType << " ";
	cout << header.dataTypeCode << " ";
	cout << header.colorMapOrigin << " ";
	cout << header.colorMapLength << " ";
	cout << header.colorMapDepth << " ";
	cout << header.yOrigin << " ";
	cout << header.xOrigin << " ";
	cout << header.width << " ";
	cout << header.height << " ";
	cout << header.bitsPerPixel << " ";
	cout << header.imageDescriptor << " ";
	cout << "    Pixels: " << GetPixelCount() << endl;
}

const TGA::Header TGA::GetHeader() const //Get the Header header object, const version
{
	return header;
}

TGA::Header TGA::GetHeader() //Get the Header header object, non-const version
{
	return header;
}

const Pixel TGA::GetPixel(int x) const //Get a pixel at location, const version
{
	return Pics.at(x);
}

Pixel TGA::GetPixel(int x) //Get a pixel at location , non-const version
{
	return Pics.at(x);
}

const int TGA::GetPixelCount() const //Get the size of the vector Pixel Pic, const version
{
	return Pics.size();
}

int TGA::GetPixelCount() //Get the size of the vector Pixel Pic, non-const version
{
	return Pics.size();
}

const short TGA::GetWidth() const //Get the width from the header.
{
	return width;
}

const short TGA::GetHeight() const //Get the height from the header
{
	return height;
}

void TGA::Add(Pixel& RGB) //Add to the Pic vector
{
	Pics.push_back(RGB);
}


//TGA.cpp file for Project 2
//Where the main information about the .tga files are kept and used in other functions
//By Daniel Laforce
//Completed 3/24/2022
