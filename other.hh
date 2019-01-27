#ifndef OTHER_HH
#define OTHER_HH

#include "gameobject.hh"
#include "trafficplace.hh"

#include <math.h>
#include <QObject>
#include <QList>
#include <QHash>
#include <QVector>
#include <QPointF>
#include <iostream>

/**
 * @brief namespace MATHFUNCTIONS contains commonly used
    mathematical methods available to all objects in project
 */

namespace MATHFUNCTIONS
{
    QPointF makeUnitVector(QPointF startPoint, QPointF endPoint);
    double distanceFromObject(GameObject* object, GameObject* otherObject);
    double distanceFromPoint(QPointF point, QPointF otherPoint);
    double pathLength(QVector<TrafficPlace *> path);
    bool isPointOnALine(QPointF* point, GameObject* p1, GameObject* p2);
    GameObject* findCloser(QPointF* point, GameObject* p1, GameObject* p2);
    GameObject* locate(QPointF *playerTrain, const QList<QObject *> &currentPath);
    double rotationOfTwoPoints(QPointF fromPoint,QPointF toPoint);
    QPointF latLonToMercator(double lat, double lon);
}

#endif // OTHER_HH
