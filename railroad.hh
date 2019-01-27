#ifndef RAILROAD_HH
#define RAILROAD_HH

#include "rail.hh"
#include "trafficplace.hh"

#include <QQuickPaintedItem>
#include <QVector>
#include <QPainter>
#include <QPen>
#include <QMap>
#include <iostream>

/**
 * @brief The RailRoad class is used to draw graph of
 * railroad system into gamemap
 */

class RailRoad : public QQuickPaintedItem
{
    Q_OBJECT

public:
    RailRoad(QQuickItem *parent = 0);
    virtual ~RailRoad();

    /** @brief paint method is a virtual method of QQuickItem class that is called
     * whenever QQuickItems update method is called
     * @post all added rails are drawn to gamemap*/
    void paint(QPainter *painter);

    inline QMap<QString, Rail*> rails(){return rails_;}
    void addRail(Rail* rail);

signals:
    void railsChanged();

private:
    QMap<QString, Rail*> rails_;
};

#endif // RAILROAD_HH
