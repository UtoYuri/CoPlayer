#-------------------------------------------------
#
# Project created by QtCreator 2016-11-03T15:28:46
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = player
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    videocontroller.cpp \
    progressbar.cpp \
    videoplayer.cpp \
    videowidget.cpp

HEADERS  += mainwindow.h \
    videocontroller.h \
    progressbar.h \
    videoplayer.h \
    videowidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    image/image.qrc \
    qss/qss.qrc
