#ifndef RANDOMOBJECT_HH
#define RANDOMOBJECT_HH

#include "gameobject.hh"
#include "gamesettings.hh"
#include "other.hh"

#include <QObject>
#include <QVector>


/**
 * @brief Instances of RandomObject class are used as obstacles
 * that spawn on to the gamemap to cause havoc
 */
class RandomObject : public QObject, public GameObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    Q_PROPERTY(RandomObject* pointer READ pointer)
    Q_PROPERTY(bool exists READ exists NOTIFY existsChanged)
    Q_PROPERTY(QPointF location READ location NOTIFY locationChanged)
    //Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    //Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    //Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(double speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(double rotation READ rotation NOTIFY rotationChanged)
    //Q_PROPERTY(QPointF destination READ destination WRITE setDestination NOTIFY destinationChanged)

public:
    RandomObject(QObject *parent = 0);
    RandomObject(QString objectType, bool movable, double speed, QVector<QPointF> route, QString id);

    void updateModel(int updateInterval);
    inline QString id(){return id_;}
    //inline int width(){return width_;}
    //inline int height(){return height_;}
    //inline QString color(){return color_;}
    inline QString objectType(){return objectType_;}
    inline RandomObject* pointer(){return this;}
    inline bool exists(){return exists_;}
    inline QPointF location(){return location_;}
    inline QPointF destination(){return *destination_;}
    inline double speed(){return speed_;}
    inline double rotation(){return rotation_;}
    void move(int updateInterval);

    //inline void setWidth(int width){width_ = width;}
    //inline void setHeight(int height){height_ = height;}
    //inline void setColor(QString color){color_ = color;}
    inline void setSpeed(double speed){speed_ = speed;}
    inline void setRotation(double rotation){rotation_ = rotation;}
    inline void setExists(bool exists){exists_ = exists;}
    //inline void setDestination(QPointF destination){destination_ = destination;}

signals:
    void existsChanged();
    void locationChanged();
    //void widthChanged();
    //void heightChanged();
    //void colorChanged();
    void speedChanged();
    void rotationChanged();
    void destinationChanged();
    void idChanged();

private:
    //int width_;
    //int height_;
    //QString color_;
    QString objectType_;
    bool exists_;
    double speed_;
    double rotation_;
    QVector<QPointF> route_;
    QVector<QPointF>::const_iterator destination_;
    QString id_;
};

#endif // RANDOMOBJECT_HH
