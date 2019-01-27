
#include "gameobject.hh"
#include "trafficplace.hh"
#include "other.hh"

#include <QString>
#include <QtTest>

// This class is written in order to do the unit tests for the DataReader class
// of TrainGame.

class TrafficPlaceTest : public QObject
{
    Q_OBJECT

public:
    TrafficPlaceTest();

private Q_SLOTS:
    void creationTest();
    void attributeTest();
    void neighbourTest();
};

TrafficPlaceTest::TrafficPlaceTest()
{
}

void TrafficPlaceTest::creationTest()
{
    TrafficPlace* testPlace1 = new TrafficPlace(false,"FI","Ahonpää","AHO",0,0,"STATION");
    QCOMPARE(testPlace1 != nullptr, true);
}


void TrafficPlaceTest::attributeTest()
{
    TrafficPlace* testPlace1 = new TrafficPlace(false,"FI","Ahonpää","AHO",0,0,"STATION");

    QCOMPARE(testPlace1->getStationName() == "Ahonpää", true);
    QCOMPARE(testPlace1->isTraffic() == false, true);
    QCOMPARE(testPlace1->getType() == "STATION", true);
    QCOMPARE(testPlace1->getStationShortCode() == "AHO", true);
    QCOMPARE(testPlace1->getCountryCode() == "FI", true);
}

void TrafficPlaceTest::neighbourTest()
{
    TrafficPlace* testPlace1 = new TrafficPlace(false,"FI","Ahonpää","AHO",0,0,"STATION");
    TrafficPlace* neighbour1 = new TrafficPlace(true,"FI","Neighbour1","N1",0,0,"STATION");
    TrafficPlace* neighbour2 = new TrafficPlace(true,"FI","Neighbour2","N2",0,0,"STATION");
    testPlace1->addNeighbour(neighbour1);
    testPlace1->addNeighbour(neighbour2);

    std::vector<TrafficPlace *> neighbours = testPlace1->getNeighbours();
    std::vector<TrafficPlace *>::iterator neighbourIt  = neighbours.begin();
    bool neighbourFound = false;
    while (neighbourIt != neighbours.end()) {
        if ( (*neighbourIt)->getStationShortCode() == "N2" ) {
            neighbourFound = true;
        }

        ++neighbourIt;
    }
    QCOMPARE(neighbourFound, true);
}

QTEST_APPLESS_MAIN(TrafficPlaceTest)

#include "tst_trafficplacetest.moc"
