#include "pch.h"
#include "Magic_Cube.h"
#include <fstream>
Magic_Cube mc;// Magic_Cube include Cube

void Magic_Cube::disorder() {
	std::unique_lock<std::mutex> lck(cube.finish_mtx);
	const int times = 1000;
	unsigned instruction = 1;
	srand((unsigned)time(NULL));
	for (int i = 0; i < times; ++i) {
		int j = rand() % (instru_num-6);
		add_message(instruction << j);
	}
	cube.finish_modify.wait(lck);
}
void Magic_Cube::restore() {
	std::unique_lock<std::mutex> lck(cube.finish_mtx);
	// restore the cross of white plane 
	if (White != cube[5][7] || Red != cube[0][1]) {
		white_cross(Red);
	}// restore the white plane with red arris
	cube_turn();
	cube.finish_modify.wait(lck);
 	if (White != cube[5][7] || Green != cube[0][1]) {
		white_cross(Green);
	}// restore the white plane with green arris
	cube_turn();
	cube.finish_modify.wait(lck);
	if (White != cube[5][7] || Orange != cube[0][1]) {
		white_cross(Orange);
	}// restore the white plane with orange arris
	cube_turn();
	cube.finish_modify.wait(lck);
	if (White != cube[5][7] || Blue != cube[0][1]) {
		white_cross(Blue);
	}// restore the white plane with blue arris
	cube_turn();
	cube.finish_modify.wait(lck);
	// restore the corner block of white plane
	if (Red != cube[0][2] || Green != cube[2][0]||White!=cube[5][8]) {
		white_corner_block(Red, Green);
	}
	cube_turn();
	cube.finish_modify.wait(lck);
	if (Green != cube[0][2] || Orange != cube[2][0] || White != cube[5][8]) {
		white_corner_block(Green,Orange);
	}
	cube_turn();
	cube.finish_modify.wait(lck);
	if (Orange != cube[0][2] || Blue != cube[2][0] || White != cube[5][8]) {
		white_corner_block(Orange, Blue);
	}
	cube_turn();
	cube.finish_modify.wait(lck);
	if (Blue != cube[0][2] || Red != cube[2][0] || White != cube[5][8]) {
		white_corner_block(Blue, Red);
	}
	cube_turn();
	cube.finish_modify.wait(lck);
	// restore the middle arris
	if (Red != cube[0][5] || Green != cube[2][3]) {
		middle_arris(Red, Green);
	}
	cube_turn();
	cube.finish_modify.wait(lck);
	if (Green != cube[0][5] || Orange != cube[2][3]) {
		middle_arris(Green, Orange);
	}
	cube_turn();
	cube.finish_modify.wait(lck);
	if (Orange != cube[0][5] || Blue != cube[2][3]) {
		middle_arris(Orange,Blue);
	}
	cube_turn();
	cube.finish_modify.wait(lck);
	if (Blue != cube[0][5] || Red != cube[2][3]) {
		middle_arris(Blue, Red);
	}
	cube_turn();
	cube.finish_modify.wait(lck);


	// restore the upper plane
	if (!check_yellow_plane()) {
		bool result=yellow_plane();
		if (!result) {
			bool flag = false;
			if (this->yellow_plane_line())
				//this->yellow_plane_line();
				flag = true;
			else if (this->yellow_plane_rightangle())
				//this->yellow_plane_rightangle();
				flag = true;
			else if (this->yellow_plane_center())
				//this->yellow_plane_center();
				flag = true;
			cube.finish_modify.wait(lck);
			this->yellow_plane();
		}
	}
	cube.finish_modify.wait(lck);

	// restore the upper edge block 
	int num = 0;
	while (!upper_edge_is_ok()&&num<10) {
		upper_edge_block();
		cube.finish_modify.wait(lck);
		++num;
	}
}

void Magic_Cube::add_message(unsigned instruction, int zv, double *rv, int*tv) {
	cube.add_message(instruction, zv, rv, tv);
}

