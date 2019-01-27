#ifndef ACHIEVEMENTS_HH
#define ACHIEVEMENTS_HH

#include <QObject>
#include <QTimer>
#include <QFile>
#include <QVector>

/**
 * @brief The Achievements class is used to read and write players'
 * accomplishments
 */

class Achievements : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<bool> achievementList READ achievementList NOTIFY achievementListChanged)

public:
    explicit Achievements(QObject *parent = nullptr);

    void initialize();
    void writeEmptyAchievementFile();
    bool readAchievementFile();
    bool writeAchievementFile();
    void achievementAchieved(int index);

    inline QVector<bool> achievementList() {return achievements_;}

    QString boolToQString(bool input);

signals:
    void achievementListChanged();

public slots:

private:
    QString fileName_;
    QFile achievementFile_;
    QVector<bool> achievements_;
};

#endif // ACHIEVEMENTS_HH
