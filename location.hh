#ifndef LOCATION_H
#define LOCATION_H

#include <QPointF>

class Location
{
public:
    Location(){}
    Location(double latitude, double longitude);
    virtual ~Location();
    inline QPointF getCoordinates() const {return coordinates_;}
    inline void setCoordinates(QPointF coordinates) {coordinates_ = coordinates;}
    double distanceFromLocation(Location comparison);
private:
    QPointF coordinates_;
};

#endif // LOCATION_H
