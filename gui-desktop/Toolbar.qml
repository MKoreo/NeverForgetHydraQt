import QtQuick 2.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.14
import home.NeverForgetHydra 1.0

Rectangle {
    id: _toolbar
    color: Material.accent


    property int foldedDateWidth: 75
    property int unfoldedDateWidth: 140
    property int edgeMargin: 7
    anchors.fill: parent

    RowLayout{
        Material.accent: Material.background
        id: _toolRow
        anchors.fill: parent

        TextField{
            // Help
            ToolTip.delay: 500
            ToolTip.timeout: 5000
            ToolTip.visible: hovered
            hoverEnabled: true
            ToolTip.text: qsTr("Fill in/scroll for a date to view its records/add records to.")

            Material.foreground: Material.background
            id: _tfDate
            Layout.margins: edgeMargin
            text: BackEnd.date.substring(5,10)
            leftPadding: 0
            topPadding: 0
            Layout.fillHeight: true
            horizontalAlignment: Text.AlignHCenter
            // Start in small position
            state: "folded"

            selectByMouse: true

            // Increase size if we pop calendar
            states: [
                State {
                    name: "unfolded";
                    PropertyChanges { target: _tfDate; implicitWidth: unfoldedDateWidth; }
                    PropertyChanges { target: _testarea; visible: true }
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

            MouseArea {
                id: _testarea
                anchors.fill: parent
                visible: false
                propagateComposedEvents: true
                onWheel: {
                    if (wheel.angleDelta.y > 0) {
                        // Mousewheel up
                        if (wheel.modifiers == Qt.NoModifier){
                            BackEnd.increaseDate(0);
                        } else if (wheel.modifiers == Qt.ControlModifier){
                            BackEnd.increaseDate(1);
                        } else {
                            BackEnd.increaseDate(2);
                        }
                    } else {
                        // Mousewheel down
                        if (wheel.modifiers == Qt.NoModifier){
                            BackEnd.decreaseDate(0);
                        } else if (wheel.modifiers == Qt.ControlModifier){
                            BackEnd.decreaseDate(1);
                        } else {
                            BackEnd.decreaseDate(2);
                        }
                    }
                    _tfDate.text = BackEnd.date
                    _dataGridViewModel.refresh(BackEnd.date)
                }
            }

            onActiveFocusChanged: if(state == "unfolded") { state = "folded";  BackEnd.date = text; text = BackEnd.date.substring(5,10); _dataGridViewModel.refresh(BackEnd.date);} else { state = "unfolded"; text = BackEnd.date}

            onHoveredChanged: {

            }

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

            // Help
            ToolTip.delay: 500
            ToolTip.timeout: 5000
            ToolTip.visible: hovered
            hoverEnabled: true
            ToolTip.text: qsTr("Fill in/select a costcenter for the record.")

            // Looks
            Material.foreground: Material.background
            font.bold: true
            Layout.fillWidth: true
            implicitWidth: 150
            Layout.fillHeight: true
            Layout.margins: edgeMargin

            // Modifiers
            wheelEnabled: true
            editable: true

            // Data
            textRole: "costCenter"
            model: _cbCostCenterModel

            // Textedit
            property string oldText
            property bool cancelling

            Keys.onEscapePressed: {
                // Cancel the save, and deselect the text input
                cancelling = true
                focus = false
            }

            onCurrentIndexChanged: {
                _cbProjectModel.setCurrentCostCenter(_cbCostCenter.textAt(currentIndex));
                _cbSubjectModel.setCurrentCostCenter(_cbCostCenter.textAt(currentIndex));
                _cbProjectModel.renew();
                _cbSubjectModel.renew();

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
                    // Handle new text
                    if(editText != "" && editText != currentText){
                        oldText = editText;
                        _cbCostCenterModel.insert(editText)
                        //_cbCostCenterModel.renew();
                        _cbCostCenter.currentIndex = _cbCostCenter.find(oldText);
                    }
                }
            }

            Component.onCompleted: _cbCostCenterModel.renew();




        }
        ComboBox {
            id: _cbProject

            // Help
            ToolTip.delay: 500
            ToolTip.timeout: 5000
            ToolTip.visible: hovered
            hoverEnabled: true
            ToolTip.text: qsTr("Fill in/select a project for the record.")

            // Looks
            Material.foreground: Material.background
            font.bold: true
            Layout.fillWidth: true
            implicitWidth: 150
            Layout.fillHeight: true
            Layout.margins: edgeMargin

            // Modifiers
            wheelEnabled: true
            editable: true

            // Data
            textRole: "project"
            model: _cbProjectModel

            // TextEdit
            property string oldText
            property bool cancelling

            Keys.onEscapePressed: {
                // Cancel the save, and deselect the text input
                cancelling = true
                focus = false
            }

            onCurrentIndexChanged: {
                _cbSubjectModel.setCurrentProject(_cbProject.textAt(currentIndex));
                _cbSubjectModel.renew();
            }

            onActiveFocusChanged: {

                if (activeFocus) {
                    // When we first gain focus, save the old text and select everything for clearing.
                    oldText = editText
                    selectAll()
                } else if (cancelling) {
                    // When cancelling, restore the old text, and clear state.
                    editText = oldText
                    oldText = ""
                    cancelling = false
                } else {
                    // Handle new text: Check if exsists, if not add
                    if(editText != "" && editText != currentText){
                        oldText = editText;
                        _cbProjectModel.insert(editText)
                        //_cbProjectModel.renew();
                        _cbProject.currentIndex = _cbProject.find(oldText)
                    }
                }
            }

            Component.onCompleted: _cbProjectModel.renew();
        }

        ComboBox {
            id: _cbSubject

            // Help
            ToolTip.delay: 500
            ToolTip.timeout: 5000
            ToolTip.visible: hovered
            hoverEnabled: true
            ToolTip.text: qsTr("Fill in/select a subject for the record.")

            // Looks
            Material.foreground: Material.background
            font.bold: true
            Layout.fillWidth: true
            implicitWidth: 150
            Layout.fillHeight: true
            Layout.margins: edgeMargin

            // Modifiers
            wheelEnabled: true
            editable: true

            // Data
            model: _cbSubjectModel
            textRole: "subject"

            // TextEdit
            property string oldText
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
                    // Handle new text
                    if(editText != "" && editText != currentText){
                        oldText = editText;
                        _cbSubjectModel.insert(oldText)
                        //_cbSubjectModel.renew();
                        _cbSubject.currentIndex = _cbSubject.find(oldText)
                    }
                }
            }

            Component.onCompleted: _cbSubjectModel.renew();
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
                BackEnd.costCenter = _cbCostCenter.currentText;
                BackEnd.project = _cbProject.currentText;
                BackEnd.subject = _cbSubject.currentText;
                BackEnd.minutes = _sbTime.value;
                BackEnd.addRecord();
                _dataGridViewModel.refresh(BackEnd.date);
            }

            ToolTip.delay: 500
            ToolTip.timeout: 5000
            ToolTip.visible: hovered
            hoverEnabled: true
            ToolTip.text: qsTr("Click to add a record")

        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:50;width:640}
}
##^##*/
