import QtQuick 2.3

import QtQuick.Controls 2.5
import QtQuick.Controls.Universal 2.3
import QtQuick.Layouts 1.14
import io.home.essentials.backend 1.0
import io.home.essentials.CostCenterNamesModel 1.0
import io.home.essentials.SubjectNamesModel 1.0
import io.home.essentials.ProjectNamesModel 1.0

Rectangle {

    id: _toolbar
    color: palette.highlight
    property int foldedDateWidth: 60
    property int unfoldedDateWidth: 110
    property int edgeMargin: 5
    anchors.fill: parent

    BackEnd {
        id: _backend
    }

    RowLayout{
        id: _toolRow
        anchors.fill: parent

        TextField{
            id: _tfDate
            text: qsTr("")
            Layout.margins: edgeMargin
            horizontalAlignment: Text.AlignHCenter
            // Start in small position
            state: "folded"
            Layout.fillHeight: true
            selectByMouse: true

            // Increase size if we pop calendar
            states: [
                State {
                    name: "unfolded";
                    PropertyChanges { target: _tfDate; implicitWidth: unfoldedDateWidth }

                },
                State {
                    name: "folded";
                    PropertyChanges { target: _tfDate; implicitWidth: foldedDateWidth }
                }
            ]

            transitions: Transition {
                // smoothly reanchor myRect and move into new position
                PropertyAnimation {  property: "implicitWidth"; duration: 350; easing.type: Easing.InOutSine}
                PropertyAnimation {  property: "text"; duration: 0; easing.type: Easing.InOutQuad }
            }

            onActiveFocusChanged: if(state == "unfolded") { state = "folded";  _backend.date = text; text = _backend.date.substring(0, 5)} else { state = "unfolded"; text = _backend.date}
        }

        SpinBox {
            id: _sbTime
            Layout.margins: edgeMargin
            editable: true
            wheelEnabled: true
            implicitWidth: 75
            Layout.fillHeight: true

        }

        ComboBox {
            id: _cbCostCenter
            enabled: true
            Layout.margins: edgeMargin
            wheelEnabled: true
            editable: true
            Layout.fillWidth: true
            implicitWidth: 150
            Layout.fillHeight: true

            model: CostCenterNamesModel {
                id: _cbCostCenterModel

            }

            // Store the previous text for restoring it if we cancel
            property string oldText

            // Lets us know that the user is cancelling the save
            property bool cancelling

            Keys.onEscapePressed: {
                // Cancel the save, and deselect the text input
                cancelling = true
                focus = false
            }

            onActiveFocusChanged: {
                // When we first gain focus, save the old text and select everything for clearing.
                if (activeFocus) {
                    oldText = editText
                    selectAll()
                } else if (cancelling) {
                    // When cancelling, restore the old text, and clear state.
                    editText = oldText
                    oldText = ""
                    cancelling = false
                } else {
                    // TO DO: Handle new text
                    //_backend.costCenter = editText
                    if(editText != "" && editText != currentText){
                        _cbCostCenterModel.insert(_cbCostCenter.editText);
                    }
                }
            }


        }
        ComboBox {
            id: _cbProject

            wheelEnabled: true
            editable: true
            Layout.margins: edgeMargin
            Layout.fillWidth: true
            implicitWidth: 150
            Layout.fillHeight: true

            // TBD
            model: ProjectNamesModel {
                id: _cbProjectModel
            }
            // Store the previous text for restoring it if we cancel
            property string oldText

            // Lets us know that the user is cancelling the save
            property bool cancelling

            Keys.onEscapePressed: {
                // Cancel the save, and deselect the text input
                cancelling = true
                focus = false
            }

            onActiveFocusChanged: {
                // When we first gain focus, save the old text and select everything for clearing.
                if (activeFocus) {
                    oldText = editText
                    selectAll()
                } else if (cancelling) {
                    // When cancelling, restore the old text, and clear state.
                    editText = oldText
                    oldText = ""
                    cancelling = false
                } else {
                    // TO DO: Handle new text
                    //_backend.project = editText
                    if(editText != "" && editText != currentText){
                        _cbProjectModel.insert(_cbProject.editText);
                    }
                }
            }
        }

        ComboBox {
            id: _cbSubject
            wheelEnabled: true
            editable: true
            Layout.fillHeight: true
            Layout.margins: edgeMargin
            Layout.fillWidth: true
            implicitWidth: 150
            implicitHeight: parent.height

            // TBD
            model: SubjectNamesModel {
                id: _cbSubjetModel
            }
            // Store the previous text for restoring it if we cancel
            property string oldText

            // Lets us know that the user is cancelling the save
            property bool cancelling

            Keys.onEscapePressed: {
                // Cancel the save, and deselect the text input
                cancelling = true
                focus = false
            }

            onActiveFocusChanged: {
                // When we first gain focus, save the old text and select everything for clearing.
                if (activeFocus) {
                    oldText = editText
                    selectAll()
                } else if (cancelling) {
                    // When cancelling, restore the old text, and clear state.
                    editText = oldText
                    oldText = ""
                    cancelling = false
                } else {
                    // TO DO: Handle new text
                    //_backend.subject = editText
                    if(editText != "" && editText != currentText){
                        _cbSubjetModel.insert(_cbSubject.editText);
                    }
                }
            }
        }

        ToolButton{
            text: "ADD"
            Layout.preferredWidth: 50


            implicitHeight: parent.height
            Layout.fillHeight: true
            Layout.margins: edgeMargin
            onClicked: {
                _backend.costCenter = _cbCostCenter.currentText;
                _backend.project = _cbProject.currentText;
                _backend.subject = _cbSubject.currentText;
                _backend.minutes = _sbTime.value;
                _backend.date = _tfDate.text;
                _backend.addRecord();
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:40;width:1000}
}
##^##*/
