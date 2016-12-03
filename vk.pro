#-------------------------------------------------
#
# Project created by QtCreator 2016-11-17T19:22:54
#
#-------------------------------------------------

QT       += core gui network webenginewidgets webview

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vk
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    vkconnect.cpp \
    form.cpp \
    w_login.cpp \
    myqtextedit.cpp \
    error_dialog.cpp \
    chat.cpp \
    crypt.cpp

HEADERS  += widget.h \
    vkconnect.h \
    form.h \
    w_login.h \
    myqtextedit.h \
    error_dialog.h \
    chat.h \
    crypt.h

FORMS    += widget.ui \
    form.ui \
    w_login.ui \
    myqtextedit.ui \
    error_dialog.ui

RESOURCES += \
    res.qrc

DISTFILES +=
LIBS += /usr/local/lib/libbotan-1.11.33.33.dylib
INCLUDEPATH += /usr/local/include
