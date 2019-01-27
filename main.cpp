#include "traingame.hh"
#include "gamecontroller.hh"
#include "railroad.hh"
#include "rail.hh"
#include "gamemap.hh"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<RailRoad>("GameMapItems", 1, 0, "RailRoad");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    TrainGame* game = new TrainGame;
    GameController ctrl(game);
    ctrl.setEngine(&engine);

    engine.rootContext()->setContextProperty("GCtrl", &ctrl);
    engine.rootContext()->setContextProperty("GameSettings", game->gameSettings());
    engine.rootContext()->setContextProperty("PlayerStats", game->playerStats());
    engine.rootContext()->setContextProperty("Achievements", game->achievements());

    return app.exec();
}
