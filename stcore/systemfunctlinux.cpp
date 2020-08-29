#include "systemfunctlinux.h"

SystemFunctLinux::SystemFunctLinux() : SystemFunct()
{

}

bool SystemFunctLinux::enableStartup(){
    if (!desktop->exists()){
        if (!desktop->open(QIODevice::WriteOnly | QIODevice::Text))
            return false;

        QTextStream output(desktop);
        output << "[Desktop Entry]" << "\n";
        output << "Name=NeverForgetHydraQt" << "\n";
        output << "Comment=Never Forget Hydra Professional Personal Time Archiver" << "\n";
        output << "Icon=" << QDir::currentPath() + "/hourglas.ico" << "\n";
        output << "Exec=" << QDir::currentPath() + "/NeverForgetHydraQt" << "\n";
        output << "Terminal=false" << "\n";
        output << "Type=Application" << "\n";
        output << "Categories=" << "\n";
        output << "NotShowIn=" << "\n";

        desktop->close();

        if(desktop->exists()){
            return true;
        } else {
            return false;
        }
    } else {
        return true;
    }
}

bool SystemFunctLinux::checkStartup(){
    return desktop->exists();
}

bool SystemFunctLinux::disableStartup(){
    if(desktop->exists()){
        return desktop->remove();
    } else {
        return true;
    }
}
