QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    acceptfriend.cpp \
    addfriend.cpp \
    basewindow.cpp \
    bbtpasswordedit.cpp \
    chatwindow.cpp \
    dragscroll.cpp \
    frilist.cpp \
    iconchange.cpp \
    listwidget.cpp \
    main.cpp \
    loginwidget.cpp \
    registerwidget.cpp \
    sendfile.cpp \
    titlebar.cpp

HEADERS += \
    acceptfriend.h \
    addfriend.h \
    basewindow.h \
    bbtpasswordedit.h \
    chatwindow.h \
    dragscroll.h \
    frilist.h \
    iconchange.h \
    listwidget.h \
    loginwidget.h \
    registerwidget.h \
    sendfile.h \
    titlebar.h

FORMS += \
    acceptfriend.ui \
    addfriend.ui \
    chatwindow.ui \
    frilist.ui \
    iconchange.ui \
    listwidget.ui \
    loginwidget.ui \
    registerwidget.ui \
    sendfile.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc \
    src.qrc

DISTFILES += \
    QiuQiu.pro.user
