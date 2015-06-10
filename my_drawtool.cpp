#include <fstream>
#include <cmath>
#include <string>
#include <list>
#include <algorithm>
#include <iostream>
using namespace std;
#define ROUNDING(x, dig)    (floor((x) * pow(10, dig) + 0.5f) / pow(10, dig))

string ToString(int n);	// Change integer type to string type
string ToString(double n);	// Change double type to string type
int counter_ID=0;

class Shape	// abstract class
{
private:
	char selectPolygon;
	double r,g,b;
	int number_ID;
	int shape;
public:
	string gbufferHead;
	string gbufferGrid;
	string gbufferRGB;
	double *saveGrid;
public:
	Shape();	// Constructor
	virtual void drawFigure() =0;	// 순수 가상 함수
	virtual void modifyGrid(double dx, double dy) =0;
	virtual void changeSize(double n) =0;
	void setShape(int n);
	void setRGB();
	void modifyRGB(double r, double g, double b);
	double getR() const {return r;}
	double getG() const {return g;}
	double getB() const {return b;}
	void changeIDnumber();
	int getShape() const;
	int getID() const;
	~Shape(){ delete []saveGrid; }
};

class Circle : public Shape
{
private:
	double x, y, rad;
public:
	Circle();
	Circle(double x, double y, double rad);
	void drawFigure();
	void modifyGrid(double dx, double dy);
	void setGrid();
	void changeSize(double n);
};

class Triangle : public Shape
{
private:
	double ax, ay, bx, by, cx, cy;
	void GetcircumCenterXY(double &circumCenterX, double &circumCenterY);
public:
	Triangle();
	Triangle(double ax, double ay, double bx, double by, double cx, double cy);
	void drawFigure();
	void modifyGrid(double dx, double dy);
	void setGrid();
	void changeSize(double n);
};

class Rectangle : public Shape
{
private:
	double ux, uy, dx, dy;
public:
	Rectangle();
	Rectangle(double ux, double uy, double dx, double dy);
	void drawFigure();
	void modifyGrid(double dx, double dy);
	void setGrid();
	void changeSize(double n);
};

class Polygon	// handler
{
private:
	string gbuffer;
	std::list<Shape*> ls;
	std::list<Shape*>::iterator it;
private:	
	// Make Polygon
	void drawFigure(Circle *(&cir));	// draw Circle
	void drawFigure(Triangle *(&tri));	// draw Triangle
	void drawFigure(Rectangle *(&sqr));	// draw Rectangle
	void getBufferFromShape(Shape *(&shp));	// get string from Shape class

	// Menu
	void draw();
	void select();
	void EXIT();

public:
	// Constructor
	Polygon(string gbuffer);

	// Execute function
	void ExeFunc();
};

/*-----Member functions-----*/
// Constructor
Shape::Shape() : number_ID(counter_ID++)
{
}

void Shape::setShape(int c)
{
	shape=c;
}

int Shape::getShape() const
{
	return shape;
}

void Shape::changeIDnumber()
{
	number_ID=counter_ID++;
}

int Shape::getID() const
{
	return number_ID;
}

void Shape::modifyRGB(double r, double g, double b)
{
	this->r=r;
	this->g=g;
	this->b=b;
	this->gbufferRGB = ToString(r) + " " + ToString(g) + " " + ToString(b) + "  setrgbcolor		% r g b\n" + "fill				% draw a shape by filling with the current color\n\n";
}

void Shape::setRGB()
{
	cin >> r >> g >> b;
	gbufferRGB = ToString(r) + " " + ToString(g) + " " + ToString(b) + "  setrgbcolor		% r g b\n" + "fill				% draw a shape by filling with the current color\n\n";
}

// Constructor
Circle::Circle()
{
	setShape(0);
	gbufferHead = "% draw a circle (ID: ";
	gbufferHead += ToString(getID());
	gbufferHead += ")\nnewpath\n";
}

Circle::Circle(double x, double y, double rad) : x(x), y(y), rad(rad)
{
	setShape(0);
	gbufferHead = "% draw a circle (ID: ";
	gbufferHead += ToString(getID());
	gbufferHead += ")\nnewpath\n";
	saveGrid=new double[3];
	saveGrid[0]=x; saveGrid[1]=y; saveGrid[2]=rad;
}

