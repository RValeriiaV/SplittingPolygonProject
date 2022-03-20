#include "Polygon.h"
#include <cmath>

const double eps = 0.0001; //из-за погрешностей вычислений используется отличие не более чем на точность вместо равенство 



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

//добавление точки
void Polygon::AddPoint(double X, double Y) {
    if (!first) { //если прямоугольник еще не создан, добавляемая точка становится первой 
        Point^ newPoint = gcnew Point(X, Y);
        first = newPoint; 
        first->setCurNext(newPoint);
        first->setCurPrev(newPoint);
        return;
    }
	Point^ newPoint = gcnew Point(X, Y, first, first->getCurPrev()); //иначе добавляется в конец, что равносильно "перед первой"
	first->getCurPrev()->setCurNext(newPoint);
	first->setCurPrev(newPoint);
}

#pragma region ForSplitting
//поиск ближайшего пересечения прямой, проходящей через критическую точку, и другой стороны многоугольника
Point^ Intersection(Point^ start, double& k, double& b) {
    double length = -1; //расстояние между критической точкой и точкой пересечения, должно быть минимальным
    Point^ intersection = gcnew Point();
    Point^ probably; //для перехвата, если пересечение совпало с уже имеющейся точкой; расстояние может оказаться не лучшим, нельзя сразу менять соседей уже имеющейся точки
    Point^ cur = start->getCurNext(); //рассматривать соседнюю (следующую) сторону бессмысленно, с ней пересечение в критической точке
    do {
        double x1 = cur->getX(); //начало рассматриваемой стороны
        double y1 = cur->getY(); //начало рассматриваемой стороны
        double x2 = cur->getCurNext()->getX(); //конец рассматриваемой стороны
        double y2 = cur->getCurNext()->getY(); //конец рассматриваемой стороны
        double x_inter; //координаты пересечения
        double y_inter; //координаты пересечения
        if (x1 != x2) { //рассматриваемая сторона не вертикальная
            double k_now = (y2 - y1) / (x2 - x1); //для уравнения стороны, с которой потенциально пересекается
            if (k_now == k) { //если стороны параллельны, пересечения точно нет
                cur = cur->getCurNext();
                continue;
            }
            double b_now = (x2 * y1 - x1 * y2) / (x2 - x1); //для уравнения стороны, с которой потенциально пересекается
            x_inter = (b_now - b) / (k - k_now); //координаты пересечения
            if (abs(abs(x_inter - x1) + abs(x_inter - x2) - abs(x1 - x2)) > eps) { //точка пересечения не лежит на стороне (за краями стороны по x), пересечение не со стороной, а с продолжением
                cur = cur->getCurNext();
                continue;
            }
            y_inter = k_now * x_inter + b_now; //координаты пересечения
        }
        else { //рассматриваемая сторона вертикальная
            y_inter = k * x1 + b; //координаты пересечения
            if (abs(y_inter - y1) + abs(y_inter - y2) != abs(y1 - y2)) { //точка пересечения не лежит на стороне (за краями стороны по y)
                cur = cur->getCurNext();
                continue;
            }
            x_inter = x1; //координаты пересечения
        }

        double length_now = sqrt((start->getX() - x_inter) * (start->getX() - x_inter) + (start->getY() - y_inter) * (start->getY() - y_inter)); //расстояние между критической точкой и пересечением со стороной
        if (length == -1 || length_now < length) { //нужное пересечение максимально близко к критической точке
            if (abs(y_inter - y1) < eps && abs(x_inter - x1) < eps) { //пересечение совпало с начальной точкой стороны (рассмотрено на предыдущем шаге как совпадение с конечной)
                cur = cur->getCurNext();
                continue;
            }
            if (abs(y_inter - y2) < eps && abs(x_inter - x2) < eps) { //пересечение совпало с конечной точкой стороны
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
    } while (cur != start->getCurPrev()->getCurPrev()); //не рассматриваем соседнюю (предыдущую) сторону
    if (probably)
        if (abs(sqrt((start->getX() - probably->getX()) * (start->getX() - probably->getX()) + (start->getY() - probably->getY()) * (start->getY() - probably->getY())) - length) < eps) {
            intersection = probably; 
            intersection->getCurPrev()->setCurNext(intersection);
            intersection->getCurNext()->setCurPrev(intersection);
            intersection->newPrev(start);
        }
    return intersection;
}

//пересечение для вертикальной изначальной прямой
Point^ Intersection(Point^ start) {
    double x = start->getX();
    double length = -1; //расстояние между критической точкой и точкой пересечения, должно быть минимальным
    Point^ intersection = gcnew Point();
    Point^ probably;
    Point^ cur = start->getCurNext(); //рассматривать соседнюю (следующую) сторону бессмысленно 
    do {
        double x1 = cur->getX(); //начало рассматриваемой стороны
        double y1 = cur->getY(); //начало рассматриваемой стороны
        double x2 = cur->getCurNext()->getX(); //конец рассматриваемой стороны
        double y2 = cur->getCurNext()->getY(); //конец рассматриваемой стороны
        if (abs(x1 - x2) < eps) { //две вертикальные прямые не пересекаются
            cur = cur->getCurNext();
            continue;
        }
        else {
            if (abs(abs(x - x1) + abs(x - x2) - abs(x1 - x2)) < eps) { //точка пересечения лежит на стороне
                double k_now = (y2 - y1) / (x2 - x1); //для уравнения стороны, с которой пересекается
                double b_now = (x2 * y1 - x1 * y2) / (x2 - x1); //для уравнения стороны, с которой пересекается
                double y_inter = k_now * x + b_now; //координаты пересечения
                double length_now = abs(start->getY() - y_inter); //расстояние от критической точки до пересечения
                if (length == -1 || length_now < length) { //нужное пересечение максимально близко к критической точке
                    if (abs(y_inter - y1) < eps && abs(x - x1) < eps) { //пересечение совпало с начальной точкой стороны (рассмотрено на предыдущем шаге как совпадение с конечной)
                        cur = cur->getCurNext();
                        continue;
                    }
                    if (abs(y_inter - y2) < eps && abs(x - x2) < eps) { //пересечение совпало с конечной точкой стороны
                        
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
    } while (cur != start->getCurPrev()->getCurPrev()); //не рассматриваем соседнюю (предыдущую) сторону
    if (probably)
        if (abs(sqrt((start->getX() - probably->getX()) * (start->getX() - probably->getX()) + (start->getY() - probably->getY()) * (start->getY() - probably->getY())) - length) < eps) {
            intersection = probably;
            intersection->getCurPrev()->setCurNext(intersection);
            intersection->getCurNext()->setCurPrev(intersection);
            intersection->newPrev(start);
        }
    return intersection;
}

void static СonsiderTwoPolygons(Point^ cur, Point^ intersection) {

    //чтобы не терялись при совпадении точек
    Point^ OtherNextForCur = cur->getCurNext();
    Point^ OtherPrevForIntersection = intersection->getOtherPrev();

    cur->setCurNext(intersection);
    intersection->getCurNext()->newPrev(intersection);

    //если идти через критическую точку и пересечение по часовой стрелке
    Polygon^ newPolygon = gcnew Polygon(intersection);
    Polygon::Splitting(newPolygon);

    //второй многоугольник
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
    //обход многоугольника с поиском критических точек, где прерывается выпуклость
    Point^ cur = polygon->getFirst();
    do {
#pragma region Координаты
        double x1 = cur->getCurPrev()->getX(); //предыдущая точка
        double y1 = cur->getCurPrev()->getY(); //предыдущая точка
        double x2 = cur->getX(); //текущая точка
        double y2 = cur->getY(); //текущая точка
        double x3 = cur->getCurNext()->getX(); //следующая точка
        double y3 = cur->getCurNext()->getY(); //следующая точка
#pragma endregion

        //текущая и предыдущая не лежат на одной вертикали 
        if (x1 != x2) {
            double k = (y2 - y1) / (x2 - x1); //прямая, на которой лежат предыдущая и текущая точки
            double b = (x2 * y1 - x1 * y2) / (x2 - x1); //прямая, на которой лежат предыдущая и текущая точки

            //если следующая точка лежит не по нужную сторону от прямой, проходящей через предыдущую и текущую, то нарушается выпуклость; начинаем разбиение с текущей точки
            if ((x2 - x1) * (y3 - k * x3 - b) < -eps)
            {
                Point^ intersection = Intersection(cur, k, b);
                СonsiderTwoPolygons(cur, intersection);
                return;
            }
        }

        //текущая и предыдущая точка лежат на одной вертикали
        else
            //если следующая точка лежит не по нужную сторону от вертикали, проходящей через предыдущую и текущую, то нарушается выпуклость; начинаем разбиение с текущей точки
            if ((y1 - y2) * (x3 - x2) < -eps)
            {
                Point^ intersection = Intersection(cur);
                СonsiderTwoPolygons(cur, intersection);
                return;
            }

        cur = cur->getCurNext();
    } while (cur != polygon->getFirst());

    del(polygon->getFirst());
}
