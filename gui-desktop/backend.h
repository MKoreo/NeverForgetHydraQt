#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <sysinfo.h>

// Include datatypes
#include "diary.h"
#include "record.h"


class BackEnd : public QObject
{
  Q_OBJECT

  // Q_PROPERTY 's -> Create a variable that has getter & setter + emits signal when changed
  //Q_PROPERTY(double cpu READ getCpu WRITE setCpu NOTIFY cpuChanged)
  Q_PROPERTY(QString cpu READ getCpu NOTIFY cpuChanged)
  Q_PROPERTY(Diary log READ getLog NOTIFY logChanged)
public:
  explicit BackEnd(QObject *parent = nullptr);

  QString getCpu();
  //void setCpu(const double &userName);

signals:
  // Signals back to the GUI to update something
  void cpuChanged();

public slots:
  // Functions that can be called

private:
  QString m_cpu;
};

#endif // BACKEND_H
