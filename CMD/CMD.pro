TEMPLATE = app
CONFIG += console c++11

SOURCES += \
        main.cpp

LIBS += -L$$OUT_PWD/../stcore/ -lstcore
INCLUDEPATH += $$PWD/../stcore
DEPENDPATH += $$PWD/../stcore

LIBS += -L$$OUT_PWD/../stdata/ -lstdata
INCLUDEPATH += $$PWD/../stdata
DEPENDPATH += $$PWD/../stdata

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target


