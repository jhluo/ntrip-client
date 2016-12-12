#-------------------------------------------------
#
# Project created by QtCreator 2016-08-31T08:51:09
#
#-------------------------------------------------

QT       += core gui network serialport quick qml positioning location

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NtripClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Widgets/MainWindowWidget.cpp \
    Widgets/SerialSettingsDialog.cpp \
    Client/Client.cpp \
    Client/SourceTableManager.cpp \
    NtripClient.cpp \
    Misc/Logger.cpp \
    Widgets/MessageViewer.cpp \
    Widgets/NtripStatusbar.cpp \
    Client/ClientManager.cpp \
    Widgets/MapViewer.cpp \
    styles/FusionStyle.cpp


HEADERS  += mainwindow.h \
    Widgets/MainWindowWidget.h \
    Widgets/SerialSettingsDialog.h \
    Client/Client.h \
    Client/SourceTableManager.h \
    NtripClient.h \
    Misc/Logger.h \
    Widgets/MessageViewer.h \
    Widgets/NtripStatusbar.h \
    Client/ClientManager.h \
    Widgets/MapViewer.h \
    styles/FusionStyle.h

DISTFILES += \
    .qmake.stash \
    object_script.NtripClient.Debug \
    object_script.NtripClient.Release \
    Qml/mapviewer.qml \
    Qml/mapTest.qml \
    Qml/helper.js \
    Qml/MessageForm.ui.qml \
    Qml/Message.qml \
    Qml/MapComponent.qml

SUBDIRS += \
    QtMapViewer/mapviewer.pro

RESOURCES +=

