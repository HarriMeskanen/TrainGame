#include "gamemap.hh"

#include <QDebug>


GameMap::GameMap(QObject *parent)
    :QObject(parent), railRoad_(), nonMovableLeft_(0), movableLeft_(0), maxRandom_(4), respawnTime_{8}
{
    //std::random_device rd; // obtain a random number from hardware, useless now
    std::mt19937 eng(time(0)); // seed the generator with current time
    rng_ = eng;
}

GameMap::~GameMap()
{

}


bool GameMap::initializeStationsAndRails(QObject* gameMapView,
                         std::shared_ptr<std::unordered_map<std::string, TrafficPlace *> > map,
                                         QString startingStation)
{
    gameMapView_ = gameMapView;
    QObject* railRoadView = gameMapView->findChild<QObject*>("railRoadView");
    if(!railRoadView)
        return false;
    railRoad_ = dynamic_cast<RailRoad*>(railRoadView);
    trafficPlaceMap_ = map;

    for (auto it = map->begin(); it != map->end(); ++it ) {
        if(it->first == startingStation.toStdString()){
            std::cout << "Asema " << startingStation.toStdString() << " set as gameMapOrigin" << std::endl;
            gameMapOrigin_ = it->second;
        }

        // All stations are added to trafficPlaces_, but only those that have no nearby station are added
        // to the view with gameObjectCreated() signal. Otherwise the screen is too crowded.
        if(it->second->isTraffic()){
            if (trafficPlaces_.isEmpty()) {
                trafficPlaces_.append(it->second);
            } else if (!tooClose(it->second)) {
                trafficPlaces_.append(it->second);
                emit gameObjectCreated(it->second);
            } else {
                trafficPlaces_.append(it->second);
            }
        }

        std::vector<TrafficPlace *> neighbours = it->second->getNeighbours();
        for (auto it2 = neighbours.begin(); it2 != neighbours.end(); it2++) {
            TrafficPlace *temp = *it2;
            Rail *railToAdd = new Rail(it->second->location(),
                                       temp->location(),
                                       QString::fromStdString(it->first)+temp->stationShortCode());

            if (!isRailInRailRoad(railToAdd)) {
                railRoad_->addRail(railToAdd);
                emit gameObjectCreated(railToAdd);
            }
        }
    }
    std::cout << "Raiteiden lkm: " << railRoad_->rails().size() << std::endl;
    std::cout << "TrafficPlacejen lkm: " << trafficPlaceMap_.get()->size() << std::endl;

    // At this point we insert the random objects
    // insertRandoms();


    std::cout << "Raiteiden lkm: " << railRoad_->rails().size() << std::endl;

    // railroad item is updated only once after full creation
    // to enhance performance... update() method calls QQuickItem's
    // paint() method which will draw the item into view
    railRoad_->update();
    playerTrain_ = new Train(gameMapOrigin_->location());
    emit gameObjectCreated(playerTrain_);

    return true;
}

bool GameMap::initializeVRTrains(std::shared_ptr<std::unordered_map<int, VRTrain *>> vrTrains) {    
    vrTrains_ = vrTrains;

    std::unordered_map<int, VRTrain *>::const_iterator it = vrTrains->begin();
    while (it != vrTrains->end()) {
        emit gameObjectCreated(it->second);
        it++;
    }

    std::cout << "VRTrain lukumäärä: " << vrTrains_->size() << std::endl;
    return true;
}

bool GameMap::tooClose(TrafficPlace *station) {
    for (int i = 0; i < trafficPlaces_.size(); i++) {
        if (MATHFUNCTIONS::distanceFromObject(station,trafficPlaces_.at(i)) < 15.0) {
            return true;
        }
    }
    return false;
}

bool GameMap::isRailInRailRoad(Rail *railToBeAdded) {
    for(Rail* rail : railRoad_->rails()) {
        if(rail->p1() == railToBeAdded->p2() && rail->p2() == railToBeAdded->p1()){
            return true;
        }
    }
    return false;
}

TrafficPlace* GameMap::getTrafficPlace(std::string id)
{
    return trafficPlaceMap_->at(id);
}

