#include "pch.h"
#include "Cube.h"
#include <algorithm>
#include <cmath>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;


cv::Point start(0, 0);// record the mouse start point
std::chrono::system_clock::time_point ms;// avoid frequently calling

// function about COLOR
uchar R(COLOR color) { return color >> 16; }
uchar G(COLOR color) { return color >> 8; }
uchar B(COLOR color) { return color; }
COLOR light(COLOR color, Double I) {
	uchar r = R(color);
	uchar g = G(color);
	uchar b = B(color);
	r *= I;
	g *= I;
	b *= I;
	return RGB(r, g, b);
}
//function about Point3d
bool Equal_slope(const Point3d&x, const Point3d& y, const Point3d& z) {
	Double delta_x1, delta_x2;
	Double delta_y1, delta_y2;
	Double delta_z1, delta_z2;
	delta_x1 = x.x - y.x;
	delta_x2 = y.x - z.x;
	delta_y1 = x.y - y.y;
	delta_y2 = y.y - z.y;
	delta_z1 = x.z - y.z;
	delta_z2 = y.z - z.z;
	return delta_x1 * delta_y2 == delta_x2 * delta_y1&&delta_x1*delta_z2 == delta_x2 * delta_z1&&delta_y1*delta_z2 == delta_y2 * delta_z1;
}


//function about Plane3d
void Plane3d::get_equation() {
	if (num < 3||Equal_slope(p[0],p[1],p[2])) {
		cerr << "Error plane!!!" << endl;
		return;
	}
	Double equation[4][5];
	const int row = 3, col = 4;
	// Initialize the equation
	equation[0][0] = p[0].x;
	equation[0][1] = p[0].y;
	equation[0][2] = p[0].z;
	equation[0][3] = 1;
	equation[0][4] = 1;
	equation[1][0] = p[1].x;
	equation[1][1] = p[1].y;
	equation[1][2] = p[1].z;
	equation[1][3] = 1;
	equation[1][4] = 1;
	for (int i = 2; i < num; ++i) {
		if (!Equal_slope(p[0], p[1], p[i])) {
			equation[i][0] = p[i].x;
			equation[i][1] = p[i].y;
			equation[i][2] = p[i].z;
			equation[i][3] = 1;
			equation[i][4] = 1;
		}
	}

	bool freeX[col];
	bool x_flag[col];
	int freeE[col];
	Double x[col];
	Double dx[col];
	Double rx[col];
	int free_num = 0;
	for (int i = 0; i < col; ++i) {
		freeE[i] = 0;
		freeX[i] = true;
		x[i] = 0;
		rx[i] = 0;
		dx[i] = 0;
		x_flag[i] = false;
	}
	// solve the equation and get A,B,C,D
	for (int i = 0, j = 0; i < row&&j < col; ++i, ++j) {
		int maxr = i;
		for (int k = i + 1; k < row; ++k) {
			if (abs(equation[maxr][j]) < abs(equation[k][j])) { maxr = k; }
		}
		if (0 == equation[maxr][j]) {
			freeE[free_num] = j;
			++free_num;
			continue;
		}
		if (maxr != i) {
			for (int k = 0; k <= col; ++k) {
				std::swap(equation[maxr][k], equation[i][k]);
			}
		}
		for (int k = i + 1; k < row; ++k) {
			if (0 == equation[k][j])
				continue;
			int lcm = LCM(abs(equation[i][j]), abs(equation[k][j]));
			int ta, tb;
			ta = lcm / abs(equation[i][j]);
			tb = lcm / abs(equation[k][j]);
			if (equation[i][j] * equation[k][j] < 0)tb = -tb;
			for (int h = j; h <= col; ++h)
			{
				equation[k][h] = equation[i][h] * ta - equation[k][h] * tb;
			}
		}
	}
	for (int i = row - 1; i >= 0; --i) {
		int num = 0;
		int index = 0;
		for (int j = i; j < col; ++j) {
			if (equation[i][j] && freeX[j]) {
				++num;
				index = j;
			}
		}
		if (num > 1) {
			continue;
		}
		Double temp = equation[i][col];
		for (int j = 0; j < col; ++j) {
			if (equation[i][j] && j != index) {
				temp -= equation[i][j] * x[j];
			}
		}
		freeX[index] = false;
		x[index] = temp/equation[i][index];
		rx[index] = temp;
		dx[index] = equation[i][index];
		x_flag[index] = true;
	}
	for (int i = 0; i < free_num; ++i) {
		x[freeE[i]] = 1;
		x_flag[freeE[i]] = true;
	}
	for (int i = row-1; i >= 0; --i) {
		int q = 0;
		for (q = 0; q< col; ++q) {
			if (equation[i][q])
				break;
		}
		Double temp = equation[i][col];
		for (int j = q + 1; j < col; ++j) {
			if (x_flag[j]) {
				temp -= equation[i][j] * x[j];
			}
		}
		x[q] = temp/equation[i][q];
		rx[q] = temp;
		dx[q] = equation[i][q];
		x_flag[q] = true;
	}
	/*Double lcm = 1;
	Double gcd = 1;
	for (int i = 0; i < col; ++i) {
		if (dx[i]) {
			lcm = LCM(lcm, dx[i]);
		}
	}
	for (int i = 0; i < col; ++i) {
		if (dx[i] != 0)
		{
			x[i] = rx[i] * lcm / dx[i];
			gcd = x[i];
		}
	}
	for (int i = 0; i < col; ++i) {
		if(x[i])
			gcd = GCD(gcd, x[i]);
	}*/
	A = x[0];
	B = x[1];
	C = x[2];
	D = -(A * equation[0][0] + B * equation[0][1] + C * equation[0][2]);
}

// functions in Illumination
Double Illumination::illumination(const Plane&plane, const Point&point) {
	Double I = 0;
	for (int i = 0; i < light.size(); ++i) {
		I += illumination(plane, point, light[i]);
	}
	I = std::min(I, 1.0);
	return I;
}

