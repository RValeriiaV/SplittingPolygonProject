#pragma once
#include "Point.h"
using namespace MyPoints;

ref class Polygon
{
	Point^ first; //������ ����� ��������������
public:
	Polygon(); 
	Polygon(Point^ first);
	Polygon(Polygon^ other);
	Point^ getFirst(); //��������� ������ �����
	void setFirst(Point^ first);//������������ ������ �����
	void AddPoint(double X, double Y); //���������� ����� � ����� ��������������

	void static Splitting(Polygon^ polygon); //��������� �������������� (���������, ��� ��� X ���������� ������, ��� Y - ����)
	delegate void Delegate(MyPoints::Point^); //������� ��� ����������� �� ��� ������ ����� ����������� ��������������
	static Delegate^ del;
};

