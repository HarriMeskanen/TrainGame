import QtQuick 2.0

Item {
    property  QtObject model
    objectName: model.id

    Rectangle {
        width: 12
        height: 8
        x: model.location.x - width/2
        y: model.location.y - height/2
        color: "green"
        radius: 3
        visible: model.exists
    }
}