Double Illumination::illumination(const Plane&plane, const Point&point,const Point&light) {
	const int dimension = 3;
	const int n = 3;
	const Double Idc = 0.5;
	Double I=Ia*ka;
	Double Ip = 1.0;
	Double dx = light.x - point.x;
	Double dy = light.y - point.y;
	Double dz = light.z - point.z;
	if (dz >200)
	{
		int a=0;
		a = a + 1;
	}
	Double vdx = view_point.x - point.x;
	Double vdy = view_point.y - point.y;
	Double vdz = view_point.z - point.z;
	Double distance = sqrt(dx*dx + dy * dy + dz * dz);
	Double visual_distance= sqrt(vdx*vdx + vdy * vdy + vdz * vdz);
	Double normal_vector[3] = {plane.get_A(),plane.get_B(),plane.get_C()};
	Double light_vector[3] = {dx/distance,dy/distance,dz/distance};
	Double visual_vector[3] = { vdx / visual_distance,vdy / visual_distance,vdz / visual_distance };
	Double reflection_vector[3];
	Double temp = vector_multipy(normal_vector, light_vector, dimension);
	Double S0 = get_S0(point.z);
	for (int i = 0; i < dimension; ++i) {
		reflection_vector[i] = 2 * normal_vector[i]*temp + light_vector[i];
	}
	I += f(distance)*Ip*(ks*(vector_multipy(light_vector, normal_vector)) + ks * fast_power(vector_multipy(visual_vector, reflection_vector), n));
	//I = S0 * I + (1 - S0)*Idc;
	I = std::min(I, 1.0);
	return I;
}

Double Illumination::vector_multipy(Double *a, Double *b, int num) {
	Double res = 0;
	for (int i = 0; i < num; ++i) {
		res += a[i] * b[i];
	}
	return res;
}

Double Illumination::f(Double d) {
	const Double c0 = 0.5, c1 = 0.0003125, c2 = 0.0000015625;
	//std::cout << d << std::endl;
	return std::min(1 / (c0 + c1 * d + c2 * d*d)-1.0, 1.0);
}

template <typename T>
T Illumination::fast_power(T a, int b) {
	T ans = 1;
	while (b) {
		if (b & 1)ans *= a;
		a *= a;
		b >>= 1;
	}
	return ans;
}
Double Illumination::get_S0(Double Z0) {
	const Double Zb = -15, Zf = 15;
	const Double Sb = 0.2, Sf = 0.8;
	if (Z0 > Zf)
		return Sf;
	if (Z0 < Zb)
		return Sb;
	return Sb + (Sf - Sb) / (Zf - Zb)*(Z0 - Zb);
}

// functions in Blanking
void Blanking::blank(std::vector<std::vector<COLOR>>& res,const std::vector<Plane>& plane,const Int width,const Int height) {
	typedef std::vector<Plane>::size_type SIZE;
	// Initialize the polygon
	std::vector<Polygon> polygon;
	
	Int vmax = -INF;
	Int vmin = INF;
	for (SIZE i = 0; i < plane.size(); ++i) {
		polygon.push_back(Polygon(plane[i], (Int)i));
		vmax = std::max(vmax, polygon[i].vmax);
		vmin = std::min(vmin, polygon[i].vmin);
	}

	// Initialize the PT table
	PT pt(polygon);
	APL apl(pt);

	
	std::vector<Double> Z;// Z Buffer
	res.resize(height);// keep the function result
	Z.resize(width);
	for (int i = 0; i < height; ++i) {
		res[i].resize(width);
		for (int j = 0; j < width; ++j) {
			res[i][j] = Black;
		}
	}
	
	// Initial the ET and EPL table
	std::vector<ET> et;
	std::vector<EPL> epl;
	
	int num = polygon.size();
	
	et.resize(num);
	epl.resize(num);
	std::vector<std::map<Int, Int>> border(num);

	for (Int i = vmin; i <= vmax; ++i) {
		for (int j = 0; j < width; ++j) {
			Z[j] = -INF;
		}
		std::vector<std::vector<Int>> change=apl.update(i);
		for (std::vector<Int>::size_type j = 0; j < change[0].size(); ++j) {
			int t = change[0][j];
			ET temp;
			border[change[0][j]]=temp.set(plane[t]);
			et[t]=temp;
			epl[t].set_ET(&et[t]);
			epl[t].set_Polygon(&polygon[t]);
		}
		for (std::vector<Int>::size_type j = 0; j < change[1].size(); ++j) {
			int t = change[1][j];
			border[change[1][j]].clear();
			et[t].clear();
			epl[t].clear();
		}
		for (int j = 0; j < num; ++j) {
			epl[j].update(i);
			const std::list<EP> temp=epl[j].get_EP();
			for (auto p : temp) {
				Int b = p.begin()+width/2;
				Int e = p.end()+width/2;
				Double n = p.get_Z();
				Double delta_n = p.get_delta_nu();
				if (Z[b] <= n) {
					res[i + height / 2][b] = Black;
					Z[b] = n;
				}
				n += delta_n;
				for (int k = b+1; k < e; ++k) {
					if (Z[k] < n) {
						if(border[j].find(i)!=border[j].end())
							res[i + height / 2][k] = Black;
						else {
							Double I=illumination.illumination(plane[j], Point(i, k, n));
							res[i + height / 2][k] = light(plane[j].get_color(),I);
						}
						Z[k] = n;
					}
					n += delta_n;
				}
				if (Z[e] <= n) {
					res[i + height / 2][e] = Black;
					Z[e] = n;
				}
			}
		}
	}
}

// functions int Blanking of Polygon
void Blanking::Polygon::set(const Plane&p,int _Pl) {
	A = p.get_A();
	B = p.get_B();
	C = p.get_C();
	D = p.get_D();
	color = p.get_color();
	Pl = _Pl;
	Point *point = p.get_point();
	int num = p.get_num();
	Int vmax = -INF;
	Int vmin = INF;
	for (int i = 0; i < num; ++i) {
		if (p[i].y > vmax) {
			vmax = p[i].y;
		}
		if (p[i].y < vmin) {
			vmin = p[i].y;
		}
	}
	this->vmax = vmax;
	this->vmin = vmin;
}

// functions in Blanking of PT
std::list<Blanking::Polygon*> Blanking::PT::null;

