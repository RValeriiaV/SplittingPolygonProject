#pragma once
#include "Point.h"
using namespace MyPoints;

ref class Polygon
{
	Point^ first; //первая точка многоугольника
public:
	Polygon(); 
	Polygon(Point^ first);
	Polygon(Polygon^ other);
	Point^ getFirst(); //получение певрой точки
	void setFirst(Point^ first);//установление первой точки
	void AddPoint(double X, double Y); //добавление точки в конец многоугольника

	void static Splitting(Polygon^ polygon); //разбиение многоугольника (считается, что ось X направлена вправо, ось Y - вниз)
	delegate void Delegate(MyPoints::Point^); //делегат для возвращения во вне первой точки полученного многоугольника
	static Delegate^ del;
};

