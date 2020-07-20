#include "backend.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
    // Upon creating, fill in current date
    setCurrentDate();
}

// ---- MenuItems
void BackEnd::newDiary(QString path){
    // TODO: comfirmation that you will delete the old one
    if(path.contains("file:")){
        m_path = path.remove(0, 7);
    } else {
        m_path = path;
    }

    Diary::instance().newDiary(m_path);
}

void BackEnd::loadDiary(){
    newDiary(m_path);
    Diary::instance().loadDiary(m_path);
}

void BackEnd::saveDiary(){
    Diary::instance().saveDiary(m_path);
}

void BackEnd::openHydra() const {
    // TODO: Change url to realy HYDRA Url
    QDesktopServices::openUrl(QUrl("/home", QUrl::TolerantMode));
}

// ---- Methods
void BackEnd::addRecord(){
    if (validateMembers()){
        Diary::instance().addRecord(new Record(QDate::currentDate().toString("yyyy-MM-dd"), m_date, m_costCenter, m_project, m_subject, m_minutes));
        Diary::instance().saveDiary(m_path);
    } else {
        // TODO: Popup that something isn't good yet
    }
}

bool BackEnd::validateMembers() const{
    // Determines if the parameters to create a record are correct
    // TODO: Improve validation
    if(m_date.count() != 10 || m_date[4] != "-" || m_date[7] != "-"){
        return false;
    } else if(m_costCenter != "" && m_project != "" && m_subject != "" && m_minutes != ""){
        return true;
    }
    return false;
}

void BackEnd::setCurrentDate(){
    // Set m_date to current date in yyyy-MM-dd format
    setDate(QDate::currentDate().toString("yyyy-MM-dd"));
}

void BackEnd::increaseDate(const int &type){
    QDate qdate = QDate::fromString(m_date, "yyyy-MM-dd");

    switch(type){
    case 1: m_date = qdate.addYears(1).toString("yyyy-MM-dd");
        break;
    case 2:
        m_date = qdate.addMonths(1).toString("yyyy-MM-dd");
        break;
    default: m_date = qdate.addDays(1).toString("yyyy-MM-dd");
        break;
    }
}
void BackEnd::decreaseDate(const int &type){
    QDate qdate = QDate::fromString(m_date, "yyyy-MM-dd");
    switch(type){
    case 1: m_date = qdate.addYears(-1).toString("yyyy-MM-dd");
        break;
    case 2:
        m_date = qdate.addMonths(-1).toString("yyyy-MM-dd");
        break;
    default: m_date = qdate.addDays(-1).toString("yyyy-MM-dd");
        break;
    }
}

// Setters
void BackEnd::setCostCenter(const QString costCenter){
    m_costCenter = costCenter;
}
void BackEnd::setProject(const QString project){
    m_project = project;
}
void BackEnd::setSubject(const QString subject){
    m_subject = subject;
}
void BackEnd::setMinutes(const QString minutes){
    m_minutes = minutes;
}
void BackEnd::setPath(const QString path){
    m_path = path;
}
void BackEnd::setDate(const QString date){
    m_date = date;
}

// Getters
QString BackEnd::getDate() const{
    return m_date;
}
QString BackEnd::getPath() const{
    return m_path;
}
