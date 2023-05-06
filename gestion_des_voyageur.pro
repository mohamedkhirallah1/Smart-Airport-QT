#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql network multimedia multimediawidgets charts printsupport widgets axcontainer
QT +=charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
QT       += core gui  serialport

QT += network

QT+= printsupport
TARGET = QtCustomProgressbar
TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    QrCode.cpp \
    arduino.cpp \
    calendrier.cpp \
    employe.cpp \
    gvol.cpp \
    gvoyageur.cpp \
    login.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    pdf.cpp \
    qrcodegeneratordemo.cpp \
    qrcodegenratorworke.cpp \
    qrwidget.cpp \
    reclamation.cpp \
    smtp.cpp

HEADERS += \
    QrCode.hpp \
    arduino.h \
    calendrier.h \
    employe.h \
    gvol.h \
    gvoyageur.h \
    login.h \
        mainwindow.h \
    connection.h \
    pdf.h \
    qrcodegenratorworke.h \
    qrwidget.h \
    reclamation.h \
    smtp.h

FORMS += \
        login.ui \
        mainwindow.ui \
        pdf.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
