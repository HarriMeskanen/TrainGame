#include "gameobject.hh"

#include "other.hh"


GameObject::GameObject(double x, double y, bool movable):
    location_(QPointF(x, y)), movable_(movable)
{

}

void GameObject::setLocation(QPointF location){
    if(this->movable_)
        location_ = location;
    else std::cout << "gameobject not movable" << std::endl;
}

bool GameObject::objectClose(GameObject *comparison)
{
    if (MATHFUNCTIONS::distanceFromPoint(location_, comparison->location()) < 25) {
         return true;
    } else {
         return false;
    }
}
