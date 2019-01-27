#ifndef GAMEMAP_HH
#define GAMEMAP_HH

#include "rail.hh"
#include "datareader.hh"
#include "railroad.hh"
#include "train.hh"
#include "randomobject.hh"

#include <QObject>
#include <QList>
#include <QSet>
#include <QVector>
#include <unordered_set>
#include <random>

/**
 * @brief The GameMap class contains all the game's gameobjects
 */

class GameMap : public QObject
{
    Q_OBJECT

public:
    GameMap(QObject* parent = 0);
    virtual ~GameMap();
    bool initializeStationsAndRails(QObject *gameMapView,
                    std::shared_ptr<std::unordered_map<std::string,TrafficPlace *>> Map, QString startingStation);
    bool initializeVRTrains(std::shared_ptr<std::unordered_map<int, VRTrain *>> vrTrains);
    void reset();
    void changeDifficulty(QString difficulty);


    inline RailRoad* railRoad(){return railRoad_;}
    inline std::shared_ptr<std::unordered_map<std::string, TrafficPlace *>> trafficPlaceMap() {return trafficPlaceMap_;}
    inline std::shared_ptr<std::unordered_map<int, VRTrain *>> vrTrains() {return vrTrains_;}

    void setRailRoad(RailRoad* railRoad){railRoad_ = railRoad;}
    TrafficPlace* getTrafficPlace(std::string id);
    inline TrafficPlace* gameMapOrigin(){return gameMapOrigin_;}
    inline Train* playerTrain(){return playerTrain_;}
    void update(QDateTime gameTime, int updateInterval);
    void insertRandoms(QDateTime gameTime);
    bool tooClose(TrafficPlace* station);

signals:
    void gameObjectCreated(GameObject* object);
    void gameObjectDestroyed(GameObject* object);
    void vrTrainHit();
    void playerTrainHit();
    void vrTrainReachedDestination();
    void leafPileDestroyed();

private:
    bool isRailInRailRoad(Rail * railToBeAdded);
    QObject* gameMapView_;
    RailRoad* railRoad_;
    QList<TrafficPlace*> trafficPlaces_;
    std::shared_ptr<std::unordered_map<std::string, TrafficPlace *>> trafficPlaceMap_;
    std::shared_ptr<std::unordered_map<int, VRTrain *>> vrTrains_;
    QList<RandomObject *> randomObjects_;
    TrafficPlace* gameMapOrigin_;
    Train* playerTrain_;
    QMap<QString, int> blackListedRandomObjectIds_;

    // randomObject related stuff
    std::mt19937 rng_;
    QDateTime removeTimeNonMovable_;
    QDateTime removeTimeMovable_;
    int nonMovableLeft_;
    int movableLeft_;
    int maxRandom_;
    qint64 respawnTime_;


};

#endif // GAMEMAP_HH