void Magic_Cube::white_cross(const COLOR color) {
	if (White == cube[5][1] && color == cube[1][1]) {
		cube.add_message(TURN_B);
		cube.add_message(TURN_B);
		cube.add_message(TURN_U);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		//std::cout << "1" << std::endl;
	}
	else if (White == cube[5][3] && color == cube[3][1]) {
		cube.add_message(TURN_L);
		cube.add_message(TURN_L);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		//std::cout << "2" << std::endl;
	}
	else if (White == cube[5][5] && color == cube[2][1]) {
		cube.add_message(TURN_R);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		//std::cout << "3" << std::endl;
	}
	else if (color == cube[5][1] && White == cube[1][1]) {
		cube.add_message(TURN_B);
		cube.add_message(TURN_B);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_R);
		//std::cout << "4" << std::endl;
	}
	else if (color == cube[5][3] && White == cube[3][1]) {
		cube.add_message(TURN_LN);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_L);
		//std::cout << "5" << std::endl;
	}
	else if (color == cube[5][5] && White == cube[2][1]) {
		cube.add_message(TURN_R);
		cube.add_message(TURN_F);
		cube.add_message(TURN_RN);
		//std::cout << "6" << std::endl;
	}
	else if (color == cube[5][7] && White == cube[0][1]) {
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_L);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_LN);
		//std::cout << "7" << std::endl;
	}
	else if (White == cube[0][5] && color == cube[2][3]) {
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		//std::cout << "8" << std::endl;
	}
	else if (color == cube[0][5] && White == cube[2][3]) {
		cube.add_message(TURN_F);
		//std::cout << "9" << std::endl;
	}
	else if (White == cube[0][3] && color == cube[3][5]) {
		cube.add_message(TURN_LN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_L);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		//std::cout << "10" << std::endl;
	}
	else if (color == cube[0][3] && White == cube[3][5]) {
		cube.add_message(TURN_FN);
		//std::cout << "11" << std::endl;
	}
	else if (White == cube[1][3] && color == cube[2][5]) {
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		//std::cout << "12" << std::endl;
	}
	else if (color == cube[1][3] && White == cube[2][5]) {
		cube.add_message(TURN_RN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_R);
		cube.add_message(TURN_R);
		//std::cout << "13" << std::endl;
	}
	else if (White == cube[1][5] && color == cube[3][3]) {
		cube.add_message(TURN_L);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_LN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		//std::cout << "14" << std::endl;
	}
	else if (color == cube[1][5] && White == cube[3][3]) {
		cube.add_message(TURN_L);
		cube.add_message(TURN_L);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_LN);
		cube.add_message(TURN_LN);
		//std::cout << "15" << std::endl;
	}
	else if (White == cube[0][7] && color == cube[4][1]) {
		cube.add_message(TURN_U);
		cube.add_message(TURN_L);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_LN);
		//std::cout << "16" << std::endl;
	}
	else if (color == cube[0][7] && White == cube[4][1]) {
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		//std::cout << "17" << std::endl;
	}
	else if (White == cube[1][7] && color == cube[4][7]) {
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_R);
		//std::cout << "18" << std::endl;
	}
	else if (color == cube[1][7] && White == cube[4][7]) {
		cube.add_message(TURN_U);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		//std::cout << "19" << std::endl;
	}
	else if (White == cube[2][7] && color == cube[4][5]) {
		cube.add_message(TURN_RN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_R);
		//std::cout << "20" << std::endl;
	}
	else if (color == cube[2][7] && White == cube[4][5]) {
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		//std::cout << "21" << std::endl;
	}
	else if (White == cube[3][7] && color == cube[4][3]) {
		cube.add_message(TURN_L);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_LN);
		//std::cout << "22" << std::endl;
	}
	else if (color == cube[3][7] && White == cube[4][3]) {
		cube.add_message(TURN_UN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		//std::cout << "23" << std::endl;
	}
}

