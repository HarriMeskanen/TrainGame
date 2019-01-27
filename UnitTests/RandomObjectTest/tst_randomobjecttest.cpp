
#include "gameobject.hh"
#include "randomobject.hh"
#include "other.hh"

#include <QString>
#include <QVector>
#include <QtTest>

// This class is written in order to do the unit tests for the DataReader class
// of TrainGame.

class RandomObjectTest : public QObject
{
    Q_OBJECT

public:
    RandomObjectTest();

private Q_SLOTS:
    void creationTest();
    void attributeTest();
    //void moveTest();
};

RandomObjectTest::RandomObjectTest()
{
}

void RandomObjectTest::creationTest()
{
    QVector<QPointF> route;
    route.push_back({0,0});
    route.push_back({1,1});
    RandomObject* testObject1 = new RandomObject("Moose", true, 1, route);
    QCOMPARE(testObject1 != nullptr, true);
    QCOMPARE(testObject1->exists(), true);
}


void RandomObjectTest::attributeTest()
{
    QVector<QPointF> route;
    route.push_back({0,0});
    route.push_back({1,1});
    RandomObject* testObject1 = new RandomObject("Moose", true, 1, route);

    QCOMPARE(testObject1->objectType() == "Moose", true);
    QCOMPARE(testObject1->speed() == 1, true);
    QPointF point1 = {0,0};
    QPointF point2 = {1,1};
    QCOMPARE(testObject1->location() == point1, true);
    QCOMPARE(testObject1->destination() == point2, true);
}

/*
void RandomObjectTest::moveTest()
{
    QVector<QPointF> route;
    route.append({0,0});
    route.append({2,0});
    route.append({2,2});
    route.append({0,2});
    RandomObject* testObject1 = new RandomObject("Moose", true, 1, route);

    QCOMPARE(testObject1->rotation(), 0);
    testObject1->move();
    qDebug() << testObject1->location().x() << ", " <<
                testObject1->location().y()  << ", " << testObject1->rotation();
    qDebug() << "Destination: " << testObject1->destination().x()
             << testObject1->destination().y() << ", "
             << MATHFUNCTIONS::distanceFromPoint(testObject1->location(),
                                                 testObject1->destination());
    testObject1->move();
    qDebug() << testObject1->location().x() << ", " <<
                testObject1->location().y()  << ", " << testObject1->rotation();
    qDebug() << "Destination: " << testObject1->destination().x()
             << testObject1->destination().y() << ", "
             << MATHFUNCTIONS::distanceFromPoint(testObject1->location(),
                                                 testObject1->destination());
    testObject1->move();
    qDebug() << testObject1->location().x() << ", " <<
                testObject1->location().y()  << ", " << testObject1->rotation();
    qDebug() << "Destination: " << testObject1->destination().x()
             << testObject1->destination().y() << ", "
             << MATHFUNCTIONS::distanceFromPoint(testObject1->location(),
                                                 testObject1->destination());
    testObject1->move();
    qDebug() << testObject1->location().x() << ", " <<
                testObject1->location().y()  << ", " << testObject1->rotation();
    qDebug() << "Destination: " << testObject1->destination().x()
             << testObject1->destination().y() << ", "
             << MATHFUNCTIONS::distanceFromPoint(testObject1->location(),
                                                 testObject1->destination());

}
*/

QTEST_APPLESS_MAIN(RandomObjectTest)

#include "tst_randomobjecttest.moc"
