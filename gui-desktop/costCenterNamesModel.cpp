#include "costCenterNamesModel.h"

CostCenterNamesModel::CostCenterNamesModel(QObject *parent)
    : QAbstractListModel(parent)
{
    Diary::instance().loadDiary("/home/thomas/Bureaublad/qt_records_write.xml");
    QVector<Record*> records = Diary::instance().getRecords();
    QList<QString> keep;
    int count = 0;
    foreach(Record* rec, records){
        if(++count <= g_MAX_HISTORY){
            if(!keep.contains(rec->costCenter())){
                keep.append(rec->costCenter());
            }
        } else {
            break;
        }
    }
    foreach(QString qstr, keep){
        m_comboEntries.append(qstr);
    }
}
int CostCenterNamesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_comboEntries.size();
}

QVariant CostCenterNamesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(role == defaultRole){
        return QVariant(m_comboEntries[index.row()]);
    }
    return QVariant();
}

QHash<int, QByteArray> CostCenterNamesModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[defaultRole] = "name";
    return roles;
}

void CostCenterNamesModel::insert(QString value){
    // Add it to the top.
    beginInsertRows(QModelIndex(), 0, 0);
    m_comboEntries.insert(0, value);
    endInsertRows();
}