void Magic_Cube::white_corner_block(const COLOR l,const COLOR r) {
	if (r == cube[0][2] && White == cube[2][0] && l == cube[5][8]) {
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
		add_message(TURN_UN);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
		//std::cout << "1" << std::endl;
	}
	else if (White == cube[0][2] && l == cube[2][0] && r == cube[5][8]) {
		add_message(TURN_FN);
		add_message(TURN_UN);
		add_message(TURN_F);
		add_message(TURN_U);
		add_message(TURN_U);
		add_message(TURN_R);
		add_message(TURN_UN);
		add_message(TURN_RN);
		//std::cout << "2" << std::endl;
	}
	else if (l == cube[0][0] && White == cube[3][2] && r == cube[5][6]) {
		add_message(TURN_R);
		add_message(TURN_LN);
		add_message(TURN_UN);
		add_message(TURN_L);
		add_message(TURN_RN);
		//std::cout << "3" << std::endl;
	}
	else if (White == cube[0][0] && r == cube[3][2] && l == cube[5][6]) {
		add_message(TURN_F);
		add_message(TURN_UN);
		add_message(TURN_UN);
		add_message(TURN_FN);
		add_message(TURN_U);
		add_message(TURN_F);
		//std::cout << "4" << std::endl;
	}
	else if (r == cube[0][0] && l == cube[3][2] && White == cube[5][6]) {
		add_message(TURN_F);
		add_message(TURN_U);
		add_message(TURN_FN);
		add_message(TURN_R);
		add_message(TURN_UN);
		add_message(TURN_UN);
		add_message(TURN_RN);
		//std::cout << "5" << std::endl;
	}
	else if (r == cube[1][2] && White == cube[3][0] && l == cube[5][0]) {
		add_message(TURN_L);
		add_message(TURN_U);
		add_message(TURN_LN);
		add_message(TURN_U);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
		//std::cout << "6" << std::endl;
	}
	else if (White == cube[1][2] && l == cube[3][0] && r == cube[5][0]) {
		add_message(TURN_BN);
		add_message(TURN_UN);
		add_message(TURN_B);
		add_message(TURN_R);
		add_message(TURN_UN);
		add_message(TURN_RN);
		//std::cout << "7" << std::endl;
	}
	else if (l == cube[1][2] && r == cube[3][0] && White == cube[5][0]) {
		add_message(TURN_BN);
		add_message(TURN_UN);
		add_message(TURN_UN);
		add_message(TURN_B);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
		//std::cout << "8" << std::endl;
	}
	else if (l == cube[1][0] && White == cube[2][2] && r == cube[5][2]) {
		add_message(TURN_RN);
		add_message(TURN_U);
		add_message(TURN_U);
		add_message(TURN_R);
		add_message(TURN_R);
		add_message(TURN_UN);
		add_message(TURN_RN);
		//std::cout << "9" << std::endl;
	}
	else if (White == cube[1][0] && r == cube[2][2] && l == cube[5][2]) {
		add_message(TURN_B);
		add_message(TURN_U);
		add_message(TURN_BN);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
		//std::cout << "10" << std::endl;
	}
	else if (r == cube[1][0] && l == cube[2][2] && White == cube[5][2]) {
		add_message(TURN_B);
		add_message(TURN_U);
		add_message(TURN_U);
		add_message(TURN_BN);
		add_message(TURN_R);
		add_message(TURN_UN);
		add_message(TURN_RN);
		//std::cout << "11" << std::endl;
	}
	else if (l == cube[0][8] && White == cube[2][6] && r == cube[4][2]) {
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
		//std::cout << "12" << std::endl;
	}
	else if (White == cube[0][8] && r == cube[2][6] && l == cube[4][2]) {
		add_message(TURN_U);
		add_message(TURN_R);
		add_message(TURN_UN);
		add_message(TURN_RN);
		//std::cout << "13" << std::endl;
	}
	else if (r == cube[0][8] && l == cube[2][6] && White == cube[4][2]) {
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_U);
		add_message(TURN_RN);
		add_message(TURN_UN);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
		//std::cout << "14" << std::endl;
	}
	else if (r == cube[0][6] && White == cube[3][8] && l == cube[4][0]) {
		add_message(TURN_R);
		add_message(TURN_UN);
		add_message(TURN_RN);
		//std::cout << "15" << std::endl;
	}
	else if (White == cube[0][6] && l == cube[3][8] && r == cube[4][0]) {
		add_message(TURN_UN);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
		//std::cout << "16" << std::endl;
	}
	else if (l == cube[0][6] && r == cube[3][8] && White == cube[4][0]) {
		add_message(TURN_UN);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_U);
		add_message(TURN_RN);
		add_message(TURN_UN);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
		//std::cout << "17" << std::endl;
	}
	else if (l == cube[1][8] && White == cube[3][6] && r == cube[4][6]) {
		add_message(TURN_UN);
		add_message(TURN_UN);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
		//std::cout << "18" << std::endl;
	}
	else if (White == cube[1][8] && r == cube[3][6] && l == cube[4][6]) {
		add_message(TURN_R);
		add_message(TURN_UN);
		add_message(TURN_UN);
		add_message(TURN_RN);
		//std::cout << "19" << std::endl;
	}
	else if (r == cube[1][8] && l == cube[3][6] && White == cube[4][6]) {
		add_message(TURN_UN);
		add_message(TURN_UN);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_U);
		add_message(TURN_RN);
		add_message(TURN_UN);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
		//std::cout << "20" << std::endl;
	}
	else if (r == cube[1][6] && White == cube[2][8] && l == cube[4][8]) {
		add_message(TURN_U);
		add_message(TURN_U);
		add_message(TURN_R);
		add_message(TURN_UN);
		add_message(TURN_RN);
		//std::cout << "21" << std::endl;
	}
	else if (White == cube[1][6] && l == cube[2][8] && r == cube[4][8]) {
		add_message(TURN_U);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
		//std::cout << "22" << std::endl;
	}
	else if (l == cube[1][6] && r == cube[2][8] && White == cube[4][8]) {
		add_message(TURN_U);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_U);
		add_message(TURN_RN);
		add_message(TURN_UN);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
		//std::cout << "23" << std::endl;
	}
}