// functions in Blanking of APL
std::vector<Int> Blanking::APL::add(Int v) {
	std::list<Polygon*>&pt = this->pt.get(v);
	std::vector<Int> res;
	while (!pt.empty()) {
		apl.push_back(pt.front());
		res.push_back(pt.front()->Pl);
		pt.pop_front();
	}
	return res;
}

std::vector<Int> Blanking::APL::drop(Int v) {
	std::vector<Int> res;
	std::list<Polygon*>::iterator it = apl.begin();
	while (it != apl.end()) {
		if ((*it)->vmax < v) {
			res.push_back((*it)->Pl);
			it = apl.erase(it);

		}
		else ++it;
	}
	return res;
}
// functons in Blanking of ET
std::map<Int,Int> Blanking::ET::set(const Plane&plane){
	int num = plane.get_num();
	std::vector<Edge> te;
	std::map<Int,Int> border;
	const Point *p = plane.get_point();
	Int vmax = -INF;
	Int vmin = INF;
	for (int i = 0; i < num-1; ++i) {
		//Edge temp(p[i], p[i + 1]);
		if(p[i].y!=p[i+1].y)
		{	te.push_back(Edge(p[i], p[i + 1]));
			vmax = std::max(vmax, te[te.size()-1].vmax);
			vmin = std::min(vmin, te[te.size()-1].vmin);
		}
		else {
			border[p[i].y] = p[i].y;
		}
	}
	if (p[num - 1].y != p[0].y)
	{
		te.push_back(Edge(p[num - 1], p[0]));
		vmax = std::max(vmax, te[te.size()-1].vmax);
		vmin = std::min(vmin, te[te.size()-1].vmin);
	}
	else {
		border[p[num-1].y] = p[num-1].y;
	}
	this->maxv = vmax;
	this->minv = vmin;
	
	for (std::vector<Edge>::size_type i = 0; i < te.size(); ++i) {
		et[te[i].vmin].push_back(te[i]);
	}
	for (std::map<Int,std::list<Edge>>::iterator i = et.begin(); i != et.end(); ++i) {
		i->second.sort([](const Edge&a, const Edge&b) {if (a.u != b.u)return a.u < b.u; else return a.delta_u < b.delta_u; });
	}
	return border;
}
std::list<Blanking::Edge> Blanking::ET::null;
// functions in Blanking of EP
void Blanking::EP::update() {
	l.u += l.delta_u;
	r.u += r.delta_u;
	l.n += delta_nu * l.delta_u + delta_nv;
	r.n += delta_nv * r.delta_u + delta_nv;
}
// functions in Blanking of EPL
void Blanking::EPL::update(Int v) {
	if (et == NULL)
		return;
	std::list<EP>::iterator it = epl.begin();
	while (it != epl.end()) {
		it->update();
		if (it->l.vmax < v && it->r.vmax < v) {
			it = epl.erase(it);
			continue;
		}
		if (it->l.vmax <= v) {
			std::list<Edge>& e = et[Pl].get(v);
			std::list<Edge>::iterator i = e.begin();
			while (i != e.end()) {
				if (i->u <= it->r.u) {
					it->set_left((*i));
					e.erase(i);
					break;
				}
				++i;
			}
		}
		if (it->r.vmax <= v) {
			std::list<Edge>& e = et[Pl].get(v);
			std::list<Edge>::iterator i = e.begin();
			while (i != e.end()) {
				if (i->u >= it->l.u) {
					it->set_right((*i));
					e.erase(i);
					break;
				}
				++i;
			}
		}
		++it;
	}
	std::list<Edge>& e = et->get(v);
	std::list<Edge>::iterator i = e.begin();
	int k = 0;
	std::list<Edge>::iterator a;
	while (i != e.end()) {
		if (k == 1) {
			epl.push_back(EP((*a),(*i),p));
			k = 0;
			a = e.erase(a);
			i = e.erase(a);
		}
		else {
			++k;
			a = i;
			++i;
		}
	}
}



// functions in Geometric_transformation

