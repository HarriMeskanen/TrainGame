import QtQuick 2.0



Rectangle{
    id: train
    width: 30
    height: 20
    color: "green"
    x: GameSettings.gameMapOrigin.x
    y: GameSettings.gameMapOrigin.y

    property int speed: 100
    property double pathLength
    property int actionCount: 0

    function setPath(){
        animationPath.pathElements = []
        var array = []
        for(var i=0; i < GCtrl.currentPath.length; i++){
            var object = Qt.createQmlObject(
                        'import QtQuick 2.0; PathLine{}',
                        train, "PathLine")
            object.x = GCtrl.currentPath[i].x
            object.y = GCtrl.currentPath[i].y
            array.push(object)
        }
        animationPath.pathElements = array
    }

    Connections{
        target: GCtrl

        onCurrentPathChanged:{
            setPath()
            pathLength = length
            actionCount += 1
        }
    }
    Path{
        id: animationPath
        startX: train.x
        startY: train.y
    }
    Behavior on actionCount {

        PathAnimation{
            target: train
            duration: 1000 * pathLength / speed
            path: animationPath
        }
    }
}