void Circle::drawFigure()
{
	cout << "원의 중심 좌표 (x, y) 값을 입력하세요: ";
	cin >> x >> y;
	cout << "원의 반지름 R 값을 입력하세요: ";
	cin >> rad;
	gbufferGrid = ToString(x) + " " + ToString(y) + " " + ToString(rad) + " 0 360 arc	% x y r start_angle end_angle\nclosepath\n";
	cout<< "원의 색깔 (r, g, b) 값을 입력하세요: ";
	setRGB();
	saveGrid=new double[3];
	saveGrid[0]=x; saveGrid[1]=y; saveGrid[2]=rad;
}

void Circle::setGrid()
{
	gbufferGrid = ToString(x) + " " + ToString(y) + " " + ToString(rad) + " 0 360 arc	% x y r start_angle end_angle\nclosepath\n";
}

void Circle::modifyGrid(double dx, double dy)
{
	x+=dx;
	y+=dy;
	gbufferGrid = ToString(x) + " " + ToString(y) + " " + ToString(rad) + " 0 360 arc	% x y r start_angle end_angle\nclosepath\n";
}

void Circle::changeSize(double n)
{
	rad*=n;
	gbufferGrid = ToString(x) + " " + ToString(y) + " " + ToString(rad) + " 0 360 arc	% x y r start_angle end_angle\nclosepath\n";
}

// Constructor
Triangle::Triangle()
{
	setShape(1);
	gbufferHead = "% draw a triangle (ID: ";
	gbufferHead += ToString(getID());
	gbufferHead += ")\nnewpath\n";
}

Triangle::Triangle(double ax, double ay, double bx, double by, double cx, double cy) : ax(ax), ay(ay), bx(bx), by(by), cx(cx), cy(cy)
{
	setShape(1);
	gbufferHead = "% draw a triangle (ID: ";
	gbufferHead += ToString(getID());
	gbufferHead += ")\nnewpath\n";
	saveGrid=new double[6];
	saveGrid[0]=ax; saveGrid[1]=ay; saveGrid[2]=bx; saveGrid[3]=by; saveGrid[4]=cx; saveGrid[5]=cy;
}

void Triangle::drawFigure()
{
	cout << "삼각형의 세 꼭지점 좌표 (x, y) 값을 반시계 방향 순서로 입력하세요: ";
	cin >> ax >> ay >> bx >> by >> cx >> cy;
	gbufferGrid = ToString(ax) + " " + ToString(ay) + " " + " moveto\n";
	gbufferGrid += ToString(bx) + " " + ToString(by) + " " + " lineto\n";
	gbufferGrid += ToString(cx) + " " + ToString(cy) + " " + " lineto\n";
	gbufferGrid += "closepath\n";
	cout<< "삼각형의 색깔 (r, g, b) 값을 입력하세요: ";
	setRGB();
	saveGrid=new double[6];
	saveGrid[0]=ax; saveGrid[1]=ay; saveGrid[2]=bx; saveGrid[3]=by; saveGrid[4]=cx; saveGrid[5]=cy;
}

void Triangle::setGrid()
{
	gbufferGrid = ToString(ax) + " " + ToString(ay) + " " + " moveto\n";
	gbufferGrid += ToString(bx) + " " + ToString(by) + " " + " lineto\n";
	gbufferGrid += ToString(cx) + " " + ToString(cy) + " " + " lineto\n";
	gbufferGrid += "closepath\n";
}

void Triangle::modifyGrid(double dx, double dy)
{
	ax += dx;
	bx += dx;
	cx += dx;
	ay += dy;
	by += dy;
	cy += dy;
	gbufferGrid = ToString(ax) + " " + ToString(ay) + " " + " moveto\n";
	gbufferGrid += ToString(bx) + " " + ToString(by) + " " + " lineto\n";
	gbufferGrid += ToString(cx) + " " + ToString(cy) + " " + " lineto\n";
	gbufferGrid += "closepath\n";
}