void Magic_Cube::middle_arris(const COLOR l,const COLOR r) {
	if (r == cube[0][5] && l == cube[2][3]) {
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);

		cube.add_message(TURN_UN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		//std::cout << "1"<<std::endl;
	}
	else if (r == cube[0][3] && l == cube[3][5]) {
		cube.add_message(TURN_FN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);

		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		//std::cout << "2" << std::endl;
	}
	else if (l == cube[0][3] && r == cube[3][5]) {
		cube.add_message(TURN_FN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);

		cube.add_message(TURN_U);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		//std::cout << "3" << std::endl;
	}
	else if (r == cube[1][5] && l == cube[3][3]) {
		cube.add_message(TURN_LN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_LN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_LN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_L);
		cube.add_message(TURN_U);
		cube.add_message(TURN_L);

		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		//std::cout << "4" << std::endl;
	}
	else if (l == cube[1][5] && r == cube[3][3]) {
		cube.add_message(TURN_LN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_LN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_LN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_L);
		cube.add_message(TURN_U);
		cube.add_message(TURN_L);

		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		//std::cout << "5" << std::endl;
	}
	else if (r == cube[1][3] && l == cube[2][5]) {
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);

		cube.add_message(TURN_UN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		//std::cout << "6" << std::endl;
	}
	else if (l == cube[1][3] && r == cube[2][5]) {
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);

		cube.add_message(TURN_U);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		//std::cout << "7" << std::endl;
	}
	else if (r == cube[0][7] && l == cube[4][1]) {
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		//std::cout << "8" << std::endl;
	}
	else if (r == cube[3][7] && l == cube[4][3]) {
		cube.add_message(TURN_UN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		//std::cout << "9" << std::endl;
	}
	else if (r == cube[1][7] && l == cube[4][7]) {
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		//std::cout << "10" << std::endl;
	}
	else if (r == cube[2][7] && l == cube[4][5]) {
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		//std::cout << "11" << std::endl;
	}
	else if (l == cube[0][7] && r == cube[4][1]) {
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		//std::cout << "12" << std::endl;
	}
	else if (l == cube[3][7] && r == cube[4][3]) {
		cube.add_message(TURN_UN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		//std::cout << "13" << std::endl;
	}
	else if (l == cube[1][7] && r == cube[4][7]) {
		cube.add_message(TURN_U);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		//std::cout << "14" << std::endl;
	}
	else if (l == cube[2][7] && r == cube[4][5]) {
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		//std::cout << "15" << std::endl;
	}
}

bool Magic_Cube::yellow_plane() {

	bool yellow[9];
	bool edge[4][3];

	
	yellow[6] = true; yellow[7] = true; yellow[8] = false;
	yellow[3] = true; yellow[4] = true; yellow[5] = true;
	yellow[0] = true; yellow[1] = true; yellow[2] = false;

	edge[0][0] = false; edge[0][1] = false; edge[0][2] = false;
	edge[1][0] = false; edge[1][1] = false; edge[1][2] = false;
	edge[2][0] = true; edge[2][1] = false; edge[2][2] = true;
	edge[3][0] = false; edge[3][1] = false; edge[3][2] = false;

	/*
	== |
	===
	== |
	*/

	if (is_type(yellow, edge)) {
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		return true;
	}

	/*
	| = |
	 ===
	 ===
	*/

	yellow[6] = false; yellow[7] = true; yellow[8] = false;
	yellow[3] = true; yellow[4] = true; yellow[5] = true;
	yellow[0] = true; yellow[1] = true; yellow[2] = true;

	edge[0][0] = false; edge[0][1] = false; edge[0][2] = false;
	edge[1][0] = false; edge[1][1] = false; edge[1][2] = false;
	edge[2][0] = false; edge[2][1] = false; edge[2][2] = true;
	edge[3][0] = true; edge[3][1] = false; edge[3][2] = false;

	if (is_type(yellow, edge)) {
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		return true;
	}


	/*
	- -
	 = 
	===
	 = 
	_ _
	*/

	yellow[6] = false; yellow[7] = true; yellow[8] = false;
	yellow[3] = true; yellow[4] = true; yellow[5] = true;
	yellow[0] = false; yellow[1] = true; yellow[2] = false;

	edge[0][0] = true; edge[0][1] = false; edge[0][2] = true;
	edge[1][0] = true; edge[1][1] = false; edge[1][2] = true;
	edge[2][0] = false; edge[2][1] = false; edge[2][2] = false;
	edge[3][0] = false; edge[3][1] = false; edge[3][2] = false;

	if (is_type(yellow, edge)) {
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		return true;
	}

	/*
	- -
	 =
	===
   | = |
	*/

	yellow[6] = false; yellow[7] = true; yellow[8] = false;
	yellow[3] = true; yellow[4] = true; yellow[5] = true;
	yellow[0] = false; yellow[1] = true; yellow[2] = false;

	edge[0][0] = false; edge[0][1] = false; edge[0][2] = false;
	edge[1][0] = true; edge[1][1] = false; edge[1][2] = true;
	edge[2][0] = true; edge[2][1] = false; edge[2][2] = false;
	edge[3][0] = false; edge[3][1] = false; edge[3][2] = true;

	if (is_type(yellow, edge)) {
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		return true;
	}

	/*
	_
	 ==
	===
	== |
	*/
	yellow[6] = false; yellow[7] = true; yellow[8] = true;
	yellow[3] = true; yellow[4] = true; yellow[5] = true;
	yellow[0] = true; yellow[1] = true; yellow[2] = false;

	edge[0][0] = false; edge[0][1] = false; edge[0][2] = false;
	edge[1][0] = false; edge[1][1] = false; edge[1][2] = true;
	edge[2][0] = true; edge[2][1] = false; edge[2][2] = false;
	edge[3][0] = false; edge[3][1] = false; edge[3][2] = false;


	if (is_type(yellow, edge)) {
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		return true;

	}

	/*
	| ==
	 ===
	  = |
	 -
	*/

	yellow[6] = false; yellow[7] = true; yellow[8] = true;
	yellow[3] = true; yellow[4] = true; yellow[5] = true;
	yellow[0] = false; yellow[1] = true; yellow[2] = false;

	edge[0][0] = true; edge[0][1] = false; edge[0][2] = false;
	edge[1][0] = false; edge[1][1] = false; edge[1][2] = false;
	edge[2][0] = true; edge[2][1] = false; edge[2][2] = false;
	edge[3][0] = true; edge[3][1] = false; edge[3][2] = false;

	if (is_type(yellow, edge)) {
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_R);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_RN);
		return true;
	}

	/*
	 -
	  = |
	 ===
	| ==
	*/

	yellow[6] = false; yellow[7] = true; yellow[8] = false;
	yellow[3] = true; yellow[4] = true; yellow[5] = true;
	yellow[0] = false; yellow[1] = true; yellow[2] = true;

	edge[0][0] = false; edge[0][1] = false; edge[0][2] = false;
	edge[1][0] = false; edge[1][1] = false; edge[1][2] = true;
	edge[2][0] = false; edge[2][1] = false; edge[2][2] = true;
	edge[3][0] = false; edge[3][1] = false; edge[3][2] = true;

	if (is_type(yellow, edge)) {
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		return true;
	}

	return false;

}

