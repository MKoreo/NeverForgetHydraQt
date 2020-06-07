import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import QtQuick.Controls.Universal 2.3
import QtQuick.Layouts 1.14
import io.home.essentials.backend 1.0

ScrollView {
    anchors.fill: parent
    contentWidth: width
    // quicksettings
    property int quickTitelBarHeight: 20
    property int quickSettingsSpacing: 20
    property int quickSettingsRadius: 5
    clip: true
    ColumnLayout {
        id: _root


        spacing: quickSettingsSpacing
        anchors.fill: parent
        anchors.margins: quickSettingsSpacing

        Rectangle {
            id: _quickTitelBarQuickSettings
            color: palette.highlight
            radius: quickSettingsRadius
            Layout.fillWidth: true
            Layout.preferredHeight: quickTitelBarHeight
            border.width: 1
            Text {
                color: palette.highlightedText
                anchors.fill: parent

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                text: qsTr("Quicksettings")
                fontSizeMode: Text.Fit
            }
        }


        ColumnLayout{
            id: _quickQuickSettingsPart1
            clip: true
            spacing: 10
            Layout.fillWidth: true
            RowLayout {
                id: _rowTimer
                //spacing: 25
                Layout.fillWidth: true

                Label {
                    id: _timerLabel
                    text: qsTr("Timer(min):")
                }

                Rectangle {
                    Layout.fillWidth: true;
                }

                SpinBox {
                    id: _timerSpin
                    wheelEnabled: true
                    from: 15
                    stepSize: 5
                    editable: true
                    to: 60
                    Layout.preferredWidth: 65

                }

                Button{
                    text: qsTr("Reset")
                }
            }

            CheckBox{
                id: _cbAdd
                text: "Minimize on adding record"
                Layout.fillWidth: true
            }

            CheckBox{
                id: _cbFilter
                text: "Filter dropdown lists"
                Layout.fillWidth: true
            }

            RowLayout {
                id: _rowSort
                //spacing: 25
                Layout.fillWidth: true


                Label {
                    id: _sortLabel
                    text: qsTr("Sort dropdown list:")
                }
                ComboBox {
                    id: _cbSort
                    enabled: true
                    editable: false
                    Layout.fillWidth: true


                    // TBD
                    model: ["Most Recent", "Alphabet"]

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
                        }
                    }
                }

            }

        }

        Rectangle {
            id: _quickTitelBarQuickSettings2
            color: palette.highlight
            radius: quickSettingsRadius
            Layout.fillWidth: true
            Layout.preferredHeight: quickTitelBarHeight
            border.width: 1
            Text {
                color: palette.highlightedText
                anchors.fill: parent

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                text: qsTr("Global settings")
                fontSizeMode: Text.Fit
            }
        }

        ColumnLayout{
            id: _quickQuickSettingsPart2
            clip: true
            spacing: 0
            Layout.fillWidth: true
            RowLayout {
                id: _rowView
                Layout.fillWidth: true

                Label {
                    id: _historyLabel
                    text: qsTr("History ticks in lists:")
                    verticalAlignment: Text.AlignBottom
                }

                Rectangle {
                    Layout.fillWidth: true;
                }

                SpinBox {
                    id: _historySpin
                    wheelEnabled: true
                    from: 5
                    stepSize: 1
                    editable: true
                    to: 100
                    Layout.preferredWidth: 65
                }
            }

            CheckBox{
                id: _cbStartup
                text: "Start NeverForgetHydra with OS"
                Layout.fillWidth: true
                Layout.leftMargin: -5
            }

            CheckBox{
                Rectangle{
                    color: if (_cbStacktrace.checked) {
                               "#00EEEE22"
                           } else {
                               "#55EEEE22"
                           }
                    radius: quickSettingsRadius
                    anchors.fill: parent
                    anchors.topMargin: 5
                    anchors.bottomMargin: 5
                    anchors.leftMargin: -5
                }

                id: _cbStacktrace
                text: if (_cbStacktrace.checked) {
                          "THANKS: Send stacktrace on crash"
                      } else {
                          "PLEASE: Send stacktrace on crash"
                      }

                Layout.leftMargin: -5
            }
        }

        Rectangle {
            id: _quickTitelBarQuickSettings3
            color: palette.highlight
            radius: quickSettingsRadius
            Layout.fillWidth: true
            Layout.preferredHeight: quickTitelBarHeight
            border.width: 1
            Text {
                color: palette.highlightedText
                anchors.fill: parent

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                text: qsTr("Record view settings")
                fontSizeMode: Text.Fit
            }
        }

        Rectangle {
            id: _quickTitelBarQuickSettings4
            color: palette.highlight
            radius: quickSettingsRadius
            Layout.fillWidth: true
            Layout.preferredHeight: quickTitelBarHeight
            border.width: 1
            Text {
                color: palette.highlightedText
                anchors.fill: parent

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                text: qsTr("Statistics view settings")
                fontSizeMode: Text.Fit
            }
        }
        Rectangle{
            //filler
            Layout.fillHeight: true
        }

    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#000000";height:250;width:250}
}
##^##*/
