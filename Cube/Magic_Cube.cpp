#include "pch.h"
#include "Magic_Cube.h"

Magic_Cube mc;// Magic_Cube include Cube

void Magic_Cube::disorder() {
	std::unique_lock<std::mutex> lck(cube.cube_mtx);
	const int times = 10;
	unsigned instruction = 1;
	srand((unsigned)time(NULL));
	for (int i = 0; i < times; ++i) {
		int j = rand() % (instru_num-6);
		add_message(instruction << j);
	}
	cube.finish_modify.wait(lck);
}
void Magic_Cube::restore() {
	// restore the cross of white plane 
	if (White != cube[5][7] || Red != cube[0][1]) {
		white_cross(Red);
	}// restore the white plane with red arris
	cube_turn();
	if (White != cube[5][7] || Green != cube[0][1]) {
		white_cross(Green);
	}// restore the white plane with green arris
	cube_turn();
	if (White != cube[5][7] || Orange != cube[0][1]) {
		white_cross(Orange);
	}// restore the white plane with orange arris
	cube_turn();
	if (White != cube[5][7] || Blue != cube[0][1]) {
		white_cross(Blue);
	}// restore the white plane with blue arris
	cube_turn();

	// restore the corner block of white plane
	if (Red != cube[0][2] || Green != cube[2][0]||White!=cube[5][8]) {
		white_corner_block(Red, Green);
	}
	cube_turn();
	if (Green != cube[0][2] || Orange != cube[2][0] || White != cube[5][8]) {
		white_corner_block(Green,Orange);
	}
	cube_turn();
	if (Orange != cube[0][2] || Blue != cube[2][0] || White != cube[5][8]) {
		white_corner_block(Orange, Blue);
	}
	cube_turn();
	if (Blue != cube[0][2] || Red != cube[2][0] || White != cube[5][8]) {
		white_corner_block(Blue, Red);
	}
	cube_turn();

	// restore the middle arris
	if (Red != cube[0][5] || Green != cube[2][3]) {
		middle_arris(Red, Green);
	}
	cube_turn();
	if (Green != cube[0][5] || Orange != cube[2][3]) {
		middle_arris(Green, Orange);
	}
	cube_turn();
	if (Orange != cube[0][5] || Blue != cube[2][3]) {
		middle_arris(Orange,Blue);
	}
	cube_turn();
	if (Blue != cube[0][5] || Red != cube[2][3]) {
		middle_arris(Blue, Red);
	}
	cube_turn();
	std::unique_lock<std::mutex> lck(cube.cube_mtx);
	cube.finish_modify.wait(lck);
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
		std::cout << "1" << std::endl;
	}
	else if (White == cube[5][3] && color == cube[3][1]) {
		cube.add_message(TURN_L);
		cube.add_message(TURN_L);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		std::cout << "2" << std::endl;
	}
	else if (White == cube[5][5] && color == cube[2][1]) {
		cube.add_message(TURN_R);
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		std::cout << "3" << std::endl;
	}
	else if (color == cube[5][1] && White == cube[1][1]) {
		cube.add_message(TURN_B);
		cube.add_message(TURN_B);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_R);
		std::cout << "4" << std::endl;
	}
	else if (color == cube[5][3] && White == cube[3][1]) {
		cube.add_message(TURN_LN);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_L);
		std::cout << "5" << std::endl;
	}
	else if (color == cube[5][5] && White == cube[2][1]) {
		cube.add_message(TURN_R);
		cube.add_message(TURN_F);
		cube.add_message(TURN_RN);
		std::cout << "6" << std::endl;
	}
	else if (color == cube[5][7] && White == cube[0][1]) {
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		cube.add_message(TURN_U);
		cube.add_message(TURN_L);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_LN);
		std::cout << "7" << std::endl;
	}
	else if (White == cube[0][5] && color == cube[2][3]) {
		cube.add_message(TURN_R);
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		std::cout << "8" << std::endl;
	}
	else if (color == cube[0][5] && White == cube[2][3]) {
		cube.add_message(TURN_F);
		std::cout << "9" << std::endl;
	}
	else if (White == cube[0][3] && color == cube[3][5]) {
		cube.add_message(TURN_LN);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_L);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		std::cout << "10" << std::endl;
	}
	else if (color == cube[0][3] && White == cube[3][5]) {
		cube.add_message(TURN_FN);
		std::cout << "11" << std::endl;
	}
	else if (White == cube[1][3] && color == cube[2][5]) {
		cube.add_message(TURN_RN);
		cube.add_message(TURN_U);
		cube.add_message(TURN_R);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		std::cout << "12" << std::endl;
	}
	else if (color == cube[1][3] && White == cube[2][5]) {
		cube.add_message(TURN_RN);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_R);
		cube.add_message(TURN_R);
		std::cout << "13" << std::endl;
	}
	else if (White == cube[1][5] && color == cube[3][3]) {
		cube.add_message(TURN_L);
		cube.add_message(TURN_UN);
		cube.add_message(TURN_LN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		std::cout << "14" << std::endl;
	}
	else if (color == cube[1][5] && White == cube[3][3]) {
		cube.add_message(TURN_L);
		cube.add_message(TURN_L);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_LN);
		cube.add_message(TURN_LN);
		std::cout << "15" << std::endl;
	}
	else if (White == cube[0][7] && color == cube[4][1]) {
		cube.add_message(TURN_U);
		cube.add_message(TURN_L);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_LN);
		std::cout << "16" << std::endl;
	}
	else if (color == cube[0][7] && White == cube[4][1]) {
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		std::cout << "17" << std::endl;
	}
	else if (White == cube[1][7] && color == cube[4][7]) {
		cube.add_message(TURN_U);
		cube.add_message(TURN_RN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_R);
		std::cout << "18" << std::endl;
	}
	else if (color == cube[1][7] && White == cube[4][7]) {
		cube.add_message(TURN_U);
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		std::cout << "19" << std::endl;
	}
	else if (White == cube[2][7] && color == cube[4][5]) {
		cube.add_message(TURN_RN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_R);
		std::cout << "20" << std::endl;
	}
	else if (color == cube[2][7] && White == cube[4][5]) {
		cube.add_message(TURN_U);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		std::cout << "21" << std::endl;
	}
	else if (White == cube[3][7] && color == cube[4][3]) {
		cube.add_message(TURN_L);
		cube.add_message(TURN_FN);
		cube.add_message(TURN_LN);
		std::cout << "22" << std::endl;
	}
	else if (color == cube[3][7] && White == cube[4][3]) {
		cube.add_message(TURN_UN);
		cube.add_message(TURN_F);
		cube.add_message(TURN_F);
		std::cout << "23" << std::endl;
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
	}
	else if (l == cube[0][0] && White == cube[3][2] && r == cube[5][6]) {
		add_message(TURN_R);
		add_message(TURN_LN);
		add_message(TURN_UN);
		add_message(TURN_L);
		add_message(TURN_RN);
	}
	else if (White == cube[0][0] && r == cube[3][2] && l == cube[5][6]) {
		add_message(TURN_F);
		add_message(TURN_UN);
		add_message(TURN_UN);
		add_message(TURN_FN);
		add_message(TURN_U);
		add_message(TURN_F);
	}
	else if (r == cube[0][0] && l == cube[3][2] && White == cube[5][6]) {
		add_message(TURN_F);
		add_message(TURN_U);
		add_message(TURN_FN);
		add_message(TURN_R);
		add_message(TURN_UN);
		add_message(TURN_UN);
		add_message(TURN_RN);
	}
	else if (r == cube[1][2] && White == cube[3][0] && l == cube[5][0]) {
		add_message(TURN_L);
		add_message(TURN_U);
		add_message(TURN_LN);
		add_message(TURN_U);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
	}
	else if (White == cube[1][2] && l == cube[3][0] && r == cube[5][0]) {
		add_message(TURN_BN);
		add_message(TURN_UN);
		add_message(TURN_B);
		add_message(TURN_R);
		add_message(TURN_UN);
		add_message(TURN_RN);
	}
	else if (r == cube[1][2] && l == cube[3][0] && White == cube[5][0]) {
		add_message(TURN_BN);
		add_message(TURN_UN);
		add_message(TURN_UN);
		add_message(TURN_B);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
	}
	else if (l == cube[1][0] && White == cube[2][2] && r == cube[5][2]) {
		add_message(TURN_RN);
		add_message(TURN_U);
		add_message(TURN_U);
		add_message(TURN_R);
		add_message(TURN_R);
		add_message(TURN_UN);
		add_message(TURN_RN);
	}
	else if (White == cube[1][0] && r == cube[2][2] && l == cube[5][2]) {
		add_message(TURN_B);
		add_message(TURN_U);
		add_message(TURN_BN);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
	}
	else if (r == cube[1][0] && l == cube[2][2] && White == cube[5][2]) {
		add_message(TURN_B);
		add_message(TURN_U);
		add_message(TURN_U);
		add_message(TURN_BN);
		add_message(TURN_R);
		add_message(TURN_UN);
		add_message(TURN_RN);
	}
	else if (l == cube[0][8] && White == cube[2][6] && r == cube[4][2]) {
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
	}
	else if (White == cube[0][8] && r == cube[2][6] && l == cube[4][2]) {
		add_message(TURN_U);
		add_message(TURN_R);
		add_message(TURN_UN);
		add_message(TURN_RN);
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
	}
	else if (r == cube[0][6] && White == cube[3][8] && l == cube[4][0]) {
		add_message(TURN_R);
		add_message(TURN_UN);
		add_message(TURN_RN);
	}
	else if (White == cube[0][6] && l == cube[3][8] && r == cube[4][0]) {
		add_message(TURN_UN);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
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
	}
	else if (l == cube[1][8] && White == cube[3][6] && r == cube[4][6]) {
		add_message(TURN_UN);
		add_message(TURN_UN);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
	}
	else if (White == cube[1][8] && r == cube[3][6] && l == cube[4][6]) {
		add_message(TURN_R);
		add_message(TURN_UN);
		add_message(TURN_UN);
		add_message(TURN_RN);
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
	}
	else if (r == cube[1][6] && White == cube[2][8] && l == cube[4][8]) {
		add_message(TURN_U);
		add_message(TURN_U);
		add_message(TURN_R);
		add_message(TURN_UN);
		add_message(TURN_RN);
	}
	else if (White == cube[1][6] && l == cube[2][8] && r == cube[4][8]) {
		add_message(TURN_U);
		add_message(TURN_R);
		add_message(TURN_U);
		add_message(TURN_RN);
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

void Magic_Cube::cube_turn() {
	std::unique_lock<std::mutex> lck(cube.cube_mtx);
	cube.add_message(TURN_U);
	cube.add_message(TURN_XM);
	cube.add_message(TURN_DN);
	cube.finish_modify.wait(lck);
}
void Magic_Cube::cube_turn_N() {
	std::unique_lock<std::mutex> lck(cube.cube_mtx);
	cube.add_message(TURN_UN);
	cube.add_message(TURN_XMN);
	cube.add_message(TURN_D);
	cube.finish_modify.wait(lck);
}
