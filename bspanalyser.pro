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
    src/util/textutil.cpp \
    src/bsp/viscompressor.cpp \
    src/bsp/visibilitylumpdef.cpp \
    src/bsp/structlumpdef.cpp \
    src/configs/abstractlumpconfigreader.cpp \
    src/configs/visibilitylumpconfigreader.cpp \
    src/configs/keyvalueslumpconfigreader.cpp \
    src/configs/structlumpconfigreader.cpp \
    src/bsp/struct/bspstruct.cpp \
    src/bsp/struct/bspstructitemtypes.cpp \
    src/bsp/struct/bspstructgenericblock.cpp \
    src/bsp/struct/bspstructitemtypeconverter.cpp \
    src/bsp/struct/bspstructitemtypeconverter_integer.cpp \
    src/bsp/struct/bspstructitemtypeconverter_float.cpp \
    src/bsp/struct/bspstructitemtypeconverter_fvector.cpp \
    src/bsp/struct/bspstructitemtypeconverter_rgb8.cpp \
    src/bsp/axiallyalignedboundingbox.cpp \
    src/bsp/struct/bspstructitemtypeconverterfactory.cpp \
    src/configs/structmembers/structmemberconfigreader.cpp \
    src/configs/structmembers/structmemberconfigreaderfactory.cpp \
    src/configs/structmembers/structmemberconfigreader_integer.cpp \
    src/configs/structmembers/structmemberconfigreader_simple.cpp \
    src/bsp/struct/bspstructitemattributes.cpp \
    src/bsp/struct/bspstructitemtypeconverter_string.cpp \
    src/widgets/structlumpviewwidget.cpp \
    src/widgets/infodisplaygroupbox.cpp \
    src/widgets/keyvaluesview.cpp \
    src/widgets/keyvalueslumpviewwidget.cpp \
    src/widgets/displaystringconversion.cpp \
    src/widgets/notimplementedplaceholderwidget.cpp \
    src/widgets/visibilitylumpviewwidget.cpp \
    src/configs/embeddedtexturesconfigreader.cpp \
    src/widgets/valuesearchwidget.cpp

HEADERS += \
        src/widgets/mainwindow.h \
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
    src/util/textutil.h \
    src/bsp/viscompressor.h \
    src/bsp/visibilitylumpdef.h \
    src/bsp/structlumpdef.h \
    src/exceptions/enumvaluenotfoundexception.h \
    src/configs/abstractlumpconfigreader.h \
    src/configs/visibilitylumpconfigreader.h \
    src/configs/keyvalueslumpconfigreader.h \
    src/configs/structlumpconfigreader.h \
    src/bsp/struct/bspstruct.h \
    src/bsp/struct/bspstructitemtypes.h \
    src/bsp/struct/bspstructgenericblock.h \
    src/exceptions/bspstructexceptions.h \
    src/bsp/struct/bspstructitemtypeconverter.h \
    src/bsp/struct/bspstructitemtypeconverter_integer.h \
    src/bsp/struct/bspstructitemtypeconverter_float.h \
    src/bsp/struct/bspstructitemtypeconverter_fvector.h \
    src/bsp/struct/bspstructitemtypeconverter_rgb8.h \
    src/bsp/axiallyalignedboundingbox.h \
    src/bsp/struct/bspstructitemtypeconverterfactory.h \
    src/configs/structmembers/structmemberconfigreader.h \
    src/configs/structmembers/structmemberconfigreaderfactory.h \
    src/configs/structmembers/structmemberconfigreader_integer.h \
    src/configs/structmembers/structmemberconfigreader_simple.h \
    src/bsp/struct/bspstructitemattributes.h \
    src/bsp/struct/bspstructitemtypeconverter_string.h \
    src/widgets/structlumpviewwidget.h \
    src/widgets/infodisplaygroupbox.h \
    src/widgets/keyvaluesview.h \
    src/widgets/keyvalueslumpviewwidget.h \
    src/widgets/displaystringconversion.h \
    src/widgets/notimplementedplaceholderwidget.h \
    src/widgets/visibilitylumpviewwidget.h \
    src/configs/embeddedtexturesconfigreader.h \
    src/widgets/valuesearchwidget.h

FORMS += \
        src/widgets/mainwindow.ui \
    src/widgets/visibilitylumpviewwidget.ui \
    src/widgets/structlumpviewwidget.ui \
    src/widgets/keyvalueslumpviewwidget.ui \
    src/widgets/notimplementedplaceholderwidget.ui \
    src/widgets/valuesearchwidget.ui

RESOURCES += \
    resources/resources.qrc

INCLUDEPATH += \
    src