void Geometric_transformation::rotate(std::vector<Plane>& plane, int axis, double angle) {
	for (int i = 0; i < plane.size(); ++i) {
		rotate(plane[i], axis,angle);
	}
}
void Geometric_transformation::zoom(std::vector<Plane>& plane, double size) {
	for (int i = 0; i < plane.size(); ++i) {
		zoom(plane[i], size);
	}
}
void Geometric_transformation::translation(std::vector<Plane>& plane, int dx, int dy,int dz) {
	for (int i = 0; i < plane.size();++i) {
		translation(plane[i], dx,dy,dz);
	}
}
void Geometric_transformation::rotate(Plane& plane, int axis,double angle) {
	vector<vector<double>> matric=get_rotate_matric(axis,angle);
	
	int num = plane.get_num();
	Point *p = plane.get_point();
	for (int i = 0; i < num; ++i) {
		multiply(p[i], matric);
	}
	plane.get_equation();
}
void Geometric_transformation::zoom(Plane& plane, double size) {
	std::vector<std::vector<std::vector<double>>> temp = get_zoom_matric(size);
	vector<vector<double>> matric=temp[0];
	vector<vector<double>> shift=temp[1];
	vector<vector<double>> back_shift=temp[2];
	for (int i = 0; i < 4; ++i) {
		vector<double> temp(4);
		for (int j = 0; j < 4; ++j) {
			if(i!=j)
				temp[j] = 0;
			else temp[j] = 1;
		}
		matric.push_back(temp);
		shift.push_back(temp);
		back_shift.push_back(temp);
	}

	matric[3][3] = size;
	int num = plane.get_num();
	Point *p = plane.get_point();
	for (int i = 0; i < num; ++i) {
		shift[3][0] = -p[i].x;
		shift[3][1] = -p[i].y;
		shift[3][2] = -p[i].z;
		back_shift[3][0] = p[i].x/size;
		back_shift[3][1] = p[i].y/size;
		back_shift[3][2] = p[i].z/size;
		multiply(p[i], shift);
		multiply(p[i], matric);
		multiply(p[i], back_shift);
	}
	plane.get_equation();
}
void Geometric_transformation::translation(Plane& plane, int dx=0, int dy=0,int dz=0) {
	vector<vector<double>> matric = get_translation_matric(dx, dy, dz);
	int num = plane.get_num();
	Point *p = plane.get_point();
	for (int i = 0; i < num; ++i) {
		multiply(p[i], matric);
	}
	plane.get_equation();
}
void Geometric_transformation::multiply(Point&point, const vector<vector<double>>&matric){
	double res[4];
	res[3] = 1;
	for (int i = 0; i < 4; ++i) {
		res[i] = matric[0][i] * point.x + matric[1][i] * point.y + matric[2][i] * point.z + res[3] * matric[3][i];
	}
	point.x = res[0] / res[3];
	point.y = res[1] / res[3];
	point.z = res[2] / res[3];
}
void Geometric_transformation::rotate(Point& point, int axis, double angle) {
	vector<vector<double>> matric = get_rotate_matric(axis, angle);
	multiply(point, matric);
}
void Geometric_transformation::zoom(Point& point, double size) {
	std::vector<std::vector<std::vector<double>>> temp = get_zoom_matric(size);
	vector<vector<double>> matric = temp[0];
	vector<vector<double>> shift = temp[1];
	vector<vector<double>> back_shift = temp[2];
	shift[3][0] = -point.x;
	shift[3][1] = -point.y;
	shift[3][2] = -point.z;
	back_shift[3][0] = point.x / size;
	back_shift[3][1] = point.y / size;
	back_shift[3][2] = point.z / size;
	multiply(point, shift);
	multiply(point, matric);
	multiply(point, back_shift);
}
void Geometric_transformation::translation(Point& point, int dx, int dy, int dz) {
	vector<vector<double>> matric = get_translation_matric(dx, dy, dz);
	multiply(point, matric);
}
std::vector<std::vector<double>> Geometric_transformation::get_rotate_matric(int axis, double angle) {
	double cos_zita = cos(angle);
	double sin_zita = sin(angle);
	vector<vector<double>> matric;
	if (0 == axis)// axis x
	{
		vector<double> temp(4);
		temp[0] = 1;
		temp[1] = 0;
		temp[2] = 0;
		temp[3] = 0;

		matric.push_back(temp);

		temp[0] = 0;
		temp[1] = cos_zita;
		temp[2] = sin_zita;
		temp[3] = 0;

		matric.push_back(temp);

		temp[0] = 0;
		temp[1] = -sin_zita;
		temp[2] = cos_zita;
		temp[3] = 0;

		matric.push_back(temp);


		temp[0] = 0;
		temp[1] = 0;
		temp[2] = 0;
		temp[3] = 1;

		matric.push_back(temp);
	}
	else if (1 == axis)// axis y
	{
		vector<double> temp(4);
		temp[0] = cos_zita;
		temp[1] = 0;
		temp[2] = -sin_zita;
		temp[3] = 0;

		matric.push_back(temp);

		temp[0] = 0;
		temp[1] = 1;
		temp[2] = 0;
		temp[3] = 0;

		matric.push_back(temp);

		temp[0] = sin_zita;
		temp[1] = 0;
		temp[2] = cos_zita;
		temp[3] = 0;

		matric.push_back(temp);


		temp[0] = 0;
		temp[1] = 0;
		temp[2] = 0;
		temp[3] = 1;

		matric.push_back(temp);
	}
	else// axis z 
	{
		vector<double> temp(4);

		temp[0] = cos_zita;
		temp[1] = sin_zita;
		temp[2] = 0;
		temp[3] = 0;

		matric.push_back(temp);

		temp[0] = -sin_zita;
		temp[1] = cos_zita;
		temp[2] = 0;
		temp[3] = 0;

		matric.push_back(temp);

		temp[0] = 0;
		temp[1] = 0;
		temp[2] = 1;
		temp[3] = 0;

		matric.push_back(temp);


		temp[0] = 0;
		temp[1] = 0;
		temp[2] = 0;
		temp[3] = 1;

		matric.push_back(temp);
	}
	return matric;
}
std::vector<std::vector<double>> Geometric_transformation::get_translation_matric(int dx, int dy, int dz) {
	vector<vector<double>> matric;
	for (int i = 0; i < 4; ++i) {
		vector<double> temp(4);
		for (int j = 0; j < 4; ++j) {
			if (i != j)
				temp[j] = 0;
			else temp[j] = 1;
		}
		matric.push_back(temp);
	}
	matric[3][0] = dx;
	matric[3][1] = dy;
	matric[3][2] = dz;
	return matric;
}
std::vector<std::vector<std::vector<double>>>Geometric_transformation::get_zoom_matric(double size) {
	vector<vector<double>> matric;
	vector<vector<double>> shift;
	vector<vector<double>> back_shift;
	for (int i = 0; i < 4; ++i) {
		vector<double> temp(4);
		for (int j = 0; j < 4; ++j) {
			if (i != j)
				temp[j] = 0;
			else temp[j] = 1;
		}
		matric.push_back(temp);
		shift.push_back(temp);
		back_shift.push_back(temp);
	}
	std::vector<std::vector<std::vector<double>>>temp;
	temp.push_back(matric);
	temp.push_back(shift);
	temp.push_back(back_shift);
	return temp;
}
void Geometric_transformation::transform(std::vector<Plane>& plane, const std::vector<std::vector<double>>& matric) {
	for (int i = 0; i < plane.size(); ++i) {
		transform(plane[i], matric);
	}
}
void Geometric_transformation::transform(Plane& plane, const std::vector<std::vector<double>>& matric) {
	int num = plane.get_num();
	Point *p = plane.get_point();
	for (int i = 0; i < num; ++i) {
		multiply(p[i], matric);
	}
	plane.get_equation();
}
void Geometric_transformation::transform(Point& point, const std::vector<std::vector<double>>& matric) {
	multiply(point, matric);
}

// functions in Cube_Plane
Cube_Plane::Cube_Plane() {
	for (int i = 0; i < 6; ++i) {
		std::vector<COLOR> temp;
		for (int j = 0; j < 9; ++j) {
			temp.push_back(CUBE_COLOR[i]);
		}
		cube_plane.push_back(temp);
	}
}

Cube_Plane::Cube_Plane(const Cube_Plane& c):cube_plane(c.cube_plane) {

}

Cube_Plane::Cube_Plane(const std::vector<std::vector<COLOR>>_cube_plane):cube_plane(_cube_plane) {

}



