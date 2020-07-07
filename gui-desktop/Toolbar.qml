import QtQuick 2.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.14
import io.home.essentials 1.0

Rectangle {
    id: _toolbar
    color: Material.accent

    property int foldedDateWidth: 75
    property int unfoldedDateWidth: 140
    property int edgeMargin: 7
    anchors.fill: parent

    BackEnd {
        id: _backend
    }

    RowLayout{
        Material.accent: Material.background
        id: _toolRow
        anchors.fill: parent

        TextField{
            Material.foreground: Material.background
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
            Material.foreground: Material.background
            Layout.margins: edgeMargin
            editable: true
            wheelEnabled: true
            implicitWidth: 120
            Layout.fillHeight: true

        }

        ComboBox {
            id: _cbCostCenter
            Material.foreground: Material.background
            enabled: true
            Layout.margins: edgeMargin
            wheelEnabled: true
            editable: true
            Layout.fillWidth: true
            implicitWidth: 150
            Layout.fillHeight: true
            textRole: "costCenter"
            model: ComboBoxNamesModel {
                id: _cbCostCenterModel
                g_role: _cbCostCenter.textRole
            }
            // S
            font.bold: true
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

            Material.foreground: Material.background
            wheelEnabled: true
            editable: true
            Layout.margins: edgeMargin
            Layout.fillWidth: true
            implicitWidth: 150
            Layout.fillHeight: true
            font.bold: true
            // TBD
            textRole: "project"
            model: ComboBoxNamesModel {
                id: _cbProjectModel
                g_role: _cbProject.textRole
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
            textRole: "subject"
            wheelEnabled: true
            Material.foreground: Material.background
            editable: true
            Layout.fillHeight: true
            Layout.margins: edgeMargin
            Layout.fillWidth: true
            implicitWidth: 150
            implicitHeight: parent.height
            font.bold: true
            // TBD
            model: ComboBoxNamesModel {
                id: _cbSubjetModel
                g_role: _cbSubject.textRole
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

        Button{
            id: _addButton
            text: "ADD"
            Layout.preferredWidth: 60
            highlighted: true

            Material.foreground: Material.backgroundDimColor

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
    D{i:0;autoSize:true;height:60;width:1000}
}
##^##*/
