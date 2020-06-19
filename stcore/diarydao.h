#ifndef DIARYDAO_H
#define DIARYDAO_H

#include "record.h"
#include <QString>
#include <xmlparser.h>

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
  QVector<Record*>* read(const QString& path);
  void write(const QString& path);
};

#endif // DIARYDAO_H

