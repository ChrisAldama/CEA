TEMPLATE = app

CONFIG += c++11

QT += qml quick widgets

SOURCES += main.cpp \
    board.cpp \
    evo.cpp \
    stimuli.cpp \
    model.cpp \
    graphics.cpp \
    iprovider.cpp \
    controller.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    board.h \
    evo.h \
    stimuli.h \
    vector.h \
    sigmoid.h \
    model.h \
    graphics.h \
    iprovider.h \
    controller.h

DISTFILES += \
    or.json \
    and.json \
    xor.json


