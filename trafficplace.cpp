#include "trafficplace.hh"

TrafficPlace::TrafficPlace(QPointF location, QObject *parent)
    :QObject(parent), GameObject(location.x(), location.y(), 0)
{

}

TrafficPlace::TrafficPlace(bool passengerTraffic, std::string countryCode,
                           std::string stationName, std::string stationShortCode,
                           double x, double y, std::string type, QObject *parent):
    QObject(parent), GameObject(x, y, 0),
    passengerTraffic_{passengerTraffic}, countryCode_{countryCode},
    stationName_{stationName}, stationShortCode_{stationShortCode}

{
    if ( type == "STATION" ){
        type_ = "STATION";
    } else if ( type == "STOPPING_POINT" ) {
        type_ = "STOPPING_POINT";
    } else {
        type_ = "TURNOUT_IN_THE_OPEN_LINE";
    }
}

bool TrafficPlace::isTraffic()
{
    return passengerTraffic_;
}

std::string TrafficPlace::getStationShortCode()
{
    return stationShortCode_;
}

std::string TrafficPlace::getCountryCode()
{
    return countryCode_;
}

std::string TrafficPlace::getStationName()
{
    return stationName_;
}

QString TrafficPlace::stationShortCode()
{
    return QString::fromStdString(stationShortCode_);
}

std::string TrafficPlace::getType()
{
    return type_;
}

void TrafficPlace::addNeighbour(TrafficPlace *neighbour)
{
    neighbours_.push_back(neighbour);
}

std::vector<TrafficPlace *> TrafficPlace::getNeighbours()
{
    return neighbours_;
}
