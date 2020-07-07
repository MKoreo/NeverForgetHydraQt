import QtQuick 2.3
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.3
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12


Dialog {
    standardButtons: StandardButton.Ok
    title: "About Never Forget Hydra"
    RowLayout {
        implicitWidth: 400
        implicitHeight: 100
        spacing: 10

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            Label {
                text: qsTr("Developer:")
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
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
