import QtQuick 2.3
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.14
//import QtQuick.Controls.Universal 2.3

Item {
    id: container
    //Universal.theme: Universal.Dark
    //Universal.accent: Univeral.Violet
    // Properties
    property alias backColor: background.color
    property int marginBorder: 5

    // -- Height predefined
    height: 45
    width: parent.width

    // Span a rectangle to achieve a background color
    Rectangle{
        id: background

        // property overriden
        color : "#e60000"

        // Fill parent
        anchors.fill : parent

        RowLayout {
            // Config
            spacing: marginBorder/2

            // Anchors
            anchors.fill : parent
            anchors.leftMargin: marginBorder
            anchors.rightMargin: marginBorder

            Row {
                id: dateinput

                // Anchors
                Layout.fillHeight: true
                Layout.fillWidth: false
                Layout.topMargin: marginBorder
                Layout.bottomMargin: marginBorder
                spacing: 0

                Button {
                    id: previousbtn

                    width: 50
                    height: dateinput.height

                    text: "<<"
                    font.family: "Consolas"
                    font.pointSize: 12
                    font.bold: true
                }

                TextField {
                    id: textDate

                    width: 175
                    height: dateinput.height

                    placeholderText: qsTr("Choose date")
                    text: "dd-MM-yyyy"
                    font.bold: true
                    font.family:"Consolas"

                    // Theming
                    selectionColor: backColor   // Selection of Text

                }

                Button {
                    id: nextbtn

                    width: 50
                    height: dateinput.height

                    text: ">>"
                    font.family: "Consolas"
                    font.pointSize: 12
                    font.bold: true
                }
            }

            Rectangle {
                id: timeinput

                // Anchors
                Layout.fillWidth: false
                Layout.fillHeight: true
                Layout.preferredWidth: 100
                Layout.topMargin: marginBorder
                Layout.leftMargin: marginBorder
                Layout.bottomMargin: marginBorder


                SpinBox {
                    id: sbTime

                    width: parent.width
                    height: timeinput.height
                }
            }

            Rectangle {
                id: costcenterinput

                // Anchors
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredWidth: 200
                Layout.topMargin: marginBorder
                Layout.leftMargin: marginBorder
                Layout.bottomMargin: marginBorder

                ComboBox {
                    //id: cbCostCenter

                    width: parent.width
                    height: costcenterinput.height

                    displayText: qsTr("")
                    flat: true
                }
            }

            Rectangle {

                id: projectinput

                // Anchors
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 200
                Layout.topMargin: marginBorder
                Layout.leftMargin: marginBorder
                Layout.bottomMargin: marginBorder

                ComboBox {
                    id: cbProject

                    width: parent.width
                    height: costcenterinput.height

                    displayText: qsTr("")
                    flat: true
                }
            }

            Rectangle {

                id: subjectinput

                // Anchors
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 200
                Layout.topMargin: marginBorder
                Layout.leftMargin: marginBorder
                Layout.bottomMargin: marginBorder

                ComboBox {
                    id: cbSubject

                    width: parent.width
                    height: costcenterinput.height

                    displayText: qsTr("")
                    flat: true
                }
            }
            Rectangle {
                id: add

                // Anchors
                Layout.fillWidth: false
                Layout.fillHeight: true
                Layout.preferredWidth: 100
                Layout.topMargin: marginBorder
                Layout.leftMargin: marginBorder
                Layout.bottomMargin: marginBorder


                Button {
                    id: addbutton

                    width: parent.width
                    height: timeinput.height
                    text: "Add"
                }
            }
        }
    }
}





/*##^##
Designer {
    D{i:0;width:800}
}
##^##*/
