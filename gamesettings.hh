#ifndef GAMESETTINGS_HH
#define GAMESETTINGS_HH

#include "trafficplace.hh"
#include <QObject>
#include <iostream>
#include <QDateTime>

/**
 * @brief The GameSettings class contains settings chosen by player in game's starting view
 */

class GameSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString playerName READ playerName WRITE setPlayerName NOTIFY playerNameChanged)
    Q_PROPERTY(QPointF gameMapOrigin READ gameMapOrigin WRITE setGameMapOrigin NOTIFY gameMapOriginChanged)
    Q_PROPERTY(int framerate READ framerate WRITE setFramerate NOTIFY framerateChanged)
    Q_PROPERTY(QString difficulty READ difficulty WRITE setDifficulty NOTIFY difficultyChanged)
    Q_PROPERTY(QDateTime gameDate READ gameDate WRITE setGameDate NOTIFY gameDateChanged)
    Q_PROPERTY(QString startingCity READ startingCity WRITE setStartingCity NOTIFY startingCityChanged)

public:
    GameSettings(QObject* parent = 0);
    void initialize();

    inline QString playerName(){return playerName_;}
    QPointF gameMapOrigin(){return gameMapOrigin_;}

    void setPlayerName(QString playerName){playerName_ = playerName;}
    inline void setGameMapOrigin(QPointF origin) {gameMapOrigin_ = origin;}

    inline int framerate() {return framerate_;}
    inline void setFramerate(int framerate) {framerate_ = framerate;}

    inline QString difficulty() {return difficulty_;}
    inline void setDifficulty(QString difficulty) {difficulty_ = difficulty;}

    inline QDateTime gameDate() {return gameDate_;}
    inline void setGameDate(QDateTime gameDate) {gameDate_ = gameDate;}
    QString parseDateToString();

    inline QString startingCity() {return startingCity_;}
    inline void setStartingCity(QString startingCity) {startingCity_ = startingCity;}

signals:
    void playerNameChanged();
    void gameMapOriginChanged();
    void framerateChanged();
    void difficultyChanged();
    void gameDateChanged();
    void startingCityChanged();

private:
    QString playerName_;
    QPointF gameMapOrigin_;

    int framerate_;
    QString difficulty_;
    QDateTime gameDate_;
    QString startingCity_;
};

#endif // GAMESETTINGS_HH
