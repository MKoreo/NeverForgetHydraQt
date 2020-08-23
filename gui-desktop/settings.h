#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include "stcore.h"
#include "notifier.h"

enum ThemeSetting {
    Light = 0,
    Dark
};

enum ColourSetting {
    Red = 0,
    Green,
    Blue
};

class Settings : public QObject
{
    Q_OBJECT

    // QuickSettings
    Q_PROPERTY(int timer READ timer WRITE setTimer NOTIFY s_timerChanged);
    Q_PROPERTY(bool minimizeOnAdd READ minimizeOnAdd WRITE setMinimizeOnAdd);
    Q_PROPERTY(bool filterDropdown READ filterDropdown WRITE setFilterDropDown NOTIFY s_filterDropdownChanged);
    Q_PROPERTY(int filterType READ filterType WRITE setFilterType);

    // Global settings
    Q_PROPERTY(int historyTicks READ historyTicks WRITE setHistoryTicks NOTIFY s_historyTicksChanged);
    Q_PROPERTY(bool startWithOs READ startWithOs WRITE setStartWithOs NOTIFY s_startWithOsChanged);
    Q_PROPERTY(bool sendStacktrace READ sendStacktrace WRITE setSendStacktrace);
    Q_PROPERTY(int theme READ theme WRITE setTheme NOTIFY s_themeChanged);
    Q_PROPERTY(int colour READ colour WRITE setColour NOTIFY s_colourChanged);

    // Record View settings

    // Statistics View settings
public:
    explicit Settings(QObject *parent = nullptr);
     ~Settings();
    // Getters
    int timer() const;
    bool minimizeOnAdd() const;
    bool filterDropdown() const;
    int filterType() const;

    int historyTicks() const;
    bool startWithOs() const;
    bool sendStacktrace() const;

    int theme() const;
    int colour() const;

    // Setters
    void setTimer(const int timer);
    void setMinimizeOnAdd(const bool check);
    void setFilterDropDown(const bool check);
    void setFilterType(const int type);

    void setHistoryTicks(const int ticks);
    void setStartWithOs(const bool check);
    void setSendStacktrace(const bool check);

    void setTheme(int& theme);
    void setColour(int& colour);

private:
    void loadSettings();
    void writeSettings();

signals:
    void s_timerChanged();
    void s_timerReset();
    void s_filterDropdownChanged();
    void s_filterTypeChanged();
    void s_historyTicksChanged();
    void s_startWithOsChanged();
    void s_themeChanged();
    void s_colourChanged();

    // No signal for:
    // minimizeOnAdd -> Setting directly used
    // sendStackTrace -> Setting directly used

private slots:
    void timerReset();
    void timerChanged();
    void filterDropdownChanged();
    void filterTypeChanged();
    void historyTicksChanged();
    void startWithOsChanged();

private:
    int m_timer;
    bool m_minimizeOnAdd;
    bool m_filterDropdown;
    int m_filterType;

    int m_historyTicks;
    bool m_startWithOs;
    bool m_sendStacktrace;

    ThemeSetting m_theme;
    ColourSetting m_colour;
};

#endif // SETTINGS_H
