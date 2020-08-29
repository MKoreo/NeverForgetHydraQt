#include "settings.h"
#include <QDebug>
#include <QFile>
Settings::Settings(QObject *parent) : QObject(parent)
{
    // Attempt to load settings.ini
    if (QFile::exists("./settings.ini")) {
        qDebug() << "DEBUG: Settings.ini found";
        loadSettings();

    } else {
        qDebug() << "DEBUG: Settings.ini not found";
        qDebug() << "DEBUG: Restoring default settings";

        m_timer = 30;
        m_minimizeOnAdd = 1;
        m_filterDropdown = 1;
        m_filterType = 1;
        m_historyTicks = 5;
        m_startWithOs = 0;
        m_sendStacktrace = 1;
        m_theme = ThemeSetting::Light;
        m_colour = ColourSetting::Red;

        writeSettings();
    }

    // Connect signals from setting that can change
    connect(this,     &Settings::s_timerChanged,          this, &Settings::timerChanged);
    connect(this,     &Settings::s_timerReset,            this, &Settings::timerReset);
    connect(this,     &Settings::s_filterTypeChanged,     this, &Settings::filterTypeChanged);
    connect(this,     &Settings::s_filterDropdownChanged, this, &Settings::filterDropdownChanged);
    connect(this,     &Settings::s_historyTicksChanged,   this, &Settings::historyTicksChanged);
    connect(this,     &Settings::s_startWithOsChanged,    this, &Settings::startWithOsChanged);

    //emit s_themeChanged();
    //emit s_colourChanged();
}

Settings::~Settings(){
        writeSettings();
}

void Settings::loadSettings(){
    QVector<QVector<QString>> settings = StCore::instance().loadSettings();


    m_timer = settings[0][1].toInt();
    m_minimizeOnAdd = settings[1][1].toInt();
    m_filterDropdown = settings[2][1].toInt();
    m_filterType = settings[3][1].toInt();
    m_historyTicks = settings[4][1].toInt();
    m_startWithOs = settings[5][1].toInt();
    m_sendStacktrace = settings[6][1].toInt();
    m_theme = (ThemeSetting)(settings[7][1].toInt());
    m_colour = (ColourSetting)(settings[8][1].toInt());
    emit s_themeChanged();
    emit s_colourChanged();
}

void Settings::writeSettings(){
    QVector<QVector<QString>> settings;

    QVector<QString> setting;
    setting.append("timer");
    setting.append(QString::number(m_timer));
    settings.append(setting);
    setting.clear();
    setting.append("minimizeOnAdd");
    setting.append(QString::number(m_minimizeOnAdd));
    settings.append(setting);
    setting.clear();
    setting.append("filterDropdown");
    setting.append(QString::number(m_filterDropdown));
    settings.append(setting);
    setting.clear();
    setting.append("filterType");
    setting.append(QString::number(m_filterType));
    settings.append(setting);
    setting.clear();

    setting.append("historyTicks");
    setting.append(QString::number(m_historyTicks));
    settings.append(setting);
    setting.clear();
    setting.append("startWithOs");
    setting.append(QString::number(m_startWithOs));
    settings.append(setting);
    setting.clear();
    setting.append("sendStacktrace");
    setting.append(QString::number(m_sendStacktrace));
    settings.append(setting);
    setting.clear();
    setting.append("theme");
    setting.append(QString::number(m_theme));
    settings.append(setting);
    setting.clear();
    setting.append("colour");
    setting.append(QString::number(m_colour));
    settings.append(setting);
    setting.clear();

    StCore::instance().writeSettings(settings);
}


// Getters
int Settings::timer() const{
    return m_timer;
}

bool  Settings::minimizeOnAdd() const{
    return m_minimizeOnAdd;
}

bool Settings::filterDropdown() const{
    return m_filterDropdown;
}

int Settings::filterType() const{
    return m_filterType;
}

int Settings::historyTicks() const {
    return m_historyTicks;
}

bool Settings::startWithOs() const{
    return m_startWithOs;
}

bool Settings::sendStacktrace()const{
    return m_sendStacktrace;
}

int Settings::colour() const{
    return (int)m_colour;
}

int Settings::theme() const{
    return m_theme;
}

// Setters
void Settings::setTimer(const int timer){
    qDebug() << "setTimer value from " <<  QString::number(m_timer) << " to " << QString::number(timer);
    m_timer = timer;
    emit s_timerChanged();
}

void Settings::setFilterDropDown(bool check){
    qDebug() << "setFilterDropDown value from " <<  QString::number(m_filterDropdown) << " to " << QString::number(check);
    m_filterDropdown = check;
    emit s_filterDropdownChanged();
}

void Settings::setFilterType(int type){
    qDebug() << "setFilterType value from " <<  QString::number(m_filterType) << " to " << QString::number(type);

    // Check QuickSettings.qml to match model options
    m_filterType = type;

    emit s_filterTypeChanged();
}

void Settings::setHistoryTicks(int ticks){
    qDebug() << "setHistoryTicks value from " <<  QString::number(m_historyTicks) << " to " << QString::number(ticks);

    m_historyTicks = ticks;
    emit s_historyTicksChanged();
}

void Settings::setStartWithOs(bool check){
    qDebug() << "setStartWithOs value from " <<  QString::number(m_startWithOs) << " to " << QString::number(check);

    m_startWithOs = check;
    emit s_startWithOsChanged();
}

void Settings::setSendStacktrace(bool check){
    qDebug() << "setSendStacktrace value from " <<  QString::number(m_sendStacktrace) << " to " << QString::number(check);

    m_sendStacktrace = check;
}

void Settings::setMinimizeOnAdd(bool check){
    qDebug() << "setMinimizeOnAdd value from " <<  QString::number(m_minimizeOnAdd) << " to " << QString::number(check);
    m_minimizeOnAdd = check;
}

void Settings::setTheme(int& theme){
    m_theme = (ThemeSetting)theme;
    emit s_themeChanged();
}

void Settings::setColour(int& colour){
    m_colour = (ColourSetting)colour;
    emit s_colourChanged();
}

// slots
void Settings::timerReset(){

}
void Settings::timerChanged(){
}

void Settings::filterDropdownChanged(){

}
void Settings::filterTypeChanged(){

}
void Settings::historyTicksChanged(){

}

void Settings::startWithOsChanged(){
    if(m_startWithOs){
        SystemFunct::instance().enableStartup();
    } else {
        SystemFunct::instance().disableStartup();
    }
}
