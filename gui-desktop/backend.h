#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>

// Include datatypes
#include "diary.h"
#include "record.h"
#include "comboBoxNamesModel.h"
#include "settings.h"

// Open Url
#include <QDesktopServices>
#include <QUrl>

class BackEnd : public QObject
{
    Q_OBJECT

    // Q_PROPERTY 's -> Create a variable that has getter & setter + emits signal when changed
    Q_PROPERTY(QString path READ getPath WRITE setPath);
    Q_PROPERTY(QString date READ getDate WRITE setDate NOTIFY DateChanged);
    Q_PROPERTY(QString costCenter WRITE setCostCenter NOTIFY costCenterChanged);
    Q_PROPERTY(QString project WRITE setProject NOTIFY projectChanged);
    Q_PROPERTY(QString subject WRITE setSubject NOTIFY subjectChanged);
    Q_PROPERTY(QString minutes WRITE setMinutes NOTIFY minutesChanged);

public:
    // If method 1 connection used, this must be explicit
    BackEnd(QObject *parent, Settings *settings);

    // Current working path -> QProperty
    QString getPath() const;
    void setPath(const QString path);

    // Currently selected Date -> QProperty
    void setDate(const QString date);
    QString getDate() const;

    // Currently selected dropdowns -> QProperty
    void setCostCenter(const QString costCenter);
    void setProject(const QString project);
    void setSubject(const QString subject);
    void setMinutes(const QString minutes);

signals:    // Signals back to the GUI to update something

    // QProperty's -> handle date, minutes + comboboxes
    void DateChanged();
    void costCenterChanged();
    void projectChanged();
    void subjectChanged();
    void minutesChanged();
    void requestNotification(QString m_title, QString m_content, bool m_important, bool m_critical) const;

public slots:
    // Functions that can be called from QML & connected to signals

    // Basically want to have acces to all Diary functions
    void newDiary(QString path);    // Menuitem
    void loadDiary();               // Menuitem
    void saveDiary();               // Menuitem

    // Open webpage
    void openHydra() const;               // Menuitem

    // Method to set current selected date to today()
    void setCurrentDate();

    // Method to add a record.
    void addRecord();               // Addbutton

    // Change date with scrollwheel
    void increaseDate(const int &type);
    void decreaseDate(const int &type);

private:
    // Validate if contents of m_ vars needed to create record are valid
    bool validateMembers() const;

    // Store current working path
    QString m_path;

    // Vars needed to create a record
    QString m_date;
    QString m_costCenter;
    QString m_project;
    QString m_subject;
    QString m_minutes;

    // Settings
    Settings *m_settings;


};

#endif // BACKEND_H
