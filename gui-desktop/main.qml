import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.14
import home.NeverForgetHydra 1.0 as NFH
import QtQuick.Controls.Material 2.12
import "qrc:///dialogs"
import Qt.labs.platform 1.1 as Labs

ApplicationWindow {
    id: _root
    title: "NeverForgetHydraQt"

    // Dimensions
    visible: true
    minimumHeight: 450
    minimumWidth: 1000

    Connections {
        target: Settings

        function onS_themeChanged(){
            _root.Material.theme = (Settings.theme == 0 ? Material.Light : Material.Dark);
        }

        function onS_colourChanged(){
            _root.Material.accent = (Settings.colour == 0 ? Material.Red : (Settings.colour == 1 ? Material.Blue : Material.Green));
        }
    }



    // Models used
    NFH.ComboBoxNamesModel {
        id: _cbCostCenterModel
        settings: Settings
        role: "costCenter"
    }

    NFH.ComboBoxNamesModel {
        id: _cbProjectModel
        settings: Settings
        role: "project"
    }

    NFH.ComboBoxNamesModel {
        id: _cbSubjectModel
        settings: Settings
        role: "subject"
    }

    NFH.DatagridViewModel {
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
            Action { text: qsTr("&Hydra");      onTriggered: BackEnd.openHydra(); }
            Action { text: qsTr("&Quit");       onTriggered: Qt.callLater(Qt.quit)}
        }

        Menu {
            title: qsTr("&Preferences");
            Action { text: qsTr("Settings");    onTriggered: _quickSettings.open()}
            //Action { text: qsTr("Theme");       onTriggered: _root.Material.theme = (_root.Material.theme == Material.Light ? Material.Dark : Material.Light)}
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
        enabled: false;
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
                        //onClicked:
                    }
                }
            }

        }
    }


    // Show notifications, popup
    Connections {
        target: BackEnd

        function onS_minutePassed(minutesLeft){
            _tray.minutesLeft = minutesLeft;
        }

        function onS_timerPassed(){
            _root.show();
        }
    }

    Connections {
        target: Notifier

        function onFireNotification(m_title, m_content, m_important, m_critical){
            _notification.notificationTitle = m_title
            _notification.notificationContent = m_content
            _notification.notificationImportant = m_important
            _notification.notificationCritical = m_critical
            _notification.open();
        }
    }
    Popup {
        id: _notification

        x: Math.round((parent.width - width) - 10)
        y: Math.round((parent.height - height) - 10)

        property string notificationTitle : ""
        property string notificationContent : ""
        property bool notificationImportant: false
        property bool notificationCritical: false

        modal: notificationImportant
        focus: false


        Material.background: if(notificationCritical){ Material.Red } else { Material.accent }

        Column {
            spacing: 2
            Text {
                id: _popupTitle
                text: _notification.notificationTitle
                font.bold: true
                font.pointSize: 10
                color: _root.Material.background
            }

            Text {
                id: _popupContent
                text: _notification.notificationContent
                font.pointSize: 8
                color: _root.Material.background
            }
        }
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        onClosed: Notifier.notificationKilled()
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
        id: _tray
        property string minutesLeft : "Calculating..."
        tooltip: "NeverForgetHydra\n Time till popup: " + minutesLeft

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




