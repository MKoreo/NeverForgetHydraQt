#ifndef SYSTEMFUNCTLINUX_H
#define SYSTEMFUNCTLINUX_H

#include "systemfunct.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>

class SystemFunctLinux : public SystemFunct
{
public:
    SystemFunctLinux();

    // Systemfunct interface
    bool enableStartup();
    bool disableStartup();
    bool checkStartup();

private:
    QFile *desktop = new QFile("/home/thomas/.config/autostart/NeverForgetHydraQt.desktop");
};

#endif // SYSTEMFUNCTLINUX_H