void Cube_Plane::R() {

	int p[4] = { 0,4,1,5 };
	int b[4][3] = { { 2,5,8 },{2,5,8 } , { 6,3,0  }, { 2,5,8  } };
	turn(p, b, 2);
}
void Cube_Plane::L() {

	int p[4] = { 0,5,1,4 };
	int b[4][3] = { { 0,3,6 },{ 0,3,6 } , { 8,5,2 }, { 0,3,6 } };
	turn(p, b, 3);
}
void Cube_Plane::F() {

	int p[4] = { 2,5,3,4 };
	int b[4][3] = { {0, 3, 6} , { 6,7,8 },{8, 5, 2} , { 2,1,0 } };
	turn(p, b, 0);
}
void Cube_Plane::B() {

	int p[4] = { 3,5,2,4 };
	int b[4][3] = { {0,3,6},{2,1,0},{8,5,2},{6,7,8} };
	turn(p, b, 1);
}
void Cube_Plane::U() {

	int p[4] = { 0,3,1,2 };
	int b[4][3] = { {6,7,8} ,{6,7,8},{6,7,8},{6,7,8} };
	turn(p, b, 4);
}
void Cube_Plane::D() {

	int p[4] = { 1,3,0,2 };
	int b[4][3] = { {0,1,2} ,{0,1,2},{0,1,2},{0,1,2} };
	turn(p, b, 5);
}
void Cube_Plane::XM() {
	int p[4] = { 1,2,0,3 };
	int b[4][3] = { {3,4,5} ,{3,4,5},{3,4,5},{3,4,5} };
	turn(p, b);

}
void Cube_Plane::YM() {

	int p[4] = { 2,5,3,4 };
	int b[4][3] = { {1,4,7} ,{3,4,5},{7,4,1},{5,4,3} };
	turn(p, b);
}
void Cube_Plane::ZM() {

	int p[4] = { 1,5,0,4 };
	int b[4][3] = { { 1,4,7 },{ 7,4,1 } , { 7,4,1 }, { 7,4,1 } };
	turn(p, b);
}

void Cube_Plane::RN() {

	int p[4] = { 0,5,1,4 };
	int b[4][3] = { { 2,5,8 },{2,5,8 } , { 6,3,0  }, { 2,5,8  } };
	turn(p, b, 2, false);
}
void Cube_Plane::LN() {

	int p[4] = { 0,4,1,5 };
	int b[4][3] = { { 0,3,6 },{ 0,3,6 } , { 8,5,2 }, { 0,3,6 } };
	turn(p, b, 3, false);
}
void Cube_Plane::FN() {

	int p[4] = { 2,4,3,5 };
	int b[4][3] = { {0, 3, 6} , { 2,1,0 },{8, 5, 2} , { 6,7,8 } };
	turn(p, b, 0, false);
}
void Cube_Plane::BN() {

	int p[4] = { 3,4,2,5 };
	int b[4][3] = { {0,3,6},{6,7,8},{8,5,2}, {2,1,0}};
	turn(p, b, 1, false);
}
void Cube_Plane::UN() {

	int p[4] = { 0,2,1,3 };
	int b[4][3] = { {6,7,8} ,{6,7,8},{6,7,8},{6,7,8} };
	turn(p, b, 4,false);
}
void Cube_Plane::DN() {

	int p[4] = { 1,2,0,3 };
	int b[4][3] = { {0,1,2} ,{0,1,2},{0,1,2},{0,1,2} };
	turn(p, b, 5,false);
}
void Cube_Plane::XMN() {
	int p[4] = { 1,3,0,2 };
	int b[4][3] = { {3,4,5} ,{3,4,5},{3,4,5},{3,4,5} };
	turn(p, b);
}
void Cube_Plane::YMN() {

	int p[4] = { 2,4,3,5 };
	int b[4][3] = { {1,4,7} ,{5,4,3},{7,4,1},{3,4,5} };
	turn(p, b);
}
void Cube_Plane::ZMN() {

	int p[4] = { 1,4,0,5 };
	int b[4][3] = { { 1,4,7 },{ 7,4,1 } , { 7,4,1 }, { 7,4,1 } };
	turn(p, b);
}

void Cube_Plane::turn(int p[4], int b[4][3], int pf,bool flag) {
	const int pnum = 4, bnum = 3;
	COLOR temp[3] = { cube_plane[p[3]][b[3][0]],cube_plane[p[3]][b[3][1]],cube_plane[p[3]][b[3][2]] };
	for (int i = pnum - 1; i > 0; --i) {
		cube_plane[p[(i) % pnum]][b[i][0]] = cube_plane[p[(i - 1) % pnum]][b[i - 1][0]];
		cube_plane[p[(i) % pnum]][b[i][1]] = cube_plane[p[(i - 1) % pnum]][b[i - 1][1]];
		cube_plane[p[(i) % pnum]][b[i][2]] = cube_plane[p[(i - 1) % pnum]][b[i - 1][2]];
	}
	cube_plane[p[0]][b[0][0]] = temp[0];
	cube_plane[p[0]][b[0][1]] = temp[1];
	cube_plane[p[0]][b[0][2]] = temp[2];
	if (pf!=-1&&flag) {
		std::vector<COLOR> temp;
		temp.push_back(cube_plane[pf][2]);
		temp.push_back(cube_plane[pf][5]);
		temp.push_back(cube_plane[pf][8]);
		temp.push_back(cube_plane[pf][1]);
		temp.push_back(cube_plane[pf][4]);
		temp.push_back(cube_plane[pf][7]);
		temp.push_back(cube_plane[pf][0]);
		temp.push_back(cube_plane[pf][3]);
		temp.push_back(cube_plane[pf][6]);
		cube_plane[pf] = temp;
	}
	else if (pf!=-1&&!flag) {
		std::vector<COLOR> temp;
		temp.push_back(cube_plane[pf][6]);
		temp.push_back(cube_plane[pf][3]);
		temp.push_back(cube_plane[pf][0]);
		temp.push_back(cube_plane[pf][7]);
		temp.push_back(cube_plane[pf][4]);
		temp.push_back(cube_plane[pf][1]);
		temp.push_back(cube_plane[pf][8]);
		temp.push_back(cube_plane[pf][5]);
		temp.push_back(cube_plane[pf][2]);
		cube_plane[pf] = temp;
	}
}

