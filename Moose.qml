import QtQuick 2.0

Item {
    property QtObject model
    objectName: model.id

    Rectangle {
        width: 12
        height: 5
        x: model.location.x - width/2
        y: model.location.y - height/2
        rotation: -model.rotation
        color: "brown"
        radius: 3
        visible: model.exists

        MouseArea{
            scale: 1.5
            anchors.fill: parent
            onClicked: {
                GCtrl.mooseClickAction(model.pointer)
            }
        }
    }
}
