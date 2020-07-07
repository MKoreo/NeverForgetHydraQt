#include "comboBoxNamesModel.h"

ComboBoxNamesModel::ComboBoxNamesModel(QObject *parent)
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
        m_costCenters.append(qstr);
    }

    count = 0;
    keep.clear();
    foreach(Record* rec, records){
        if(++count <= g_MAX_HISTORY){
            if(!keep.contains(rec->project())){
                keep.append(rec->project());
            }
        } else {
            break;
        }
    }
    foreach(QString qstr, keep){
        m_projects.append(qstr);
    }

    count = 0;
    keep.clear();
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
        m_subjects.append(qstr);
    }
}
int ComboBoxNamesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    // TODO
    if(g_role == "subject"){
        return m_subjects.count();
    }

    if(g_role == "project"){
        return m_subjects.count();
    }

    if(g_role == "costCenter"){
        return m_subjects.count();
    }

    return 5;
}

QVariant ComboBoxNamesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(role == costCenterRole){
        return QVariant(m_costCenters[index.row()]);
    }

    if(role == projectRole){
        return QVariant(m_projects[index.row()]);
    }

    if(role == subjectRole){
        return QVariant(m_subjects[index.row()]);
    }
    return QVariant();
}

QHash<int, QByteArray> ComboBoxNamesModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[costCenterRole] = "costCenter";
    roles[projectRole] = "project";
    roles[subjectRole] = "subject";
    return roles;
}

void ComboBoxNamesModel::insert(QString value, int role){
    // Add it to the top.
    beginInsertRows(QModelIndex(), 0, 0);
    if(role == costCenterRole){
        m_costCenters.insert(0, value);
    }

    if(role == projectRole){
        m_projects.insert(0, value);
    }

    if(role == subjectRole){
        m_subjects.insert(0, value);
    }
    endInsertRows();
}


QString ComboBoxNamesModel::role(){
    return g_role;
}
void ComboBoxNamesModel::setRole(QString role) {
    g_role=role;
}