bool Magic_Cube::check_yellow_plane() {
	if (Yellow != cube[4][0] ||
		Yellow != cube[4][1] ||
		Yellow != cube[4][2] ||
		Yellow != cube[4][3] ||
		Yellow != cube[4][4] ||
		Yellow != cube[4][5] ||
		Yellow != cube[4][6] ||
		Yellow != cube[4][7] ||
		Yellow != cube[4][8]) {
		return false;
	}
	return true;
}

bool Magic_Cube::yellow_plane_center() {
	bool yellow[9];
	yellow[6] = false; yellow[7] = false; yellow[8] = false;
	yellow[3] = false; yellow[4] = true; yellow[5] = false;
	yellow[0] = false; yellow[1] = false; yellow[2] = false;
	if (is_type(yellow)) {
		cube.add_message(TURN_F);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);

		cube.add_message(TURN_U);
		cube.add_message(TURN_U);

		cube.add_message(TURN_F);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);

		cube.add_message(TURN_F);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		return true;
	}
	return false;
}

bool Magic_Cube::yellow_plane_rightangle() {
	bool yellow[9];
	yellow[6] = false; yellow[7] = true; yellow[8] = false;
	yellow[3] = true; yellow[4] = true; yellow[5] = false;
	yellow[0] = false; yellow[1] = false; yellow[2] = false;
	if (is_type(yellow)) {
		cube.add_message(TURN_F);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		
		cube.add_message(TURN_F);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		return true;
	}
	return false;
}

