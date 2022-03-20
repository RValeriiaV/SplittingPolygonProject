#include "Point.h"
using namespace MyPoints;

//конструктор по умолчанию
Point::Point() {
	X = Y = 0;
	curNext = curPrev = nullptr;
	otherNext = nullptr;
	otherPrev = nullptr;
}

//установка координат
Point::Point(double X, double Y):Point() { 
	this->X = X;
	this->Y = Y;
}

//установка всей информации
Point::Point(double X, double Y, Point^ curNext, Point^ curPrev) :Point(X, Y) { 
	this->curNext = curNext;
	this->curPrev = curPrev;
}

void Point::change(double X, double Y, Point^ curNext, Point^ curPrev, Point^ otherNext, Point^ otherPrev) {
	this->X = X;
	this->Y = Y;
	this->curNext = curNext; 
	this->curPrev = curPrev; 
	this->otherNext = otherNext; 
	this->otherPrev = otherPrev;
}

double Point::getX() {
	return X;
}

double Point::getY() {
	return Y;
}

void Point::setX(double X) {
	this->X = X;
}

void Point::setY(double Y) {
	this->Y = Y;
}

Point^ Point::getCurNext() { return curNext; }

void Point::setCurNext(Point^ curNext) {
	this->curNext = curNext;
}

Point^ Point::getCurPrev() { return curPrev; }

void Point::setCurPrev(Point^ curPrev) {
	this->curPrev = curPrev;
}

Point^ Point::getOtherNext() {
	return otherNext; 
}
void Point::setOtherNext(Point^ biggerNext) {
	this->otherNext = biggerNext;
}

Point^ Point::getOtherPrev() {
	return otherPrev;
}
void Point::setOtherPrev(Point^ biggerPrev) {
	this->otherPrev = biggerPrev;
}

void Point::newNext(Point^ next) {
	otherNext = curNext; //текущая следующая становится дополнительной
	curNext = next; //переданная становится основной
}
void Point::newPrev(Point^ prev) {
	otherPrev = curPrev; //текущая предыдущая становится дополнительной
	curPrev = prev; //переданная становится основной
}
