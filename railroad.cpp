#include "railroad.hh"

RailRoad::RailRoad(QQuickItem *parent)
    :QQuickPaintedItem(parent)
{

}

RailRoad::~RailRoad()
{
    /*auto iter = rails_.begin();
    while(iter != rails_.end())
        delete iter.value();*/
    qDeleteAll(rails_);

    rails_.clear();
}

void RailRoad::addRail(Rail *rail)
{
    rails_.insert(rail->id(), rail);
    emit railsChanged();
}

void RailRoad::paint(QPainter *painter)
{

    QPen pen(QColor("dimgray"), 2);
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
    painter->setRenderHints(QPainter::Antialiasing, true);

    for(auto iter = rails_.begin(); iter != rails_.end(); iter++){
        painter->drawLine(iter.value()->p1(),
                          iter.value()->p2());
    }
}
