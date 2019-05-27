#pragma once

#include "pch.h"


//the point axis value type
typedef int Int;
typedef double Double;// the type of the element of equation

const int WIDTH = 500;
const int HEIGHT = 667;
const int time_span = 1;

// Color value and equation
typedef unsigned int COLOR;
#define RGB(r,g,b) ((COLOR)(r)*65536+(COLOR)(g)*256+(COLOR)(b))
uchar R(COLOR color);
uchar G(COLOR color);
uchar B(COLOR color);
COLOR light(COLOR color, Double I);
#define LightPink			0xFFB6C1
#define Pink				0xFFC0CB
#define Crimson				0xDC143C
#define LavenderBlush		0xFFF0F5
#define PaleVioletRed		0xDB7093
#define HotPink				0xFF69B4
#define DeepPink			0xFF1493
#define MediumVioletRed		0xC71585
#define Orchid				0xDA70D6
#define Thistle				0xD8BFD8
#define plum				0xDDA0DD
#define Violet				0xEE82EE
#define Magenta				0xFF00FF
#define Fuchsia				0xFF00FF
#define DarkMagenta			0x8B008B
#define Purple				0x800080
#define MediumOrchid		0xBA55D3
#define DarkVoilet			0x9400D3
#define DarkOrchid			0x9932CC
#define Indigo				0x4B0082
#define BlueViolet			0x8A2BE2
#define MediumPurple		0x9370DB
#define MediumSlateBlue		0x7B68EE
#define SlateBlue			0x6A5ACD
#define DarkSlateBlue		0x483D8B
#define Lavender			0xE6E6FA
#define GhostWhite			0xF8F8FF
#define Blue				0x0000FF
#define MediumBlue			0x0000CD
#define MidnightBlue		0x191970
#define DarkBlue			0x00008B
#define Navy				0x000080
#define RoyalBlue			0x4169E1
#define CornflowerBlue		0x6495ED
#define LightSteelBlue		0xB0C4DE
#define LightSlateGray		0x778899
#define SlateGray			0x708090
#define DoderBlue			0x1E90FF
#define AliceBlue			0xF0F8FF
#define SteelBlue			0x4682B4
#define LightSkyBlue		0x87CEFA
#define SkyBlue				0x87CEEB
#define DeepSkyBlue			0x00BFFF
#define LightBLue			0xADD8E6
#define PowDerBlue			0xB0E0E6
#define CadetBlue			0x5F9EA0
#define Azure				0xF0FFFF
#define LightCyan			0xE1FFFF
#define PaleTurquoise		0xAFEEEE
#define Cyan				0x00FFFF
#define Aqua				0x00FFFF
#define DarkTurquoise		0x00CED1
#define DarkSlateGray		0x2F4F4F
#define DarkCyan			0x008B8B
#define Teal				0x008080
#define MediumTurquoise		0x48D1CC
#define LightSeaGreen		0x20B2AA
#define Turquoise			0x40E0D0
#define Auqamarin			0x7FFFAA
#define MediumAquamarine	0x00FA9A
#define MediumSpringGreen	0x00FF7F
#define MintCream			0xF5FFFA
#define SpringGreen			0x3CB371
#define SeaGreen			0x2E8B57
#define Honeydew			0xF0FFF0
#define LightGreen			0x90EE90
#define PaleGreen			0x98FB98
#define DarkSeaGreen		0x8FBC8F
#define LimeGreen			0x32CD32
#define Lime				0x00FF00
#define ForestGreen			0x228B22
#define Green				0x008000
#define DarkGreen			0x006400
#define Chartreuse			0x7FFF00
#define LawnGreen			0x7CFC00
#define GreenYellow			0xADFF2F
#define OliveDrab			0x556B2F
#define Beige				0xF5F5DC
#define LightGoldenrodYellow	0xFAFAD2
#define Ivory				0xFFFFF0
#define LightYellow			0xFFFFE0
#define Yellow				0xFFFF00
#define Olive				0x808000
#define DarkKhaki			0xBDB76B
#define LemonChiffon		0xFFFACD
#define PaleGodenrod		0xEEE8AA
#define Khaki				0xF0E68C
#define Gold				0xFFD700
#define Cornislk			0xFFF8DC
#define GoldEnrod			0xDAA520
#define FloralWhite			0xFFFAF0
#define OldLace				0xFDF5E6
#define Wheat				0xF5DEB3
#define Moccasin			0xFFE4B5
#define Orange				0xFFA500
#define PapayaWhip			0xFFEFD5
#define BlanchedAlmond		0xFFEBCD
#define NavajoWhite			0xFFDEAD
#define AntiqueWhite		0xFAEBD7
#define Tan					0xD2B48C
#define BrulyWood			0xDEB887
#define Bisque				0xFFE4C4
#define DarkOrange			0xFF8C00
#define Linen				0xFAF0E6
#define Peru				0xCD853F
#define PeachPuff			0xFFDAB9
#define SandyBrown			0xF4A460
#define Chocolate			0xD2691E
#define SaddleBrown			0x8B4513
#define SeaShell			0xFFF5EE
#define Sienna				0xA0522D
#define LightSalmon			0xFFA07A
#define Coral				0xFF7F50
#define OrangeRed			0xFF4500
#define DarkSalmon			0xE9967A
#define Tomato				0xFF6347
#define MistyRose			0xFFE4E1
#define Salmon				0xFA8072
#define Snow				0xFFFAFA
#define LightCoral			0xF08080
#define RosyBrown			0xBC8F8F
#define IndianRed			0xCD5C5C
#define Red					0xFF0000
#define Brown				0xA52A2A
#define FireBrick			0xB22222
#define DarkRed				0x8B0000
#define Maroon				0x800000
#define White				0xFFFFFF
#define WhiteSmoke			0xF5F5F5
#define Gainsboro			0xDCDCDC
#define LightGrey			0xD3D3D3
#define Silver				0xC0C0C0
#define DarkGray			0xA9A9A9
#define Gray				0x808080
#define DimGray				0x696969
#define Black				0x000000

