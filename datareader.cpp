#include "datareader.hh"
#include "other.hh"

#include <QDebug>
#include <QCoreApplication>
#include <QtNetwork>

std::shared_ptr<std::unordered_map<std::string, TrafficPlace *> > DataReader::readPlaceAndTrackData(QString PlaceFilePath, QString TrackFilePath)
{
    // Initialize the unordered_map of stations.
    std::shared_ptr<std::unordered_map<std::string,TrafficPlace *>> TrafficMap =
            std::make_shared<std::unordered_map<std::string,TrafficPlace *>>();
    jsfile = new QFile(PlaceFilePath);

     if (!jsfile->open(QIODevice::ReadOnly | QIODevice::Text)) {
         std::cout << "Could not open: "<< std::endl << std::flush;
         return TrafficMap;
     }
     QByteArray data = jsfile->readAll();
     QJsonParseError err;
     QJsonDocument doc = QJsonDocument::fromJson(data,&err);
     std::cout << "Err=" << err.errorString().toStdString() << std::endl << std::flush;
     QJsonArray PlaceArray = doc.array();

     // Read the array while converting the QJsonObjects within into TrafficPlace
     // objects.
     parsePlaceArray(TrafficMap, PlaceArray);

     // Close the file and open a new one.
     jsfile->close();
     jsfile->setFileName(TrackFilePath);

      if (!jsfile->open(QIODevice::ReadOnly | QIODevice::Text)) {
          std::cout << "Could not open: " << std::endl << std::flush;
          return TrafficMap;
      }

      // Read the data and make a QJsonArray of it.
      QByteArray data2 = jsfile->readAll();
      QJsonDocument doc2 = QJsonDocument::fromJson(data2);
      QJsonValue val2 = (doc2.object().find("tracks")).value();
      QJsonArray tracks = val2.toArray();

      // Read the QJsonArray while adding neighbourhood stations to each station.
      parseTrackArray(TrafficMap, tracks);

      // Close the file and return the unordered_map.
      jsfile->close();

      return TrafficMap;
}

void DataReader::parsePlaceArray(std::shared_ptr<std::unordered_map<std::string, TrafficPlace *> > TrafficMap,
                                 QJsonArray &Places)
{
    QJsonArray::const_iterator placeIt = Places.constBegin();
    while (placeIt != Places.constEnd()) {
        QJsonValue value = *placeIt;
        QJsonObject place = value.toObject();

        // Take values from object and convert them
        bool passengerTraffic = place.find("passengerTraffic")->toBool();
        std::string type = (place.find("type")->toString()).toStdString();
        std::string stationName = (place.find("stationName")->toString()).toStdString();
        std::string stationShortCode = (place.find("stationShortCode")->toString()).toStdString();
        std::string countryCode = (place.find("countryCode")->toString()).toStdString();
        QPointF xy = MATHFUNCTIONS::latLonToMercator(place.find("latitude")->toDouble(),place.find("longitude")->toDouble());
        double x = 32.821*xy.x()-11721;
        double y = 36.86*xy.y()-9616;

        TrafficPlace *placeToAdd = new TrafficPlace(passengerTraffic,
                                  countryCode, stationName, stationShortCode, x, y, type);
        TrafficMap->insert(std::make_pair(stationShortCode,placeToAdd));
        ++placeIt;
    }
    return;
}

void DataReader::parseTrackArray(std::shared_ptr<std::unordered_map<std::string, TrafficPlace *> > TrafficMap, QJsonArray &Tracks)
{
    QJsonArray::const_iterator trackIt = Tracks.constBegin();
    while (trackIt != Tracks.constEnd()) {
        QJsonValue value = *trackIt;
        QJsonObject track = value.toObject();
        QJsonArray stations = (track.find("stations"))->toArray();
        // Create an iterator to the first element in the array
        QJsonArray::const_iterator stationIt = stations.constBegin();
        // Create an iterator to the LAST element in the array
        QJsonArray::const_iterator lastStation = stations.constEnd();
        --lastStation;
        while (stationIt != lastStation) {
            // Convert the current element into QJsonObject
            QJsonValue value1 = *stationIt;
            QJsonObject station1 = value1.toObject();
            std::string stationName1 = (station1.find("name")->toString()).toStdString();
            ++stationIt;

            // Convert the next element into QJsonObject.
            QJsonValue value2 = *stationIt;
            QJsonObject station2 = value2.toObject();
            std::string stationName2 = (station2.find("name")->toString()).toStdString();

            // Check if the station names are found.
            std::unordered_map<std::string,TrafficPlace *>::iterator station1It;
            station1It = TrafficMap->find(stationName1);
            TrafficPlace * station1Ptr = nullptr;
            if ( station1It != TrafficMap->end() ) {
                station1Ptr = station1It->second;
            }
            std::unordered_map<std::string, TrafficPlace *>::iterator station2It;
            station2It = TrafficMap->find(stationName2);
            TrafficPlace * station2Ptr = nullptr;
            if ( station2It != TrafficMap->end() ) {
                station2Ptr = station2It->second;
            }

            // If both were found, add each other as neighbours.
            if ( station1Ptr != nullptr && station2Ptr != nullptr ){
                station1Ptr->addNeighbour(station2Ptr);
                station2Ptr->addNeighbour(station1Ptr);
            }
        }
        ++trackIt;
    }

    return;
}

