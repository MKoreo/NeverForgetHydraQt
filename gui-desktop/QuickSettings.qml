import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.5
import QtQuick.Controls.Universal 2.3
import QtQuick.Layouts 1.14
import io.home.essentials.backend 1.0

ColumnLayout {
    id: _root

    // quicksettings
    property int quickTitelBarHeight: 20
    property int quickSettingsSpacing: 20
    property int quickSettingsRadius: 5
    property alias quickTitelBarQuickSettingsColor: _quickTitelBarQuickSettings.color

    spacing: quickSettingsSpacing
    anchors.fill: parent
    anchors.margins: quickSettingsSpacing

    Rectangle {
        id: _quickTitelBarQuickSettings
        color: "#df3a3a"
        radius: quickSettingsRadius
        Layout.fillWidth: true
        Layout.preferredHeight: quickTitelBarHeight
        border.width: 1
        Text {
            color: "white"
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
        spacing: 0
        Layout.fillWidth: true
        RowLayout {
            id: _rowTimer
            spacing: 25
            Layout.fillWidth: true

            Label {
                id: _timerLabel
                text: qsTr("Timer(min):")
                verticalAlignment: Text.AlignBottom
            }
            SpinBox {
                Layout.fillWidth: true
                id: _timerSpin
                wheelEnabled: true
                from: 15
                stepSize: 5
                editable: true
                to: 60

            }

            Button{
                text: qsTr("Reset")
                Layout.preferredWidth: 50
                Layout.fillWidth: false
                Layout.leftMargin: -30
                z:-1
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

        CheckBox{
            id: _cbStartup
            text: "Start NFHQ with OS"
            Layout.fillWidth: true
        }

    }

    ColumnLayout{
        id: _quickQuickSettingsPart2
        clip: true
        spacing: 0
        Layout.fillWidth: true
        RowLayout {
            id: _rowView
            spacing: 25
            Layout.fillWidth: true
        }

    }
    Rectangle{
        //filler
        Layout.fillHeight: true
    }

}


/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#000000";height:250;width:250}
}
##^##*/
