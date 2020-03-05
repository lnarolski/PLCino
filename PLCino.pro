#-------------------------------------------------
#
# Project created by QtCreator 2017-08-02T12:27:50
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PLCino
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        plcino.cpp \
    elementy_drabinki.cpp \
    uzywane_zmienne.cpp \
    dodawanie_zmiennej.cpp \
    model_uzywane_zmienne.cpp \
    model_drabinka.cpp \
    wybor_portu.cpp \
    edycja_specjalna.cpp

HEADERS += \
        plcino.h \
    elementy_drabinki.h \
    typy_wyliczeniowe.h \
    uzywane_zmienne.h \
    dodawanie_zmiennej.h \
    model_uzywane_zmienne.h \
    model_drabinka.h \
    wybor_portu.h \
    zmienna_w_arduino.h \
    edycja_specjalna.h \
    elementy_schematu.h

FORMS += \
        plcino.ui \
    uzywane_zmienne.ui \
    dodawanie_zmiennej.ui \
    wybor_portu.ui

DISTFILES += \
    C:/Users/Łukasz/Box Sync/Inżynierka/Ikony/dodaj_kolumne.png \
    C:/Users/Łukasz/Box Sync/Inżynierka/Ikony/dodaj_wiersz.png \
    C:/Users/Łukasz/Box Sync/Inżynierka/Ikony/nowa_linia.png \
    C:/Users/Łukasz/Box Sync/Inżynierka/Ikony/rsz_dodaj_wiersz.png \
    C:/Users/Łukasz/Box Sync/Inżynierka/Ikony/usun_kolumne.png \
    C:/Users/Łukasz/Box Sync/Inżynierka/Ikony/usun_linie.png \
    C:/Users/Łukasz/Box Sync/Inżynierka/Ikony/usun_wiersz.png

RESOURCES += \
    zasoby.qrc
