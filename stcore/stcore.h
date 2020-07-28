#ifndef STCORE_H
#define STCORE_H

#include <QString>
#include <QVector>

class StCore
{
public:
    // Only one instance of the StCore is required
    // So going for singleton design
  static StCore& instance();
  ~StCore();

private:
  // Disable constructor and copy operator
  StCore(){};
  StCore& operator=(const StCore& rhs) = delete;

public:
  QVector<QVector<QString>> loadSettings();
  void writeSettings(QVector<QVector<QString>> input);
};

#endif // STCORE_H
