#include "record.h"

Record::Record()
    : m_creationDate()
{

}

Record::Record(const QString creationDate, const QString recordDate, const QString costCenter, const QString project, const QString subject,  const QString minutes){
    m_creationDate = QDate::fromString(creationDate,"yyyy-MM-dd");
    m_recordDate = QDate::fromString(recordDate,"yyyy-MM-dd");
    m_costCenter = costCenter;
    m_project = project;
    m_subject = subject;
    m_minutes = minutes.toInt();
}

Record::Record(QDate creationDate, QDate recordDate, QString costCenter, QString project, QString subject, int minutes){
    m_creationDate = creationDate;
    m_recordDate = recordDate;
    m_costCenter = costCenter;
    m_project = project;
    m_subject = subject;
    m_minutes = minutes;
}

// -- Getters & setters --
void Record::setCreationDate(QDate creationDate) {
    m_creationDate = creationDate;
}
QDate Record::creationDate() const{
    return m_creationDate;
}

void Record::setRecordDate(QDate recordDate) {
    m_recordDate = recordDate;
}
QDate Record::recordDate() const{
    return m_recordDate;
}

void Record::setCostCenter(QString costCenter) {
    m_costCenter = costCenter;
}
QString Record::costCenter() const{
    return m_costCenter;
}

void Record::setProject(QString costCenter) {
    m_costCenter = costCenter;
}
QString Record::project() const{
    return m_project;
}

void Record::setSubject(QString subject) {
    m_subject = subject;
}
QString Record::subject() const{
    return m_subject;
}

int Record::minutes() const{
    return m_minutes;
}
void Record::setMinutes(int minutes){
    m_minutes = minutes;
}

// -- Others --
void Record::addMinutes(int minutes){
    m_minutes += minutes;
}

EqualityGrade Record::compare(const Record& rec) {
    EqualityGrade grade = EqualityGrade::none;

    if(recordDate() == rec.recordDate()){
        grade = EqualityGrade::recordDate;
        if(costCenter() == rec.costCenter()) {
            grade = EqualityGrade::costCenter;
            if (project() == rec.project()){
                grade = EqualityGrade::project;
                if(subject() == rec.subject()){
                    grade = EqualityGrade::subject;
                    if(minutes() == rec.minutes()){
                        grade = EqualityGrade::minutes;
                    }
                }
            }
        }
    }

    return grade;
}

bool Record::validateParameters(const QString *params){
    // Determines if the parameters to create a record are correct
    // TODO: Improve validation

    // Check date
    if(!(QDate::fromString(params[0],"yyyy-MM-dd").isValid())){
        return false;
    }

    // Check minutes
    if (params[1].toInt() < 1) {
        return false;
    }

    // Check costcenter, project, subject
    if (params[2].count() <= 0 && params[3].count() <= 0 && params[4].count() <= 0){
        return false;
    }

    return true;
}
