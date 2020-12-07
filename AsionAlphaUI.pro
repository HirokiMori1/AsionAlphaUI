#-------------------------------------------------
#
# Project created by QtCreator 2020-10-24T21:02:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AsionAlphaUI
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
        main.cpp \
        mainwindow.cpp \
    Thumbnail.cpp \
    Singleton.cpp \
    YamlReader.cpp \
    ProcessingFileUtil.cpp \
    waitmessagedialog.cpp \
    aboutdialog.cpp \
    license.cpp

HEADERS += \
        mainwindow.h \
    Define.h \
    Thumbnail.h \
    Singleton.h \
    YamlReader.h \
    ProcessingFileUtil.h \
    waitmessagedialog.h \
    aboutdialog.h \
    license.h

FORMS += \
        mainwindow.ui \
    Thumbnail.ui \
    waitmessagedialog.ui \
    aboutdialog.ui \
    licensedialog.ui

unix:!macx: LIBS += -L$$PWD/../../../usr/lib/x86_64-linux-gnu/ -lyaml-cpp

INCLUDEPATH += $$PWD/../../../usr/lib/x86_64-linux-gnu
DEPENDPATH += $$PWD/../../../usr/lib/x86_64-linux-gnu