void Triangle::changeSize(double n)
{
	double centerX1, centerY1;
	centerX1 = (ax + bx + cx) / 3;
	centerY1 = (ay + by + cy) / 3;

	ax*=n;	bx*=n;	cx*=n;
	ay*=n;	by*=n;	cy*=n;
	
	double centerX2, centerY2;
	centerX2 = (ax + bx + cx) / 3;
	centerY2 = (ay + by + cy) / 3;

	n=centerX2-centerX1;
	ax-=n;	bx-=n;	cx-=n;
	n=centerY2-centerY1;
	ay-=n;	by-=n;	cy-=n;
	ax=ROUNDING(ax,3.0);	bx=ROUNDING(bx, 3.0);	cx=ROUNDING(cx, 3.0);
	ay=ROUNDING(ay, 3.0);	by=ROUNDING(by, 3.0);	cy=ROUNDING(cy, 3.0);
	setGrid();
}

// Constructor
Rectangle::Rectangle()
{
	setShape(2);
	gbufferHead = "% draw a rectangle (ID: ";
	gbufferHead += ToString(getID());
	gbufferHead += ")\nnewpath\n";
}


Rectangle::Rectangle(double ux, double uy, double dx, double dy) : ux(ux), uy(uy), dx(dx), dy(dy)
{
	setShape(2);
	gbufferHead = "% draw a rectangle (ID: ";
	gbufferHead += ToString(getID());
	gbufferHead += ")\nnewpath\n";
	saveGrid=new double[4];
	saveGrid[0]=ux; saveGrid[1]=uy; saveGrid[2]=dx; saveGrid[3]=dy;
}

void Rectangle::drawFigure()
{
	cout << "사각형의 좌상단 좌표 (x, y) 값을 입력하세요: ";
	cin >> ux >> uy;
	cout << "사각형의 우하단 좌표 (x, y) 값을 입력하세요: ";
	cin >> dx >> dy;
	gbufferGrid = ToString(ux) + " " + ToString(uy) + " moveto\n" + ToString(ux) + " " + ToString(dy) + " lineto\n" + ToString(dx) + " " + ToString(dy) + " lineto\n" + ToString(dx) + " " +ToString(uy) + " lineto\n";
	gbufferGrid += "closepath\n";
	cout<< "사각형의 색깔 (r, g, b) 값을 입력하세요: ";
	setRGB();
	saveGrid=new double[4];
	saveGrid[0]=ux; saveGrid[1]=uy; saveGrid[2]=dx; saveGrid[3]=dy;
}

void Rectangle::setGrid()
{
	gbufferGrid = ToString(ux) + " " + ToString(uy) + " moveto\n" + ToString(ux) + " " + ToString(dy) + " lineto\n" + ToString(dx) + " " + ToString(dy) + " lineto\n" + ToString(dx) + " " +ToString(uy) + " lineto\n";
	gbufferGrid += "closepath\n";
}

void Rectangle::modifyGrid(double dxC, double dyC)
{
	ux += dxC;
	dx += dxC;
	uy += dyC;
	dy += dyC;
	gbufferGrid = ToString(ux) + " " + ToString(uy) + " moveto\n" + ToString(ux) + " " + ToString(dy) + " lineto\n" + ToString(dx) + " " + ToString(dy) + " lineto\n" + ToString(dx) + " " +ToString(uy) + " lineto\n";
	gbufferGrid += "closepath\n";
}

void Rectangle::changeSize(double n)
{
	double centerX1, centerY1;
	centerX1 = (ux + dx) / 2;
	centerY1 = (uy + dy) / 2;

	ux*=n;	dx*=n;
	uy*=n;	dy*=n;
	
	double centerX2, centerY2;
	centerX2 = (ux + dx) / 2;
	centerY2 = (uy + dy) / 2;

	n=centerX2-centerX1;
	ux-=n;	dx-=n;
	n=centerY2-centerY1;
	uy-=n;	dy-=n;
	ux=ROUNDING(ux, 3.0);	dx=ROUNDING(dx, 3.0);
	uy=ROUNDING(uy, 3.0);	dy=ROUNDING(dy, 3.0);
	gbufferGrid = ToString(ux) + " " + ToString(uy) + " moveto\n" + ToString(ux) + " " + ToString(dy) + " lineto\n" + ToString(dx) + " " + ToString(dy) + " lineto\n" + ToString(dx) + " " +ToString(uy) + " lineto\n";
	gbufferGrid += "closepath\n";
}

/*-----Handler Class-----*/
// Constructor
Polygon::Polygon(string gbuffer)
{
	this->gbuffer += gbuffer;
}

