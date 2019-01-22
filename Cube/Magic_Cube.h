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

	bool check_yellow_plane();
	bool yellow_plane();

	bool yellow_plane_center();
	bool yellow_plane_line();
	bool yellow_plane_rightangle();

	bool is_type(bool yellow[9], bool edge[4][3]);
	bool is_type(bool yellow[9]);
	void upper_plane_turn(bool yellow[9], bool edge[4][3]);
	void upper_plane_turn(bool yellow[9]);

	void upper_edge_block();
	bool upper_edge_is_ok();
	void cube_turn();
	void cube_turn_N();
	Cube cube;
};