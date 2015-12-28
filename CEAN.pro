TEMPLATE = app

CONFIG += c++14

QT += qml quick widgets

SOURCES += main.cpp \
    board.cpp \
    evo.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    board.h \
    evo.h

