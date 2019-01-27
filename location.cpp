#include "location.hh"
#include <math.h>


Location::Location(double latitude, double longitude):
    coordinates_(53.5*longitude-1066.7,-94*latitude+6352)
{

}

double Location::distanceFromLocation(Location comparison)
{
    double deltaX = this->coordinates_.x() - comparison.coordinates_.x();
    double deltaY = this->coordinates_.y() - comparison.coordinates_.y();

    return sqrt(deltaX*deltaX + deltaY*deltaY);
}

Location::~Location()
{

}
