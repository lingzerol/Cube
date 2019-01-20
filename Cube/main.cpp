// Cube.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp> 
#include <chrono>
#include "Model.h"
Geometric_transformation gt;
void Init(std::vector<Plane>& temp, double x, double y, double z) {
	temp.push_back(Plane(red0, 4, Red));
	temp.push_back(Plane(red1, 4, Red));
	temp.push_back(Plane(red2, 4, Red));
	temp.push_back(Plane(red3, 4, Red));
	temp.push_back(Plane(red4, 4, Red));
	temp.push_back(Plane(red5, 4, Red));
	temp.push_back(Plane(red6, 4, Red));
	temp.push_back(Plane(red7, 4, Red));
	temp.push_back(Plane(red8, 4, Red));


	temp.push_back(Plane(orange0, 4, Orange));
	temp.push_back(Plane(orange1, 4, Orange));
	temp.push_back(Plane(orange2, 4, Orange));
	temp.push_back(Plane(orange3, 4, Orange));
	temp.push_back(Plane(orange4, 4, Orange));
	temp.push_back(Plane(orange5, 4, Orange));
	temp.push_back(Plane(orange6, 4, Orange));
	temp.push_back(Plane(orange7, 4, Orange));
	temp.push_back(Plane(orange8, 4, Orange));

	temp.push_back(Plane(blue0, 4, Blue));
	temp.push_back(Plane(blue1, 4, Blue));
	temp.push_back(Plane(blue2, 4, Blue));
	temp.push_back(Plane(blue3, 4, Blue));
	temp.push_back(Plane(blue4, 4, Blue));
	temp.push_back(Plane(blue5, 4, Blue));
	temp.push_back(Plane(blue6, 4, Blue));
	temp.push_back(Plane(blue7, 4, Blue));
	temp.push_back(Plane(blue8, 4, Blue));

	temp.push_back(Plane(green0, 4, Green));
	temp.push_back(Plane(green1, 4, Green));
	temp.push_back(Plane(green2, 4, Green));
	temp.push_back(Plane(green3, 4, Green));
	temp.push_back(Plane(green4, 4, Green));
	temp.push_back(Plane(green5, 4, Green));
	temp.push_back(Plane(green6, 4, Green));
	temp.push_back(Plane(green7, 4, Green));
	temp.push_back(Plane(green8, 4, Green));

	temp.push_back(Plane(yellow0, 4, Yellow));
	temp.push_back(Plane(yellow1, 4, Yellow));
	temp.push_back(Plane(yellow2, 4, Yellow));
	temp.push_back(Plane(yellow3, 4, Yellow));
	temp.push_back(Plane(yellow4, 4, Yellow));
	temp.push_back(Plane(yellow5, 4, Yellow));
	temp.push_back(Plane(yellow6, 4, Yellow));
	temp.push_back(Plane(yellow7, 4, Yellow));
	temp.push_back(Plane(yellow8, 4, Yellow));

	temp.push_back(Plane(white0, 4, White));
	temp.push_back(Plane(white1, 4, White));
	temp.push_back(Plane(white2, 4, White));
	temp.push_back(Plane(white3, 4, White));
	temp.push_back(Plane(white4, 4, White));
	temp.push_back(Plane(white5, 4, White));
	temp.push_back(Plane(white6, 4, White));
	temp.push_back(Plane(white7, 4, White));
	temp.push_back(Plane(white8, 4, White));
	
	gt.zoom(temp, 0.05);
	//gt.translation(temp, 50, 10, 0);
	gt.rotate(temp,1, x);
	gt.rotate(temp, 0, y);
	gt.rotate(temp, 2, z);
}
extern Cube cube;
int main()
{

	int instruction;

	while (std::cin >> instruction) {
		cube.add_message(instruction);
	}
	cube.add_message(QUIT);
}