void Cube_Plane::transform(unsigned instruction) {
	int q = 1;
	for (int j = 0; j < instru_num; ++j) {
		switch ((q << j)&instruction) {
		case TURN_L:
			L();
			break;
		case TURN_R:
			R();
			break;
		case TURN_F:
			F();
			break;
		case TURN_B:
			B();
			break;
		case TURN_U:
			U();
			break;
		case TURN_D:
			D();
			break;
		case TURN_XM:
			XM();
			break;
		case TURN_YM:
			YM();
			break;
		case TURN_ZM:
			ZM();
			break;
		case TURN_LN:
			LN();
			break;
		case TURN_RN:
			RN();
			break;
		case TURN_FN:
			FN();
			break;
		case TURN_BN:
			BN();
			break;
		case TURN_UN:
			UN();
			break;
		case TURN_DN:
			DN();
			break;
		case TURN_XMN:
			XMN();
			break;
		case TURN_YMN:
			YMN();
			break;
		case TURN_ZMN:
			ZMN();
			break;
		}
	}
	/*std::ofstream out("./cube.txt",std::ios::app|std::ios::out);
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 6; ++j) {
			switch (cube_plane[i][j]) {
			case red:
				out << 0 << " ";
				break;
			case orange:
				out << 1 << " ";
				break;
			case green:
				out << 2 << " ";
				break;
			case blue:
				out << 3 << " ";
				break;
			case yellow:
				out << 4 << " ";
				break;
			case white:
				out << 5 << " ";
				break;
			}
		}
	}
	switch (instruction)
	{
	case turn_l :
		out << 1 << std::endl;
		break;
	case turn_ln :
		out << 0 << std::endl;
		break;
	case turn_r :
		out << 3 << std::endl;
		break;	
	case turn_rn :
		out << 2 << std::endl;
		break;
	case turn_f :
		out << 5 << std::endl;
		break;
	case turn_fn :
		out << 4 << std::endl;
		break;
	case turn_b :
		out << 7 << std::endl;
		break;
	case turn_bn :
		out << 6 << std::endl;
		break;
	case turn_u :
		out << 9 << std::endl;
		break;
	case turn_un :
		out << 8 << std::endl;
		break;
	case turn_d :
		out << 11 << std::endl;
		break;
	case turn_dn :
		out << 10 << std::endl;
		break;
	}
	out.close();*/
}

// functions in Model
void Model::Initialize(const Cube_Plane&cube_plane,int zv, double *rv, int *tv ) {
	set_plane(cube_plane);
	if (zv != 0) {
		zoom(zv);
	}
	if (rv) {
		rotate(0, rv[0]);
		rotate(1, rv[1]);
		rotate(2, rv[2]);
	}
	if (tv) {
		translation(tv[0], tv[1], tv[2]);
	}
	//gt.translation(plane, 50, 10, 0);
	zoom(0.05);
	rotate(1, 0.2);
	rotate(0, 0.2);
	rotate(2, 0.2);
}

Model::Model(const Model&m):plane(m.plane),gt(m.gt),blank(m.blank),zv(this->zv){
	memcpy(rv, m.rv, sizeof(rv));
	memcpy(tv, m.tv, sizeof(tv));
}

Model::Model(const Cube_Plane&cube_plane, int zv, double *rv, int *tv):zv(zv) {
		blank.add_light(Point(0, 100, 200));
		blank.add_light(Point(-100, 100, 200));
		if (rv) {
			memcpy(this->rv, rv, sizeof(this->rv));
		}
		else {
			memset(this->rv, 0, sizeof(this->rv));
		}
		if (tv) {
			memcpy(this->tv, tv, sizeof(this->tv));
		}
		else {
			memset(this->tv, 0, sizeof(this->tv));
		}
		Initialize(cube_plane,zv,rv,tv);
}
Model Model::operator  = (const Model& dm) {
	blank = dm.blank;
	gt = dm.gt;
	plane = dm.plane;
	zv = dm.zv;
	memcpy(rv, dm.rv, sizeof(rv));
	memcpy(tv, dm.tv, sizeof(tv));
	return *this;
}
void Model::set_plane(const Cube_Plane&cube_plane) {
	for (int i = 0; i < cube_plane.size(); ++i) {
		for (int j = 0; j < cube_plane[i].size(); ++j) {
			plane.push_back(Plane(CUBE_PLANE[i][j],4,cube_plane[i][j]));
		}
	}
}

void Model::rotate(int axis, double angle) {
	rv[axis] += angle;
	gt.rotate(plane, axis, angle);
}

void Model::zoom(double size) {
	zv *= size;
	gt.zoom(plane, size);
}

void Model::translation(int dx, int dy, int dz) {
	dx += dx;
	dy += dy;
	dz += dz;
	gt.translation(plane, dx, dy, dz);
}

std::vector<std::vector<COLOR>> Model::transform(unsigned instruction, double angle) {
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	std::vector<std::vector<COLOR>>res;
		int q = 1;
		for (int j = 0; j < instru_num; ++j) {
			switch ((q << j)&instruction) {
			case TURN_L:
				turn((&Model::L), angle);
				break;
			case TURN_R:
				turn((&Model::R), angle);
				break;
			case TURN_F:
				turn((&Model::F), angle);
				break;
			case TURN_B:
				turn((&Model::B), angle);
				break;
			case TURN_U:
				turn((&Model::U), angle);
				break;
			case TURN_D:
				turn((&Model::D), angle);
				break;
			case TURN_XM:
				turn((&Model::XM), angle);
				break;
			case TURN_YM:		
				turn((&Model::YM), angle);
				break;
			case TURN_ZM:
				turn((&Model::ZM), angle);
				break;
			case TURN_LN:
				turn((&Model::LN), angle);
				break;
			case TURN_RN:
				turn((&Model::RN), angle);
				break;
			case TURN_FN:
				turn((&Model::FN), angle);
				break;
			case TURN_BN:
				turn((&Model::BN), angle);
				break;
			case TURN_UN:
				turn((&Model::UN), angle);
				break;
			case TURN_DN:
				turn((&Model::DN), angle);
				break;
			case TURN_XMN:
				turn((&Model::XMN), angle);
				break;
			case TURN_YMN:
				turn((&Model::YMN), angle);
				break;
			case TURN_ZMN:
				turn((&Model::ZMN), angle);
				break;
			}
		}	

	blank.blank(res, plane, 500, 500);
	//std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	//std::cout << (std::chrono::duration_cast<std::chrono::duration<double>>(end - start)).count() << std::endl;
	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	//std::cout << (std::chrono::duration_cast<std::chrono::duration<double>>(end - start)).count() << std::endl;
	return res;
}

