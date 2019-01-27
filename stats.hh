
#ifndef STATS_HH
#define STATS_HH

#include <QObject>
#include <QDateTime>

//
/**
 * @brief Stats is a class that contains information about players game progression.
 *  Bought abilities and upgrades are saved here.
 *  Stats has also information about players current wealth.
*/
class Stats: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int tokens READ tokens NOTIFY tokensChanged)
    Q_PROPERTY(int totalTokens READ totalTokens)
    Q_PROPERTY(QString gameTimeStr READ gameTimeStr NOTIFY gameTimeStrChanged)
    Q_PROPERTY(QString gameTimeStrDate READ gameTimeStrDate NOTIFY gameTimeStrDateChanged)
    Q_PROPERTY(int happiness READ happiness WRITE setHappiness NOTIFY happinessChanged)
    Q_PROPERTY(int health READ health WRITE setHealth NOTIFY healthChanged)
    Q_PROPERTY(bool jump READ jump WRITE setJump NOTIFY jumpChanged)
    Q_PROPERTY(double speed READ speed WRITE setSpeed NOTIFY speedChanged)

public:
    Stats(QObject* parent = 0);

    void reset();
    int tokens();
    inline void setTokens (double newTokens) {tokens_ = newTokens; emit tokensChanged();}
    void addTokens(double toBeAdded);
    void subtractTokens(double toBeSubtracted);

    inline double totalTokens() {return totalTokens_;}

    inline int happiness() {return happiness_;}
    inline void setHappiness(int happiness) {happiness_ = happiness; emit happinessChanged();}
    void addHappiness(int toBeAdded);
    inline void subtractHappiness(int toBeSubtracted) {happiness_ = happiness_ - toBeSubtracted; emit happinessChanged();}

    inline void setGameTime(QDateTime gameTime) {gameTime_ = gameTime;}
    inline QDateTime getGameTime() {return gameTime_;}
    void addGameTime(int secs);

    inline void setGameEndTime(QDateTime gameEndtime) {gameEndTime_ = gameEndtime;}
    inline QDateTime getGameEndTime() {return gameEndTime_;}

    inline int health() {return health_;}
    inline void setHealth(int health) {health_ = health; emit healthChanged();}
    inline void subtractHealth(int toBeSubtracted) {health_ = health_ - toBeSubtracted; emit healthChanged();}

    inline bool jump() {return jump_;}
    inline void setJump(bool jump) {jump_ = jump; emit jumpChanged();}

    inline int speed() {return speed_;}
    inline void setSpeed(double speed) {speed_ = speed; emit speedChanged();}

    inline int leafPileDestroyed() {return leafPileDestroyed_;}
    inline void addLeafPileDestroyed() {leafPileDestroyed_ = leafPileDestroyed_ + 1;}

    inline int mooseKilled() {return mooseKilled_;}
    inline void addMooseKilled() {mooseKilled_ = mooseKilled_ + 1;}

    QString gameTimeStr();
    QString gameTimeStrDate();

signals:
    void tokensChanged();
    void happinessChanged();
    void gameTimeStrChanged();
    void gameTimeStrDateChanged();
    void healthChanged();
    void jumpChanged();
    void speedChanged();

private:
    double tokens_;
    double totalTokens_;
    int health_;
    double speed_;
    bool jump_;
    int happiness_;
    QDateTime gameTime_;
    QDateTime gameEndTime_;
    int leafPileDestroyed_;
    int mooseKilled_;
};

#endif // STATS_HH
