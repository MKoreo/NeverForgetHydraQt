#include "subjectNamesModel.h"

SubjectNamesModel::SubjectNamesModel(QObject *parent)
    : QAbstractListModel(parent)
{
    Diary::instance().loadDiary("/home/thomas/Bureaublad/qt_records_write.xml");
    QVector<Record*> records = Diary::instance().getRecords();
    QList<QString> keep;
    int count = 0;
    foreach(Record* rec, records){
        if(++count <= g_MAX_HISTORY){
            if(!keep.contains(rec->subject())){
                keep.append(rec->subject());
            }
        } else {
            break;
        }
    }
    foreach(QString qstr, keep){
        m_comboEntries.append(qstr);
    }
}
int SubjectNamesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_comboEntries.size();
}

QVariant SubjectNamesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(role == defaultRole){
        return QVariant(m_comboEntries[index.row()]);
    }
    return QVariant();
}

QHash<int, QByteArray> SubjectNamesModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[defaultRole] = "name";
    return roles;
}

void SubjectNamesModel::insert(QString value){
    // Add it to the top.
    beginInsertRows(QModelIndex(), 0, 0);
    m_comboEntries.insert(0, value);
    endInsertRows();
}
