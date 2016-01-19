import QtQuick 2.3
import QtQuick.Controls 1.4
import QuickPlot 1.0

Item {

    PlotArea {
        anchors.fill: parent
        anchors.leftMargin: 30
        anchors.topMargin: 30
        yScaleEngine: FixedScaleEngine {
            id: scale
            min: 0
            max: 1.1
        }

        items: [Curve{
                id: curve
                color: "#000"
            }]
    }


    Connections {
        target: Controller
        onErrorDataChanged: {
            curve.setData(Controller.errorData);

        }
    }

    Timer {
        interval:1500
        repeat: true
        running: true

        onTriggered: {
            //console.log("timer");
            curve.setData(Controller.errorData);
        }
    }

    Component.onCompleted: {
        console.log("render");
        curve.setData(Controller.errorData);
    }



}
