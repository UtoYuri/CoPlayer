#-------------------------------------------------
#
# Project created by QtCreator 2016-10-04T16:29:53
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TeamShare_Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    server.cpp \
    usersocket.cpp

HEADERS  += mainwindow.h \
    server.h \
    usersocket.h \
    user.h

FORMS    += mainwindow.ui
