#ifndef TRAINGAME_HH
#define TRAINGAME_HH

#include "gameobject.hh"
#include "gamemap.hh"
#include "trafficplace.hh"
#include "train.hh"
#include "gamesettings.hh"
#include "stats.hh"
#include "achievements.hh"

#include <QObject>
#include <QTimer>

/**
 * @brief The TrainGame class is the main class of the application. It contains
 * all the information and logic related to the game.
 */

class TrainGame: public QObject
{
    Q_OBJECT
public:
    explicit TrainGame(QObject* parent = 0);
    bool initialize(QObject *gameMapView);
    void reset();
    bool initializeGameTime();
    inline GameMap* gameMap(){return gameMap_;}
    TrafficPlace* getTrafficPlace(std::string id);
    inline GameSettings* gameSettings(){return &gameSettings_;}
    inline Stats* playerStats() {return &playerStats_;}
    void startTimer();
    inline void setGameRunning(bool running) {gameRunning_ = running;}
    inline Achievements* achievements() {return achievements_;}

public slots:
    void sendUpdateNotification();
    void sendAddHappiness();
    void sendSubtractHappiness();
    void updateHealth();
    void checkForNewAchievements();
    void leafPileDestroyed();

signals:
    void gameEndingConditionReached();

private:
    GameSettings gameSettings_;
    Achievements* achievements_;
    GameMap* gameMap_;
    QTimer* timer_;
    QTimer* achievementTimer_;
    DataReader dataReader_;
    Stats playerStats_;
    bool gameRunning_;
};

#endif // TRAINGAME_HH