// Make Polygon
void Polygon::drawFigure(Circle *(&cir))	//circle
{
	cir->drawFigure();
	cout<< "원(도형 ID: ";
	cout<< cir->getID();
	cout<< ")이 생성되었습니다.\n";
	ls.push_back(cir);
}

void Polygon::drawFigure(Triangle *(&tri))	//triangle
{
	tri->drawFigure();
	cout<< "삼각형(도형 ID: ";
	cout<< tri->getID();
	cout<< ")이 생성되었습니다.\n";
	ls.push_back(tri);
}

void Polygon::drawFigure(Rectangle *(&sqr))	//rectangle
{
	sqr->drawFigure();
	cout<< "사각형(도형 ID: ";
	cout<< sqr->getID();
	cout<< ")이 생성되었습니다.\n";
	ls.push_back(sqr);
}

void Polygon::getBufferFromShape(Shape *(&shp))
{
	gbuffer += shp->gbufferHead;
	gbuffer += shp->gbufferGrid;
	gbuffer += shp->gbufferRGB;
}

// Menu
void Polygon::draw()
{
	while(1)
	{
		char selectPolygon;
		cout << "다음 중 그리고 싶은 도형 하나를 선택하십시오." << endl;
		cout << "(a) 원, (b) 삼각형, (c) 사각형: ";
		cin >> selectPolygon;

		if(selectPolygon=='a')
		{
			Circle *shp=new Circle;
			drawFigure(shp);
		}
		else if(selectPolygon=='b')
		{
			Triangle *shp=new Triangle;
			drawFigure(shp);
		}	
		else if(selectPolygon=='c')
		{
			Rectangle *shp=new Rectangle;
			drawFigure(shp);
		}
		else
		{
			cout<<"Invalid value."<<endl;
			continue;
		}
		break;	
	}
}

void Polygon::select()
{
	while(1)
	{
		int selectnum;
		int *select;
		cout << "선택할 도형의 개수와 ID를 입력하세요: ";
		cin >> selectnum;
		select = new int[selectnum];
		for(int z=0; z<selectnum; z++)
			cin >> select[z];
		cout << "선택된 도형에 대해 수행할 작업을 입력하세요.\n";
		cout << "(a) 복사 및 붙여넣기, (b) 맨 앞으로 가져오기, (c) 맨 뒤로 보내기, (t) 이동, (s) 확대축소 (d) 삭제: ";
		char sel;
		cin >> sel;
				
		if(sel=='d')
		{
			for(int z=0; z<selectnum; z++)
			{
				for(it = ls.begin(); it != ls.end(); ++it)
				{
					if ( (*it)->getID() == select[z] )
					{
						ls.erase(it);
						break;
					}
				}
			}
			delete []select;
			break;
		}

		else if(sel=='a')
		{
			for(int z=0; z<selectnum; z++)
			{
				for(it = ls.begin(); it != ls.end(); ++it)
				{
					if ( (*it)->getID() == select[z] )
					{
						if( (*it)->getShape() == 0)
						{
							Circle *cir = new Circle((*it)->saveGrid[0]+0.5,(*it)->saveGrid[1]-0.5,(*it)->saveGrid[2]);
							cir->setGrid();
							double r, g, b;
							cir->modifyRGB((*it)->getR(), (*it)->getG(), (*it)->getB());
							ls.push_back(cir);
							cout<< "원(도형 ID: "<< cir->getID() <<")이 생성되었습니다."<<endl;
						}
						else if( (*it)->getShape() == 1)
						{
							Triangle *tri = new Triangle((*it)->saveGrid[0]+0.5, (*it)->saveGrid[1]-0.5, (*it)->saveGrid[2]+0.5, (*it)->saveGrid[3]-0.5, (*it)->saveGrid[4]+0.5, (*it)->saveGrid[5]-0.5);
							tri->setGrid();
							tri->modifyRGB((*it)->getR(), (*it)->getG(), (*it)->getB());
							ls.push_back(tri);
							cout<< "삼각형(도형 ID: "<< tri->getID() <<")이 생성되었습니다."<<endl;
						}
						else
						{
							Rectangle *sqr = new Rectangle((*it)->saveGrid[0]+0.5, (*it)->saveGrid[1]-0.5, (*it)->saveGrid[2]+0.5, (*it)->saveGrid[3]-0.5);
							sqr->setGrid();
							sqr->modifyRGB((*it)->getR(), (*it)->getG(), (*it)->getB());
							ls.push_back(sqr);
							cout<< "사각형(도형 ID: "<< sqr->getID() <<")이 생성되었습니다."<<endl;
						}
						break;
					}
				}
			}
			delete []select;
			break;
		}

		else if(sel=='b')
		{
			for(int z=0; z<selectnum; z++)
			{
				for(it = ls.begin(); it != ls.end(); ++it)
				{
					if ( (*it)->getID() == select[z] )
					{
						if (it != ls.begin())
							ls.splice(ls.begin(), ls, it);
						break;
					}
				}
			}
			delete []select;
			break;
		}

		else if(sel=='c')
		{
			for(int z=0; z<selectnum; z++)
			{
				for(it = ls.begin(); it != ls.end(); ++it)
				{
					if ( (*it)->getID() == select[z] )
					{
						if (it != ls.end())
							ls.splice(ls.end(), ls, it);
						break;
					}
				}
			}
			delete []select;
			break;
		}

		else if(sel=='t')
		{
			cout<<"이동량 (dx, dy) 값을 입력하세요: "<<endl;
			double dx, dy;
			cin >> dx >> dy;
			for(int z=0; z<selectnum; z++)
			{
				for(it = ls.begin(); it != ls.end(); ++it)
				{
					if ( (*it)->getID() == select[z] )
					{
						(*it)->modifyGrid(dx, dy);
						break;
					}
				}
			}
			delete []select;
			break;
		}

		else if(sel=='s')
		{
			cout<<"확대축소량을 입력하세요: "<<endl;
			double n;
			cin >> n;
			for(int z=0; z<selectnum; z++)
			{
				for(it = ls.begin(); it != ls.end(); ++it)
				{
					if ( (*it)->getID() == select[z] )
					{
						(*it)->changeSize(n);
						break;
					}
				}
			}				
			delete []select;
			break;
		}

		else
		{
			delete []select;
			continue;
		}
	}
}

