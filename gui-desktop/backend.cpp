#include "backend.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
    // Create stCore and let it do things
    // Change stuff in backend to get it to the GUI
}

void BackEnd::newDiary(){
    Diary::instance().newDiary(m_path);
}

void BackEnd::loadDiary(){

}

void BackEnd::openHydra(){
    QDesktopServices::openUrl(QUrl("/home", QUrl::TolerantMode));
}

void BackEnd::addRecord(){
    Diary::instance().addRecord(new Record(QDate::currentDate().toString("yyyy-MM-dd"), m_date, m_costCenter, m_project, m_subject, m_minutes));
}

QString BackEnd::getPath(){
    return m_path;
}

void BackEnd::setPath(const QString &path){
    m_path = path;
}

void BackEnd::setDate(const QString &date){
    m_date = date;
}

QString BackEnd::getDate(){
    return m_date;
}
void BackEnd::setCostCenter(const QString &costCenter){
    m_costCenter = costCenter;
}
void BackEnd::setProject(const QString &project){
    m_project = project;
}
void BackEnd::setSubject(const QString &subject){
    m_subject = subject;
}
void BackEnd::setMinutes(const QString &minutes){
    m_minutes = minutes;
}
