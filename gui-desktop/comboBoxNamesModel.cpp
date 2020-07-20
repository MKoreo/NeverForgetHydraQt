#include "comboBoxNamesModel.h"

ComboBoxNamesModel::ComboBoxNamesModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

void ComboBoxNamesModel::renew(){
    QVector<Record*> records = Diary::instance().getRecords();

    int c = 0;
    foreach(Record* rec, records){
        if(++c <= g_MAX_HISTORY){

            if (g_role == "costCenter") {
                if(!m_items.contains(rec->costCenter())){
                    m_items.append(rec->costCenter());
                }else {
                    c--;
                }
            } else if (g_role == "project") {
                if(!m_items.contains(rec->project())){
                    m_items.append(rec->project());
                }else {
                    c--;
                }
            } else if(g_role == "subject") {
                if (!m_items.contains(rec->subject())){
                    m_items.append(rec->subject());
                } else {
                    c--;
                }
            } else {
                break;
            }
        }
    }
    beginInsertRows(QModelIndex(), 0, c-1);
    endInsertRows();


}

int ComboBoxNamesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_items.count();
}

QVariant ComboBoxNamesModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role);

    if (!index.isValid()){
        return QVariant();
    }

    return QVariant(m_items[index.row()]);


}

QHash<int, QByteArray> ComboBoxNamesModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[costCenterRole] = "costCenter";
    roles[projectRole] = "project";
    roles[subjectRole] = "subject";
    return roles;
}

void ComboBoxNamesModel::insert(QString value){
    // Add it to the top.
    beginInsertRows(QModelIndex(), 0, 0);
    m_items.insert(0, value);
    endInsertRows();
}


QString ComboBoxNamesModel::role(){
    return g_role;
}
void ComboBoxNamesModel::setRole(QString role) {
    g_role=role;
}
