TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bibliothek.cpp \
        buch.cpp \
        cd.cpp \
        hoerbuch.cpp \
        kunde.cpp \
        main.cpp \
        medien.cpp

HEADERS += \
    bibliothek.h \
    buch.h \
    cd.h \
    hoerbuch.h \
    kunde.h \
    medien.h
