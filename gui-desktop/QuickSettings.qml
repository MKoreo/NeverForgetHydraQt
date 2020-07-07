import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import QtQuick.Controls.Universal 2.3
import QtQuick.Layouts 1.14
import io.home.essentials 1.0
import QtQuick.Controls.Material 2.3

ScrollView {
    anchors.fill: parent
    contentWidth: width

    // quicksettings
    property int quickSettingsSpacing: 20
    property int quickSettingsRadius: 5

    clip: true

    ColumnLayout {
        id: _root
        anchors.fill: parent
        anchors.margins: quickSettingsSpacing
        spacing: quickSettingsSpacing

        Pane {
            Layout.fillWidth: true
            Material.elevation: 1


            Column {
                anchors.fill: parent
                Label {
                    id: _labelQuicksettings
                    text: qsTr("Quicksettings")
                    font.bold: true
                    font.pointSize: 14
                    fontSizeMode: Text.Fit
                    //horizontalAlignment: Text.AlignHCenter
                    //verticalAlignment: Text.AlignVCenter
                }

                MenuSeparator { anchors.left: _labelQuicksettings.left; anchors.right: _labelQuicksettings.right }

                ColumnLayout{
                    anchors.left: parent.left
                    anchors.right: parent.right

                    RowLayout {
                        Layout.fillWidth: true

                        Label {
                            text: qsTr("Timer(min):")
                        }

                        Rectangle {
                            // Spacer
                            Layout.fillWidth: true;
                        }

                        Button{
                            text: qsTr("Reset")
                        }

                        SpinBox {
                            id: _timerSpin
                            wheelEnabled: true
                            from: 15
                            stepSize: 5
                            editable: true
                            to: 60
                            Layout.preferredWidth: 100
                        }
                    }

                    CheckBox{
                        id: _cbAdd
                        text: "Minimize on adding record"
                    }

                    CheckBox{
                        id: _cbFilter
                        text: "Filter dropdown lists"
                    }

                    RowLayout {
                        id: _rowSort
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
            }

        }





        Pane {
            Layout.fillWidth: true
            Material.elevation: 1

            Column {
                anchors.fill: parent
                Label {
                    id: _labelGlobalSettings
                    text: qsTr("Global settings")
                    font.bold: true
                    font.pointSize: 14
                    fontSizeMode: Text.Fit
                }

                MenuSeparator { anchors.left: _labelGlobalSettings.left; anchors.right: _labelGlobalSettings.right }

                ColumnLayout{
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
                            Layout.preferredWidth: 100
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
                                       Material.background
                                   } else {
                                       Material.accent
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
            }
        }

        Pane {
            Layout.fillWidth: true
            Material.elevation: 1

            Column {
                anchors.fill: parent
                Label {
                    id: _labelRecordViewSettings
                    text: qsTr("Record View settings")
                    font.bold: true
                    font.pointSize: 14
                    fontSizeMode: Text.Fit
                }

                MenuSeparator { anchors.left: _labelRecordViewSettings.left; anchors.right: _labelRecordViewSettings.right }
            }
        }

        Pane {
            Layout.fillWidth: true
            Material.elevation: 1

            Column {
                anchors.fill: parent
                Label {
                    id: _labelStatisticsViewSettings
                    text: qsTr("Statistics view settings")
                    font.bold: true
                    font.pointSize: 14
                    fontSizeMode: Text.Fit
                }

                MenuSeparator { anchors.left: _labelStatisticsViewSettings.left; anchors.right: _labelStatisticsViewSettings.right }
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
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
