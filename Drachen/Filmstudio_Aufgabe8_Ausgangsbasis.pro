CONFIG += c++17
QT     += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    drache.cpp \
    drachenflug.cpp \
    drachenflugdialog.cpp \
    drachenreise.cpp \
    dragonmap.cpp \
    dragonpoilayer.cpp \
    filmstudio.cpp \
    kartenszene.cpp \
    main.cpp \
    mainwindow.cpp \
    nachtlager.cpp \
    nachtlagerdialog.cpp \
    poi.cpp \
    reiseplan.cpp \
    suchergebnisdialog.cpp

HEADERS += \
    drache.h \
    drachenart.h \
    drachenflug.h \
    drachenflugdialog.h \
    drachenreise.h \
    dragonmap.h \
    dragonpoilayer.h \
    filmstudio.h \
    kartenszene.h \
    mainwindow.h \
    json.hpp \
    poi.json\
    nachtlager.h \
    nachtlagerdialog.h \
    poi.h \
    reiseplan.h \
    suchergebnisdialog.h

FORMS += \
    drachenflugdialog.ui \
    mainwindow.ui \
    nachtlagerdialog.ui \
    suchergebnisdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    icons/_arrival.svg \
    icons/_arrival.svg \
    icons/_delete.svg \
    icons/_delete.svg \
    icons/_departure.svg \
    icons/_departure.svg \
    icons/_help.svg \
    icons/_help.svg \
    icons/baumkrone.svg \
    icons/beenden.svg \
    icons/beenden.svg \
    icons/bergplateau.svg \
    icons/drache.svg \
    icons/drache.svg \
    icons/drachenflug.svg \
    icons/drachenreise.svg \
    icons/drachenreise.svg \
    icons/draggonport.svg \
    icons/einlesen.svg \
    icons/einlesen.svg \
    icons/flug.svg \
    icons/hoehle.svg \
    icons/hoehle_.svg \
    icons/landkarte.svg \
    icons/nachtlager.svg \
    icons/passagier.svg \
    icons/passagier.svg \
    icons/poi.svg \
    icons/reiseplan.svg \
    icons/reiseplan.svg \
    icons/speichern.svg \
    icons/speichern.svg \
    icons/suchen.svg \
    icons/suchen.svg

RESOURCES += \
    icons.qrc





