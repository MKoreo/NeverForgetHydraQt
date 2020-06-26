#ifndef RECORD_H
#define RECORD_H

// No Datetime class in c++ so QDateTime
#include <QDateTime>
#include <QString>

enum EqualityGrade {
    none,
    recordDate,
    costCenter,
    project,
    subject,
    minutes
};

class Record
{
public:
  Record();
  Record(QDate creationDate, QDate recordDate, QString costCenter, QString project, QString subject, int minutes);
  Record(const QString &creationDate, const QString &recordDate, const QString &costCenter, const QString &project, const QString &subject,  const QString &minutes);

  // Compare record to other record
  EqualityGrade compare(const Record& rec);

public: // Getters - Setters
  void setCreationDate(QDate creationDate);
  QDate creationDate() const;

  void setRecordDate(QDate recordDate);
  QDate recordDate() const;

  void setCostCenter(QString costCenter);
  QString costCenter() const;

  void setProject(QString project);
  QString project() const;

  void setSubject(QString subject);
  QString subject() const;

  void setMinutes(int minutes);
  int minutes() const;

  void addMinutes(int minutes);

private:
  QDate m_creationDate;
  QDate m_recordDate;
  QString m_costCenter;
  QString m_project;
  QString m_subject;
  int m_minutes;
};

#endif // RECORD_H
