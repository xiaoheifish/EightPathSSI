#-------------------------------------------------
#
# Project created by QtCreator 2017-02-15T22:19:06
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport core gui
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}


TARGET = EightPathSSI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    writethread.cpp \
    masterthread.cpp \
    serialportinfomanager.cpp

HEADERS  += mainwindow.h \
    writethread.h \
    masterthread.h \
    serialportinfomanager.h

FORMS    += mainwindow.ui
