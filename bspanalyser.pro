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
    src/bsp/bsplumpdef.cpp \
    src/bsp/bspdatafragment.cpp \
    src/model/bspfilemodel.cpp \
    src/configs/bspformatreader.cpp \
    src/bsp/bspfilestructure.cpp \
    src/configs/jsonreaderutil.cpp \
    src/model/applicationmodel.cpp \
    src/configs/bspformatcollection.cpp \
    src/widgets/bsplumpviewarea.cpp \
    src/bsp/keyvaluesjsonconverter.cpp \
    src/configs/jsonreaderitem.cpp \
    src/widgets/lumpviewfactory.cpp \
    src/widgets/keyvalueslumpviewwidget.cpp \
    src/util/textutil.cpp \
    src/widgets/visibilitylumpviewwidget.cpp \
    src/bsp/viscompressor.cpp \
    src/bsp/visibilitylumpdef.cpp \
    src/bsp/structlumpdef.cpp \
    src/configs/abstractlumpconfigreader.cpp \
    src/configs/visibilitylumpconfigreader.cpp \
    src/configs/keyvalueslumpconfigreader.cpp \
    src/configs/structlumpconfigreader.cpp \
    src/bsp/struct/bspstructitem.cpp \
    src/bsp/struct/bspstruct.cpp \
    src/bsp/struct/bspstructitem_integer.cpp \
    src/bsp/struct/bspstructitem_float.cpp \
    src/bsp/struct/bspstructitem_string.cpp

HEADERS += \
        src/widgets/mainwindow.h \
    src/widgets/hexdisplaywidget.h \
    src/widgets/mainwidget.h \
    src/commands/mainwindowcommands.h \
    src/bsp/bsplumpdef.h \
    src/bsp/ibspdataitem.h \
    src/bsp/bspdatafragment.h \
    src/model/bspfilemodel.h \
    src/bsp/bspdefs.h \
    src/configs/bspformatreader.h \
    src/bsp/bspfilestructure.h \
    src/configs/jsonreaderutil.h \
    src/model/applicationmodel.h \
    src/configs/bspformatcollection.h \
    src/exceptions/genericexception.h \
    src/widgets/bsplumpviewarea.h \
    src/bsp/keyvaluesjsonconverter.h \
    src/util/enumnamemap.h \
    src/configs/jsonreaderexception.h \
    src/configs/jsonreaderitem.h \
    src/widgets/lumpviewfactory.h \
    src/widgets/ilumpviewwidget.h \
    src/widgets/keyvalueslumpviewwidget.h \
    src/util/textutil.h \
    src/widgets/visibilitylumpviewwidget.h \
    src/bsp/viscompressor.h \
    src/bsp/visibilitylumpdef.h \
    src/bsp/structlumpdef.h \
    src/exceptions/enumvaluenotfoundexception.h \
    src/configs/abstractlumpconfigreader.h \
    src/configs/visibilitylumpconfigreader.h \
    src/configs/keyvalueslumpconfigreader.h \
    src/configs/structlumpconfigreader.h \
    src/bsp/struct/bspstructitem.h \
    src/bsp/struct/bspstruct.h \
    src/bsp/struct/bspstructitem_integer.h \
    src/bsp/struct/bspstructitem_float.h \
    src/bsp/struct/bspstructitem_string.h

FORMS += \
        src/widgets/mainwindow.ui \
    src/widgets/visibilitylumpviewwidget.ui

RESOURCES += \
    resources/resources.qrc

INCLUDEPATH += \
    src
