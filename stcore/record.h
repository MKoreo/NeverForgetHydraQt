#ifndef RECORD_H
#define RECORD_H

// No Datetime class in c++ so QDateTime
#include <QDateTime>
#include <QString>

class Record
{
public:
  Record();
  Record(QDateTime creationDate, QDateTime recordDate, QString costCenter, QString project, QString subject, int minutes);
  Record(const QString &creationDate, const QString &recordDate, const QString &costCenter, const QString &project, const QString &subject,  const QString &minutes);

  // Compare record to other record
  bool compare(Record rec);

public: // Getters - Setters
  void setCreationDate(QDateTime creationDate);
  QDateTime creationDate();

  void setRecordDate(QDateTime recordDate);
  QDateTime recordDate();

  void setCostCenter(QString costCenter);
  QString costCenter();

  void setProject(QString project);
  QString project();

  void setSubject(QString subject);
  QString subject();

  void setMinutes(int minutes);
  int minutes();

  void addMinutes(int minutes);

private:
  QDateTime m_creationDate;
  QDateTime m_recordDate;
  QString m_costCenter;
  QString m_project;
  QString m_subject;
  int m_minutes;

};

#endif // RECORD_H