// 3 dimension point
struct Point3d {
	Point3d() :x(0), y(0), z(0) {}
	Point3d(Int _x, Int _y, Int _z) :x(_x), y(_y), z(_z) {}
	Int x, y, z;
};

typedef struct Point3d Point;
bool Equal_slope(const Point3d&x, const Point3d& y, const Point3d& z);//judge three point is not in one straight line

//represent a plane in 3 dimension space
class Plane3d {
public:
	Plane3d():p(NULL),num(0),color(0) {}
	Plane3d(const Plane3d &_plane):p(NULL) {
		set(_plane.p, _plane.num,_plane.color);
		A = _plane.A;
		B = _plane.B;
		C = _plane.C;
		D = _plane.D;
	}
	Plane3d(const Point *_p, int num,COLOR _color) :p(NULL) {
		set(_p, num,_color);
		get_equation();
	}
	const Plane3d& operator =(const Plane3d &_plane){
		set(_plane.p, _plane.num,_plane.color);
		A = _plane.A;
		B = _plane.B;
		C = _plane.C;
		D = _plane.D;
		return *this;
	}
	void set(const Point *_p, int _num,COLOR _color) {
		clear();
		p = new Point[_num];
		num = _num;
		color = _color;
		memcpy(p, _p, sizeof(Point)*_num);
	}
	void clear() {
		if(p)
			delete p;
		p = NULL;
		num = 0;
		A = B = C = D = 0;
	}
	~Plane3d() {
		delete p;
	}
	Point& operator[](int i) {
		return p[i];
	}
	const Point& operator[](int i) const{
		return p[i];
	}
	int get_num() const {
		return num;
	}
	Double get_A() const {
		return A;
	}
	Double get_B() const {
		return B;
	}
	Double get_C() const {
		return C;
	}
	Double get_D() const {
		return D;
	}
	COLOR get_color() const{
		return color;
	}
	Point* get_point() const {
		return p;
	}
	void get_equation();
private:

	Point *p;// the vertex of the plane
	int num; // the number of vertex
	Double A, B, C, D;
	COLOR color;
};

typedef Plane3d Plane;



// interface of projection transformation

class Projection {
public:
	Projection() {}
private:
};

// interface of blanking transformation

