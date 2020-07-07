import QtQuick 2.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12

Dialog {
    title: "About Never Forget Hydra"
    id: _dialog
    contentItem: Pane {
        ColumnLayout {
            implicitWidth: 400
            implicitHeight: 100
            RowLayout {
                Layout.fillHeight: true
                Layout.fillWidth: true
                spacing: 10

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Label {
                        text: qsTr("Developed by:")
                        font.weight: Font.Bold
                        Layout.fillWidth: true
                        horizontalAlignment: Text.left
                    }

                    Label {
                        text: qsTr("Contact:")
                        font.weight: Font.Bold
                        Layout.fillWidth: true
                        horizontalAlignment: Text.left
                    }

                    Label {
                        text: qsTr("Made with:")
                        font.weight: Font.Bold
                        Layout.fillWidth: true
                        horizontalAlignment: Text.left
                    }
                }


                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Label {
                        text: qsTr("Thomas Poppe (THOPOP)")
                        Layout.fillWidth: true
                        horizontalAlignment: Text.right
                    }

                    Label {
                        text: qsTr("thomas.poppe@barco.com")
                        Layout.fillWidth: true
                        horizontalAlignment: Text.right
                    }

                    Label {
                        text: qsTr("Opensource QT 5.14")
                        Layout.fillWidth: true
                        horizontalAlignment: Text.right
                    }
                }

            }

            Button {
                text: qsTr("What ABOUT it?!")
                Layout.fillWidth: true
                Layout.fillHeight: true
                highlighted: true
                onClicked: _dialog.close()
            }
        }


    }
}







/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
