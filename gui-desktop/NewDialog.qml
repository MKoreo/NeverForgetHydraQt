import QtQuick 2.2
import QtQuick.Dialogs 1.3

FileDialog {
    id: _newFileDialog
    title: "Please choose a file"
    folder: shortcuts.home
    selectExisting: false
    selectMultiple: false
    selectFolder: false
    nameFilters: [ "XML files (*.xml)", "All files (*)" ]
    onAccepted: {
        BackEnd.newDiary(_newFileDialog.fileUrl);
        _mainToolBar.enabled = true;
    }
    onRejected: {
        console.log("Canceled")
    }
}

