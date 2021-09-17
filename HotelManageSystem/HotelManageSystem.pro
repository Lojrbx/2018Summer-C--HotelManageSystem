#-------------------------------------------------
#
# Project created by QtCreator 2018-07-25T16:45:24
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HotelManageSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        logindialog.cpp \
        register.cpp\
    choose.cpp \
    platformdialog.cpp \
    hotelmanagerdialog.cpp \
    list.cpp \
    userdialog.cpp \
    hotellist.cpp \
    order.cpp \
    hotellogin.cpp \
    hotelregister.cpp \
    platformlogin.cpp

HEADERS += \
        logindialog.h \
        register.h\
    choose.h \
    platformdialog.h \
    hotelmanagerdialog.h \
    list.h \
    userdialog.h \
    hotellist.h \
    order.h \
    hotellogin.h \
    hotelregister.h \
    platformlogin.h

FORMS += \
        logindialog.ui \
        register.ui\
    userdialog.ui \
    choose.ui \
    platformdialog.ui \
    hotelmanagerdialog.ui \
    userdialog.ui \
    userdialog.ui \
    hotellogin.ui \
    hotelregister.ui \
    platformlogin.ui
RC_ICONS = logo.ico
