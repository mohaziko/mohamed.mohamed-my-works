QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += qt testlib
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QT += core gui testlib

# Projektinformationen
TEMPLATE = app
TARGET = 06-08_unit_test

SOURCES += \
    adresse.cpp \
    main.cpp \
    mainwindow.cpp \
    myort.cpp \
    ort.cpp \
    poi.cpp \
    test.cpp

HEADERS += \
    adresse.h \
    mainwindow.h \
    myort.h \
    ort.h \
    poi.h \
    test.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Map_Germany.qrc
