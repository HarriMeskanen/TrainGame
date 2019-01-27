#ifndef GAMECONTROLLER_HH
#define GAMECONTROLLER_HH

#include "traingame.hh"
#include "trafficplace.hh"
#include "randomobject.hh"
#include "other.hh"
#include "navigator.hh"

#include<QObject>
#include<QPointF>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

/**
 * @brief The GameController class is used to connect model and view related events
 */

class GameController : public QObject
{
    Q_OBJECT

public:
    explicit GameController(TrainGame* game, QObject* parent = 0);

    inline QList<QObject*> currentPath(){return currentPath_;}
    inline void setEngine(QQmlApplicationEngine* engine){engine_ = engine;}
    Train* playerTrain();

public slots:
    void initialize();
    void resetGame();
    void mooseClickAction(RandomObject* moose);
    void moveAction(QString clickPoint);
    void jumpAction();
    void modelToView(GameObject *object);
    void pauseGame();
    void resumeGame();
    void upgradeSpeed();
    void upgradeJump();
    void repairPlayerTrain();
    void clearAchievements();
    void closeApplication();
    void gameEnded();

signals:
    void gameInitCompleted();
    void trafficPlaceCreated(TrafficPlace* trafficPlace);
    void vrTrainCreated(VRTrain* vrTrain);
    void leafPileCreated(RandomObject* randomObject);
    void mooseCreated(RandomObject* randomObject);
    void playerTrainCreated(Train* train);
    void currentPathChanged(double length);
    void moveActionCompleted(bool status, QPointF clickPoint);
    void showGameEndView();

private:
    TrainGame* game_;
    QQmlApplicationEngine* engine_;
    Navigator* navigator_;
    QList<QObject*> currentPath_;
};

#endif // GAMECONTROLLER_HH
