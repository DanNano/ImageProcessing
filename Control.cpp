#include "Control.h"
using namespace Control;
//Using namespace as after research it appears to solve a couple problems that I was having

//Set the max and min values for the RGB values, which go from 255-0.
const unsigned char global_max = 255;
const unsigned char global_min = 0;

TGA Control::Read(string path) //Read the file from an input source
{
	ifstream file(path, ios_base::binary);

	if (file.is_open())
	{
		TGA::Header head;
		file.read(&head.idLength, sizeof(head.idLength));
		file.read(&head.colorMapType, sizeof(head.colorMapType));
		file.read(&head.dataTypeCode, sizeof(head.dataTypeCode));
		file.read((char*)&head.colorMapOrigin, sizeof(head.colorMapOrigin));
		file.read((char*)&head.colorMapLength, sizeof(head.colorMapLength));
		file.read((char*)&head.colorMapDepth, sizeof(head.colorMapDepth));
		file.read((char*)&head.xOrigin, sizeof(head.xOrigin));
		file.read((char*)&head.yOrigin, sizeof(head.yOrigin));
		file.read((char*)&head.width, sizeof(head.width));
		file.read((char*)&head.height, sizeof(head.height));
		file.read(&head.bitsPerPixel, sizeof(head.bitsPerPixel));
		file.read(&head.imageDescriptor, sizeof(head.imageDescriptor));

		TGA T = TGA(head);

		for (int i = 0; i < (head.height * head.width); i++)
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			file.read((char*)&B, sizeof(B));
			file.read((char*)&G, sizeof(G));
			file.read((char*)&R, sizeof(R));
			Pixel PG = Pixel(R, G, B);
			T.Add(PG);
		}

		file.close();
		return T;
	}

	cout << "Could not load: '" << path << "'. Please try again!" << endl;
	//Will be the main message shown if the input folder isn't properly placed
	return TGA();
}

bool Control::Write(string path, TGA& tga) //Write the file to an output source
{
	ofstream file(path, ios_base::binary);
	if (file.is_open())
	{
		TGA::Header head = tga.GetHeader();
		file.write(&head.idLength, sizeof(head.idLength));
		file.write(&head.colorMapType, sizeof(head.colorMapType));
		file.write(&head.dataTypeCode, sizeof(head.dataTypeCode));
		file.write((char*)&head.colorMapOrigin, sizeof(head.colorMapOrigin));
		file.write((char*)&head.colorMapLength, sizeof(head.colorMapLength));
		file.write((char*)&head.colorMapDepth, sizeof(head.colorMapDepth));
		file.write((char*)&head.xOrigin, sizeof(head.xOrigin));
		file.write((char*)&head.yOrigin, sizeof(head.yOrigin));
		file.write((char*)&head.width, sizeof(head.width));
		file.write((char*)&head.height, sizeof(head.height));
		file.write(&head.bitsPerPixel, sizeof(head.bitsPerPixel));
		file.write(&head.imageDescriptor, sizeof(head.imageDescriptor));

		for (int i = 0; i < tga.GetPixelCount(); i++)
		{
			unsigned char rgb[3];
			Pixel Pix = tga.GetPixel(i);

			for (int j = 0; j < 3; j++)
			{
				rgb[j] = Pix.RGB(j);
			}

			file.write((char*)&rgb[2], sizeof(rgb[2]));
			file.write((char*)&rgb[1], sizeof(rgb[1]));
			file.write((char*)&rgb[0], sizeof(rgb[0]));
		}

		file.close();
		return true;
	}

	return false;
}

void Control::Print(TGA& tga) //Print TGA Header Function
{
	tga.HeaderPrint();
}

float Control::CharChar(unsigned char t, unsigned char ttop, unsigned char tbottom) //Used to alter certain variables
{
	float CChar = ((float)t / (float)(ttop - tbottom));
	return CChar;
}

