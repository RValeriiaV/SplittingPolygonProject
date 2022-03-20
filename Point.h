#pragma once

namespace MyPoints {
	ref class Point
	{
		double X; //����������
		double Y;
		Point^ curNext; //��������� �����
		Point^ curPrev; //���������� �����

		Point^ otherNext; //�������������� ���������

		Point^ otherPrev; //�������������� ����������

	public:

		Point(); //����������� �� ���������

		Point(double X, double Y); //��������� ���������

		Point(double X, double Y, Point^ curNext, Point^ curPrev); //��������� ���� ����������

		void change(double X, double Y, Point^ curNext, Point^ curPrev, Point^ otherNext, Point^ otherPrev); //����� ���� ����������

		double getX(); //��������� ���������
		double getY(); //��������� ���������

		void setX(double X); //��������� ���������
		void setY(double Y); //��������� ���������

		Point^ getCurNext(); //��������� ��������� �����
		void setCurNext(Point^ curNext); //������������ ��������� �����

		Point^ getCurPrev(); //��������� ���������� �����
		void setCurPrev(Point^ curPrev); //������������ ��������� �����

		Point^ getOtherNext(); //��������� �������������� ��������� �����
		void setOtherNext(Point^ otherNext); //������������ �������������� ��������� �����

		Point^ getOtherPrev(); //��������� �������������� ���������� �����
		void setOtherPrev(Point^ otherPrev); //������������ �������������� ���������� �����

		void newNext(Point^ next); //������������ ����� ��������� �����
		void newPrev(Point^ prev); //������������ ����� ���������� �����
	};
}


