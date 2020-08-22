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
        BackEnd.path = _openFileDialog.fileUrl;
        BackEnd.loadDiary();

        _cbCostCenterModel.renew();
        _cbProjectModel.renew();
        _cbSubjectModel.renew();

        _dataGridViewModel.refresh(BackEnd.date);

        _mainToolBar.enabled = true;
    }
    onRejected: {
        console.log("Canceled")
    }
}
