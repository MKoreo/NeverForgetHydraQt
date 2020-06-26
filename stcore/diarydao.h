#ifndef DIARYDAO_H
#define DIARYDAO_H

#include <QString>

#include "record.h"
#include "xmlparser.h"

class DiaryDao
{
public:
  // Only one instance of the DiaryDao is required
  // So going for singleton design
  static DiaryDao& instance();
  ~DiaryDao();

private:
  // Disable constructor and copy operator
  DiaryDao(){};
  DiaryDao& operator=(const DiaryDao& rhs) = delete;

public:
  void read(const QString& path, QVector<Record*> &records);
  void write(const QString& path,  const QVector<Record*> &records);
};

#endif // DIARYDAO_H

