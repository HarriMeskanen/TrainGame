#include "stats.hh"

Stats::Stats(QObject *parent)
    :QObject(parent), tokens_{100}, totalTokens_{100}, health_{100}, speed_{150},
      jump_{false}, happiness_{100}, leafPileDestroyed_{0}, mooseKilled_{0}
{

}

void Stats::reset()
{
    happiness_ = 100;
    health_ = 100;
    tokens_ = 100;
    leafPileDestroyed_ = 0;
    mooseKilled_ = 0;
    totalTokens_ = 100;
    jump_ = false;
    emit happinessChanged();
    emit healthChanged();
    emit tokensChanged();
}

int Stats::tokens() {
    int tokensInt = tokens_;
    return tokensInt;
}

void Stats::addTokens(double toBeAdded) {
    tokens_ = tokens_ + toBeAdded;
    totalTokens_ = totalTokens_ + toBeAdded;
    emit tokensChanged();
}

void Stats::subtractTokens(double toBeSubtracted) {
    tokens_ = tokens_ - toBeSubtracted;
    emit tokensChanged();
}

void Stats::addHappiness(int toBeAdded) {
    happiness_ = happiness_ + toBeAdded;
    emit happinessChanged();
}

void Stats::addGameTime(int secs) {
    gameTime_ = gameTime_.addSecs(secs);
    emit gameTimeStrChanged();
}

QString Stats::gameTimeStr() {
    return gameTime_.toString(Qt::SystemLocaleShortDate);
}

QString Stats::gameTimeStrDate () {
    return gameTime_.toString("dd.mm.yyyy");
}
