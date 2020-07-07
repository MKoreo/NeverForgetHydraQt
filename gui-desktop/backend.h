#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>

// Include datatypes
#include "diary.h"
#include "record.h"

// Open Url
#include <QDesktopServices>
#include <QUrl>

class BackEnd : public QObject
{
    Q_OBJECT

    // Q_PROPERTY 's -> Create a variable that has getter & setter + emits signal when changed
    // Q_PROPERTY(double cpu READ getCpu WRITE setCpu NOTIFY cpuChanged)
    Q_PROPERTY(QString path READ getPath WRITE setPath);
    Q_PROPERTY(QString date WRITE setDate NOTIFY DateChanged);
    Q_PROPERTY(QString costCenter WRITE setCostCenter NOTIFY costCenterChanged);
    Q_PROPERTY(QString project WRITE setProject NOTIFY projectChanged);
    Q_PROPERTY(QString subject WRITE setSubject NOTIFY subjectChanged);
    Q_PROPERTY(QString minutes WRITE setMinutes NOTIFY minutesChanged);

public:
    explicit BackEnd(QObject *parent = nullptr);

    // Current working path -> QProperty
    QString getPath();
    void setPath(const QString &path);

    // Currently selected Date -> QProperty
    void setDate(const QString &date);

    // Currently selected dropdowns -> QProperty
    void setCostCenter(const QString &costCenter);
    void setProject(const QString &project);
    void setSubject(const QString &subject);
    void setMinutes(const QString &minutes);

signals:    // Signals back to the GUI to update something

    // QProperty's -> handle date, minutes + comboboxes
    void DateChanged();
    void costCenterChanged();
    void projectChanged();
    void subjectChanged();
    void minutesChanged();

public slots:
    // Functions that can be called from QML & connected to signals

    // Basically want to have acces to all Diary functions
    void newDiary(QString path);    // Menuitem
    void loadDiary();               // Menuitem
    void saveDiary();               // Menuitem

    // Open webpage
    void openHydra();               // Menuitem

    // Method to set current selected date to today()
    void setCurrentDate();

    // Method to add a record.
    void addRecord();               // Addbutton

private:
    // Validate if contents of m_ vars needed to create record are valid
    bool validateMembers();

    // Store current working path
    QString m_path;

    // Vars needed to create a record
    QString m_date;
    QString m_costCenter;
    QString m_project;
    QString m_subject;
    QString m_minutes;
};

#endif // BACKEND_H
