#ifndef RAIL_HH
#define RAIL_HH

#include "gameobject.hh"

#include<QPointF>

/**
 * @brief A Rail object is used to connect two TrafficPlaces
 */

class Rail : public GameObject
{
public:
    Rail(QPointF p1, QPointF p2, QString id);
    virtual ~Rail();

    inline QPointF p1(){return p1_;}
    inline QPointF p2(){return p2_;}
    inline QString id(){return id_;}

private:
    QPointF p1_;
    QPointF p2_;
    QString id_;
};

#endif // RAIL_HH
