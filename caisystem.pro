QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    activinput.cpp \
    activlistitem.cpp \
    activwidget.cpp \
    alarmitem.cpp \
    alistui.cpp \
    authwarning.cpp \
    cblistitem.cpp \
    cblistiteminput.cpp \
    cblistwidget.cpp \
    cdwidget.cpp \
    clock.cpp \
    clockthread.cpp \
    coursefileitem.cpp \
    jobdetail.cpp \
    jobitem.cpp \
    login.cpp \
    logui.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    settime.cpp

HEADERS += \
    activinput.h \
    activlistitem.h \
    activwidget.h \
    alarmitem.h \
    alistui.h \
    authwarning.h \
    cblistitem.h \
    cblistiteminput.h \
    cblistwidget.h \
    cdwidget.h \
    clock.h \
    clockthread.h \
    coursefileitem.h \
    jobdetail.h \
    jobitem.h \
    login.h \
    logui.h \
    mainwindow.h \
    menu.h \
    settime.h

FORMS += \
    activinput.ui \
    activlistitem.ui \
    activwidget.ui \
    alarmitem.ui \
    alistui.ui \
    authwarning.ui \
    cblistitem.ui \
    cblistiteminput.ui \
    cblistwidget.ui \
    cdwidget.ui \
    clock.ui \
    coursefileitem.ui \
    jobdetail.ui \
    jobitem.ui \
    login.ui \
    logui.ui \
    mainwindow.ui \
    menu.ui \
    settime.ui

TRANSLATIONS += \
    caisystem_zh_CN.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/sources/course_system   #通过路径添加子文件内容
INCLUDEPATH += $$PWD/sources/common
INCLUDEPATH += $$PWD/sources/file_system
INCLUDEPATH += $$PWD/sources/time_system
INCLUDEPATH += $$PWD/sources/user_system
INCLUDEPATH += $$PWD/sources/navi_system
INCLUDEPATH += $$PWD/sources/activity_system
include($$PWD/sources/activity_system/activity_system.pri) #添加子文件夹所需pri文件
include($$PWD/sources/navi_system/navi_system.pri)
include($$PWD/sources/course_system/course_system.pri)
include($$PWD/sources/common/common.pri)
include($$PWD/sources/file_system/file_system.pri)
include($$PWD/sources/time_system/time_system.pri)
include($$PWD/sources/user_system/user_system.pri)

