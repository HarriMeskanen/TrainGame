#include "rail.hh"

Rail::Rail(QPointF p1, QPointF p2, QString id)
    :GameObject(p1.x(), p1.y(), 0),
     p1_(p1), p2_(p2), id_(id)
{

}

Rail::~Rail()
{

}
