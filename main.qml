import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1


ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("CEAN")

    Image {
        id: view
        source: "image://IProvider/id"
        anchors.fill: parent
    }

    Connections{
        target: Controller
        onNewImage: {
            board.source = "image://IProvider/" + id;
        }
    }

    Button {
        id: cButton
        text: "+"
        style: ButtonStyle {
            background: Rectangle {
                implicitHeight: 50
                implicitWidth:  50
                color: "#FF0000";
                radius: width* 0.5;
                border.width: control.activeFocus ? 2 : 1
                border.color: "#888"
            }
            label : Text {
                font{
                    pointSize: 30
                    family: "Hack"
                }
                text: cButton.text
                color: "#FFF"
                styleColor: "#5c4f4f"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter

            }
        }
        MouseArea {
            anchors.fill: parent
            drag.target: parent
            onClicked: {

                menu.visible =  true;
                menu.focus = true;
            }

        }
    }

    FMenu {
        id: menu
        x: cButton.x
        y: cButton.y
        visible: false
    }
}

