#include "achievements.hh"
#include <QDebug>
#include <QDir>
#include <QTextStream>

Achievements::Achievements(QObject *parent)
    : QObject(parent), fileName_{"achievements.txt"}
{

}

void Achievements::initialize() {
    QString path = QDir::currentPath();
    QString fullFileName = path + "/" + fileName_;
    qDebug() << fullFileName;
    achievementFile_.setFileName(fullFileName);
    // If there is no earlier version of achievements.txt, a new file will be created.
    if (!achievementFile_.exists()) {
        writeEmptyAchievementFile();
    } else {
        // In case a achievements.txt file exists, we attempt to read it.
        // If reading the existing file fails, we create an empty achievementFile.
        if (!readAchievementFile()) {
            writeEmptyAchievementFile();
        }
    }
    qDebug() << "Achievements initialized";
}

// An 'empty' achievementFile is not actually empty, it just says that none of the achievements are
// currently achieved.
void Achievements::writeEmptyAchievementFile() {
    if (achievementFile_.exists()) {
        qDebug() << "poistetaan vanha tiedosto...";
        achievementFile_.remove();
    }

    QString path = QDir::currentPath();
    QString fullFileName = path + "/" + fileName_;
    achievementFile_.setFileName(fullFileName);
    //achievementFile_.setPermissions(QFile::ReadUser | QFile::ReadOther | QFile::WriteUser | QFile::WriteOther |
    //                                QFile:: ExeUser | QFile::ExeOther);

    achievementFile_.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream out(&achievementFile_);
    out << "1;false\n2;false\n3;false"
           "\n4;false\n5;false\n6;false"
           "\n7;false\n8;false\n9;false"
           "\n10;false";
    achievementFile_.close();

    // After we reset the file we want to read it into the memory
    readAchievementFile();
}

bool Achievements::readAchievementFile() {
    // Every time we read and achievementFile, we want to clear earlier achievements from the memory.
    // If the achievementFile we read would be corrupted, this does not cause any trouble since
    // the we construct an empty achievementFile.
    achievements_.clear();

    if(!achievementFile_.open(QIODevice::ReadOnly)) {
        qDebug() << "Virhe saavutustiedoston luvussa!";
        return false;
    }
    QTextStream in(&achievementFile_);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(";");
        if (fields.at(1) == "true") {
            achievements_.append(true);
        } else if (fields.at(1) == "false") {
            achievements_.append(false);
        } else {
            // The achievementfile is flawed
            achievementFile_.close();
            return false;
        }
    }

    achievementFile_.close();
    emit achievementListChanged();
    return true;
}

bool Achievements::writeAchievementFile() {
    qDebug() << "Kirjoitetaan uusi saavutustiedosto...";
    if (achievementFile_.exists()) {
        if (!achievementFile_.remove()) {
            qDebug() << "Tiedostoa ei pystytä poistamaan.";
            return false;
        }
    }

    QString path = QDir::currentPath();
    QString fullFileName = path + "/" + fileName_;
    achievementFile_.setFileName(fullFileName);

    if(!achievementFile_.open(QIODevice::ReadWrite | QIODevice::Text)) {
        return false;
    } else {
        QTextStream out(&achievementFile_);
        for (int i = 0; i < achievements_.length(); i++) {
            out << QString::number(i+1) + ";" + boolToQString(achievements_.at(i)) + "\n";
        }
        achievementFile_.close();
        out.flush();
        return true;
    }
}

void Achievements::achievementAchieved(int index) {
    achievements_[index] = true;
}

QString Achievements::boolToQString(bool input) {
    if (input) {
        return QString("true");
    } else {
        return QString("false");
    }
}