void Model::R(Double angle) {
	turn(RTURN,LRFBUD_TURN_NUM, -angle);
}
void Model::L(Double angle) {
	turn(LTURN, LRFBUD_TURN_NUM, -angle);
}
void Model::F(Double angle) {
	turn(FTURN, LRFBUD_TURN_NUM, -angle);
}
void Model::B(Double angle) {
	turn(BTURN, LRFBUD_TURN_NUM, -angle);
}
void Model::U(Double angle) {
	turn(UTURN, LRFBUD_TURN_NUM, -angle);
}
void Model::D(Double angle) {
	turn(DTURN, LRFBUD_TURN_NUM, -angle);
}
void Model::XM(Double angle) {
	turn(XMTURN, MTURN_NUM, -angle);
}
void Model::YM(Double angle) {
	turn(YMTURN, MTURN_NUM, -angle);
}
void Model::ZM(Double angle) {
	turn(ZMTURN, MTURN_NUM, angle);
}
void Model::RN(Double angle) {
	turn(RTURN, LRFBUD_TURN_NUM, angle);
}
void Model::LN(Double angle) {
	turn(LTURN, LRFBUD_TURN_NUM, angle);
}
void Model::FN(Double angle) {
	turn(FTURN, LRFBUD_TURN_NUM, angle);
}
void Model::BN(Double angle) {
	turn(BTURN, LRFBUD_TURN_NUM, angle);
}
void Model::UN(Double angle) {
	turn(UTURN, LRFBUD_TURN_NUM, angle);
}
void Model::DN(Double angle) {
	turn(DTURN, LRFBUD_TURN_NUM, angle);
}
void Model::XMN(Double angle) {
	turn(XMTURN, MTURN_NUM, angle);
}
void Model::YMN(Double angle) {
	turn(YMTURN, MTURN_NUM, angle);
}
void Model::ZMN(Double angle) {
	turn(ZMTURN, MTURN_NUM, -angle);
}
void Model::turn(void(Model::*t)(Double),double angle) {
	//std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	(this->*t)(angle);
	//std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	//int seconds = (std::chrono::duration_cast<std::chrono::duration<int, std::ratio<1, 1000>>>(end - start)).count();
	//seconds -= time_span;
	//seconds = std::max(seconds, 0);
	//std::this_thread::sleep_for(std::chrono::milliseconds(seconds));
}
void Model::turn(const int* TURN,int TURN_NUM,double angle) {
	const int n = 4;
	// make it parallel to plane XOY and rotate angle
	double x = plane[TURN[TURN_NUM]].get_A() * 1000, y = plane[TURN[TURN_NUM]].get_B() * 1000, z = plane[TURN[TURN_NUM]].get_C() * 1000;
	double r = sqrt(x*x + y * y + z * z);
	double a = x / r, b = y / r, c = z / r;
	double sin_afa = b / sqrt(a*a + b * b), cos_afa = a / sqrt(a*a + b * b);
	double sin_gama = sqrt(a*a + b * b), cos_gama = c;
	std::vector<std::vector<double>> matric;
	for (int i = 0; i < n; ++i) {
		std::vector<double> temp;
		for (int j = 0; j < n; ++j) {
			if (i == j) {
				temp.push_back(1);
			}
			else temp.push_back(0);
		}
		matric.push_back(temp);
	}
	matric[0][0] = cos_afa;
	matric[0][1] = -sin_afa;
	matric[1][0] = sin_afa;
	matric[1][1] = cos_afa;
	for (int i = 0; i < TURN_NUM; ++i) {
		gt.transform(plane[TURN[i]], matric);
	}


	matric.clear();
	for (int i = 0; i < n; ++i) {
		std::vector<double> temp;
		for (int j = 0; j < n; ++j) {
			if (i == j) {
				temp.push_back(1);
			}
			else temp.push_back(0);
		}
		matric.push_back(temp);
	}
	matric[0][0] = cos_gama;
	matric[0][2] = sin_gama;
	matric[2][0] = -sin_gama;
	matric[2][2] = cos_gama;
	for (int i = 0; i < TURN_NUM; ++i) {
		gt.transform(plane[TURN[i]], matric);
	}


	for (int i = 0; i < TURN_NUM; ++i) {
		gt.rotate(plane[TURN[i]], 2, angle);
	}

	// rotate back into original sample 

	matric.clear();
	for (int i = 0; i < n; ++i) {
		std::vector<double> temp;
		for (int j = 0; j < n; ++j) {
			if (i == j) {
				temp.push_back(1);
			}
			else temp.push_back(0);
		}
		matric.push_back(temp);
	}
	matric[0][0] = cos_gama;
	matric[0][2] = -sin_gama;
	matric[2][0] = sin_gama;
	matric[2][2] = cos_gama;
	for (int i = 0; i < TURN_NUM; ++i) {
		gt.transform(plane[TURN[i]], matric);
	}


	matric.clear();
	for (int i = 0; i < n; ++i) {
		std::vector<double> temp;
		for (int j = 0; j < n; ++j) {
			if (i == j) {
				temp.push_back(1);
			}
			else temp.push_back(0);
		}
		matric.push_back(temp);
	}
	matric[0][0] = cos_afa;
	matric[0][1] = sin_afa;
	matric[1][0] = -sin_afa;
	matric[1][1] = cos_afa;
	for (int i = 0; i < TURN_NUM; ++i) {
		gt.transform(plane[TURN[i]], matric);
	}
}

