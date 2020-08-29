#include "systemfunct.h"
#include <QtGlobal>

#ifdef Q_OS_WIN
  #include "systemfunctwindows.h"
#elif defined(Q_OS_LINUX)
  #include "systemfunctlinux.h"
#endif

SystemFunct& SystemFunct::instance(){
#ifdef Q_OS_WIN
  static SystemFunctWindows singleton;
#elif defined(Q_OS_LINUX)
  static SystemFunctLinux singleton;
#endif

  return singleton;
}

SystemFunct::SystemFunct()
{

}

SystemFunct::~SystemFunct()
{

}
