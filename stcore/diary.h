#ifndef DIARY_H
#define DIARY_H

#include <record.h>



#include <QDateTime>
#include <QString>
#include <QVector>

class Diary
{
public:
  // Only one instance of the diary is required
  // So going for singleton design
  static Diary& instance();
  ~Diary();

protected:
  // Disable constructor and copy operator
  Diary();
  Diary& operator=(const Diary& rhs);

  // Creating Diary
  void newDiary(const QString path);
  bool loadDiary(const QString path);
  bool saveDiary();

  // Manipulating diary
  void addRecord(const Record* rec);
  bool removeRecord(const Record* rec);

  // checking content
  int contains(const Record* rec) const;
  QVector<Record*> getRecordsByDate(const QDateTime* const date) const;
  QVector<Record*> getRecordsByDates(const QDateTime* const startDate, const QDateTime* const endDate) const;
private:
  QString m_path;
  QVector<Record*>* m_records;
  QVector<Record*>* m_deletedRecords;

};

#endif // DIARY_H
