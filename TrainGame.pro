TEMPLATE = app

QT += qml quick
QT += network
CONFIG += c++11

SOURCES += main.cpp \
    traingame.cpp \
    datareader.cpp \
    gameobject.cpp \
    trafficplace.cpp \
    gamecontroller.cpp \
    rail.cpp \
    gamemap.cpp \
    other.cpp   \
    location.cpp \
    gamesettings.cpp \
    railroad.cpp \
    vrtrain.cpp \
    train.cpp \
    navigator.cpp \
    randomobject.cpp \
    stats.cpp \
    achievements.cpp


RESOURCES += qml.qrc \
    inputdata.qrc \
    images.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    traingame.hh \
    datareader.hh \
    gameobject.hh \
    trafficplace.hh \
    gamecontroller.hh \
    rail.hh \
    gamemap.hh \
    other.hh    \
    location.hh \
    gamesettings.hh \
    railroad.hh \
    train.hh \
    vrtrain.hh \
    navigator.hh \
    randomobject.hh \
    stats.hh \
    achievements.hh

