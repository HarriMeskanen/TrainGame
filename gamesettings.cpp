#include "gamesettings.hh"
#include <QDebug>

GameSettings::GameSettings(QObject *parent)
    :QObject(parent)
{

}

void GameSettings::initialize()
{
    qDebug() << "Gamesettings initialized";
    framerate_ = 30;
    difficulty_ = "Normal";
    gameDate_ = QDateTime::currentDateTime();
    startingCity_ = "TPE";
}

QString GameSettings::parseDateToString() {
    return gameDate_.toString("yyyy-MM-dd");
}