void Polygon::EXIT()
{
	for (it = ls.begin(); it != ls.end(); ++it)
		getBufferFromShape(*it);
	gbuffer += "showpage";
	cout<< "지금까지 그린 도형을 저장할 파일 이름을 입력하세요: ";
	string fileName;
	cin >> fileName;
	fileName += ".ps";
	ofstream fout(fileName);
	cout<< "현재 디렉토리에 "<<fileName<<" 파일이 생성되었습니다." <<endl;
	fout << gbuffer;			
	cout<< "도형 드로잉 툴을 종료합니다."<<endl;
	cout<< ">";
	fout.close();
}

// Execute Function
void Polygon::ExeFunc()
{
	while(1)
	{
		char menu;
		cout <<"모드를 선택하십시오.\n(1) 도형 그리기, (2) 도형 선택, (x) 프로그램 종료: ";
		cin >> menu;
		if(menu=='1')
			draw();
		else if(menu=='2')
			select();
		else if(menu=='x')
		{
			EXIT();
			break;
		}
		else
			continue;
	}
}

/*--------main--------*/
int main()
{
	cout << "> ./my_drawtool.exe" <<endl;
	cout << "도형 드로잉 툴을 구동합니다." << endl;
	string gbuffer;
	gbuffer = "%!\n";
	gbuffer += "50 50 scale			% just scale the coordinate. DO NOT TOUCH THIS LINE.\n\n";
	
	//Shape a; 추상 클래스를 인스턴스화 할 수 없습니다.

	Polygon myP(gbuffer);
	myP.ExeFunc();
	return 0;
}

/*-------global function-------*/
string ToString(int n)
{
      string tmp="";
      if ( n >= 10 )
           tmp = ToString( n/10 );
      tmp += (n%10) + '0';
      return tmp;
}

string ToString(double n)
{
	int a, b;
	a = b = n;
	int tenC=1;
	while(b!=n)
	{
		b = (n*=10);
		tenC *= 10;
	}
	b %= tenC;
	string tmp="";
	tmp = ToString(a) + '.' + ToString(b);
	return tmp;
}