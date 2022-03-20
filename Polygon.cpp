#include "Polygon.h"
#include <cmath>

const double eps = 0.0001; //��-�� ������������ ���������� ������������ ������� �� ����� ��� �� �������� ������ ��������� 



Polygon::Polygon() {
	first = nullptr;
}

Polygon::Polygon(Point^ first) {
	this->first = first;
}

Polygon::Polygon(Polygon^ other){
    Point^ cur = gcnew Point(); 
    cur = other->getFirst();
    do {
        this->AddPoint(cur->getX(), cur->getY());
        cur = cur->getCurNext();
    } while (cur != other->getFirst());
}

Point^ Polygon::getFirst() {
	return first;
}

void Polygon::setFirst(Point^ first) {
	this->first = first;
}

//���������� �����
void Polygon::AddPoint(double X, double Y) {
    if (!first) { //���� ������������� ��� �� ������, ����������� ����� ���������� ������ 
        Point^ newPoint = gcnew Point(X, Y);
        first = newPoint; 
        first->setCurNext(newPoint);
        first->setCurPrev(newPoint);
        return;
    }
	Point^ newPoint = gcnew Point(X, Y, first, first->getCurPrev()); //����� ����������� � �����, ��� ����������� "����� ������"
	first->getCurPrev()->setCurNext(newPoint);
	first->setCurPrev(newPoint);
}

#pragma region ForSplitting
//����� ���������� ����������� ������, ���������� ����� ����������� �����, � ������ ������� ��������������
Point^ Intersection(Point^ start, double& k, double& b) {
    double length = -1; //���������� ����� ����������� ������ � ������ �����������, ������ ���� �����������
    Point^ intersection = gcnew Point();
    Point^ probably; //��� ���������, ���� ����������� ������� � ��� ��������� ������; ���������� ����� ��������� �� ������, ������ ����� ������ ������� ��� ��������� �����
    Point^ cur = start->getCurNext(); //������������� �������� (���������) ������� ������������, � ��� ����������� � ����������� �����
    do {
        double x1 = cur->getX(); //������ ��������������� �������
        double y1 = cur->getY(); //������ ��������������� �������
        double x2 = cur->getCurNext()->getX(); //����� ��������������� �������
        double y2 = cur->getCurNext()->getY(); //����� ��������������� �������
        double x_inter; //���������� �����������
        double y_inter; //���������� �����������
        if (x1 != x2) { //��������������� ������� �� ������������
            double k_now = (y2 - y1) / (x2 - x1); //��� ��������� �������, � ������� ������������ ������������
            if (k_now == k) { //���� ������� �����������, ����������� ����� ���
                cur = cur->getCurNext();
                continue;
            }
            double b_now = (x2 * y1 - x1 * y2) / (x2 - x1); //��� ��������� �������, � ������� ������������ ������������
            x_inter = (b_now - b) / (k - k_now); //���������� �����������
            if (abs(abs(x_inter - x1) + abs(x_inter - x2) - abs(x1 - x2)) > eps) { //����� ����������� �� ����� �� ������� (�� ������ ������� �� x), ����������� �� �� ��������, � � ������������
                cur = cur->getCurNext();
                continue;
            }
            y_inter = k_now * x_inter + b_now; //���������� �����������
        }
        else { //��������������� ������� ������������
            y_inter = k * x1 + b; //���������� �����������
            if (abs(y_inter - y1) + abs(y_inter - y2) != abs(y1 - y2)) { //����� ����������� �� ����� �� ������� (�� ������ ������� �� y)
                cur = cur->getCurNext();
                continue;
            }
            x_inter = x1; //���������� �����������
        }

        double length_now = sqrt((start->getX() - x_inter) * (start->getX() - x_inter) + (start->getY() - y_inter) * (start->getY() - y_inter)); //���������� ����� ����������� ������ � ������������ �� ��������
        if (length == -1 || length_now < length) { //������ ����������� ����������� ������ � ����������� �����
            if (abs(y_inter - y1) < eps && abs(x_inter - x1) < eps) { //����������� ������� � ��������� ������ ������� (����������� �� ���������� ���� ��� ���������� � ��������)
                cur = cur->getCurNext();
                continue;
            }
            if (abs(y_inter - y2) < eps && abs(x_inter - x2) < eps) { //����������� ������� � �������� ������ �������
                probably = gcnew Point(cur->getCurNext()->getX(), cur->getCurNext()->getY(), cur->getCurNext()->getCurNext(), cur);
                /*intersection = cur->getCurNext();
                intersection->setCurPrev(start);
                intersection->setOtherPrev(cur);*/
                cur = cur->getCurNext();
                length = length_now;
                continue;
            }
            intersection->change(x_inter, y_inter, cur->getCurNext(), start, nullptr, cur);
            length = length_now;
        }
        cur = cur->getCurNext();
    } while (cur != start->getCurPrev()->getCurPrev()); //�� ������������� �������� (����������) �������
    if (probably)
        if (abs(sqrt((start->getX() - probably->getX()) * (start->getX() - probably->getX()) + (start->getY() - probably->getY()) * (start->getY() - probably->getY())) - length) < eps) {
            intersection = probably; 
            intersection->getCurPrev()->setCurNext(intersection);
            intersection->getCurNext()->setCurPrev(intersection);
            intersection->newPrev(start);
        }
    return intersection;
}

