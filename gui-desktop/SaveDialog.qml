import QtQuick 2.2
import QtQuick.Dialogs 1.2

FileDialog {
    id: _saveFileDialog
    title: "Please choose a location and name to save the XML diary"
    folder: shortcuts.home

    selectExisting: true
    selectMultiple: false
    selectFolder: false

    nameFilters: [ "XML files (*.xml)", "All files (*)" ]

    onAccepted: {
        _backend.saveDiary(_saveFileDialog.fileUrl);
    }
    onRejected: {
        console.log("Canceled")
    }
}
