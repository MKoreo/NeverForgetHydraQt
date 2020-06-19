#include "record.h"

Record::Record()
{

}

Record::Record(const QString &creationDate, const QString &recordDate, const QString &costCenter, const QString &project, const QString &subject,  const QString &minutes){
  m_creationDate = QDateTime::fromString(creationDate,"yyyy-MM-d");
  m_recordDate = QDateTime::fromString(recordDate,"yyyy-MM-d");
  m_costCenter = costCenter;
  m_project = project;
  m_subject = subject;
  m_minutes = minutes.toInt();
}

Record::Record(QDateTime creationDate, QDateTime recordDate, QString costCenter, QString project, QString subject, int minutes){
  m_creationDate = creationDate;
  m_recordDate = recordDate;
  m_costCenter = costCenter;
  m_project = project;
  m_subject = subject;
  m_minutes = minutes;
}

// -- Getters & setters --
void Record::setCreationDate(QDateTime creationDate) {
  m_creationDate = creationDate;
}
QDateTime Record::creationDate(){
  return m_creationDate;
}

void Record::setRecordDate(QDateTime recordDate) {
  m_recordDate = recordDate;
}
QDateTime Record::recordDate(){
  return m_recordDate;
}

void Record::setCostCenter(QString costCenter) {
  m_costCenter = costCenter;
}
QString Record::costCenter(){
  return m_costCenter;
}

void Record::setProject(QString costCenter) {
  m_costCenter = costCenter;
}
QString Record::project(){
  return m_project;
}

void Record::setSubject(QString subject) {
  m_subject = subject;
}
QString Record::subject(){
  return m_subject;
}

int Record::minutes() {
  return m_minutes;
}
void Record::setMinutes(int minutes){
  m_minutes = minutes;
}

// -- Others --
void Record::addMinutes(int minutes){
  m_minutes += minutes;
}