void GameMap::update(QDateTime gameTime, int updateInterval)
{
    if(playerTrain_)
        playerTrain_->updateModel(updateInterval);

    if (playerTrain_->hitTime().msecsTo(gameTime) > 120000) {
        playerTrain_->setColor("black");
    }

    std::unordered_map<int,VRTrain *>::iterator it = vrTrains_->begin();
    while (it != vrTrains_->end()) {

        if ( it->second != nullptr ) {
            VRTrain * trainToBeUpdated = it->second;
            // If the train has only one station, it has reached its destination and it will be removed
            // from the GameMap. Otherwise it's position will be updated.
            if (trainToBeUpdated->getStations().length() == 1) {

                QObject* vrTrainView = gameMapView_->findChild<QObject*>(it->second->id());
                if(vrTrainView)
                delete vrTrainView;
                delete it->second;
                it->second = nullptr;
                emit vrTrainReachedDestination();
            } else {
                trainToBeUpdated->updateModel(gameTime,trafficPlaceMap(),updateInterval);
                // Check, if the player has hit a VRTrain
                // First check if the playertrain is not immune (which it is during jump).
                if (!playerTrain_->immune()) {
                    // If the playerTrain path_ is shorter than 1, it means that the playerTrain is at a station.
                    // Hits are only count if playerTrain is on the same track part with another VRTrain.
                    if (playerTrain_->path().length() > 1) {
                        if ( playerTrain_->objectClose(trainToBeUpdated) ) {
                            // First time the playerTrain hits VRTrain, we must initialize hitTime_
                            if (playerTrain()->hitTime().isNull()) {
                                playerTrain_->setColor("red");
                                playerTrain_->colorChanged();
                                playerTrain_->setHitTime(gameTime);
                                emit vrTrainHit();
                                emit playerTrainHit();
                            }
                            // After player has hit a VRTrain, it has immunity of 120000 mSecs in gameTime.
                            // This is equivalent to 2 seconds in real time.
                            else if (playerTrain_->hitTime().msecsTo(gameTime) > 120000) {
                                playerTrain_->setColor("red");
                                playerTrain_->colorChanged();
                                playerTrain_->setHitTime(gameTime);
                                emit vrTrainHit();
                                emit playerTrainHit();
                            }
                        }
                    }
                }
            }
        }

        it++;
    }

    // Update randomObjects
    // At the beginnig the times are not valid, they are fixed
    // at the first update
    if ( !removeTimeMovable_.isValid() ) {
        removeTimeMovable_ = gameTime;
        removeTimeMovable_.addSecs(-100);
    }
    if ( !removeTimeNonMovable_.isValid() ) {
        removeTimeNonMovable_ = gameTime;
        removeTimeNonMovable_.addSecs(-100);
    }
    insertRandoms(gameTime);
    QList<RandomObject *>::iterator rIt = randomObjects_.begin();
    while (rIt != randomObjects_.end()) {
        if ( !(*rIt)->exists() ) {
            (*rIt)->updateModel(updateInterval);

            delete (*rIt);
            rIt = randomObjects_.erase(rIt);
            --movableLeft_;
            if ( removeTimeMovable_.secsTo(gameTime) < 2 ) {
                removeTimeMovable_ = gameTime;
            }
            continue;
        }
        if ( (*rIt)->objectClose(playerTrain_) ) {
            if ( (*rIt)->objectType() == "Leafpile" ) {

                QObject* randomObjectView = gameMapView_->findChild<QObject*>((*rIt)->id());
                if(randomObjectView){
                    delete randomObjectView;
                    if(blackListedRandomObjectIds_.contains((*rIt)->id())){
                        blackListedRandomObjectIds_.remove((*rIt)->id());
                    }
                }
                (*rIt)->setExists(false);
                emit leafPileDestroyed();
                (*rIt)->updateModel(updateInterval);
                delete (*rIt); // At this state, we do not want to delete before QML
                rIt = randomObjects_.erase(rIt);
                --nonMovableLeft_;
                // If difference between last removal and current gametiem is small
                // the removal time will be move to new one, thus new objects are created
                // later in game.
                if ( removeTimeNonMovable_.secsTo(gameTime) < 2 ) {
                    removeTimeNonMovable_ = gameTime;
                }
                continue;
            }
        }
        (*rIt)->updateModel(updateInterval);

        ++rIt;
    }
}