class Illumination {
public:
	Illumination(){}
	Illumination(const Point&_view_point,Double _ka=0.5,Double _kd=0.1,Double _ks=0.7,Double _Ia=0.2)
		:view_point(_view_point),ka(_ka),kd(_kd),ks(_ks),Ia(_Ia) {
	}
	void set(const Point&_view_point, const std::vector<Point>&_light, Double _ka = 0.5, Double _kd = 0.1, Double _ks = 0.7, Double _Ia = 0.2) {
		view_point = _view_point;
		light = _light;
		ks = _ka;
		kd = _kd;
		ks = _ks;
		Ia = _Ia;
	}
	void add_light(const Point&_light) {
		light.push_back(_light);
	}
	Double illumination(const Plane&plane, const Point&point);
	Double illumination(const Plane&plane, const Point&point,const Point& light);
private:
	Double vector_multipy(Double *a, Double *b, int num = 3);
	Double f(Double d);
	template <typename T>
	T fast_power(T a, int b);
	Double get_S0(Double Z0);
	Point view_point;
	std::vector<Point> light;
	Double ka, kd, ks;//ka environmental reflection coefficient, kd diffuse reflection coefficient, ks specular reflection coefficient
	Double Ia;// ambient intensity 
};

class Blanking {
public:
	Blanking() :illumination(Point(0,0,200)) {}
	Blanking(const Illumination& _illumination) :illumination(_illumination){}
	void blank(std::vector<std::vector<COLOR>>&res,const std::vector<Plane>& plane, Int width, Int height);
	void add_light(const Point&point) {
		illumination.add_light(point);
	}
private:

	// store the information of the Polygon
	class Polygon {
	public:
		Polygon():A(0), B(0), C(0), D(0), color(0), vmax(0),vmin(0), Pl(0) {}
		Polygon(Double _A, Double _B, Double _C, Double _D, COLOR _color, Int _vmax,Int _vmin, int _Pl) :
			A(_A), B(_B), C(_C), D(_D), color(_color), vmax(_vmax), vmin(_vmin), Pl(_Pl){}
		void set(Double _A, Double _B, Double _C, Double _D, COLOR _color, Int _vmax, Int _vmin, int _Pl) {
			A=_A;
			B=_B;
			C=_C;
			D=_D;
			color=_color;
			vmax=_vmax;
			vmin = _vmin;
			Pl = _Pl;
		}
		Polygon(const Plane&p,int _Pl){
			set(p,_Pl);
		}
		void set(const Plane&p,int _Pl);
		Double A, B, C, D;
		COLOR color;
		Int vmax;
		Int vmin;
		int Pl;
	};
	// store the Polygon in different v
	class PT {
	public:
		PT() {
		}
		PT(std::vector<Polygon>& p) {
			for (std::vector<Polygon>::size_type i = 0; i < p.size(); ++i)
				add(&p[i]);
		}
		void add(Polygon *p) {
			pt[p->vmin].push_back(p);
		}
		~PT() {
		}
		std::list<Polygon*>& get(Int v) {
			if(pt.find(v)!=pt.end())
				return pt[v];
			else return null;
		}
	private:
		static std::list<Polygon*> null;
		std::map<Int,std::list<Polygon*>> pt;
	};

	// the active Polygon
	class APL {
	public:
		APL(PT&_pt) :pt(_pt) {}
		std::vector<std::vector<Int>> update(Int v) {
			std::vector<std::vector<Int>> res;
			res.push_back(add(v));
			res.push_back(drop(v));
			return res;
		}
		std::list<Polygon*>& get() {
			return apl;
		}
	private:
		std::vector<Int> add(Int v);
		std::vector<Int> drop(Int v);
		std::list<Polygon*> apl;
		PT&pt;
	};

