import QtQuick 2.0

Item {
    property  QtObject model
    objectName: model.id

    Rectangle {
        width: 5
        height: 10
        x: model.location.x - width/2
        y: model.location.y - height/2
        color: "mediumblue"
        visible: model.running
        rotation: -model.rotation-90
    }
}
