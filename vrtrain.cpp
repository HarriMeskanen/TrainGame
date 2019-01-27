#include "vrtrain.hh"
#include "other.hh"

#include <qdebug.h>

VRTrain::VRTrain(int trainNumber, QString trainType, QVector<QString> stations,
             QVector<QDateTime> departureTimes, bool running):
     GameObject(0, 0, 1),
     trainNumber_{trainNumber}, trainType_{trainType}, stations_{stations},
     departureTimes_{departureTimes}, running_{running}, distanceBetweenStations_{0},
     timeToDestination_{0}, speed_{0}, rotation_{0}
{

}

void VRTrain::updateModel(QDateTime gameTime, std::shared_ptr<std::unordered_map<std::string, TrafficPlace *>> stations,
                   int updateInterval) {
    if (running_) {
        // If there are only 2 stations left, the train is between the last two stations.
        // When the second one is reached, the train is removed from the map by gameMaps update() method
        if (stations_.length() == 2){
            if (MATHFUNCTIONS::distanceFromPoint
                    (location(), stations->find(stations_.at(1).toStdString())->second->location()) < speed_) {
                stations_.removeFirst();
                departureTimes_.removeFirst();
                running_ = false;
                emit runningChanged();
                return;
            }
        }
        // If there are more stations left that 2, check if the train has reached the destination station
        // i.e. the 2nd station in stations_
        else if (MATHFUNCTIONS::distanceFromPoint(location(),
                     stations->find(stations_.at(1).toStdString())->second->location()) < speed_) {
            // VRTrain is at the current target station -> calculate new movement
            stations_.removeFirst();
            departureTimes_.removeFirst();

            location_ = stations->find(stations_.at(0).toStdString())->second->location();
            QPointF targetStation = stations->find(stations_.at(1).toStdString())->second->location();
            setMovementParameters(targetStation, updateInterval);
        }

        // Move the train to the direction of the calculated rotation scaled with speed.
        setLocation(QPointF(location().x()+speed_*cos(rotation_*M_PI/180),
                            location().y()-speed_*sin(rotation_*M_PI/180)));
        emit locationChanged();

    }
    // Check if the train should be already running.
    // If so, set the movement parameters.
    else if (gameTime.toMSecsSinceEpoch() >= departureTimes_.at(0).toMSecsSinceEpoch()) {
        running_ = true;
        emit runningChanged();

        location_ = stations->find(stations_.at(0).toStdString())->second->location();
        emit locationChanged();

        QPointF targetStation = stations->find(stations_.at(1).toStdString())->second->location();
        setMovementParameters(targetStation, updateInterval);
    }
}

void VRTrain::setMovementParameters(QPointF targetStation, int updateInterval) {
    // updateInterval has to be converted to double before calculating anything else
    double update = updateInterval;

    // TIMESCALE explained: 20 comes from the fact that each time timer updates gameTime, 20 s are added to the gameTime
    //                      15 is how many pixels the trains are moving at each second
    // This looks messy because it has originally been designed for constant framerate of 30 fps, and the timescale is
    // normalized around that.
    // The normalization goes like this: Assume that at 30 fps the trains timeToDestination is such that the train will
    // reach its destination in 9 updateModel() calls. At 10 fps the refresh rate is 1/3rd of the original, thus the time
    // to destination has to be 3 seconds.
    double TIMESCALE = ((1.0/600.0)/15.0)/(1/(15*20*update));
    timeToDestination_ = TIMESCALE*((1.0/600.0)/15.0)*(departureTimes_.at(1).toMSecsSinceEpoch()-
                                    departureTimes_.at(0).toMSecsSinceEpoch());
    distanceBetweenStations_ = MATHFUNCTIONS::distanceFromPoint(location_, targetStation);
    speed_ = distanceBetweenStations_/timeToDestination_;

    rotation_ = MATHFUNCTIONS::rotationOfTwoPoints(location_,targetStation);
    emit rotationChanged();
}