	class Edge {
	public:
		Edge() {}
		Edge(Int _vmax, Double _delta_u, Double _u, Double _n) :
			vmax(_vmax), delta_u(_delta_u), u(_u), n(_n){}
		Edge(const Point&b, const Point&e) {
			vmax = std::max(b.y, e.y);
			vmin = std::min(b.y, e.y);
			delta_u = (Double)(b.x - e.x) / (b.y - e.y);
			if (b.y < e.y)
			{
				u = b.x;
				n = b.z;
			}
			else {
				u = e.x;
				n = e.z;
			}
		}
		Int vmax;
		Int vmin;
		Double delta_u;
		Double u;
		Double n;
	};
	// the edge of one polygon
	class ET {
	public:
		ET():maxv(INF),minv(INF) {}
		ET(const Plane&plane) :maxv(INF), minv(INF) {set(plane); }
		std::list<Edge>& get(Int v) {
			if(et.find(v)!=et.end())
				return et[v];
			else return null;
		}
		std::map<Int,Int> set(const Plane&plane);
		~ET() {
		}
		int get_num() {
			return maxv - minv + 1;
		}
		void clear() {
			et.clear();
		}
	private:
		static std::list<Edge> null;
		std::map<Int,std::list<Edge>> et;
		Int maxv;
		Int minv;
	};
	// the edge pair
	class EP {
	public:
		EP(Edge _l,Edge _r,const Polygon *p) :l(_l),r(_r) {
			delta_nu = -p->A / p->C;
			delta_nv = -p->B / p->C;
		}
		void set_left(Edge _l) {
			l = _l;
		}
		void set_right(Edge _r) {
			r = _r;
		}
		Int begin() {
			return l.u;
		}
		Int end() {
			return r.u;
		}
		Double get_delta_nu() {
			return delta_nu;
		}
		Int get_Z() {
			return l.n;
		}
		void update();
		Edge l, r;
		Double delta_nu, delta_nv;
	};
	// the active edge pair list of one Polygon
	class EPL {
	public:
		EPL() :et(NULL), num(0), Pl(0), p(NULL) {};
		EPL(ET*_et,int _num,Int _Pl,const Polygon*_p) :et(_et),num(_num),Pl(_Pl),p(_p) {}
		void update(Int v);
		void set_ET(ET* _et) { et = _et; }
		void set_Polygon(const Polygon*_p) { p = _p; }
		void clear() { epl.clear(); et = NULL; }
		const std::list<EP>& get_EP() const{
			return epl;
		}
	private:
		std::list<EP> epl;
		ET *et;
		int num;
		const Polygon *p;
		Int Pl;
	};
private://  variable
	Illumination illumination;
};

class Geometric_transformation {
public:
	void rotate(std::vector<Plane>& plane, int axis, double angle);
	void zoom(std::vector<Plane>& plane, double size);
	void translation(std::vector<Plane>& plane, int dx, int dy,int dz);
	void rotate(Plane& plane, int axis, double angle);
	void zoom(Plane& plane, double size);
	void translation(Plane& plane, int dx, int dy,int dz);
	void rotate(Point& point, int axis, double angle);
	void zoom(Point& point, double size);
	void translation(Point& point, int dx, int dy, int dz);
	void transform(std::vector<Plane>& plane, const std::vector<std::vector<double>>& matric);
	void transform(Plane& plane, const std::vector<std::vector<double>>& matric);
	void transform(Point& point, const std::vector<std::vector<double>>& matric);
private:
	std::vector<std::vector<double>> get_rotate_matric(int axis, double angle);
	std::vector<std::vector<double>> get_translation_matric(int dx, int dy, int dz);
	std::vector<std::vector<std::vector<double>>>get_zoom_matric(double size);
	void multiply(Point&point, const std::vector<std::vector<double>>&matric);
};

const Point red0[4] = { Point(-3,-3,3),Point(-1,-3,3),Point(-1,-1,3),Point(-3,-1,3) };
const Point red1[4] = { Point(-1,-3,3),Point(1,-3,3), Point(1,-1,3), Point(-1,-1,3) };
const Point red2[4] = { Point(1,-3,3),Point(3,-3,3),Point(3,-1,3),Point(1,-1,3) };
const Point red3[4] = { Point(-3,-1,3),Point(-1,-1,3),Point(-1,1,3),Point(-3,1,3) };
const Point red4[4] = { Point(-1,-1,3),Point(1,-1,3),Point(1,1,3),Point(-1,1,3) };
const Point red5[4] = { Point(1,-1,3),Point(3,-1,3),Point(3,1,3),Point(1,1,3) };
const Point red6[4] = { Point(-3,1,3),Point(-1,1,3),Point(-1,3,3),Point(-3,3,3) };
const Point red7[4] = { Point(-1,1,3),Point(1,1,3),Point(1,3,3),Point(-1,3,3) };
const Point red8[4] = { Point(1,1,3),Point(3,1,3),Point(3,3,3),Point(1,3,3) };

