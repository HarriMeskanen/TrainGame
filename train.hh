#ifndef TRAIN_HH
#define TRAIN_HH

#include "gameobject.hh"
#include "gamesettings.hh"
#include "rail.hh"
#include "other.hh"
#include <QObject>
#include <QVector>
#include <QTimer>

/**
 * @brief An instance of Train class is used as a player's train during the game
 */

class Train : public QObject, public GameObject
{
    Q_OBJECT

    Q_PROPERTY(QPointF location READ location WRITE setLocation NOTIFY locationChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(double speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(QPointF direction READ direction WRITE setDirection NOTIFY directionChanged)    

public:
    Train(QPointF location, QObject* parent = 0);
    virtual ~Train();

    void updateModel(int updateInterval);
    void move(int updateInterval);

    inline QVector<TrafficPlace*> path(){return path_;}
    inline int width(){return width_;}
    inline int height(){return height_;}
    inline QString color(){return color_;}
    inline double speed(){return speed_;}
    inline QPointF direction(){return direction_;}    
    inline QDateTime hitTime(){return hitTime_;}    
    
    inline void setPath(QVector<TrafficPlace*> path){path_ = path;}    
    inline void setWidth(int width){width_ = width;}
    inline void setHeight(int height){height_ = height;}
    inline void setColor(QString color){color_ = color;}
    inline void setSpeed(double speed){speed_ = speed;}       
    inline void setHitTime(QDateTime hitTime){hitTime_ = hitTime;}    
    void setDirection(QPointF direction);

    void initializeJumpTimer();
    void jumpAction();
    void jumpAnimation();
    inline bool immune() {return immune_;}

signals:
    void locationChanged();
    void widthChanged();
    void heightChanged();
    void colorChanged();
    void speedChanged();
    void directionChanged();       

public slots:
    void endImmunity();

private:
    QVector<TrafficPlace*> path_;
    int width_;
    int height_;
    QString color_;
    double speed_;
    QPointF direction_;
    QPointF destination_;
    QDateTime hitTime_;
    QTimer* jumpTimer_;
    QTimer* jumpAnimationTimer_;
    bool immune_;
};

#endif // TRAIN_HH
