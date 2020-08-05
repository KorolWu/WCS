
#-------------------------------------------------
#
# Project created by QtCreator 2020-05-26T13:13:47
#
#-------------------------------------------------

QT       += core gui sql network concurrent serialport serialbus
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
    Forms/CarForms/addcar.cpp \
    Forms/TaskForms/currenttask.cpp \
    Forms/TaskForms/alltask.cpp \
    UnitClass/logmanager.cpp \
    UnitClass/ImportExportFile/localfileoperate.cpp \
    Forms/StorePosInfo/editstorenbrinfodialog.cpp \
    Forms/LogForms/logforms.cpp \
    Forms/TaskForms/labeldelegateV1.cpp \
    UnitClass/khttpserver.cpp \
    UnitClass/KCommunication.cpp \
    ControlClass/basedevice.cpp \
    Forms/CarForms/carlistform.cpp \
    ControlClass/observerbase.cpp \
    ControlClass/selectcar.cpp \
    UnitClass/TablepageWgClass/spiltpagesbyqsqltablemodel.cpp \
    Forms/StorePosInfo/pagewg/tablepagebyabstractwg.cpp \
    Forms/AlarmInfo/alarminfowg.cpp\
    ControlClass/kdispatch.cpp \
    ControlClass/dispatchcenter.cpp \
    ControlClass/AbstractClass/abstractorder.cpp \
    ControlClass/AbstractClass/rgvorder.cpp \
    Forms/TaskForms/subtask.cpp \
    MointorUI/storeitem.cpp \
    MointorUI/monitorview.cpp \
    MointorUI/monitorui.cpp




HEADERS  += mainwindow.h \
    UnitClass/jeson2object.h \
    UnitClass/c_systemlogmng.h \
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
    Forms/CarForms/addcar.h \
    Forms/TaskForms/currenttask.h \
    Forms/TaskForms/alltask.h \
    UnitClass/ImportExportFile/localfileoperate.h \
    Forms/StorePosInfo/editstorenbrinfodialog.h\
    UnitClass/myIniconfig.h \
    UnitClass/logmanager.h \
    Forms/LogForms/logforms.h \
    Forms/TaskForms/labeldelegateV1.h \
    UnitClass/khttpserver.h \
    UnitClass/KCommunication.h \
    ControlClass/basedevice.h \
    Forms/CarForms/carlistform.h \
    ControlClass/observerbase.h \
    ControlClass/selectcar.h \
    Forms/StorePosInfo/pagewg/tablepagebyabstractwg.h\
    UnitClass/TablepageWgClass/spiltpagesbyqsqltablemodel.h\
    Forms/AlarmInfo/alarminfowg.h\
    ControlClass/kdispatch.h \
    ControlClass/basedatainfooperate.h \
    ControlClass/dispatchcenter.h \
    ControlClass/AbstractClass/abstractorder.h \
    ControlClass/AbstractClass/rgvorder.h \
    Forms/TaskForms/subtask.h \
    MointorUI/storeitem.h \
    MointorUI/monitorview.h \
    MointorUI/monitorui.h

INCLUDEPATH += ../SDK/include/
include( $$PWD/../SDK/include/library/JQLibrary/JQLibrary.pri )
LIBS += -L../SDK/lib -lCRUDBaseOperation
LIBS += -L../SDK/lib -lReadTableData
FORMS    += mainwindow.ui

RESOURCES += \
    resousefile.qrc