void GameMap::insertRandoms(QDateTime gameTime)
{

    // First insert non movable objects
    if ( removeTimeNonMovable_.secsTo(gameTime) > respawnTime_ ) {
        while( nonMovableLeft_ < maxRandom_ ) {
            // Find a random place
            std::uniform_int_distribution<> placeRange(0, trafficPlaces_.size()-1);
            int placeIndex = placeRange(rng_);
            if(blackListedRandomObjectIds_.contains(QString::fromStdString(std::to_string(placeIndex))))
                continue;
            qDebug() << placeIndex;
            TrafficPlace* randomPlace = trafficPlaces_.at(placeIndex);

            // Find a random neighbour
            int neighbourIndex;
            if ( randomPlace->neighbours().size() == 0 ){
                continue;
            } else if ( randomPlace->neighbours().size() == 1 ){
                neighbourIndex = 0;
            } else {
            std::uniform_int_distribution<> neighbourRange(0,
                                                           randomPlace->neighbours().size()-1);
            neighbourIndex = neighbourRange(rng_);
            }
            TrafficPlace* randomNeighbour = randomPlace->neighbours().at(neighbourIndex);

            // Calculate location for object
            qreal newX = randomPlace->location().x() +
                         0.5*(randomPlace->location().x() - randomNeighbour->location().x());
            qreal newY = randomPlace->location().y() +
                         0.5*(randomPlace->location().y() - randomNeighbour->location().y());

            QVector<QPointF> randomV;
            randomV.append({newX,newY});

            // Create object
            RandomObject* objectToAdd = new RandomObject("Leafpile",false,0,randomV,
                                                         QString::fromStdString(std::to_string(placeIndex)));
            randomObjects_.append(objectToAdd);
            blackListedRandomObjectIds_.insert(QString::fromStdString(std::to_string(placeIndex)), placeIndex);
            emit gameObjectCreated(objectToAdd);

            ++nonMovableLeft_;
        }

    }

    // Insert movable objects
    while( movableLeft_ < maxRandom_ ) {
        QVector<QPointF> randomV;
        for ( int n=4; n>0; n-- ) {
            std::uniform_int_distribution<> xRange(100, 500);
            std::uniform_int_distribution<> yRange(300, 600);
            int xValue = xRange(rng_);
            int yValue = yRange(rng_);
            randomV.append(QPointF(xValue,yValue));
        }

        RandomObject* objectToAdd = new RandomObject("Moose",true,0.5,randomV,
                                                     QString::fromStdString(std::to_string(randomV.at(0).x())));
        randomObjects_.append(objectToAdd);
        emit gameObjectCreated(objectToAdd);

        ++movableLeft_;
    }
    return;
}

void GameMap::changeDifficulty(QString difficulty)
{
    if ( difficulty == "Easy" ) {
        respawnTime_ = 12;
        maxRandom_ = 2;
        std::cout << "Difficulty for gameMap: Easy" << std::endl;
    } else if ( difficulty == "Normal" ) {
        respawnTime_ = 8;
        maxRandom_ = 4;
        std::cout << "Difficulty for gameMap: Normal" << std::endl;
    } else if ( difficulty == "Hard" ) {
        respawnTime_ = 6;
        maxRandom_ = 8;
        std::cout << "Difficulty for gameMap: Hard" << std::endl;
    } else if ( difficulty == "Ultimate" ) {
        respawnTime_ = 3;
        maxRandom_ = 12;
        std::cout << "Difficulty for gameMap: Ultimate" << std::endl;
    } else {
        std::cout << "Invalid difficulty for gameMap." << std::endl;
    }
    return;
}

void GameMap::reset()
{
    QObject* playerTrainView = gameMapView_->findChild<QObject*>("playerTrain");
    if(playerTrainView)
        delete playerTrainView;
    if(playerTrain_)
        delete playerTrain_;
    if(railRoad_)
        delete railRoad_;

    QList<QObject*> trafficPlaceViews = gameMapView_->findChildren<QObject*>("trafficPlace");
    for(QObject* trafficPlace : trafficPlaceViews)
        delete trafficPlace;

    if(trafficPlaceMap_){
        auto iter = trafficPlaceMap_->begin();
        while(iter != trafficPlaceMap_->end()){
            delete iter->second;
            iter++;
        }
        trafficPlaceMap_->clear();
    }

    if(vrTrains_){
        auto iter2 = vrTrains_->begin();
        while(iter2 != vrTrains_->end()){
            if(!iter2->second){
                iter2++;
                continue;
            }
            QString id = iter2->second->id();
            QObject* trainView = gameMapView_->findChild<QObject*>(id);
            if(trainView)
                delete trainView;
            delete iter2->second;
            iter2++;
        }
        vrTrains_->clear();
    }


    if(!trafficPlaces_.empty()){
        trafficPlaces_.clear();
    }

    if(!randomObjects_.empty()){
        for(RandomObject* object : randomObjects_)
            delete object;
        randomObjects_.clear();
    }
    blackListedRandomObjectIds_.clear();
    nonMovableLeft_ = 0;
    movableLeft_ = 0;
    maxRandom_ = 4;
    respawnTime_ = 8;
}
