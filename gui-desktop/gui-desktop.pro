TARGET = NeverForgetHydraQt
QT += widgets quick qml quickcontrols2

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        backend.cpp \
        comboBoxNamesModel.cpp \
        datagridViewModel.cpp \
        main.cpp \
        notifier.cpp \
        settings.cpp

RESOURCES += \
    qml.qrc


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =


HEADERS += \
    backend.h \
    comboBoxNamesModel.h \
    datagridViewModel.h \
    notifier.h \
    settings.h



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

INCLUDEPATH += $$PWD/../stdata
DEPENDPATH += $$PWD/../stdata

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../stdata/release/libstdata.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../stdata/debug/libstdata.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../stdata/release/stdata.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../stdata/debug/stdata.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../stdata/libstdata.a


