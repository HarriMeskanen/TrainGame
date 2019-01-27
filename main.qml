import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4


Window {
    visible: true
    width: 1920
    height: 1080
    title: qsTr("TrainGame")
    id: root

    Loader{
        id: loader
        anchors.fill: parent
        focus: true
    }

    function showStartView(){
        loader.source = "StartView.qml"
    }

    function showGameMapView(){
        loader.source = "GameMapView.qml"
    }

    function showSettingsView(){
        var component = Qt.createComponent("SettingsView.qml")
        var window    = component.createObject(root)
        window.show()
    }

    function showAchievementView() {
        loader.source = "AchievementView.qml"
    }

    Component.onCompleted: showStartView()

}
