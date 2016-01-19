import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1


ApplicationWindow {
    visible: true
    width: 1024
    height: 768
    title: qsTr("CEAN")

    TabView{
        anchors.fill: parent
        Tab{
            title: "Board"
            Board{
                id: board
            }
        }
        Tab {
            title: "Graphics"
            ErrorGraph {

            }
        }
        Tab {
            title: "Stimuli"
            Stimuli{

            }
        }
    }


}

