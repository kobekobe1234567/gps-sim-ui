
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gps-sim
TEMPLATE = app

win32{
QMAKE_CXXFLAGS += /utf-8
CONFIG += console
}

TRANSLATIONS += english.ts

SOURCES += gpssim.cpp\
    main.cpp \
    mainwindow.cpp \
    uhd_radio_interface.cpp

HEADERS  += gpssim.h \
    radio_thread.h \
    mainwindow.h \
    gpssim_thread.h

win32{
LIBS += -luhd -llibboost_system-vc141-mt-x64-1_72 -L"C:/Program Files/UHD/lib" -LC:/Boost/lib

INCLUDEPATH += "C:/Program Files/UHD/include"
INCLUDEPATH += "C:/Boost/include/boost-1_72"
TR_EXCLUDE += "C:/Boost/include/boost-1_72/*"
}

unix{
LIBS += -lm -luhd -lboost_system
}

FORMS += \
    mainwindow.ui
