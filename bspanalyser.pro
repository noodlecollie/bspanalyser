#-------------------------------------------------
#
# Project created by QtCreator 2017-12-23T20:38:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bspanalyser
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        src/main.cpp \
        src/widgets/mainwindow.cpp \
    src/widgets/hexdisplaywidget.cpp \
    src/widgets/mainwidget.cpp \
    src/commands/mainwindowcommands.cpp \
    src/widgets/bsplumpviewarea.cpp \
    src/model/bspfile.cpp

HEADERS += \
        src/widgets/mainwindow.h \
    src/widgets/hexdisplaywidget.h \
    src/widgets/mainwidget.h \
    src/commands/mainwindowcommands.h \
    src/widgets/bsplumpviewarea.h \
    src/model/bspfile.h

FORMS += \
        src/widgets/mainwindow.ui \
    src/widgets/bsplumpviewarea.ui

RESOURCES += \
    resources/resources.qrc

INCLUDEPATH += \
    src
