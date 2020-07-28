#include "settings.h"
#include <QDebug>
#include <QFile>

Settings::Settings(QObject *parent) : QObject(parent)
{
    // 1. Attempt to load settings.ini
    if (QFile::exists("./settings.ini")) {
        qDebug() << "settings.ini found, attempting to load...";
        loadSettings();
    } else {
        // 2. If no settings found, load defaults
        m_timer = 30;
        m_minimizeOnAdd = 1;
        m_filterDropdown = 1;
        m_filterType = 1;
        m_historyTicks = 5;
        m_startWithOs = 0;
        m_sendStacktrace = 1;
        // 3. Save to disk
        writeSettings();
    }
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

// Setters
void Settings::setTimer(const int timer){
    qDebug() << "setTimer value from " <<  QString::number(m_timer) << " to " << QString::number(timer);
    m_timer = timer;

}

void Settings::setMinimizeOnAdd(bool check){
    qDebug() << "setMinimizeOnAdd value from " <<  QString::number(m_minimizeOnAdd) << " to " << QString::number(check);
    m_minimizeOnAdd = check;
}

void Settings::setFilterDropDown(bool check){
    qDebug() << "setFilterDropDown value from " <<  QString::number(m_filterDropdown) << " to " << QString::number(check);
    m_filterDropdown = check;
}

void Settings::setFilterType(int type){
    qDebug() << "setFilterType value from " <<  QString::number(m_filterType) << " to " << QString::number(type);

    // Check QuickSettings.qml to match model options
    m_filterType = type;
}

void Settings::setHistoryTicks(int ticks){
    qDebug() << "setHistoryTicks value from " <<  QString::number(m_historyTicks) << " to " << QString::number(ticks);

    m_historyTicks = ticks;
}

void Settings::setStartWithOs(bool check){
    qDebug() << "setStartWithOs value from " <<  QString::number(m_startWithOs) << " to " << QString::number(check);

    m_startWithOs = check;
}

void Settings::setSendStacktrace(bool check){
    qDebug() << "setSendStacktrace value from " <<  QString::number(m_sendStacktrace) << " to " << QString::number(check);

    m_sendStacktrace = check;
}

