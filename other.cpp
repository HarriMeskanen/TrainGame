#include "other.hh"

const double PI = 3.14159265359;

QPointF MATHFUNCTIONS::makeUnitVector(QPointF startPoint, QPointF endPoint)
{
    double dx = endPoint.x() - startPoint.x();
    double dy = endPoint.y() - startPoint.y();
    double length = sqrt(pow(dx, 2) + pow(dy, 2));

    return QPointF(dx/length, dy/length);
}

double MATHFUNCTIONS::distanceFromObject(GameObject *object, GameObject *otherObject)
{
    return distanceFromPoint(object->location(), otherObject->location());
}

double MATHFUNCTIONS::distanceFromPoint(QPointF point, QPointF otherPoint)
{
    return sqrt(pow(point.x()-otherPoint.x(), 2) + pow(point.y()-otherPoint.y(), 2));
}

double MATHFUNCTIONS::rotationOfTwoPoints(QPointF fromPoint, QPointF toPoint) {
    return atan2(-1*(toPoint.y()-fromPoint.y()),toPoint.x()-fromPoint.x())*180/PI;
}

bool MATHFUNCTIONS::isPointOnALine(QPointF *point, GameObject *p1, GameObject *p2)
{    
    double k = ( p2->location().y() - p1->location().y() ) / ( p2->location().x() - p1->location().x() );
    if(k*point->x() - k*p1->location().x() + p1->location().y() == point->y())
        return true;
    return false;
}

GameObject* MATHFUNCTIONS::findCloser(QPointF *point, GameObject *p1, GameObject *p2)
{
    double dx = abs(point->x() - p1->location().x()) - abs(point->x() - p2->location().x());
    if(dx >= 0)
        return p2;
    else
        return p1;
}

GameObject* MATHFUNCTIONS::locate(QPointF *playerTrain, const QList<QObject *> &currentPath)
{    
    for(int i = 0; i < currentPath.length()-1; i++){
        GameObject* p1 = dynamic_cast<GameObject*>(currentPath[i]);
        GameObject* p2 = dynamic_cast<GameObject*>(currentPath[i+1]);

        if(MATHFUNCTIONS::isPointOnALine(playerTrain, p1, p2)){
            if(playerTrain->x() == p1->location().x())
                return p1;
            else if(playerTrain->x() == p2->location().x())
                return p2;
            else
                return findCloser(playerTrain, p1, p2);
        }
    }
    std::cout << "Could not locate current playerTrain location" << std::endl;
    return 0;
}

double MATHFUNCTIONS::pathLength(QVector<TrafficPlace*> path)
{
    double length = 0;
    for(int i = 0; i < path.size(); i++){
        if(i != 0)
            length += distanceFromObject(path.at(i-1), path.at(i));
    }
    return length;
}

QPointF MATHFUNCTIONS::latLonToMercator(double lat, double lon) {
    double radius = 640/(2*M_PI);
    double x = radius*lon*M_PI/180+640/2;
    double y = 800/2 - radius*(log(tan((90+lat)*M_PI/360))/M_PI)*2.8;
    return QPointF(x,y);
}

