#include "comboBoxNamesModel.h"

ComboBoxNamesModel::ComboBoxNamesModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

void ComboBoxNamesModel::setSettings(Settings *settings){
    m_settings = settings;
    connect(settings, &Settings::s_filterDropdownChanged, this, &ComboBoxNamesModel::renew);
    //connect(settings, &Settings::s_filterTypeChanged, this, &ComboBoxNamesModel::renew);
}

Settings* ComboBoxNamesModel::settings(){
    return m_settings;
}

void ComboBoxNamesModel::setCurrentCostCenter(QString value){
    currentCostCenter = value;
}
void ComboBoxNamesModel::setCurrentProject(QString value){
    currentProject = value;
}
void ComboBoxNamesModel::setCurrentSubject(QString value){
    currentSubject = value;
}

void ComboBoxNamesModel::renew(){
    // Fetch sorted records in diary
    Diary::instance().sort();   // Most recent first
    QVector<Record*> records;

    bool recordsLoaded = false;

    if (m_settings->filterDropdown()){
        if (currentCostCenter != ""){
            if (currentProject != "") {
              records = Diary::instance().getRecordsByProject(currentCostCenter, currentProject);
              recordsLoaded = true;
            } else {
                records = Diary::instance().getRecordsByCostCenter(currentCostCenter);
                recordsLoaded = true;
            }
        }
    }

    if (!recordsLoaded){
        records = Diary::instance().getRecords();
    }

    // Clear current item list
    beginRemoveRows(QModelIndex(), 0, m_items.count()-1);
    m_items.clear();
    endRemoveRows();

    int c = 0;
    foreach(Record* rec, records){
        if(++c <= m_settings->historyTicks()){

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
        } else {
            break;
        }
    }

    beginInsertRows(QModelIndex(), 0, m_items.count()-1);
    endInsertRows();
}

int ComboBoxNamesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return (m_items.count() > m_settings->historyTicks() ? m_settings->historyTicks() : m_items.count());
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
