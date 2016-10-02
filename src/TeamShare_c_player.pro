#-------------------------------------------------
#
# Project created by QtCreator 2016-10-02T11:31:08
#
#-------------------------------------------------

QT       += core gui webenginewidgets network multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TeamShare_c_player
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp \
    videowidget.cpp \
    progressbar.cpp

HEADERS  += mainwindow.h \
    player.h \
    videowidget.h \
    progressbar.h

FORMS    += mainwindow.ui \
    player.ui
