import QtQuick 2.3
import QtQuick.Controls 1.4

Item {

    TableView {
        id: table
        anchors.fill: parent
        TableViewColumn{
            role: "x"
            title: "x"
            width: 100
        }
        TableViewColumn{
            role: "y"
            title: "y"
            width: 100
        }
        TableViewColumn{
            role: "z"
            title: "Training"
            width: 100
        }
        TableViewColumn{
            role: "w"
            title: "Calculado"
            width: 100
        }

        model: ListModel {
            id: lmodel
        }
    }

    Connections {
        target: Controller
        onStimuliChanged: populate()
    }

    Component.onCompleted: populate()

    function populate(){
        lmodel.clear();
        var sti = Controller.stimuli;
        console.log(sti);
        var objs = JSON.parse(sti);
        for(var i = 0; i < objs.length; ++i){
            lmodel.append(objs[i]);
        }
    }


}

