#pragma once

#include "pch.h"
#include "Cube.h"

class Magic_Cube {
public:
	Magic_Cube() {}
	void disorder();
	void restore();
	void add_message(unsigned instruction, int zv = 0, double *rv = NULL, int*tv = NULL);
private:
	void white_cross(const COLOR color);
	void white_corner_block(const COLOR l, const COLOR r);
	void middle_arris(const COLOR l, const  COLOR r);
	void cube_turn();
	void cube_turn_N();
	Cube cube;
};