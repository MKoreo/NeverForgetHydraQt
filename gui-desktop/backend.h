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
    // Q_PROPERTY(double cpu READ getCpu WRITE setCpu NOTIFY cpuChanged)
    Q_PROPERTY(QString path READ getPath WRITE setPath);
    Q_PROPERTY(QString date READ getDate WRITE setDate NOTIFY DateChanged);
    Q_PROPERTY(QString costCenter WRITE setCostCenter NOTIFY costCenterChanged);
    Q_PROPERTY(QString project WRITE setProject NOTIFY projectChanged);
    Q_PROPERTY(QString subject WRITE setSubject NOTIFY subjectChanged);
    Q_PROPERTY(QString minutes WRITE setMinutes NOTIFY minutesChanged);

public:
    explicit BackEnd(QObject *parent = nullptr);

    QString getPath();
    void setPath(const QString &path);

    // Date
    void setDate(const QString &date);
    QString getDate();

        // Dropdown
    void setCostCenter(const QString &costCenter);
    void setProject(const QString &project);
    void setSubject(const QString &subject);
    void setMinutes(const QString &minutes);

signals:
    // Signals back to the GUI to update something
    void logChanged();

    void DateChanged();
    void costCenterChanged();
    void projectChanged();
    void subjectChanged();
    void minutesChanged();


public slots:
    // Functions that can be called
    void newDiary();
    void loadDiary();
    void openHydra();

    void addRecord();


private:
    QString m_path;

    QString m_date;
    QString m_costCenter;
    QString m_project;
    QString m_subject;
    QString m_minutes;
};

#endif // BACKEND_H