std::shared_ptr<std::unordered_map<int, VRTrain *>> DataReader::readTimetable(QString gameDate,
                                    std::shared_ptr<std::unordered_map<std::string, TrafficPlace *>> trafficPlaces) {
    // The url is based on the date in the gameSettings, which is given as parameter
    QString urlString = "https://rata.digitraffic.fi/api/v1/trains/" + gameDate;
    QUrl url = QUrl(urlString);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(request);

    // Simple function that waits until the QNetworkReply is finished
    int laskuri = 0;
    while (!reply->isFinished()) {
        QTime dieTime= QTime::currentTime().addSecs(1);
        while (QTime::currentTime() < dieTime) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        qDebug() << "Fetching timetables..." << laskuri ;
        laskuri += 1;
    }

    // If the QNetworkReply contains no error, its contents will be parsed.
    if(reply->error() == QNetworkReply::NoError) {
        qDebug() << "Network request replied succesfully!";
        QByteArray response_data = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);

        if (jsonDoc.isEmpty()) {
            qDebug() << "Json document is empty!";
            return 0;
        }

        std::shared_ptr<std::unordered_map<int, VRTrain *>> paivanJunat = std::make_shared<std::unordered_map<int, VRTrain *>>();
        parseTrains(jsonDoc.array(),paivanJunat,trafficPlaces);
        reply->deleteLater();
        return paivanJunat;

    } else {
        qDebug() << "Error in network request: " << reply->errorString();
        std::shared_ptr<std::unordered_map<int, VRTrain *>> paivanJunat;
        return paivanJunat;
    }
}

void DataReader::parseTrains(QJsonArray trains, std::shared_ptr<std::unordered_map<int, VRTrain *>> paivanJunat,
                             std::shared_ptr<std::unordered_map<std::string, TrafficPlace *>> trafficPlaces) {

    // We read every second train to the gameMap_, otherwise it there is too much traffic for the
    // playerTrain to operate.
    int everySecond = 1;
    QJsonArray::const_iterator placeIt = trains.constBegin();
    while (placeIt != trains.constEnd()) {
        QJsonValue value = *placeIt;
        QJsonObject place = value.toObject();

        if (place.find("trainCategory")->toString() != "Long-distance") {
            ++placeIt;
            break;
        }

        int trainNumber = place.find("trainNumber")->toInt();
        QString trainType = place.find("trainType")->toString();
        QVector<QDateTime> departureList;
        QVector<QString> stationList;
        QJsonArray jsonArray = place["timeTableRows"].toArray();

        // Because in the timetable the time of the arrival is exactly the same as the departure from that station,
        // only departures are read from the timetable. Then the last arrival is added manually to the station list
        // to complete the route.
        foreach (const QJsonValue & value, jsonArray) {
            QJsonObject obj = value.toObject();
            if(obj["type"].toString() == "DEPARTURE") {
                QString dateString = obj["scheduledTime"].toString();
                // Qt::ISODateWithMs gave build error in linux
                // QDateTime dateToBeAdded = QDateTime::fromString(dateString,Qt::ISODateWithMs);
                QDateTime dateToBeAdded = QDateTime::fromString(dateString,Qt::ISODate);
                departureList.append(dateToBeAdded);
                stationList.append(obj["stationShortCode"].toString());
            }
        }
        // Here the arrival to the last station is added
        departureList.append(QDateTime::fromString(jsonArray.last().toObject()["scheduledTime"].toString(),Qt::ISODate));
        stationList.append(jsonArray.last().toObject()["stationShortCode"].toString());

        // We have to check if the station list contains a station that is not in our TrafficPlaces.
        if (isDepartureListValid(trafficPlaces, stationList)) {
            // If our departureList is valid, we can add a new VRTrain.
            // Initialize all trains with parameters fetched from the API. First every train has running_ = false.
            if (everySecond == 1) {
                VRTrain *trainToBeAdded = new VRTrain(trainNumber, trainType, stationList, departureList, false);
                paivanJunat->insert(std::make_pair(trainNumber,trainToBeAdded));
                ++placeIt;
                everySecond++;
            } else {
                everySecond = 1;
                placeIt++;
            }

        } else {
            ++placeIt;
        }
    }
}

bool DataReader::isDepartureListValid(std::shared_ptr<std::unordered_map<std::string, TrafficPlace *>> trafficPlaces,
                                      QVector<QString> stationList) {
    QVector<QString>::const_iterator it = stationList.begin();
    while (it != stationList.end()) {
        QString stationToFind = *it;
        if (trafficPlaces->find(stationToFind.toStdString()) == trafficPlaces->end()) {
            qDebug() << "Asema" << stationToFind << "ei ollut trafficPlaceissa.";
            return false;
        }
        it++;
    }
    return true;
}
