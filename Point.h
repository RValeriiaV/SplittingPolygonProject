#pragma once

namespace MyPoints {
	ref class Point
	{
		double X; //координаты
		double Y;
		Point^ curNext; //следующая точка
		Point^ curPrev; //предыдущая точка

		Point^ otherNext; //дополнительная следующая

		Point^ otherPrev; //дополнительная предыдущая

	public:

		Point(); //конструктор по умолчанию

		Point(double X, double Y); //установка координат

		Point(double X, double Y, Point^ curNext, Point^ curPrev); //установка всей информации

		void change(double X, double Y, Point^ curNext, Point^ curPrev, Point^ otherNext, Point^ otherPrev); //смена всей информации

		double getX(); //получение координат
		double getY(); //получение координат

		void setX(double X); //установка координат
		void setY(double Y); //установка координат

		Point^ getCurNext(); //получение следующей точки
		void setCurNext(Point^ curNext); //установление следующей точки

		Point^ getCurPrev(); //получение предыдущей точки
		void setCurPrev(Point^ curPrev); //установление следующей точки

		Point^ getOtherNext(); //получение дополнительной следующей точки
		void setOtherNext(Point^ otherNext); //установление дополнительной следующей точки

		Point^ getOtherPrev(); //получение дополнительной предыдущей точки
		void setOtherPrev(Point^ otherPrev); //установление дополнительной предыдущей точки

		void newNext(Point^ next); //установление новой следующей точки
		void newPrev(Point^ prev); //установление новой предыдущей точки
	};
}


