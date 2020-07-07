import QtQuick 2.2
import QtQuick.Dialogs 1.2

FileDialog {
    id: _openFileDialog
    title: "Please choose a file"
    folder: shortcuts.home

    selectExisting: true
    selectMultiple: false
    selectFolder: false

    nameFilters: [ "XML files (*.xml)", "All files (*)" ]

    onAccepted: {
        _backend.loadDiary(_openFileDialog.fileUrl);
    }
    onRejected: {
        console.log("Canceled")
    }
}
