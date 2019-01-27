#ifndef TRAFFICPLACE_HH
#define TRAFFICPLACE_HH

#include "gameobject.hh"

#include <QObject>
#include <QString>
#include <string>
#include <vector>

/**
 * @brief // Trafficplace class is the class for objects of VR API that are either stations,
 * stopping points or turnouts. It is inherited from GameObject class.
 */

class TrafficPlace : public QObject, public GameObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF location READ location NOTIFY locationChanged)
    Q_PROPERTY(QString stationShortCode READ stationShortCode NOTIFY stationShortCodeChanged)

public:
    TrafficPlace(QPointF location, QObject* parent = 0);
    TrafficPlace(bool passengerTraffic, std::string countryCode,
                 std::string stationName, std::string stationShortCode, double x,
                 double y, std::string type, QObject* parent = 0);

    inline QPointF location(){return location_;}
    QString stationShortCode();
    //void updateModel(int updateInterval){;}

    inline std::vector<TrafficPlace*> neighbours(){return neighbours_;}
    bool isTraffic();
    std::string getStationShortCode();
    std::string getCountryCode();
    std::string getStationName();
    std::string getType();
    void addNeighbour(TrafficPlace * neighbour);
    std::vector<TrafficPlace *> getNeighbours();

signals:
    void locationChanged();
    void stationShortCodeChanged();

private:
    bool passengerTraffic_;
    std::string countryCode_;
    std::string stationName_;
    std::string stationShortCode_;
    std::string type_;
    std::vector<TrafficPlace *> neighbours_;
};

#endif // TRAFFICPLACE_HH
