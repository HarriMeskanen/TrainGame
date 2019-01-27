#ifndef DATAREADER_HH
#define DATAREADER_HH

#include "trafficplace.hh"
#include "vrtrain.hh"

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

/**
 * @brief The DataReader is the class for reading the initialization data of the game,
 * such as the data provided by VR API.
 */
class DataReader
{
    QFile *jsfile = NULL;
public:
    //explicit DataReader(QObject *parent = nullptr);
    DataReader() {
        jsfile = NULL;
         std::cout << "DataReader constructor\n" << std::flush;
     }

    // readPlaceAndTrackData is the method for reading .json files of station and
    // track data
    std::shared_ptr<std::unordered_map<std::string,TrafficPlace *>>
            readPlaceAndTrackData(QString PlaceFilePath, QString TrackFilePath);
    std::shared_ptr<std::unordered_map<int, VRTrain *>> readTimetable(QString gameDate,
                                       std::shared_ptr<std::unordered_map<std::string, TrafficPlace *>> trafficPlaces);

private:
    // parsePlaceArray and parseTrackArray are used for parsing specific QJsonArrays
    // and adding converted elements to the unordered_map of stations.
    void parsePlaceArray(std::shared_ptr<std::unordered_map<std::string,
                         TrafficPlace *>> TrafficMap,
                         QJsonArray& Places);
    void parseTrackArray(std::shared_ptr<std::unordered_map<std::string,
                         TrafficPlace *>> TrafficMap,
                         QJsonArray& Tracks);
    void parseTrains(QJsonArray trains,
                        std::shared_ptr<std::unordered_map<int, VRTrain *> > paivanJunat, std::shared_ptr<std::unordered_map<std::string, TrafficPlace *> > trafficPlaces);
    bool isDepartureListValid(std::shared_ptr<std::unordered_map<std::string, TrafficPlace *>> trafficPlaces,
                              QVector<QString> stationList);
};

#endif // DATAREADER_HH