TGA Control::Multiply(const TGA& ttop, const TGA& tbottom) //Multiply function as used in Task 1
{
	TGA tga = TGA(ttop.GetHeader());

	for (int i = 0; i < ttop.GetPixelCount(); i++)
	{
		Pixel top = ttop.GetPixel(i);
		Pixel bottom = tbottom.GetPixel(i);
		float rgb[6];
		unsigned char newRGB[3];

		for (int j = 0; j < 6; j++)
		{
			if (j < 3)
			{
				rgb[j] = CharChar(top.RGB(j), global_max, global_min);
			}
			else
			{
				rgb[j] = CharChar(bottom.RGB(j - 3), global_max, global_min);
			}
		}

		for (int j = 0; j < 3; j++)
		{
			if (rgb[j] * rgb[j + 3] > 1)
			{
				newRGB[j] = global_max;
			}
			else
			{
				newRGB[j] = (unsigned char)((rgb[j] * rgb[j + 3]) * 255 + 0.5f);
			}
		}

		Pixel Pnew = Pixel(newRGB[0], newRGB[1], newRGB[2]);
		tga.Add(Pnew);
	}

	//Works for the first task, but I'm not sure if it's the cause of the issue with the 3rd task
	return tga;
}

TGA Control::Subtract(const TGA& ttop, const TGA& tbottom) //Subtract function as used in task 2
{
	TGA tga = TGA(ttop.GetHeader());

	for (int i = 0; i < ttop.GetPixelCount(); i++)
	{
		Pixel Top = ttop.GetPixel(i);
		Pixel Bottom = tbottom.GetPixel(i);
		
		unsigned char rgb[6];
		unsigned char otherRGB[3];

		for (int j = 0; j < 6; j++)
		{
			if (j < 3)
			{
				rgb[j] = Top.RGB(j);
			}
			else
			{
				rgb[j] = Bottom.RGB(j - 3);
			}
		}

		for (int j = 0; j < 3; j++)
		{
			if (rgb[j + 3] - rgb[j] < 0)
			{
				otherRGB[j] = global_min;
			}
			else
			{
				otherRGB[j] = (rgb[j + 3] - rgb[j]);
			}
		}

		Pixel PNew = Pixel(otherRGB[0], otherRGB[1], otherRGB[2]);
		tga.Add(PNew);
	}

	return tga;

}

TGA Control::Screen(const TGA& ttop, const TGA& tbottom, const TGA& screener) //Screener Function for 3rd task
{
	TGA otherTGA = Multiply(ttop, tbottom);
	TGA tga = TGA(otherTGA.GetHeader());

	for (int i = 0; i < screener.GetPixelCount(); i++)
	{
		Pixel Top = screener.GetPixel(i);
		Pixel Bottom = screener.GetPixel(i);
		float rgb[6];
		unsigned char newRGB[3];

		for (int j = 0; j < 6; j++)
		{
			if (j < 3)
			{
				rgb[j] = CharChar(Top.RGB(j), global_max, global_min);
			}
			else
			{
				rgb[j] = CharChar(Bottom.RGB(j - 3), global_max, global_min);
			}
		}

		for (int j = 0; j < 3; j++)
		{
			float x = 1 - (1 - rgb[j]) * (1 - rgb[j + 3]);
			if (x > 1)
			{
				x = 1;
			}
			else if (x < 0)
			{
				x = 0;
			}

			newRGB[j] = (unsigned char)(x * 255 + 0.5f);
		}

		Pixel PNew = Pixel(newRGB[0], newRGB[1], newRGB[2]);
		tga.Add(PNew);
	}

	return tga;
	//Unable to get this function to work in main, only task that I'm failing.

}

