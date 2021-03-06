// Cube.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp> 
#include <chrono>
#include "Cube.h"
#include "Magic_Cube.h"
extern Magic_Cube mc;
std::mutex mc_mtx;

int main()
{

	unsigned instruction;
	//mc.restore();
	//mc.add_message(TURN_L);
	//mc.add_message(TURN_R);
	while (std::cin >> instruction&&instruction!=0) {
		std::unique_lock<std::mutex> lck(mc_mtx);
		if (DISORDER == instruction) {
			mc.disorder();
		}
		else if (RESTORE == instruction) {
			mc.restore();
		}
		else
		{
			mc.add_message(instruction);
		}
	}
	mc.add_message(QUIT);
}