// functions in Cub
void Cube::L(){
	turn(TURN_L);
}
void Cube::R(){
	turn(TURN_R);
}
void Cube::F(){
	turn(TURN_F);
}
void Cube::B(){
	turn(TURN_B);
}
void Cube::U(){
	turn(TURN_U);
}
void Cube::D(){
	turn(TURN_D);
}
void Cube::XM(){
	turn(TURN_XM);
}
void Cube::YM(){
	turn(TURN_YM);
}
void Cube::ZM(){
	turn(TURN_ZM);
}
void Cube::LN() {
	turn(TURN_LN);
}
void Cube::RN() {
	turn(TURN_RN);
}
void Cube::FN() {
	turn(TURN_FN);
}
void Cube::BN() {
	turn(TURN_BN);
}
void Cube::UN() {
	turn(TURN_UN);
}
void Cube::DN() {
	turn(TURN_DN);
}
void Cube::XMN() {
	turn(TURN_XMN);
}
void Cube::YMN() {
	turn(TURN_YMN);
}
void Cube::ZMN() {
	turn(TURN_ZMN);
}
void Cube::Message_loop() {
	std::queue<unsigned> instruction;
	instruction.push(SHOW);
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	while (true) {
		while (!have_message) {
			std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
			int duration = (std::chrono::duration_cast<std::chrono::duration<int, std::ratio<60, 1>>>(end - start)).count();
			if (duration >= 3)
				return;
			std::this_thread::yield();
			cv::namedWindow("zero");
			cv::imshow("zero", image);
			cv::waitKey(time_span);
		}
		std::unique_lock<std::mutex> finisn_lck(finish_mtx);
		std::unique_lock<std::mutex> lck(mtx);

		while (!message_queue.empty())
		{
			instruction.push(message_queue.front());
			message_queue.pop();
		}
		have_message = false;
		lck.unlock();
		if (instruction.empty())
			break;
		while(!instruction.empty())
		{
			if (instruction.front() == 0)
				return;
			std::unique_lock<std::mutex> cube_lck(cube_mtx);
			turn(instruction.front(),zv,rv,tv);
			instruction.pop();
		}
		start = std::chrono::system_clock::now();
		finish_modify.notify_all();
	}
}
void Cube::add_message(unsigned instruction, int zv, double *rv, int*tv) {
	std::unique_lock<std::mutex> lck(mtx);
	message_queue.push(instruction);
	if (0 != zv)
		this->zv *= zv;
	if (rv)
	{
		this->rv[0] = fmod(this->rv[0] + rv[0], 2 * PI);
		this->rv[1] = fmod(this->rv[1] + rv[1], 2 * PI);
		this->rv[2] = fmod(this->rv[2] + rv[2], 2 * PI);
	}
	if (tv)
	{
		this->tv[0] = tv[0];
		this->tv[1] = tv[1];
		this->tv[2] = tv[2];
	}
	have_message = true;
}

void Cube::turn(unsigned instruction, int zv, double *rv, int*tv) {
	Model model(cube_plane);
	cube_plane.transform(instruction);
	if (zv != 0) {
		model.zoom(zv);
	}
	if (rv) {
		model.rotate(0, rv[0]);
		model.rotate(1, rv[1]);
		model.rotate(2, rv[2]);
	}
	if (tv) {
		model.translation(tv[0], tv[1], tv[2]);
	}
	if (SHOW == instruction) {
		std::vector<std::vector<COLOR>> res = model.transform(instruction,0);
		for (int j = 0; j < 500; ++j) {
			for (int k = 0; k < 500; ++k) {
				uchar* p = image.ptr(j, k);
				p[0] = ::B(res[499 - j][k]);
				p[1] = ::G(res[499 - j][k]);
				p[2] = ::R(res[499 - j][k]);
			}
		}
		cv::namedWindow("zero");
		cv::setMouseCallback("zero", on_mouse, this);
		cv::imshow("zero", image);
		cv::waitKey(time_span);
		return;
	}
	for (Double i = 0.1; i <= 0.5; i += 0.1) {
		Model temp = model;
	
		//cv::Mat image(500, 500, CV_8UC3, CV_RGB(0, 0, 0));
		std::vector<std::vector<COLOR>> res=temp.transform(instruction,i*PI);
		for (int j = 0; j < 500; ++j) {
			for (int k = 0; k < 500; ++k) {
				uchar* p = image.ptr(j, k);
				p[0] = ::B(res[499 - j][k]);
				p[1] = ::G(res[499 - j][k]);
				p[2] = ::R(res[499 - j][k]);
			}
		}
		cv::namedWindow("zero");
		cv::setMouseCallback("zero", on_mouse, this);
		cv::imshow("zero", image);
		cv::waitKey(time_span);
	}
}

std::vector<COLOR>& Cube::operator [](int i) {
	std::unique_lock<std::mutex> lck(cube_mtx);
	return cube_plane[i];
}

// basis function
int GCD(int a, int b) {
	while (a%b) {
		int t = a % b;
		a = b;
		b = t;
	}
	return b;
}
int LCM(int a, int b) {
	int gcd = GCD(a, b);
	a = a / gcd;
	b = b / gcd;
	return a * b*gcd;
}

void CV_CDECL  on_mouse(int event, int x, int y, int flags, void* userdata) {
	if (CV_EVENT_LBUTTONDOWN == event) {
		start = cv::Point(x, y);
		ms = std::chrono::system_clock::now();
	}
	else if (CV_EVENT_FLAG_LBUTTON == flags) {
	
		std::chrono::system_clock::time_point me = std::chrono::system_clock::now();
		int duration = (std::chrono::duration_cast<std::chrono::duration<int, std::ratio<1, 1000>>>(me - ms)).count();
		if (duration < 20) {
			return;// avoid refreshing frequently
		}
		int x0 = start.x;
		int y0 = start.y;
		int dx = x-x0;
		int dy = y-y0;
		double disx = dx * dx;
		double disy = dy * dy;
		double roundx = disx / 1000;
		double roundy = disy / 1000;
		if (dx < 0)
			roundx = -roundx;
		if (dy < 0)
			roundy = -roundy;
		double rv[3];
		rv[0] = -roundy;
		rv[1] = roundx;
		rv[2] = 0;
		//std::cout << roundx << std::endl;
		((Cube*)userdata)->add_message(SHOW, 0, rv);
		start = cv::Point(x, y);
		ms = std::chrono::system_clock::now();
	}
}