TGA Control::Overlay(const TGA& ttop, const TGA& tbottom) //Overlay function for 5th task
{
	TGA tga = TGA(ttop.GetHeader());

	for (int i = 0; i < ttop.GetPixelCount(); i++)
	{
		Pixel Top = ttop.GetPixel(i);
		Pixel Bottom = tbottom.GetPixel(i);
		float rgb[6];
		unsigned char newRGB[3];

		for (int j = 0; j < 6; j++)
		{
			if (j < 3)
			{
				rgb[j] = CharChar(Top.RGB(j), global_max, global_min);
			}
			else
			{
				rgb[j] = CharChar(Bottom.RGB(j - 3), global_max, global_min);
			}
		}

		for (int j = 0; j < 3; j++)
		{
			if (rgb[j + 3] <= 0.5)
			{
				float g = 2 * rgb[j] * rgb[j + 3];
				if (g > 1)
				{
					g = 1;
				}
				newRGB[j] = (unsigned char)(g * 255 + 0.5f);
			}
			else
			{
				float g = 1 - 2 * (1 - rgb[j]) * (1 - rgb[j + 3]);
				if (g > 1)
				{
					g = 1;
				}
				else if (g < 0)
				{
					g = 0;
				}
				newRGB[j] = (unsigned char)(g * 255 + 0.5f);
			}
		}

		Pixel PNew = Pixel(newRGB[0], newRGB[1], newRGB[2]);
		tga.Add(PNew);
	}

	return tga;
}

TGA Control::RGB(const TGA& ttop, unsigned char red, unsigned char green, unsigned char blue) //RGB change function for 6th task
{
	TGA tga = TGA(ttop.GetHeader());

	for (int i = 0; i < ttop.GetPixelCount(); i++)
	{
		Pixel top = ttop.GetPixel(i);
		float rgb[3];
		unsigned char newRGB[3];

		for (int j = 0; j < 3; j++)
		{
			rgb[j] = CharChar(top.RGB(j), global_max, global_min);
		}

		float b = rgb[0] + CharChar(red, global_max, global_min);
		if (b > 1)
		{
			b = 1;
		}
		newRGB[0] = (unsigned char)(b * 255 + 0.5f);
		b = rgb[1] + CharChar(green, global_max, global_min);
		if (b > 1)
		{
			b = 1;
		}
		newRGB[1] = (unsigned char)(b * 255 + 0.5f);
		b = rgb[2] + CharChar(blue, global_max, global_min);
		if (b > 1)
		{
			b = 1;
		}
		newRGB[2] = (unsigned char)(b * 255 + 0.5f);

		Pixel PNew = Pixel(newRGB[0], newRGB[1], newRGB[2]);
		tga.Add(PNew);
	}

	return tga;

}

TGA Control::Scale(const TGA& ttop, bool red, float x, bool green, float y, bool blue, float z) //Scale function
{
	TGA tga = TGA(ttop.GetHeader());

	for (int i = 0; i < ttop.GetPixelCount(); i++)
	{
		Pixel top = ttop.GetPixel(i);
		unsigned char rgb[3];
		unsigned char newRGB[3];

		for (int j = 0; j < 3; j++)
		{
			rgb[j] = top.RGB(j);
		}

		if (red == 1)
		{
			if (rgb[0] * x > global_max)
			{
				newRGB[0] = global_max;
			}
			else
			{
				newRGB[0] = (unsigned char)(rgb[0] * x);
			}
		}
		else
		{
			newRGB[0] = rgb[0];
		}

		if (green == 1)
		{
			if (rgb[1] * y > global_max)
			{
				newRGB[1] = global_max;
			}
			else
			{
				newRGB[1] = (unsigned char)(rgb[1] * y);
			}
		}
		else
		{
			newRGB[1] = rgb[1];
		}

		if (blue == 1)
		{
			if (rgb[2] * z > global_max)
			{
				newRGB[2] = global_max;
			}
			else
			{
				newRGB[2] = (unsigned char)(rgb[2] * z);
			}
		}
		else
		{
			newRGB[2] = rgb[2];
		}

		Pixel PNew = Pixel(newRGB[0], newRGB[1], newRGB[2]);
		tga.Add(PNew);
	}

	return tga;
}

