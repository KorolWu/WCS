#-------------------------------------------------
#
# Project created by QtCreator 2020-05-26T13:13:47
#
#-------------------------------------------------

QT       += core gui sql
QTPLUGIN += qgif

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WarehouseControlSystem
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


SOURCES += main.cpp\
        mainwindow.cpp \
    UnitClass/jeson2object.cpp \
    UnitClass/c_systemlogmng.cpp \
    UnitClass/databaseunit.cpp \
    UnitClass/logininfowg.cpp \
    Forms/basefrom.cpp \
    Forms/CarForms/adddevice.cpp \
    Forms/CarForms/agvform.cpp \
    Forms/CarForms/CarStatusFrom.cpp \
    Forms/CarForms/labeldelegate.cpp \
    Forms/CarForms/progressbardelegate.cpp \
    Forms/ElevatorForms/elevatorfrom.cpp \
    Forms/StorePosInfo/buttondelegate.cpp \
    Forms/StorePosInfo/storeinfowidget.cpp \
    Forms/StorePosInfo/storenbrinfotablemodel.cpp \
    Forms/StorePosInfo/storenbrtableview.cpp \
    Forms/StorePosInfo/watingdialogwg.cpp\
    Forms/ElevatorForms/addelevatorform.cpp \
    Forms/dialogabstractclass.cpp \
    Forms/StorePosInfo/localfileoperate.cpp\
    Forms/CarForms/addcar.cpp \
    Forms/TaskForms/currenttask.cpp \
   Forms/TaskForms/alltask.cpp



HEADERS  += mainwindow.h \
    UnitClass/jeson2object.h \
    UnitClass/c_systemlogmng.h \
    datastructure.h \
    UnitClass/databaseunit.h \
    UnitClass/logininfowg.h \
    Forms/basefrom.h \
    Forms/CarForms/adddevice.h \
    Forms/CarForms/agvform.h \
    Forms/CarForms/CarStatusFrom.h \
    Forms/CarForms/labeldelegate.h \
    Forms/CarForms/progressbardelegate.h \
    Forms/ElevatorForms/elevatorfrom.h \
    Forms/StorePosInfo/buttondelegate.h \
    Forms/StorePosInfo/storeinfowidget.h \
    Forms/StorePosInfo/storenbrinfotablemodel.h \
    Forms/StorePosInfo/storenbrtableview.h \
    Forms/StorePosInfo/watingdialogwg.h \
    Forms/ElevatorForms/addelevatorform.h \
    Forms/dialogabstractclass.h \
    Forms/StorePosInfo/localfileoperate.h \
    Forms/CarForms/addcar.h \
    Forms/TaskForms/currenttask.h \
    Forms/TaskForms/alltask.h \
    UnitClass/myIniconfig.h

INCLUDEPATH += ../SDK/include/
LIBS += -L../SDK/lib -lCRUDBaseOperation
LIBS += -L../SDK/lib -lReadTableData
FORMS    += mainwindow.ui

RESOURCES += \
    resousefile.qrc
