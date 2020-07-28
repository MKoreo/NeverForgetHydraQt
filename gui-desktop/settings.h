#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include "stcore.h"

class Settings : public QObject
{
    Q_OBJECT

    // QuickSettings
    Q_PROPERTY(int timer READ timer WRITE setTimer NOTIFY dummyChanged);
    Q_PROPERTY(bool minimizeOnAdd READ minimizeOnAdd WRITE setMinimizeOnAdd NOTIFY dummyChanged);
    Q_PROPERTY(bool filterDropdown READ filterDropdown WRITE setTimer NOTIFY dummyChanged);
    Q_PROPERTY(int filterType READ filterType WRITE setFilterType NOTIFY dummyChanged);

    // Global settings
    Q_PROPERTY(int historyTicks READ historyTicks WRITE setHistoryTicks NOTIFY dummyChanged);
    Q_PROPERTY(bool startWithOs READ startWithOs WRITE setStartWithOs NOTIFY dummyChanged);
    Q_PROPERTY(bool sendStacktrace READ sendStacktrace WRITE setSendStacktrace NOTIFY dummyChanged);

    // Record View settings

    // Statistics View settings
public:
    explicit Settings(QObject *parent = nullptr);



    // Getters
    int timer() const;
    bool minimizeOnAdd() const;
    bool filterDropdown() const;
    int filterType() const;

    int historyTicks() const;
    bool startWithOs() const;
    bool sendStacktrace() const;

    // Setters
    void setTimer(const int timer);
    void setMinimizeOnAdd(const bool check);
    void setFilterDropDown(const bool check);
    void setFilterType(const int type);

    void setHistoryTicks(const int ticks);
    void setStartWithOs(const bool check);
    void setSendStacktrace(const bool check);

private:
    void loadSettings();
    void writeSettings();

signals:
    void dummyChanged();

private:
    int m_timer;
    bool m_minimizeOnAdd;
    bool m_filterDropdown;
    int m_filterType;

    int m_historyTicks;
    bool m_startWithOs;
    bool m_sendStacktrace;
};

#endif // SETTINGS_H
