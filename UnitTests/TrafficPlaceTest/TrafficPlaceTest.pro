QT       += testlib
QT       -= gui

TARGET = tst_trafficplacetest
CONFIG   += console
CONFIG   -= app_bundle
LIBS -= lQtGui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../../gameobject.hh \
    ../../trafficplace.hh \
    ../../other.hh \


SOURCES += \
    tst_trafficplacetest.cpp \
    ../../gameobject.cpp \
    ../../trafficplace.cpp \
    ../../other.cpp \

INCLUDEPATH += ../../

#RESOURCES += ../../resources
#RESOURCES += qml.qrc \
#    inputdata.qrc
#RESOURCES += ../../inputdata.qrc

DEFINES += SRCDIR=\\\"$$PWD/\\\"