bool Magic_Cube::yellow_plane_line() {
	bool yellow[9];

	yellow[6] = false; yellow[7] = false; yellow[8] = false;
	yellow[3] = true; yellow[4] = true; yellow[5] = true;
	yellow[0] = false; yellow[1] = false; yellow[2] = false;
	if (is_type(yellow)) {
		cube.add_message(TURN_F);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_FN);
		return true;
	}
	return false;
}


bool Magic_Cube::is_type(bool yellow[9],bool edge[4][3]) {
	int num = 0;
	while (num < 4) {
		bool right = true;
		for (int i = 0; i < 9; ++i) {
			if (yellow[i] && Yellow != cube[4][i]|| !yellow[i] && Yellow == cube[4][i]) {
				right = false;
				break;
			}
		}
		for (int i = 0; i < 4; ++i) {
			if (edge[i][0] && Yellow != cube[i][6] || !edge[i][0] && Yellow == cube[i][6]) {
				right = false;
				break;
			}
			if (edge[i][1] && Yellow != cube[i][7] || !edge[i][1] && Yellow == cube[i][7]) {
				right = false;
				break;
			}
			if (edge[i][2] && Yellow != cube[i][8] || !edge[i][2] && Yellow == cube[i][8]) {
				right = false;
				break;
			}
		}

		if (right) {
			if (num < 2)
			{
				for (int i = 0; i < num; ++i) {
					cube.add_message(TURN_UN);
				}
			}
			else {
				num = 4 - num;
				for (int i = 0; i < num; ++i) {
					cube.add_message(TURN_U);
				}
			}
			return true;
		}
		++num;
		upper_plane_turn(yellow,edge);
	}
	return false;
}

bool Magic_Cube::is_type(bool yellow[9]) {
	int num = 0;
	while (num < 4) {
		bool right = true;
		for (int i = 0; i < 9; ++i) {
			if (yellow[i] && Yellow != cube[4][i]) {
				right = false;
				break;
			}
		}
		if (right) {
			if (num < 2)
			{
				for (int i = 0; i < num; ++i) {
					cube.add_message(TURN_UN);
				}
			}
			else {
				num = 4 - num;
				for (int i = 0; i < num; ++i) {
					cube.add_message(TURN_U);
				}
			}
			return true;
		}
		++num;
		upper_plane_turn(yellow);
	}
	return false;
}

void Magic_Cube::upper_plane_turn(bool yellow[9], bool edge[4][3]) {
	bool temp[9];
	memcpy(temp, yellow, sizeof(temp));
	yellow[0] = temp[2];
	yellow[1] = temp[5];
	yellow[2] = temp[8];
	yellow[3] = temp[1];
	yellow[4] = temp[4];
	yellow[5] = temp[7];
	yellow[6] = temp[0];
	yellow[7] = temp[3];
	yellow[8] = temp[6];
	if (edge) {
		bool te[4][3];
		memcpy(te, edge, sizeof(te));
		edge[0][0] = te[2][0];
		edge[0][1] = te[2][1];
		edge[0][2] = te[2][2];
		
		edge[3][0] = te[0][0];
		edge[3][1] = te[0][1];
		edge[3][2] = te[0][2];

		edge[1][0] = te[3][0];
		edge[1][1] = te[3][1];
		edge[1][2] = te[3][2];

		edge[2][0] = te[1][0];
		edge[2][1] = te[1][1];
		edge[2][2] = te[1][2];
	}
}


void Magic_Cube::upper_plane_turn(bool yellow[9]) {
	bool temp[9];
	memcpy(temp, yellow, sizeof(temp));
	yellow[0] = temp[2];
	yellow[1] = temp[5];
	yellow[2] = temp[8];
	yellow[3] = temp[1];
	yellow[4] = temp[4];
	yellow[5] = temp[7];
	yellow[6] = temp[0];
	yellow[7] = temp[3];
	yellow[8] = temp[6];
}

