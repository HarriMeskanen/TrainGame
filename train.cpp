#include "train.hh"
#include <QDebug>

Train::Train(QPointF location, QObject *parent)
    :QObject(parent), GameObject(location.x(), location.y(), 1),
      width_(25), height_(10), color_("black"), speed_(150), direction_(QPointF(1, 0)),
      jumpAnimationTimer_{0}, immune_{false}
{

}

Train::~Train()
{

}

void Train::setDirection(QPointF direction)
{
    direction_ = direction;
    emit directionChanged();
}

void Train::updateModel(int updateInterval)
{
    // for the very least path must contain startpoint (path_.at(0)) and endpoint (path_.at(1))
    jumpAnimation();
    if(path_.size() > 1){

        if(MATHFUNCTIONS::distanceFromPoint(location_, path_.at(1)->location()) >= speed_*(1.0/updateInterval)){
            move(updateInterval);
        }
        else{
            location_ = path_.at(1)->location();
            path_.pop_front();
            if(path_.size() > 1){
                direction_ = MATHFUNCTIONS::makeUnitVector(location_, path_.at(1)->location());
                emit directionChanged();
            }
        }
        emit locationChanged();        
        emit colorChanged();
    }
}


void Train::move(int updateInterval)
{
    location_.setX(location_.x() + speed_*direction_.x()*(1.0/updateInterval));
    location_.setY(location_.y() + speed_*direction_.y()*(1.0/updateInterval));
}

void Train::initializeJumpTimer() {
    jumpTimer_ = new QTimer;
    jumpTimer_->setSingleShot(true);
    jumpTimer_->start(500);

    jumpAnimationTimer_ = new QTimer;
    jumpAnimationTimer_->setSingleShot(true);
    connect(jumpAnimationTimer_, SIGNAL(timeout()), this, SLOT(endImmunity()));
}

void Train::jumpAction() {
    // Player can jump only every 2 seconds.
    if (jumpTimer_->remainingTime() == -1) {
        // Jump
        jumpAnimationTimer_->start(1000);
        // Player is immune during the jump
        immune_ = true;
        // Reset the cooldown timer
        jumpTimer_->start(2000);
    }
}

void Train::jumpAnimation() {
    if (jumpAnimationTimer_ == nullptr) {
        return;
    } else if (jumpAnimationTimer_->remainingTime() != -1) {
        double t = jumpAnimationTimer_->remainingTime();
        width_ = 25 + (-6e-5*t*t+0.06*t-0.0384);
        height_ = 10 + (-4e-5*t*t+0.042*t+0.046);
        emit widthChanged();
        emit heightChanged();
    }
}

void Train::endImmunity () {
    immune_ = false;
}
