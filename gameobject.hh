#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

#include <math.h>
#include <QObject>
#include <QPointF>
#include <iostream>

/**
 * @brief GameObject is the base class for all physical objects used
 * in game
 */
class GameObject
{
public:
    /** @brief An instance of GameObject must contain information
     * of its location and wheather it is movable or not*/
    GameObject(double x, double y, bool movable);

    inline void updateModel() {;}

    inline virtual QPointF location(){return location_;}
    inline bool isActive(){return isActive_;}

    void setLocation(QPointF location);
    inline virtual void setActive(bool status){isActive_ = status;}

    bool objectClose(GameObject* comparison);

protected:
    QPointF location_;
    bool movable_;
    bool isActive_;
};

#endif // GAMEOBJECT_HH
