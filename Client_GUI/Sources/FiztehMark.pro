#-------------------------------------------------
#
# Project created by QtCreator 2012-03-01T23:19:40
#
#-------------------------------------------------

QT       += core gui

TARGET = FiztehMark
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Tests/MemCpyTest/memCpyTest.cpp \
    Tests/testHandler.cpp \
    submitdialog.cpp

HEADERS  += mainwindow.h \
    Tests/MemCpyTest/memCpyTest.h \
    Tests/testHandler.h \
    submitdialog.h

FORMS    += mainwindow.ui \
    submitdialog.ui
