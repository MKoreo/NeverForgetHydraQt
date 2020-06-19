TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    gui-desktop \
    CMD \
    stdata \
    stcore

CMD.depends = stcore
stcore.depends = stdata
