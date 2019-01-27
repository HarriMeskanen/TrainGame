#ifndef VRTRAIN_H
#define VRTRAIN_H

#include "gameobject.hh"

#include <memory>
#include <QString>
#include <QVector>
#include <QDateTime>
#include <QtGlobal>
#include <unordered_map>
#include <trafficplace.hh>
#include <memory>

/**
 * @brief The VRTrain class is used to model the trains created
 * from VR api.
 */

class VRTrain : public QObject, public GameObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF location READ location NOTIFY locationChanged)
    Q_PROPERTY(double rotation READ rotation NOTIFY rotationChanged)
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)
    Q_PROPERTY(QString id READ id NOTIFY idChanged)

public:
    VRTrain(QObject* parent = 0);
    VRTrain(int trainNumber, QString trainType, QVector<QString> stations, QVector<QDateTime> departureTimes,
            bool running);

    inline QPointF location(){return location_;}
    inline QString id(){return QString::fromStdString(std::to_string(trainNumber_));}
    inline int getTrainNumber() {return trainNumber_;}
    inline QString getTrainType() {return trainType_;}
    inline QVector<QString> getStations() {return stations_;}
    inline QVector<QDateTime> getDepartureTimes() {return departureTimes_;}
    inline bool running() {return running_;}
    inline int rotation() {return rotation_;}

    void updateModel(QDateTime gameTime, std::shared_ptr<std::unordered_map<std::string, TrafficPlace *>> stations, int updateInterval);
    void setMovementParameters(QPointF targetStation, int updateInterval);

signals:
    void locationChanged();
    void runningChanged();
    void rotationChanged();
    void idChanged();

private:
    double distance(double x1, double y1, double x2, double y2);
    int trainNumber_;
    QString trainType_;
    QVector<QString> stations_;
    QVector<QDateTime> departureTimes_;
    bool running_;
    double distanceBetweenStations_;
    double timeToDestination_;
    double speed_;
    double rotation_;
};

#endif // VRTRAIN_H
