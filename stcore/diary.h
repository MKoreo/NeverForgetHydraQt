#ifndef DIARY_H
#define DIARY_H

#include <QDateTime>
#include <QString>
#include <QVector>

#include "diarydao.h"
#include "record.h"

enum SortStyle {
    DateAscending,
    DateDescending
};

class Diary
{
public:
  // Only one instance of the diary is required
  // So going for singleton design
  static Diary& instance();
  ~Diary();

protected:
  // Disable constructor and copy operator
  Diary(){};
  Diary& operator=(const Diary& rhs);

public:
  // Creating Diary
  void newDiary(const QString &path);
  bool loadDiary(const QString &path);
  bool saveDiary(const QString &path);

  // Manipulating diary
  void addRecord(Record* rec);
  bool removeRecord(const Record* rec);
  void sort(const SortStyle);

  // checking content
  Record* contains(const Record* rec) const;
  QVector<Record*> getRecordsByDate(const QDate& date);
  QVector<Record*> getRecordsByDates(const QDate& startDate, const QDate& endDate);
  QVector<Record*> getRecords();
  int count();



private:
  QString m_path;
  QVector<Record*> m_records;
  QVector<Record*> m_deletedRecords;

};

#endif // DIARY_H