const Point blue0[4] = { Point(-3,-3,-3),Point(-3,-3,-1),Point(-3,-1,-1),Point(-3,-1,-3) };
const Point blue1[4] = { Point(-3,-3,-1),Point(-3,-3,1),Point(-3,-1,1),Point(-3,-1,-1) };
const Point blue2[4] = { Point(-3,-3,1),Point(-3,-3,3),Point(-3,-1,3),Point(-3,-1,1) };
const Point blue3[4] = { Point(-3,-1,-3),Point(-3,-1,-1),Point(-3,1,-1),Point(-3,1,-3) };
const Point blue4[4] = { Point(-3,-1,-1),Point(-3,-1,1),Point(-3,1,1),Point(-3,1,-1) };
const Point blue5[4] = { Point(-3,-1,1),Point(-3,-1,3),Point(-3,1,3),Point(-3,1,1) };
const Point blue6[4] = { Point(-3,1,-3),Point(-3,1,-1),Point(-3,3,-1),Point(-3,3,-3) };
const Point blue7[4] = { Point(-3,1,-1),Point(-3,1,1),Point(-3,3,1),Point(-3,3,-1) };
const Point blue8[4] = { Point(-3,1,1),Point(-3,1,3),Point(-3,3,3),Point(-3,3,1) };


const Point white0[4] = { Point(-3,-3,-3),Point(-1,-3,-3),Point(-1,-3,-1),Point(-3,-3,-1) };
const Point white1[4] = { Point(-1,-3,-3),Point(1,-3,-3),Point(1,-3,-1),Point(-1,-3,-1) };
const Point white2[4] = { Point(1,-3,-3),Point(3,-3,-3),Point(3,-3,-1),Point(1,-3,-1) };
const Point white3[4] = { Point(-3,-3,-1),Point(-1,-3,-1),Point(-1,-3,1),Point(-3,-3,1) };
const Point white4[4] = { Point(-1,-3,-1),Point(1,-3,-1),Point(1,-3,1),Point(-1,-3,1) };
const Point white5[4] = { Point(1,-3,-1),Point(3,-3,-1),Point(3,-3,1),Point(1,-3,1) };
const Point white6[4] = { Point(-3,-3,1),Point(-1,-3,1),Point(-1,-3,3),Point(-3,-3,3) };
const Point white7[4] = { Point(-1,-3,1),Point(1,-3,1),Point(1,-3,3),Point(-1,-3,3) };
const Point white8[4] = { Point(1,-3,1),Point(3,-3,1),Point(3,-3,3),Point(1,-3,3) };

const Point orange0[4] = { Point(1,-3,-3),Point(3,-3,-3),Point(3,-1,-3),Point(1,-1,-3) };
const Point orange1[4] = { Point(-1,-3,-3),Point(1,-3,-3), Point(1,-1,-3), Point(-1,-1,-3) };
const Point orange2[4] = { Point(-3,-3,-3),Point(-1,-3,-3),Point(-1,-1,-3),Point(-3,-1,-3) };
const Point orange3[4] = { Point(1,-1,-3),Point(3,-1,-3),Point(3,1,-3),Point(1,1,-3) };
const Point orange4[4] = { Point(-1,-1,-3),Point(1,-1,-3),Point(1,1,-3),Point(-1,1,-3) };
const Point orange5[4] = { Point(-3,-1,-3),Point(-1,-1,-3),Point(-1,1,-3),Point(-3,1,-3) };
const Point orange6[4] = { Point(1,1,-3),Point(3,1,-3),Point(3,3,-3),Point(1,3,-3) };
const Point orange7[4] = { Point(-1,1,-3),Point(1,1,-3),Point(1,3,-3),Point(-1,3,-3) };
const Point orange8[4] = { Point(-3,1,-3),Point(-1,1,-3),Point(-1,3,-3),Point(-3,3,-3) };

