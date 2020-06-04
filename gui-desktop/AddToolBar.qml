import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.14

ToolBar {
    id: mainToolBar
    RowLayout{
        width: parent.width
        ToolButton{
            text: "<"
            //iconSource: ""
            onClicked: parent.color = "khaki"
        }
        TextField{

        }
        ToolButton{
            text: ">"
            //iconSource: ""
            onClicked: parent.color = "green"
        }
        SpinBox {
            id: sbTime

            width: parent.width
            height: timeinput.height
        }
        ComboBox {
            //id: cbCostCenter
            Layout.fillWidth: true
            width: parent.width
            height: costcenterinput.height
        }
        ComboBox {
            //id: cbCostCenter
            Layout.fillWidth: true
            width: parent.width
            height: costcenterinput.height
        }
        ComboBox {
            //id: cbCostCenter
            Layout.fillWidth: true
            width: parent.width
            height: costcenterinput.height
        }
        ToolButton{
            text: ">"
            //iconSource: ""
            onClicked: parent.color = "yellow"
        }
    }


}

/*##^##
Designer {
    D{i:0;height:25;width:500}
}
##^##*/
