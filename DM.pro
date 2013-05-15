#-------------------------------------------------
#
# Project created by QtCreator 2013-04-29T17:49:01
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = DM
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    sender.cpp \
    datasaver.cpp \
    receiver.cpp \
    partscontroller.cpp \
    speedcounter.cpp \
    estimatedtimecounter.cpp \
    download.cpp

HEADERS += \
    sender.h \
    datasaver.h \
    receiver.h \
    partscontroller.h \
    speedcounter.h \
    estimatedtimecounter.h \
    downloadinterface.h \
    download.h \
    receiverinterface.h
