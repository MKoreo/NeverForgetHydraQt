#include "backend.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
}

QString BackEnd::getCpu()
{
    SysInfo::instance().init();
    struct timespec ts = { 1000 / 1000, (1000 % 1000) * 1000 * 1000 };
        nanosleep(&ts, NULL);
    m_cpu = QString::number(SysInfo::instance().cpuLoadAverage());
    return m_cpu;
}

//void BackEnd::setUserName(const QString &userName)
//{
//    if (userName == m_userName)
//        return;

//    m_userName = userName;
//    emit userNameChanged();
//}
