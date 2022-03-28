#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Control.h"
#include "TGA.h"
#include "Pixel.h"
using namespace::std;
using namespace::Control;

int main()
{
	
	cout << "Starting Project 2 Image Editor: Thank you for starting!" << endl;

	//------------------------------------------------------1st Task---------------------------------------------//
	TGA TaskOneTop = Read("input/layer1.tga");
	TGA TaskOneBottom = Read("input/pattern1.tga");

	TGA TaskOne = Multiply(TaskOneTop, TaskOneBottom);
	Write("output/part1.tga", TaskOne);

	cout << "Task One: Done" << endl;

	//----------------------------------------------------2nd Task----------------------------//

	TGA TaskTwoTop = Read("input/layer2.tga");
	TGA TaskTwoBottom = Read("input/car.tga");

	TGA TaskTwo = Subtract(TaskTwoTop, TaskTwoBottom);
	Write("output/part2.tga", TaskTwo);

	cout << "Task Two: Done" << endl;

	//---------------------------------------------------3rd Task-----------------------------------//
	TGA TaskThreeTop = Read("input/layer1.tga");
	TGA TaskThreeBottom = Read("input/pattern2.tga");
	TGA TaskThreeScreen = Read("input/text.tga");

	TGA TaskThree = Screen(TaskThreeTop, TaskThreeBottom, TaskThreeScreen);
	Write("output/part3.tga", TaskThree);

	cout << "Task Three: ";
	cout << "Error! Unable to fix" << endl;
	//Unable to solve error, no matter how many times I study my code. 


	//----------------------------------------4th Task-------------------------------//
	TGA TaskFourTop = Read("input/layer2.tga");
	TGA TaskFourBottom = Read("input/circles.tga");
	TGA TaskFourWork = Read("input/pattern2.tga");

	TGA Task4Temp = Multiply(TaskFourTop, TaskFourBottom);
	TGA TaskFour = Subtract(TaskFourWork, Task4Temp);
	Write("output/part4.tga", TaskFour);

	cout << "Task Four: Done" << endl;


	//---------------------------------------------5th Task---------------------------//
	TGA TaskFiveTop = Read("input/layer1.tga");
	TGA TaskFiveBottom = Read("input/pattern1.tga");

	TGA TaskFive = Overlay(TaskFiveTop, TaskFiveBottom);
	Write("output/part5.tga", TaskFive);

	cout << "Task Five: Done" << endl;


	//--------------------------------------------6th Task-----------------------------//
	TGA TaskSixTop = Read("input/car.tga");

	TGA TaskSix = RGB(TaskSixTop, 0, 200, 0);
	Write("output/part6.tga", TaskSix);

	cout << "Task Six: Done" << endl;


	//--------------------------------------7th Task----------------------------------//
	TGA TaskSevenTop = Read("input/car.tga");

	TGA TaskSeven = Scale(TaskSevenTop, true, 4.0, false, 0.0, true, 0.0);
	Write("output/part7.tga", TaskSeven);

	cout << "Task Seven: Done" << endl;


	//-------------------------------------8th Task-----------------------------------//
	TGA TaskEightTop = Read("input/car.tga");

	vector<TGA> TaskEight = NewRGB(TaskEightTop);
	Write("output/part8_r.tga", TaskEight.at(0));
	Write("output/part8_g.tga", TaskEight.at(1));
	Write("output/part8_b.tga", TaskEight.at(2));

	cout << "Task Eight: Done" << endl;


	//---------------------------------------9th Task----------------------------------//
	TGA TaskNineRed = Read("input/layer_red.tga");
	TGA TaskNineGreen = Read("input/layer_green.tga");
	TGA TaskNineBlue = Read("input/layer_blue.tga");

	TGA TaskNine = Combine(TaskNineRed, TaskNineGreen, TaskNineBlue);
	Write("output/part9.tga", TaskNine);

	cout << "Task Nine: Done" << endl;


	//-------------------------------------10th Task-------------------------------------//
	TGA TaskTenTop = Read("input/text2.tga");

	TGA TaskTen = Rotate(TaskTenTop);
	Write("output/part10.tga", TaskTen);

	cout << "Task Ten: Done" << endl;


	//----------------------------------Extra Credit Task--------------------------------//
	TGA BL = Read("input/text.tga");
	TGA BR = Read("input/pattern1.tga");
	TGA TR = Read("input/circles.tga");
	TGA TL = Read("input/car.tga");

	TGA TaskEC = Quad(BL, BR, TL, TR);
	Write("output/extracredit.tga", TaskEC);

	cout << "Extra Credit Task: Done" << endl;

	//Had to move the variables around to get the desired outcome. 



	//------------------------------------------Closing Program------------------------------------------//
	cout << "All Tasks Completed. Initiating Computer Self-Destruct sequence" << endl;

	return 0;
}

//Main.cpp file for Project 2
//By Daniel Laforce
//All Task Plus the Extra Credit
//One Task(3) continues to fail, I gave up on it. 
//Completed 3/24/2022
