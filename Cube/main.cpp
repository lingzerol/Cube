// Cube.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp> 
#include <chrono>
#include "Cube.h"
#include "Magic_Cube.h"

extern Magic_Cube mc;
int main()
{

	int instruction;

	//mc.restore();
	//mc.add_message(TURN_L);
	//mc.add_message(TURN_R);
	while (std::cin >> instruction&&instruction!=0) {
		mc.disorder();
		mc.restore();
		//mc.add_message(instruction);
	}
	mc.add_message(QUIT);
}

