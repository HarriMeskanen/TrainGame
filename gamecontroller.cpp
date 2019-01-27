#include "gamecontroller.hh"

GameController::GameController(TrainGame *game, QObject* parent)
    : QObject(parent), game_(game), navigator_(new Navigator)
{
    connect(game_->gameMap(), SIGNAL(gameObjectCreated(GameObject*)), this, SLOT(modelToView(GameObject*)));
    connect(game_, SIGNAL(gameEndingConditionReached()), this, SLOT(gameEnded()));
}

void GameController::initialize()
{

    QObject* gameMapView = engine_->rootObjects().at(0);
    if(gameMapView){
        if(game_->initialize(gameMapView)){
            std::cout << "game initialization complete" << std::endl;
            game_->startTimer();
            emit gameInitCompleted();
        }
        else std::cout << "game initialization failed to complete" << std::endl;
    }
}

void GameController::modelToView(GameObject* object)
{

    if(dynamic_cast<TrafficPlace*>(object))
        emit trafficPlaceCreated(dynamic_cast<TrafficPlace*>(object));

    else if(dynamic_cast<Rail*>(object)){
        // in case that in future versions rails
        // will be dynamically created.
        // currently this is useless
    }
    else if(dynamic_cast<Train*>(object))
        emit playerTrainCreated(dynamic_cast<Train*>(object));

    else if(dynamic_cast<VRTrain*>(object))
        emit vrTrainCreated(dynamic_cast<VRTrain*>(object));

    else if(dynamic_cast<RandomObject*>(object)) {
        RandomObject* randomObject = dynamic_cast<RandomObject*>(object);
        //qDebug() << randomObject->destination().x();
        if ( randomObject->objectType() == "Leafpile" ) {
            emit leafPileCreated(randomObject);
            qDebug() << "Leafpile created";
        } else if ( randomObject->objectType() == "Moose" ) {
            emit mooseCreated(randomObject);
            qDebug() << "Moose created";
        } else {
            qDebug() << "Random object not recognized";
        }
    }
}

Train* GameController::playerTrain()
{
    return game_->gameMap()->playerTrain();
}

void GameController::mooseClickAction(RandomObject *moose)
{
    if ( MATHFUNCTIONS::distanceFromPoint( moose->location(), playerTrain()->location() )
         < 50 ) {
        moose->setExists(false);
        game_->playerStats()->addTokens(25);
        game_->playerStats()->addMooseKilled();
    }
}


void GameController::moveAction(QString clickPoint)
{
    Train* player = playerTrain();
    TrafficPlace* startp;
    TrafficPlace* endp = game_->gameMap()->getTrafficPlace(clickPoint.toStdString());
    bool isStartpTemp = false;

    // when moveAction is called for the first time
    if(player->path().empty())
        startp = game_->gameMap()->gameMapOrigin();

    // moveAction was called after train had arrived to the previous clickPoint
    else if(player->path().size() == 1)
        startp = player->path().at(0);

    // moveAction was called before train had arrived to the previous clickPoint
    else{
        startp = new TrafficPlace(player->location(), 0);
        startp->addNeighbour(player->path().at(0));
        startp->addNeighbour(player->path().at(1));
        isStartpTemp = true;
    }
    bool found = navigator_->navigate(startp, endp);
    if(found){
        player->setPath(navigator_->path());
        player->setDirection(MATHFUNCTIONS::makeUnitVector(player->location(),
                                                           player->path().at(1)->location()));

    }
    if(isStartpTemp)
        delete startp;
    emit moveActionCompleted(found, endp->location());
}

void GameController::resetGame()
{
    game_->reset();
}

void GameController::jumpAction() {
    game_->gameMap()->playerTrain()->jumpAction();
}

void GameController::pauseGame() {
    game_->setGameRunning(false);
}

void GameController::resumeGame() {
    game_->setGameRunning(true);
}

void GameController::upgradeSpeed() {
    if (game_->playerStats()->tokens() >= 100) {
        double currentSpeed = game_->gameMap()->playerTrain()->speed();
        game_->gameMap()->playerTrain()->setSpeed(currentSpeed+25);
        game_->playerStats()->setSpeed(game_->gameMap()->playerTrain()->speed());
        game_->playerStats()->subtractTokens(100);
    }
}

void GameController::upgradeJump() {
    if (game_->playerStats()->tokens() >= 250) {
        game_->playerStats()->setJump(true);
        game_->gameMap()->playerTrain()->initializeJumpTimer();
        game_->playerStats()->subtractTokens(250);
    }
}

void GameController::repairPlayerTrain() {
    if (game_->playerStats()->tokens() >= 2*(100-(game_->playerStats()->health()))) {
        game_->playerStats()->subtractTokens(2*(100-(game_->playerStats()->health())));
        game_->playerStats()->setHealth(100);
    }
}

void GameController::clearAchievements() {
    game_->achievements()->writeEmptyAchievementFile();
}

void GameController::closeApplication() {
    game_->achievements()->writeAchievementFile();
}

void GameController::gameEnded() {
    pauseGame();
    qDebug() << game_->playerStats()->mooseKilled() << game_->playerStats()->leafPileDestroyed();
    emit showGameEndView();
}
