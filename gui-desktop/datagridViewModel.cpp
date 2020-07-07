#include "datagridViewModel.h"

DatagridViewModel::DatagridViewModel(QObject *parent)
    : QAbstractListModel(parent)
{
    //Diary::instance().loadDiary("/home/thomas/Bureaublad/qt_records_write.xml");
    m_currentDateRecords = Diary::instance().getRecordsByDate(QDate(2020, 05, 14));
}

int DatagridViewModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_currentDateRecords.size();
}

int DatagridViewModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 6;
}


QVariant DatagridViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    else {
        if(role == recordRole){
            switch(index.column()){
            case 0: return QVariant(m_currentDateRecords[index.row()]->creationDate().toString("yyyy-MM-dd"));
                break;
            case 1: return QVariant(m_currentDateRecords[index.row()]->recordDate().toString("yyyy-MM-dd"));
                break;
            case 2: return QVariant(m_currentDateRecords[index.row()]->costCenter());
                break;
            case 3: return QVariant(m_currentDateRecords[index.row()]->project());
                break;
            case 4: return QVariant(m_currentDateRecords[index.row()]->subject());
                break;
            case 5: return QVariant(m_currentDateRecords[index.row()]->minutes());
                break;
            }
        }
    }
    return QVariant();
}

QVariant DatagridViewModel::get(const int row, const int column) const
{
    switch(column){
    case 0: return QVariant(m_currentDateRecords[row]->creationDate().toString("yyyy-MM-dd"));
        break;
    case 1: return QVariant(m_currentDateRecords[row]->recordDate().toString("yyyy-MM-dd"));
        break;
    case 2: return QVariant(m_currentDateRecords[row]->costCenter());
        break;
    case 3: return QVariant(m_currentDateRecords[row]->project());
        break;
    case 4: return QVariant(m_currentDateRecords[row]->subject());
        break;
    case 5: return QVariant(m_currentDateRecords[row]->minutes());
        break;
    }
}


QHash<int, QByteArray> DatagridViewModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[recordRole] = "records";
    return roles;
}

void DatagridViewModel::refresh(QString selectedDate){
    Q_UNUSED(selectedDate);
    QDate date = QDate(2020, 05, 14);
    m_currentDateRecords = Diary::instance().getRecordsByDate(date);
    resetInternalData();
}
