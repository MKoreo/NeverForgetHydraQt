import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
//import QtQuick.Controls.Universal 2.3
import QtQuick.Layouts 1.14
import home.NeverForgetHydra 1.0
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
                            id: __test
                            text: qsTr("Timer(min):")
                        }

                        Rectangle {
                            // Spacer
                            Layout.fillWidth: true;
                        }

                        Button{
                            text: qsTr("Reset")
                            onClicked: Settings.s_timerReset()
                        }

                        SpinBox {
                            id: _timerSpin
                            wheelEnabled: true
                            from: 15
                            stepSize: 5
                            editable: true
                            to: 60
                            Layout.preferredWidth: 100
                            value: Settings.timer
                            onValueModified: {
                                Settings.timer = value;
                            }

                        }
                    }

                    CheckBox{
                        id: _cbAdd
                        text: "Minimize on adding record"
                        Component.onCompleted: checked = Settings.minimizeOnAdd
                        onCheckedChanged: Settings.minimizeOnAdd = checked
                    }

                    CheckBox{
                        id: _cbFilter
                        text: "Filter dropdown lists"
                        Component.onCompleted: checked = Settings.filterDropdown
                        onCheckedChanged: Settings.filterDropdown = checked
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
                            model: ["Most Recent", "Alphabetically"]

                            onCurrentIndexChanged: {
                                // When we first gain focus, save the old text and select everything for clearing.
                                Settings.filterType = currentIndex
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
                        from: 1
                        stepSize: 1
                        editable: true
                        to: 100
                        Layout.preferredWidth: 100

                        value: Settings.historyTicks
                        onValueModified: {
                            Settings.historyTicks = value;
                            _cbCostCenterModel.renew("", "");
                            _cbProjectModel.renew(_mainToolBar._cbCostCenter.currentValue, "");
                            _cbSubjectModel.renew(_mainToolBar._cbCostCenter.currentValue, _mainToolBar._cbProject.currentValue);
                        }
                    }
                }


                CheckBox{
                    id: _cbStartup
                    text: "Start NeverForgetHydra with OS"
                    Layout.fillWidth: true
                    Layout.leftMargin: -5

                    Component.onCompleted: checked = Settings.startWithOs
                    onCheckedChanged: Settings.startWithOs = checked
                }

                CheckBox{
                    background: Rectangle{
                        color: {if (_cbStacktrace.checked) {
                                Material.background
                            } else {
                                Material.color(Material.Red)
                            }
                        }
                        radius: quickSettingsRadius
                    }

                    id: _cbStacktrace
                    text: if (_cbStacktrace.checked) {
                              "THANKS: Send stacktrace on crash"
                          } else {
                              "PLEASE: Send stacktrace on crash"
                          }

                    Layout.leftMargin: -5
                    Component.onCompleted: checked = Settings.sendStacktrace

                    onCheckedChanged: Settings.sendStacktrace = checked
                }


                RowLayout {
                    Layout.fillWidth: true

                    Label {
                        text: qsTr("Theme style and colour:")
                        verticalAlignment: Text.AlignBottom
                    }

                    Rectangle {
                        Layout.fillWidth: true;
                    }


                    ComboBox {
                        enabled: true
                        editable: false
                        Layout.fillWidth: true

                        model: ["Light", "Dark"]

                        currentIndex: Settings.theme

                        Component.onCompleted: currentIndex = Settings.theme

                        onEditTextChanged: {
                            Settings.theme = currentIndex
                        }
                    }

                    ComboBox {
                        enabled: true
                        editable: false
                        Layout.fillWidth: true

                        model: ["Red", "Green", "Blue"]

                        Component.onCompleted: currentIndex = Settings.colour

                        onEditTextChanged: {
                            Settings.colour = currentIndex
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
