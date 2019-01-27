#include "location.hh"
#include "gameobject.hh"
#include "trafficplace.hh"
#include "datareader.hh"
#include "vrtrain.hh"

#include <QString>
#include <QtTest>

// This class is written in order to do the unit tests for the DataReader class
// of TrainGame.

class DataReaderTest : public QObject
{
    Q_OBJECT

public:
    DataReaderTest();

private Q_SLOTS:
    void readSuccessTest();
    void attributeTest();
    void neighbourTest();
};

DataReaderTest::DataReaderTest()
{
}

void DataReaderTest::readSuccessTest()
{
    DataReader reader;
    std::shared_ptr<std::unordered_map<std::string,TrafficPlace *>> mapPtr;
    mapPtr = reader.readPlaceAndTrackData(":/resources/asemadata.json",
                                      ":/resources/ratadata.json");
    QCOMPARE(mapPtr->empty(),false);
}


void DataReaderTest::attributeTest()
{
    DataReader reader;
    std::shared_ptr<std::unordered_map<std::string,TrafficPlace *>> mapPtr;
    mapPtr = reader.readPlaceAndTrackData(":/resources/asemadata.json",
                                      ":/resources/ratadata.json");
    std::unordered_map<std::string,TrafficPlace *>::iterator findIt = mapPtr->find("AHO");
    TrafficPlace *testPlace1 = findIt->second;
    QCOMPARE(testPlace1->getStationName() == "Ahonpää", true);
    QCOMPARE(testPlace1->isTraffic() == false, true);
    QCOMPARE(testPlace1->getType() == "STATION", true);
    QCOMPARE(testPlace1->getStationShortCode() == "AHO", true);
    QCOMPARE(testPlace1->getCountryCode() == "FI", true);
}

void DataReaderTest::neighbourTest()
{
    DataReader reader;
    std::shared_ptr<std::unordered_map<std::string,TrafficPlace *>> mapPtr;
    mapPtr = reader.readPlaceAndTrackData(":/resources/asemadata.json",
                                      ":/resources/ratadata.json");
    std::unordered_map<std::string,TrafficPlace *>::iterator findIt = mapPtr->find("HPK");
    TrafficPlace *testPlace1 = findIt->second;

    std::vector<TrafficPlace *> neighbours = testPlace1->getNeighbours();
    std::vector<TrafficPlace *>::iterator neighbourIt  = neighbours.begin();
    bool neighbourFound = false;
    while (neighbourIt != neighbours.end()) {
        if ( (*neighbourIt)->getStationShortCode() == "PVI" ) {
            neighbourFound = true;
        }

        ++neighbourIt;
    }
    QCOMPARE(neighbourFound, true);
}

QTEST_APPLESS_MAIN(DataReaderTest)

#include "tst_datareadertest.moc"
