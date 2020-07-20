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

    property string path: "value";
    onAccepted: {
        _backend.path = _openFileDialog.fileUrl;
        _backend.loadDiary();

        _cbCostCenterModel.renew();
        _cbProjectModel.renew();
        _cbSubjetModel.renew();

        _dataGridViewModel.refresh(_backend.date);
    }
    onRejected: {
        console.log("Canceled")
    }
}