const Point green0[4] = { Point(3,-3,1),Point(3,-3,3),Point(3,-1,3),Point(3,-1,1) };
const Point green1[4] = { Point(3,-3,-1),Point(3,-3,1),Point(3,-1,1),Point(3,-1,-1) };
const Point green2[4] = { Point(3,-3,-3),Point(3,-3,-1),Point(3,-1,-1),Point(3,-1,-3) };
const Point green3[4] = { Point(3,-1,1),Point(3,-1,3),Point(3,1,3),Point(3,1,1) };
const Point green4[4] = { Point(3,-1,-1),Point(3,-1,1),Point(3,1,1),Point(3,1,-1) };
const Point green5[4] = { Point(3,-1,-3),Point(3,-1,-1),Point(3,1,-1),Point(3,1,-3) };
const Point green6[4] = { Point(3,1,1),Point(3,1,3),Point(3,3,3),Point(3,3,1) };
const Point green7[4] = { Point(3,1,-1),Point(3,1,1),Point(3,3,1),Point(3,3,-1) };
const Point green8[4] = { Point(3,1,-3),Point(3,1,-1),Point(3,3,-1),Point(3,3,-3) };

const Point yellow0[4] = { Point(-3,3,1),Point(-1,3,1),Point(-1,3,3),Point(-3,3,3) };
const Point yellow1[4] = { Point(-1,3,1),Point(1,3,1),Point(1,3,3),Point(-1,3,3) };
const Point yellow2[4] = { Point(1,3,1),Point(3,3,1),Point(3,3,3),Point(1,3,3) };
const Point yellow3[4] = { Point(-3,3,-1),Point(-1,3,-1),Point(-1,3,1),Point(-3,3,1) };
const Point yellow4[4] = { Point(-1,3,-1),Point(1,3,-1),Point(1,3,1),Point(-1,3,1) };
const Point yellow5[4] = { Point(1,3,-1),Point(3,3,-1),Point(3,3,1),Point(1,3,1) };
const Point yellow6[4] = { Point(-3,3,-3),Point(-1,3,-3),Point(-1,3,-1),Point(-3,3,-1) };
const Point yellow7[4] = { Point(-1,3,-3),Point(1,3,-3),Point(1,3,-1),Point(-1,3,-1) };
const Point yellow8[4] = { Point(1,3,-3),Point(3,3,-3),Point(3,3,-1),Point(1,3,-1) };

const Point* const CUBE_PLANE[6][9] = { {red0,red1,red2,red3,red4,red5,red6,red7,red8},
{orange0,orange1,orange2,orange3,orange4,orange5,orange6,orange7,orange8},
{green0,green1,green2,green3,green4,green5,green6,green7,green8},
{blue0,blue1,blue2,blue3,blue4,blue5,blue6,blue7,blue8},
{yellow0,yellow1,yellow2,yellow3,yellow4,yellow5,yellow6,yellow7,yellow8},
{white0,white1,white2,white3,white4,white5,white6,white7,white8} };
const COLOR CUBE_COLOR[6] = { Red,Orange,Green,Blue,Yellow,White };

const int RTURN[22] = { 22,18,19,20,21,23,24,25,26,2,5,8,9,12,15,38,41,44,47,50,53,22 };
const int LTURN[22] = { 31,27,28,29,30,32,33,34,35,0,3,6,11,14,17,36,39,42,45,48,51,31 };
const int FTURN[22] = {0,1,2,3,4,5,6,7,8,18,21,24,29,32,35,36,37,38,51,52,53,4};
const int BTURN[22] = {9,10,11,12,13,14,15,16,17,20,23,26,27,30,33,42,43,44,45,46,47,13};
const int UTURN[22] = {36,37,38,39,40,41,42,43,44,6,7,8,15,16,17,24,25,26,33,34,35,40};
const int DTURN[22] = {45,46,47,48,49,50,51,52,53,0,1,2,9,10,11,18,19,20,27,28,29,49};
const int LRFBUD_TURN_NUM = 21;

const int XMTURN[13] = { 3,4,5,12,13,14,21,22,23,30,31,32,40 };
const int YMTURN[13] = {19,22,25,28,31,34,39,40,41,48,49,50,4};
const int ZMTURN[13] = {1,4,7,10,13,16,37,40,43,46,49,52,31};
const int MTURN_NUM = 12;

#define TURN_L 0x000001
#define TURN_LN 0x000002
#define TURN_R 0x000004
#define TURN_RN 0x000008
#define TURN_F 0x000010
#define TURN_FN 0x000020
#define TURN_B 0x000040
#define TURN_BN 0x000080
#define TURN_U 0x000100
#define TURN_UN 0x000200
#define TURN_D 0x000400
#define TURN_DN 0x000800
#define TURN_XM 0x001000
#define TURN_XMN 0x002000
#define TURN_YM 0x004000
#define TURN_YMN 0x008000
#define TURN_ZM 0x010000
#define TURN_ZMN 0x020000
#define QUIT 0x000000
#define SHOW 0x040000
#define DISORDER 0x080000
#define RESTORE 0x100000
const int instru_num = 18;

