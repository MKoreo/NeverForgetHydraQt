TEMPLATE = app
CONFIG += console c++11
QT -= gui
SOURCES += \
        main.cpp



INCLUDEPATH += $$PWD/../stdata
DEPENDPATH += $$PWD/../stdata

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../stdata/release/libstdata.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../stdata/debug/libstdata.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../stdata/release/stdata.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../stdata/debug/stdata.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../stdata/libstdata.a
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../stcore/release/ -lstcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../stcore/debug/ -lstcore
else:unix: LIBS += -L$$OUT_PWD/../stcore/ -lstcore

INCLUDEPATH += $$PWD/../stcore
DEPENDPATH += $$PWD/../stcore

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../stcore/release/libstcore.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../stcore/debug/libstcore.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../stcore/release/stcore.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../stcore/debug/stcore.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../stcore/libstcore.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../stdata/release/ -lstdata
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../stdata/debug/ -lstdata
else:unix: LIBS += -L$$OUT_PWD/../stdata/ -lstdata
