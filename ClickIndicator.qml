import QtQuick 2.0

Image{
    id: image
    width: 24
    height: width
    opacity: 0

    function runAnimation(){
        image.opacity = 0
        image.scale = 1
        clickAnimation.restart()
    }

    ParallelAnimation{
        id: clickAnimation
        running: false
        loops: 1

        SequentialAnimation{

            NumberAnimation{
                target: image
                property: "opacity"
                to: 100
                duration: 100
            }
            NumberAnimation{
                target: image
                property: "opacity"
                to: 0
                duration: 900
                easing.type: Easing.InQuad
            }
        }
        SequentialAnimation{
            NumberAnimation{
                target: image
                property: "scale"
                to: 2
                duration: 1000
            }
            NumberAnimation{
                target: image
                property: "scale"
                to: 1
                duration: 1
            }
        }
    }
}
