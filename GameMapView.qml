import QtQuick 2.0
import QtQuick.Controls 1.4
import GameMapItems 1.0
import QtQuick.Controls.Styles 1.4

Item {
    id: gameMap
    objectName: "gameMap"
    anchors.fill: parent

    function createTrafficPlace(trafficPlace){
        var component = Qt.createComponent("TrafficPlace.qml")
        if(component.status === Component.Ready){
            var object = component.createObject(gameMap, {"model": trafficPlace})
        }
    }

    function createPlayerTrain(train){
        var component = Qt.createComponent("PlayerTrain.qml")
        if(component.status === Component.Ready){
            var object = component.createObject(gameMap, {"model": train})
        }
    }

    function createVRTrain(vrTrain){
        var component = Qt.createComponent("VrTrain.qml")
        if(component.status === Component.Ready){
            var object = component.createObject(gameMap, {"model": vrTrain})
        }
    }

    function createLeafPile(randomObject){
        var component = Qt.createComponent("LeafPile.qml")
        if(component.status === Component.Ready){
            var object = component.createObject(gameMap, {"model": randomObject})
        }
    }

    function createMoose(randomObject){
        var component = Qt.createComponent("Moose.qml")
        if(component.status === Component.Ready){
            var object = component.createObject(gameMap, {"model": randomObject})
        }
    }

    function showGameEndView() {
        var component = Qt.createComponent("GameEndView.qml")
        if(component.status === Component.Ready){
            var object = component.createObject(gameMap)
        }
    }

    function click(status, clickPoint){
        if(status === true){
            clickIndicator.source = "resources/move_OK.png"
            clickIndicator.x = clickPoint.x - 10
            clickIndicator.y = clickPoint.y - clickIndicator.height
        }
        else{
            clickIndicator.source = "resources/move_FAIL.png"
            clickIndicator.x = clickPoint.x - clickIndicator.width/2
            clickIndicator.y = clickPoint.y - clickIndicator.height/2
        }
        clickIndicator.runAnimation()
    }

    Connections{
        target: GCtrl
        onTrafficPlaceCreated:{
            createTrafficPlace(trafficPlace)
        }
        onPlayerTrainCreated:{
            createPlayerTrain(train)
        }
        onVrTrainCreated:{
            createVRTrain(vrTrain)
        }
        onLeafPileCreated:{
            createLeafPile(randomObject)
        }
        onMooseCreated:{
            createMoose(randomObject)
        }
        onMoveActionCompleted:{
            click(status, clickPoint)
        }
        onGameInitCompleted:{
            menu.z = 1
            menu.active = true
        }
        onShowGameEndView:{
            showGameEndView()
        }
    }

    ClickIndicator{
        id: clickIndicator
        z: 1
    }

    MenuView {
        id: menu
    }

    Image {
        source: "qrc:/resources/map_google.png"
        scale: 0.878
        x: -153
        y: -65

        /*
          with map.png:
          scale: 1.2
          x: -125
          y: 50
          */
    }

    ProgressBar {
        value: PlayerStats.happiness
        height: 30
        width: parent.width-30
        minimumValue: 0
        maximumValue: 100

        x: (parent.width-width)/2
        y: parent.height-3/2*height
        z: 10

        style: ProgressBarStyle {
            background:
                Rectangle {
                    radius: 2
                    color: "lightgray"
                    border.color: "gray"
                    border.width: 1
                    implicitWidth: 200
                    implicitHeight: 24
                }
            progress:
                Rectangle {
                    color: "mediumturquoise"
                    border.color: "steelblue"
                }
            }
        }

    RailRoad{
        id: railRoad
        anchors.fill: parent
        objectName: "railRoadView"
    }

    LoadingView {
        id: loadingIcon
        z: 1
    }


    Component.onCompleted:{
        GCtrl.initialize()
        loadingIcon.visible = false
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_S) {
            menu.keySPressed()
            event.accepted = true;
        } else if (event.key === Qt.Key_Space) {
            if (PlayerStats.jump) {
                console.debug("jump==true, calling GCtrl")
                GCtrl.jumpAction()
            }
        }
    }
}
