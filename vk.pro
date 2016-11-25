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
    logindialog.cpp \
    form.cpp \
    w_login.cpp \
    myqtextedit.cpp \
    error_dialog.cpp

HEADERS  += widget.h \
    vkconnect.h \
    logindialog.h \
    form.h \
    w_login.h \
    myqtextedit.h \
    error_dialog.h

FORMS    += widget.ui \
    logindialog.ui \
    form.ui \
    w_login.ui \
    myqtextedit.ui \
    error_dialog.ui
