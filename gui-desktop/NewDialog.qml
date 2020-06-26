import QtQuick 2.2
import QtQuick.Dialogs 1.2

FileDialog {
    id: fileDialog
    title: "Please choose a file"
    folder: shortcuts.home
    selectExisting: false
    selectMultiple: false
    selectFolder: true
    nameFilters: [ "XML files (*.xml)", "All files (*)" ]
    onAccepted: {
        console.log("You chose: " + fileDialog.fileUrls)
    }
    onRejected: {
        console.log("Canceled")
    }
}