void Magic_Cube::upper_edge_block() {
	int index = -1;
	int num = 0;
	for (int i = 0; i < 4; ++i) {
		if (cube[i][6] == cube[i][8]) {
			index = i;
			++num;
		}
	}
	if (num < 4) {
		if (0 == num) {
			cube.add_message(TURN_R);
			cube.add_message(TURN_BN);
			cube.add_message(TURN_R);
			cube.add_message(TURN_F);
			cube.add_message(TURN_F);
			cube.add_message(TURN_RN);
			cube.add_message(TURN_B);
			cube.add_message(TURN_R);
			cube.add_message(TURN_F);
			cube.add_message(TURN_F);
			cube.add_message(TURN_RN);
			cube.add_message(TURN_RN);
		}
		else {
			if (Red == cube[index][6]) {
				if (0 == index) {
					cube.add_message(TURN_U);
				}
				else if (1 == index) {
					cube.add_message(TURN_UN);

				}
				else if (2 == index) {
					cube.add_message(TURN_U);
					cube.add_message(TURN_U);
				}
				cube_turn_N();
			}
			else if (Orange == cube[index][6]) {
				if (0 == index) {
					cube.add_message(TURN_UN);
				}
				else if (1 == index) {
					cube.add_message(TURN_U);

				}
				else if (3 == index) {
					cube.add_message(TURN_UN);
					cube.add_message(TURN_UN);
				}
				cube_turn();
			}
			else if (Green == cube[index][6]) {
				if (2 == index) {
					cube.add_message(TURN_U);
				}
				else if (3 == index) {
					cube.add_message(TURN_UN);

				}
				else if (1 == index) {
					cube.add_message(TURN_U);
					cube.add_message(TURN_U);
				}
			}
			else if (Blue == cube[index][6]) {
				if (3 == index) {
					cube.add_message(TURN_U);
				}
				else if (2 == index) {
					cube.add_message(TURN_UN);

				}
				else if (0 == index) {
					cube.add_message(TURN_U);
					cube.add_message(TURN_U);
				}
				cube_turn();
				cube_turn();
			}
			cube.add_message(TURN_R);
			cube.add_message(TURN_BN);
			cube.add_message(TURN_R);
			cube.add_message(TURN_F);
			cube.add_message(TURN_F);
			cube.add_message(TURN_RN);
			cube.add_message(TURN_B);
			cube.add_message(TURN_R);
			cube.add_message(TURN_F);
			cube.add_message(TURN_F);
			cube.add_message(TURN_RN);
			cube.add_message(TURN_RN);
			if (Red == cube[index][6]) {
				cube_turn();
			}
			else if (Orange == cube[index][6]) {
				cube_turn_N();
			}
			else if (Blue == cube[index][6]) {
				cube_turn();
				cube_turn();
			}
		}
	}
	else {
		if (Red == cube[index][6] && 1 == index) {
			cube.add_message(TURN_U);
			cube.add_message(TURN_U);
		}
		else if (Red == cube[index][6] && 2 == index) {
			cube.add_message(TURN_U);
		}
		else if (Red == cube[index][6] && 3 == index) {
			cube.add_message(TURN_UN);
		}
		else if (Orange == cube[index][6] && 0 == index) {
			cube.add_message(TURN_U);
			cube.add_message(TURN_U);
		}
		else if (Orange == cube[index][6] && 2 == index) {
			cube.add_message(TURN_UN);
		}
		else if (Orange == cube[index][6] && 3 == index) {
			cube.add_message(TURN_U);
		}
		else if (Green == cube[index][6] && 3 == index) {
			cube.add_message(TURN_U);
			cube.add_message(TURN_U);
		}
		else if (Green == cube[index][6] && 1 == index) {
			cube.add_message(TURN_U);
		}
		else if (Green == cube[index][6] && 0 == index) {
			cube.add_message(TURN_UN);
		}
		else if (Blue == cube[index][6] && 2 == index) {
			cube.add_message(TURN_U);
			cube.add_message(TURN_U);
		}
		else if (Blue == cube[index][6] && 0 == index) {
			cube.add_message(TURN_U);
		}
		else if (Blue == cube[index][6] && 1 == index) {
			cube.add_message(TURN_UN);
		}
		else if (cube[0][7] != cube[0][6]&&cube[2][7]!=cube[2][6] && cube[3][7] != cube[3][6]) {
			bool flag = false;
			if (cube[0][4] == cube[2][7]) {
				flag = true;
			}
			cube.add_message(TURN_F);
			cube.add_message(TURN_F);
			if (flag) {
				cube.add_message(TURN_U);
			}
			else {
				cube.add_message(TURN_UN);
			}
			cube.add_message(TURN_ZM);
			cube.add_message(TURN_UN);
			cube.add_message(TURN_UN);
			cube.add_message(TURN_ZMN);
			if (flag) {
				cube.add_message(TURN_U);
			}
			else {
				cube.add_message(TURN_UN);
			}
			cube.add_message(TURN_FN);
			cube.add_message(TURN_FN);
			//std::cout << "1" << std::endl;
			}
		else if (cube[1][7] != cube[1][6] && cube[2][7] != cube[2][6] && cube[3][7] != cube[3][6]) {
			bool flag = false;
			if (cube[2][7] == cube[1][4]) {
				flag = true;
			}
			cube.add_message(TURN_B);
			cube.add_message(TURN_B);
			if (flag) {
				cube.add_message(TURN_UN);
			}
			else {
				cube.add_message(TURN_U);
			}
			cube.add_message(TURN_ZMN);
			cube.add_message(TURN_U);
			cube.add_message(TURN_U);
			cube.add_message(TURN_ZM);
			if (flag) {
				cube.add_message(TURN_UN);
			}
			else {
				cube.add_message(TURN_U);
			}
			cube.add_message(TURN_BN);
			cube.add_message(TURN_BN);
			//std::cout << "2" << std::endl;
		}
		else if (cube[1][7] != cube[1][6] && cube[2][7] != cube[2][6] && cube[0][7] != cube[0][6]) {
			bool flag = false;
			if (cube[1][7] == cube[2][4]) {
				flag = true;
			}
			cube.add_message(TURN_R);
			cube.add_message(TURN_R);
			if (flag) {
				cube.add_message(TURN_U);
			}
			else {
				cube.add_message(TURN_UN);
			}
			cube.add_message(TURN_YMN);
			cube.add_message(TURN_UN);
			cube.add_message(TURN_UN);
			cube.add_message(TURN_YM);
			if (flag) {
				cube.add_message(TURN_U);
			}
			else {
				cube.add_message(TURN_UN);
			}
			cube.add_message(TURN_RN);
			cube.add_message(TURN_RN);
			//std::cout << "3" << std::endl;
		}
		else if (cube[1][7] != cube[1][6] && cube[3][7] != cube[3][6] && cube[0][7] != cube[0][6]) {
			bool flag = false;
			if (cube[0][7] == cube[3][4]) {
				flag = true;
			}
			cube.add_message(TURN_L);
			cube.add_message(TURN_L);
			if (flag) {
				cube.add_message(TURN_U);
			}
			else {
				cube.add_message(TURN_UN);
			}
			cube.add_message(TURN_YM);
			cube.add_message(TURN_UN);
			cube.add_message(TURN_UN);
			cube.add_message(TURN_YMN);
			if (flag) {
				cube.add_message(TURN_U);
			}
			else {
				cube.add_message(TURN_UN);
			}
			cube.add_message(TURN_LN);
			cube.add_message(TURN_LN);
			//std::cout << "4" << std::endl;
		}
	}
}

bool Magic_Cube::upper_edge_is_ok() {
	if (Red == cube[0][6] && Red == cube[0][7] && Red == cube[0][8] &&
		Orange == cube[1][6] && Orange == cube[1][7] && Orange == cube[1][8] &&
		Green == cube[2][6] && Green == cube[2][7] && Green == cube[2][8] &&
		Blue == cube[3][6] && Blue == cube[3][7] && Blue == cube[3][8]) {
		return true;
	}
	return false;
}

void Magic_Cube::cube_turn() {
	std::unique_lock<std::mutex> lck(cube.cube_mtx);
	cube.add_message(TURN_U);
	cube.add_message(TURN_XM);
	cube.add_message(TURN_DN);
	//cube.finish_modify.wait(lck);
}
void Magic_Cube::cube_turn_N() {
	std::unique_lock<std::mutex> lck(cube.cube_mtx);
	cube.add_message(TURN_UN);
	cube.add_message(TURN_XMN);
	cube.add_message(TURN_D);
	//cube.finish_modify.wait(lck);
}
