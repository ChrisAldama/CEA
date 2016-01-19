import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

Rectangle {
    id: menu
    width: lay.width * 1.2
    height: lay.width * 2.3
    visible: false
    color: "#A8A8A8"
    border.color: "black"


    ColumnLayout{
        id: lay
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 10

        Button {
            text: "Open Stimuli"
            onClicked: fileD.visible = true

        }

        Button {
            text:  "Start"
            onClicked: Controller.newGame()
        }



        RowLayout {
            Label {
                text: "Speed"
            }
            Slider {
                maximumValue: 1000
                minimumValue: 1000/60
                value: 1000/60
                onValueChanged: Controller.speed = value
            }
        }

        RowLayout{
            ExclusiveGroup{
                Action {
                    id: testActio
                    text: "Test"
                    checkable: true
                    onTriggered: Controller.changeMode(0)
                }

                Action {
                    id: evAction
                    text: "Evolve"
                    checkable: true
                    onTriggered: Controller.changeMode(1)
                }
            }
        }
    }

    ColorDialog {
        id: colorD
        visible: false
        onAccepted: {
            visible = false;
            //menu.colorCaller.color = color;
        }
    }

    FileDialog {
        visible: false
        id: fileD
        title: "Select Stimuli"

        onAccepted: {
            Controller.openFile(fileUrl);
            visible = false;
        }

        onRejected: {
            visible = false;
        }
    }

   /* function getColor(caller){
        menu.colorCaller = caller;
        colorD.visible = true;
    }*/
}