//����������� ��� ������������ ����������� ������
Point^ Intersection(Point^ start) {
    double x = start->getX();
    double length = -1; //���������� ����� ����������� ������ � ������ �����������, ������ ���� �����������
    Point^ intersection = gcnew Point();
    Point^ probably;
    Point^ cur = start->getCurNext(); //������������� �������� (���������) ������� ������������ 
    do {
        double x1 = cur->getX(); //������ ��������������� �������
        double y1 = cur->getY(); //������ ��������������� �������
        double x2 = cur->getCurNext()->getX(); //����� ��������������� �������
        double y2 = cur->getCurNext()->getY(); //����� ��������������� �������
        if (abs(x1 - x2) < eps) { //��� ������������ ������ �� ������������
            cur = cur->getCurNext();
            continue;
        }
        else {
            if (abs(abs(x - x1) + abs(x - x2) - abs(x1 - x2)) < eps) { //����� ����������� ����� �� �������
                double k_now = (y2 - y1) / (x2 - x1); //��� ��������� �������, � ������� ������������
                double b_now = (x2 * y1 - x1 * y2) / (x2 - x1); //��� ��������� �������, � ������� ������������
                double y_inter = k_now * x + b_now; //���������� �����������
                double length_now = abs(start->getY() - y_inter); //���������� �� ����������� ����� �� �����������
                if (length == -1 || length_now < length) { //������ ����������� ����������� ������ � ����������� �����
                    if (abs(y_inter - y1) < eps && abs(x - x1) < eps) { //����������� ������� � ��������� ������ ������� (����������� �� ���������� ���� ��� ���������� � ��������)
                        cur = cur->getCurNext();
                        continue;
                    }
                    if (abs(y_inter - y2) < eps && abs(x - x2) < eps) { //����������� ������� � �������� ������ �������
                        
                        probably = gcnew Point(cur->getCurNext()->getX(), cur->getCurNext()->getY(), cur->getCurNext()->getCurNext(), cur);
                        cur = cur->getCurNext();
                        length = length_now;
                        continue;
                    }
                    intersection->change(x, y_inter, cur->getCurNext(), start, nullptr, cur);
                    length = length_now;
                }
            }
        }
        cur = cur->getCurNext();
    } while (cur != start->getCurPrev()->getCurPrev()); //�� ������������� �������� (����������) �������
    if (probably)
        if (abs(sqrt((start->getX() - probably->getX()) * (start->getX() - probably->getX()) + (start->getY() - probably->getY()) * (start->getY() - probably->getY())) - length) < eps) {
            intersection = probably;
            intersection->getCurPrev()->setCurNext(intersection);
            intersection->getCurNext()->setCurPrev(intersection);
            intersection->newPrev(start);
        }
    return intersection;
}

void static �onsiderTwoPolygons(Point^ cur, Point^ intersection) {

    //����� �� �������� ��� ���������� �����
    Point^ OtherNextForCur = cur->getCurNext();
    Point^ OtherPrevForIntersection = intersection->getOtherPrev();

    cur->setCurNext(intersection);
    intersection->getCurNext()->newPrev(intersection);

    //���� ���� ����� ����������� ����� � ����������� �� ������� �������
    Polygon^ newPolygon = gcnew Polygon(intersection);
    Polygon::Splitting(newPolygon);

    //������ �������������
    cur->setCurNext(OtherNextForCur);
    cur->setCurPrev(intersection);
    intersection->setCurPrev(OtherPrevForIntersection);
    intersection->setCurNext(cur);
    OtherPrevForIntersection->setCurNext(intersection);
    Polygon::Splitting(newPolygon);
    return;
}
#pragma endregion

void Polygon::Splitting(Polygon^ polygon) {
    //����� �������������� � ������� ����������� �����, ��� ����������� ����������
    Point^ cur = polygon->getFirst();
    do {
#pragma region ����������
        double x1 = cur->getCurPrev()->getX(); //���������� �����
        double y1 = cur->getCurPrev()->getY(); //���������� �����
        double x2 = cur->getX(); //������� �����
        double y2 = cur->getY(); //������� �����
        double x3 = cur->getCurNext()->getX(); //��������� �����
        double y3 = cur->getCurNext()->getY(); //��������� �����
#pragma endregion

        //������� � ���������� �� ����� �� ����� ��������� 
        if (x1 != x2) {
            double k = (y2 - y1) / (x2 - x1); //������, �� ������� ����� ���������� � ������� �����
            double b = (x2 * y1 - x1 * y2) / (x2 - x1); //������, �� ������� ����� ���������� � ������� �����

            //���� ��������� ����� ����� �� �� ������ ������� �� ������, ���������� ����� ���������� � �������, �� ���������� ����������; �������� ��������� � ������� �����
            if ((x2 - x1) * (y3 - k * x3 - b) < -eps)
            {
                Point^ intersection = Intersection(cur, k, b);
                �onsiderTwoPolygons(cur, intersection);
                return;
            }
        }

        //������� � ���������� ����� ����� �� ����� ���������
        else
            //���� ��������� ����� ����� �� �� ������ ������� �� ���������, ���������� ����� ���������� � �������, �� ���������� ����������; �������� ��������� � ������� �����
            if ((y1 - y2) * (x3 - x2) < -eps)
            {
                Point^ intersection = Intersection(cur);
                �onsiderTwoPolygons(cur, intersection);
                return;
            }

        cur = cur->getCurNext();
    } while (cur != polygon->getFirst());

    del(polygon->getFirst());
}
