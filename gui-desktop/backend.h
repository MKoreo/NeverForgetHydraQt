#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <sysinfo.h>

class BackEnd : public QObject
{
  Q_OBJECT
  //Q_PROPERTY(double cpu READ getCpu WRITE setCpu NOTIFY cpuChanged)
  Q_PROPERTY(QString cpu READ getCpu NOTIFY cpuChanged)
public:
  explicit BackEnd(QObject *parent = nullptr);

  QString getCpu();
  //void setCpu(const double &userName);

signals:
  void cpuChanged();

private:
  QString m_cpu;
};

#endif // BACKEND_H
