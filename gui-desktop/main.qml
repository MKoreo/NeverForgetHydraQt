import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.14
import io.home.essentials.backend 1.0

ApplicationWindow {
    id: _root
    title: "NeverForgetHydraQt"

    palette.highlight: "#CC3333"
    visible: true
    width: 900
    height: 350

    BackEnd {
        id: _backend
    }

    // Components
    menuBar: MenuBar {
        id: _menubar
        Menu {
            title: qsTr("&File")
            Action { text: qsTr("&New...") }
            Action { text: qsTr("&Open...") }
            Action { text: qsTr("Save &As...")}
            MenuSeparator { }
            Action { text: qsTr("&Hydra"); onTriggered: Qt.openUrlExternally("http://www.google.be"); }
            Action { text: qsTr("&Quit"); onTriggered: Qt.callLater(Qt.quit)}
        }

        Menu {
            title: qsTr("&Preferences");
            Action { text: qsTr("Settings"); onTriggered: _quickSettings.open()}
            Action { text: qsTr("Theme")}
        }

        Menu {
            title: qsTr("&View");
            Action { text: qsTr("Records"); onTriggered:{_workSpace.currentIndex = 0}}
            Action { text: qsTr("Statistics");onTriggered:{ _workSpace.currentIndex = 1}}
        }

        Menu {
            title: qsTr("&Help")
            Action { text: qsTr("&About") }
            Action { text: qsTr("&Send Feedback") }
            Action { text: qsTr("&Changelog") }
        }
    }


    Drawer {
        id: _quickSettings
        y: _mainToolBar.height + _menubar.height
        width: 250
        height: _root.height - _menubar.height - _mainToolBar.height

        contentItem: QuickSettings {
            quickTitelBarQuickSettingsColor: palette.highlight
        }

        enter: Transition { SmoothedAnimation { velocity: 2} }
        exit: Transition { SmoothedAnimation { velocity: 4 } }
    }

    ToolBar {
        id: _mainToolBar
        rightPadding: 0
        leftPadding: 0
        height: 35
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: _menubar.bottom


        Toolbar {
            // The Component
        }
    }

    RowLayout {
        id: _space
        spacing: 0
        anchors.top: _mainToolBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: _statusBar.top

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
                Rectangle {
                    anchors.fill: parent
                    color: palette.alternateBase
                    Label {
                        anchors.fill: parent
                        text: qsTr(_backend.cpu)
                    }
                }
            }

            Item {
                id: _statistics
                Rectangle {
                    anchors.fill: parent
                    color: palette.base
                }
            }

        }


    }

    Rectangle {
        //background statusbar
        id: _statusBar
        height: 20
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: palette.base

        RowLayout{
            anchors.fill: parent
            spacing: 10

            Label {
                id: _statusfield
                text: qsTr("Status: Almost exploding")


                rightPadding: 5
                leftPadding: 5
                background: Rectangle{
                    color: palette.highlight
                }

            }

            Rectangle{
                Layout.fillWidth: true
            }

            Label {
                id: _statusfield2
                text: qsTr("Helper: Not inplemented")
                rightPadding: 5
                leftPadding: 5
                background: Rectangle{
                    color: "Blue"
                }
            }

        }
    }



}

/*##^##
Designer {
    D{i:0;formeditorColor:"#ffffff";height:250;width:1000}
}
##^##*/
