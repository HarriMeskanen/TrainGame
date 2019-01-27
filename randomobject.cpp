#include "randomobject.hh"
#include "other.hh"

#include <QDebug>


RandomObject::RandomObject(QString objectType, bool movable, double speed,
                           QVector<QPointF> route, QString id)
    :GameObject(0, 0, movable), objectType_{objectType}, exists_{true},
      speed_{speed}, rotation_{0}, route_{route}, id_(id)
{
    location_ = route.first();
    if ( route.cbegin()+1 != route.cend() ){
        destination_ = (route_.cbegin()+1);
        rotation_ = MATHFUNCTIONS::rotationOfTwoPoints(*route_.cbegin(),
                                                       *(route_.cbegin()+1));
        //qDebug() << destination_->x() << " " << destination_->y();
    } else {
        destination_ = route_.cbegin();
    }
}

void RandomObject::updateModel(int updateInterval)
{
    if (exists_) {
        if (movable_) {
            if(MATHFUNCTIONS::distanceFromPoint(location_, destination() ) >= speed_){
                //qDebug() << "1: " << MATHFUNCTIONS::distanceFromPoint(location_, destination());
                move(updateInterval);
                emit locationChanged();
                emit rotationChanged();
            } else {
                ++destination_;
                if ( destination_ != route_.cend() ){
                    //qDebug() << "2: " << MATHFUNCTIONS::distanceFromPoint(location_, *destination_);
                    this->setRotation( MATHFUNCTIONS::rotationOfTwoPoints(location_,*destination_) );
                    move(updateInterval);
                    emit locationChanged();
                    emit rotationChanged();
                } else {
                    //qDebug() << "3: " << MATHFUNCTIONS::distanceFromPoint(location_, *destination_);
                    destination_ = route_.cbegin();
                    this->setRotation( MATHFUNCTIONS::rotationOfTwoPoints(location_,*destination_) );
                    move(updateInterval);
                    emit locationChanged();
                    emit rotationChanged();
                }
            }
        }
    } else {
        emit existsChanged();
    }
}

void RandomObject::move(int updateInterval)
{
    double update = updateInterval;
    setLocation(QPointF(location().x()+10*(speed_/update)*cos(rotation_*M_PI/180),
                        location().y()-10*(speed_/update)*sin(rotation_*M_PI/180)));
}