class Cube_Plane {
public:
	Cube_Plane();
	Cube_Plane(const Cube_Plane& c);
	Cube_Plane(const std::vector<std::vector<COLOR>>_cube_plane);
	std::vector<COLOR>& operator[](int i) {
		return cube_plane[i];
	}
	std::vector<int>::size_type size() {
		return cube_plane.size();
	}
	const std::vector<COLOR>& operator[](int i) const{
		return cube_plane[i];
	}
	const std::vector<int>::size_type size() const{
		return cube_plane.size();
	}
	void L();
	void R();
	void F();
	void B();
	void U();
	void D();
	void XM();
	void YM();
	void ZM();
	void LN();
	void RN();
	void FN();
	void BN();
	void UN();
	void DN();
	void XMN();
	void YMN();
	void ZMN();
	void transform(unsigned instruction);
private:
	void turn(int p[4], int b[4][3], int pf = -1, bool flag = true);
	std::vector<std::vector<COLOR>> cube_plane;// 0 is red, 1 is orange, 2 is green, 3 is blue, 4 is yellow, 5 is white, such as 01 means red plane and the 1st subplane
};


class Model {
public:
	Model(const Cube_Plane&cube_plane, int zv=0, double *rv = NULL, int *tv = NULL);
	Model(const Model&m);
	Model operator =(const Model& dm);
	std::vector<std::vector<COLOR>> transform(unsigned instruction, double angle);
	void rotate(int axis, double angle);
	void zoom(double size);
	void translation(int dx, int dy, int dz);
	void L(Double angle);
	void R(Double angle);
	void F(Double angle);
	void B(Double angle);
	void U(Double angle);
	void D(Double angle);
	void XM(Double angle);
	void YM(Double angle);
	void ZM(Double angle);
	void LN(Double angle);
	void RN(Double angle);
	void FN(Double angle);
	void BN(Double angle);
	void UN(Double angle);
	void DN(Double angle);
	void XMN(Double angle);
	void YMN(Double angle);
	void ZMN(Double angle);
private:
	void turn(void(Model::*t)(Double), double angle);
	void turn(const int *TURN,int TURN_NUM,double angle);
	void Initialize(const Cube_Plane&cube_plane,int zv=0,double *rv=NULL,int *tv=NULL);
	void set_plane(const Cube_Plane&cube_plane);
	std::vector<Plane> plane;
	Blanking blank;
	Geometric_transformation gt;
	int zv;
	double rv[3];
	int tv[3];
};

class Cube {
public:
	friend class Magic_Cube;
	Cube():image(HEIGHT, WIDTH, CV_8UC3, CV_RGB(0, 0, 0)),have_message(false),zv(0){
		//cv::namedWindow("zero");
		memset(rv, 0, sizeof(rv));
		memset(tv, 0, sizeof(tv));
		std::thread MESSAGE_QUEUE(&Cube::Message_loop, this);
		MESSAGE_QUEUE.detach();
		add_message(SHOW);
	}
	void L();
	void R();
	void F();
	void B();
	void U();
	void D();
	void XM();
	void YM();
	void ZM();
	void LN();
	void RN();
	void FN();
	void BN();
	void UN();
	void DN();
	void XMN();
	void YMN();
	void ZMN();
	void Message_loop();
	void add_message(unsigned instruction, int zv = 0, double *rv = NULL, int*tv = NULL);
	void turn(unsigned instruction, int zv = 0, double *rv = NULL, int*tv = NULL);
	std::vector<COLOR>& operator [](int i);
private:// variables
	Cube_Plane cube_plane;
	cv::Mat image;
	std::queue<unsigned> message_queue;
	int zv;
	double rv[3];
	int tv[3];
	std::atomic<bool> have_message;
	std::mutex mtx,cube_mtx,finish_mtx;
	std::condition_variable finish_modify;
private:// functions

};
// basis function
int GCD(int a, int b);
int LCM(int a, int b);


// control the model direction
void CV_CDECL on_mouse(int event, int x, int y, int flags, void* userdata);