TGA Control::Combine(const TGA& red, const TGA& green, const TGA& blue) //Combine function for 9th task
{
	TGA tga = TGA(red.GetHeader());

	for (int i = 0; i < red.GetPixelCount(); i++)
	{
		unsigned char rgb[3];

		rgb[0] = red.GetPixel(i).RGB(0);
		rgb[1] = green.GetPixel(i).RGB(0);
		rgb[2] = blue.GetPixel(i).RGB(0);

		Pixel Pnew = Pixel(rgb[0], rgb[1], rgb[2]);
		tga.Add(Pnew);
	}

	return tga;
} 

TGA Control::Rotate(const TGA& ttop) //Rotate a file function for 10th task
{
	TGA tga = TGA(ttop.GetHeader());

	int i = (ttop.GetHeight() * ttop.GetWidth()) - 1;

	for (i; i > -1; i--)
	{
		Pixel PNew = ttop.GetPixel(i);
		tga.Add(PNew);
	}

	return tga;

}

TGA Control::Quad(const TGA& first, const TGA& second, const TGA& third, const TGA& fourth) //Adds pictures into four quadrants, extra credit function
{
	int QHeights[4] = { first.GetHeight(), second.GetHeight(), third.GetHeight(), fourth.GetHeight() };
	int QWidths[4] = { first.GetWidth(), second.GetWidth(), third.GetWidth(), fourth.GetWidth() };
	TGA::Header H = first.GetHeader();
	H.width = QWidths[0] + QWidths[1];
	H.height = QHeights[0] + QHeights[1];
	TGA tga = TGA(H);

	int firstCount = 0;
	int secondCount = 0;

	for (int i = 0; i < QHeights[0]; i++)
	{
		for (int j = 0, k = 0 + firstCount; j < QWidths[0]; j++)
		{
			Pixel PNew = first.GetPixel(k);
			tga.Add(PNew);
			firstCount++;
			k++;
		}

		for (int j = 0, k = 0 + secondCount; j < QWidths[1]; j++)
		{
			Pixel PNew = second.GetPixel(k);
			tga.Add(PNew);
			secondCount++;
			k++;

		}
	}

	firstCount = 0;
	secondCount = 0;

	for (int i = 0; i < QHeights[2]; i++)
	{
		for (int j = 0, k = 0 + firstCount; j < QWidths[2]; j++)
		{
			Pixel PNew = third.GetPixel(k);
			tga.Add(PNew);
			firstCount++;
			k++;
		}
		
		for (int j = 0, k = 0 + secondCount; j < QWidths[3]; j++)
		{
			Pixel PNew = fourth.GetPixel(k);
			tga.Add(PNew);
			secondCount++;
			k++;
		}
	}

	return tga;


	//Had to move certain variable around as it took a bit of time to get my pictures in the right order
}

vector<TGA> Control::NewRGB(const TGA& ttop) //Vector for new RGBs
{
	vector<TGA> newTGA;
	newTGA.push_back(TGA(ttop.GetHeader()));
	newTGA.push_back(TGA(ttop.GetHeader()));
	newTGA.push_back(TGA(ttop.GetHeader()));

	for (int i = 0; i < ttop.GetPixelCount(); i++)
	{
		Pixel PNew = ttop.GetPixel(i);
		unsigned char newRed = PNew.RGB(0);
		unsigned char newGreen = PNew.RGB(1);
		unsigned char newBlue = PNew.RGB(2);

		Pixel RedPixel = Pixel(newRed, newRed, newRed);
		Pixel GreenPixel = Pixel(newGreen, newGreen, newGreen);
		Pixel BluePixel = Pixel(newBlue, newBlue, newBlue);

		newTGA.at(0).Add(RedPixel);
		newTGA.at(1).Add(GreenPixel);
		newTGA.at(2).Add(BluePixel);


	}

	return newTGA;
}

//Control.cpp file for Project 2 - Where most of the file processes happen. 
//By Daniel Laforce
//Completed 3/24/2022
