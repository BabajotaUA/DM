#-------------------------------------------------
#
# Project created by QtCreator 2013-05-10T12:39:54
#
#-------------------------------------------------

QT       += testlib network core

TARGET = UnitTest

SOURCES += \
    testdownload.cpp \
    test.cpp \
    ../download.cpp \
    ../speedcounter.cpp \
    ../sender.cpp \
    ../partscontroller.cpp \
    ../estimatedtimecounter.cpp \
    receivermock.cpp \
    datasavermock.cpp

HEADERS += \
    testdownload.h \
    ../download.h \
    ../speedcounter.h \
    ../sender.h \
    ../receiverinterface.h \
    ../partscontroller.h \
    ../estimatedtimecounter.h \
    ../downloadinterface.h \
    receivermock.h \
    datasavermock.h \
    ../datasaverinterface.h
