#-------------------------------------------------
#
# Project created by QtCreator 2016-10-05T17:10:38
#
#-------------------------------------------------

QT       += core gui network multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TeamShare_Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp \
    progressbar.cpp \
    videowidget.cpp

HEADERS  += mainwindow.h \
    player.h \
    progressbar.h \
    videowidget.h

FORMS    += mainwindow.ui \
    player.ui
