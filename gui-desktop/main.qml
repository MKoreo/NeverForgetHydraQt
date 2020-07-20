import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.14
import home.NeverForgetHydra 1.0
import QtQuick.Controls.Material 2.12
import "qrc:///dialogs"
import Qt.labs.platform 1.1 as Labs

ApplicationWindow {
    id: _root
    title: "NeverForgetHydraQt"

    // Dimensions
    visible: true
    width: 1200
    height: 550

    Material.theme: Material.Dark

    // Connection
    BackEnd {
        id: _backend
    }

    ComboBoxNamesModel {
        id: _cbCostCenterModel
        role: "costCenter"
    }

    ComboBoxNamesModel {
        id: _cbProjectModel
        role: "project"
    }

    ComboBoxNamesModel {
        id: _cbSubjetModel
        role: "subject"
    }

    DatagridViewModel {
        id: _dataGridViewModel
    }

    // Components
    menuBar: MenuBar {
        id: _menubar
        Menu {
            title: qsTr("&File")
            Action { text: qsTr("&New...");     onTriggered: _newFileDialog.open()}
            Action { text: qsTr("&Open...");    onTriggered: _openFileDialog.open();}
            Action { text: qsTr("Save &As..."); onTriggered: _saveFileDialog()}
            MenuSeparator { }
            Action { text: qsTr("&Hydra");      onTriggered: _backend.openHydra(); }
            Action { text: qsTr("&Quit");       onTriggered: Qt.callLater(Qt.quit)}
        }

        Menu {
            title: qsTr("&Preferences");
            Action { text: qsTr("Settings");    onTriggered: _quickSettings.open()}
            Action { text: qsTr("Theme");       onTriggered: _root.Material.theme = (_root.Material.theme == Material.Light ? Material.Dark : Material.Light)}
        }

        Menu {
            title: qsTr("&View");
            Action { text: qsTr("Records");     onTriggered:{_workSpace.currentIndex = 0}}
            Action { text: qsTr("Statistics");  onTriggered:{ _workSpace.currentIndex = 1}}
        }

        Menu {
            title: qsTr("&Help")
            Action { text: qsTr("&About");          onTriggered:{ _aboutDialog.open()} }
            Action { text: qsTr("&Send Feedback") }
            Action { text: qsTr("&Changelog") }
        }
    }


    Drawer {
        id: _quickSettings
        Material.elevation: -50 // Prevent shadow on toolbar
        y: _mainToolBar.height + _menubar.height
        width: 500
        height: _root.height - _menubar.height - _mainToolBar.height

        contentItem: QuickSettings {
        }

        enter: Transition { SmoothedAnimation { velocity: 2} }
        exit: Transition { SmoothedAnimation { velocity: 4 } }
    }

    ToolBar {
        id: _mainToolBar
        rightPadding: 0
        leftPadding: 0
        height: 50
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: _menubar.bottom


        Toolbar {
            // The Component
            z: 100
        }
    }

    RowLayout {
        z: -1
        id: _space
        spacing: 0
        anchors.topMargin: 10
        anchors.top: _mainToolBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Button {
            id: _openQuick
            Layout.preferredWidth: 25
            text: ">"
            focusPolicy: Qt.NoFocus
            Layout.fillHeight: true
            flat: true
            display: AbstractButton.TextBesideIcon
            onClicked: _quickSettings.open()
        }

        SwipeView {
            id: _workSpace
            clip: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            currentIndex: 0
            orientation: Qt.Horizontal
            interactive: false


            Item {
                id: _records

                ListView {
                    id: listView
                    anchors.fill: parent

                    contentWidth: width
                    //flickableDirection: Flickable.HorizontalAndVerticalFlick
                    headerPositioning: ListView.InlineHeader
                    header: Row { z: 120

                        spacing: 0
                        function itemAt(index) { return repeater.itemAt(index) }
                        Repeater {
                            id: repeater
                            model: ["Record Date", "Add Date", "Cost Center", "Project", "Subject", "Minutes"]
                            Rectangle {
                                implicitWidth: (listView.width/6) -5
                                implicitHeight: _text.height

                                color: Material.accent
                                Label {
                                    id: _text
                                    anchors.centerIn: parent
                                    text: modelData
                                    color: Material.background
                                    font.bold: true
                                    font.pixelSize: 18
                                    padding: 5

                                }
                            }


                        }
                    }

                    model: _dataGridViewModel

                    delegate: Column {
                        id: delegate
                        property int row: index
                        Rectangle {
                            color: "silver"
                            width: _arow.width
                            height: 1
                        }
                        Row {
                            id: _arow
                            spacing: 0
                            Repeater {
                                model: 6

                                ItemDelegate {
                                    property int column: index

                                    Text {
                                        anchors.fill: parent
                                        text: _dataGridViewModel.get(delegate.row, column)
                                        color: Material.foreground
                                        verticalAlignment: Text.AlignVCenter
                                        horizontalAlignment: Text.AlignHCenter

                                    }

                                    width: listView.headerItem.itemAt(column).width
                                    Rectangle {
                                        color: "silver"
                                        width: 1
                                        height: parent.height
                                    }
                                }

                            }
                            Rectangle {
                                color: "silver"
                                width: 1
                                height: parent.height
                            }

                        }
                        Rectangle {
                            color: "silver"
                            width: _arow.width
                            height: 1
                        }
                    }

                    ScrollIndicator.horizontal: ScrollIndicator { }
                    ScrollIndicator.vertical: ScrollIndicator { }
                }



            }


            Item {
                id: _statistics
                Rectangle {
                    anchors.fill: parent
                    color: Material.buttonDisabledColor
                    Button {
                        anchors.fill: parent
                        onClicked: popup.open()
                    }
                }
            }

        }
    }

    Item {
        //background statusbar
        id: _status
        height: popup.height
        width: popup.width
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 10



        Popup {
            id: popup
            modal: false
            focus: false

            Material.background: Material.accent


            Column {
                spacing: 2
                Text {
                    id: _popupTitle
                    text: "Record has been altered"
                    font.bold: true
                    font.pointSize: 12
                    color: _root.Material.background
                }

                Text {
                    id: _popupContent
                    text: "The minutes have been increased by 30."
                    font.pointSize: 10
                    color: _root.Material.background
                }
            }
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        }

    }

    AboutDialog {
        id: _aboutDialog


    }

    NewDialog {
        id: _newFileDialog
    }

    OpenDialog {
        id: _openFileDialog

    }
    SaveDialog {
        id: _saveFileDialog

    }

    Labs.SystemTrayIcon {
        // Needs widgets include
        visible: true
        icon.source: "qrc:/images/hourglas.png"

        menu: Labs.Menu {

            Labs.MenuItem {
                text: qsTr("Show")
                onTriggered: {
                    _root.show()
                    _root.raise()
                    _root.requestActivate();
                }
            }

            Labs.MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit()
            }

        }

        onActivated: {
            _root.show()
            _root.raise()
            _root.requestActivate()
        }
    }
}




