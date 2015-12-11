#-------------------------------------------------
#
# Project created by QtCreator 2014-12-10T04:45:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = eventfinder
TEMPLATE = app

INCLUDEPATH += /usr/src/QT/Extras/qcustomplot where qcustomplot.h

SOURCES += main.cpp\
        mainwindow.cpp \
    ../../../../../../../usr/src/QT/Extras/qcustomplot/qcustomplot.cpp \
    plot.cpp \
    cursor.cpp \
    data.cpp \
    file.cpp \
    event.cpp \
    eventmanager.cpp \
    columnselect_dialogue.cpp \
    overwritefile_dialogue.cpp \
    peakmanager.cpp

HEADERS  += mainwindow.h \
    ../../../../../../../usr/src/QT/Extras/qcustomplot/qcustomplot.h \
    plot.h \
    cursor.h \
    data.h \
    file.h \
    event.h \
    eventmanager.h \
    columnselect_dialogue.h \
    overwritefile_dialogue.h \
    peak.h \
    peakmanager.h

FORMS    += mainwindow.ui \
    columnselect_dialogue.ui \
    overwritefile_dialogue.ui

RESOURCES += \
    Buttons/buttons.qrc

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES +=
