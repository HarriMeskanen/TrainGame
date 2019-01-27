#include "traingame.hh"

TrainGame::TrainGame(QObject *parent)
    :QObject(parent), achievements_(new Achievements) ,gameMap_(new GameMap), timer_(new QTimer),
      achievementTimer_(new QTimer)
{
    connect(timer_, SIGNAL(timeout()), this, SLOT(sendUpdateNotification()));
    connect(achievementTimer_, SIGNAL(timeout()), this, SLOT(checkForNewAchievements()));
    connect(gameMap(), SIGNAL(vrTrainHit()), this, SLOT(sendSubtractHappiness()));
    connect(gameMap(), SIGNAL(playerTrainHit()), this, SLOT(updateHealth()));
    connect(gameMap(), SIGNAL(vrTrainReachedDestination()), this, SLOT(sendAddHappiness()));
    connect(gameMap(), SIGNAL(leafPileDestroyed()), this, SLOT(leafPileDestroyed()));
    gameSettings_.initialize();
    achievements_->initialize();
    achievementTimer_->setInterval(2000);
    achievementTimer_->start();
}

bool TrainGame::initialize(QObject* gameMapView)
{
    if(!gameMap_->initializeStationsAndRails(gameMapView,
                             dataReader_.readPlaceAndTrackData(
                                 ":/resources/asemadata.json",
                                 ":/resources/ratadatav2.json"),gameSettings_.startingCity())){
        std::cout << "gamemap init failed" << std::endl;
        return false;
    }

    if (!gameMap_->initializeVRTrains(dataReader_.readTimetable(gameSettings()->parseDateToString(),
                                                                gameMap_->trafficPlaceMap()))) {
            std::cout << "VRTrains init failed" << std::endl;
    }

    gameSettings_.setGameMapOrigin(gameMap_->gameMapOrigin()->location());
    gameMap_->changeDifficulty(gameSettings_.difficulty());

    if(!initializeGameTime()) {
        std::cout << "gameTime init failed";
        return false;
    }
    gameRunning_ = true;
    return true;
}

TrafficPlace* TrainGame::getTrafficPlace(std::string id)
{
    return gameMap_->getTrafficPlace(id);
}

bool TrainGame::initializeGameTime() {
    std::shared_ptr<std::unordered_map<int, VRTrain *>> paivanJunat =  gameMap_->vrTrains();
    QDateTime firstDeparture;
    QDateTime lastArrival;

    std::unordered_map<int,VRTrain *>::const_iterator it = paivanJunat->begin();
    if (it == paivanJunat->end()) {
        qDebug() << "gameTime init failed";
        return false;
    } else {
        while (it != paivanJunat->end()) {
            if (firstDeparture.isNull()) {
                firstDeparture = it->second->getDepartureTimes().at(0);
                lastArrival = it->second->getDepartureTimes().back();
            } else if (firstDeparture.toMSecsSinceEpoch() > it->second->getDepartureTimes().at(0).toMSecsSinceEpoch()) {
                firstDeparture = it->second->getDepartureTimes().at(0);
            } else if (lastArrival.toMSecsSinceEpoch() < it->second->getDepartureTimes().back().toMSecsSinceEpoch()) {
                lastArrival = it->second->getDepartureTimes().back();
            }
            it++;
        }
    }
    playerStats_.setGameTime(firstDeparture);
    playerStats_.setGameEndTime(lastArrival);
    qDebug() << "peliaika on " << firstDeparture.toString();
    qDebug() << "lopetusaika on" << lastArrival.toString();
    return true;
}

void TrainGame::startTimer()
{
    timer_->setInterval(1000/gameSettings_.framerate());
    timer_->start();
    qDebug() << "Timer started with framerate of " << gameSettings_.framerate();
}

void TrainGame::sendUpdateNotification()
{
    // Each time the timer send timeout() signal, the gametime progresses 20 seconds
    // As timer sends timeout signal 30 times in a second, this means that the gametime progresses 10 minutes each second
    if (gameRunning_) {
        playerStats_.addGameTime((30.0/gameSettings_.framerate())*20.0);
        playerStats_.addTokens((30.0/gameSettings_.framerate())*0.05);
        gameMap_->update(playerStats_.getGameTime(),gameSettings_.framerate());
        if (playerStats_.getGameTime().toMSecsSinceEpoch() > playerStats_.getGameEndTime().toMSecsSinceEpoch()) {
            emit gameEndingConditionReached();
        }
    }
    return;
}


void TrainGame::reset()
{
    timer_->stop();
    gameMap_->reset();
    playerStats_.reset();
}


void TrainGame::sendSubtractHappiness() {
    playerStats_.subtractHappiness(10);
    if (playerStats_.happiness() <= 0) {
        emit gameEndingConditionReached();
    }
}

void TrainGame::updateHealth() {
    playerStats_.subtractHealth(10);
    if (playerStats_.health() <= 0) {
        emit gameEndingConditionReached();
    }
}

void TrainGame::sendAddHappiness() {
    playerStats_.addHappiness(5);
}

void TrainGame::leafPileDestroyed() {
    playerStats_.addTokens(25);
    playerStats_.addLeafPileDestroyed();
}

void TrainGame::checkForNewAchievements() {
    // We are checking for new achievements every 2 seconds
    if (playerStats()->totalTokens() >= 500) {
        achievements_->achievementAchieved(0);
    } if (playerStats()->totalTokens() >= 1000) {
        achievements_->achievementAchieved(1);
    } if (playerStats()->totalTokens() >= 1500) {
        achievements_->achievementAchieved(2);
    } if (playerStats()->leafPileDestroyed() >= 5) {
        achievements_->achievementAchieved(3);
    } if (playerStats()->leafPileDestroyed() >= 10) {
        achievements_->achievementAchieved(4);
    } if (playerStats()->leafPileDestroyed() >= 25) {
        achievements_->achievementAchieved(5);
    } if (playerStats()->mooseKilled() >= 5) {
        achievements_->achievementAchieved(6);
    } if (playerStats()->mooseKilled() >= 10) {
        achievements_->achievementAchieved(7);
    } if (playerStats()->mooseKilled() >= 25) {
        achievements_->achievementAchieved(8);
    } if (gameSettings()->framerate() == 60) {
        achievements_->achievementAchieved(9);
    }
}
