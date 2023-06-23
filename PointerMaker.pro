#-------------------------------------------------
#
# Project created by QtCreator 2022-08-26T12:48:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


INCLUDEPATH += $$PWD/QScintilla-2.11.5/Qt4Qt5
LIBS += -L$$PWD/QScintilla-2.11.5/build-qscintilla-Desktop_Qt_5_9_0_MinGW_32bit-Debug/debug/ -lqscintilla2_qt5d

TARGET = PointerMaker
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


SOURCES += \
    Widgets/sourcefilewidget.cpp \
        main.cpp \
        mainwindow.cpp \
    editor/codeeditor.cpp \
    editor/myhighlighter.cpp\
    cmdPart/cmdpart.cpp \
    Widgets/bottomwidget.cpp \
    Widgets/editorwidget.cpp \
    Widgets/mainwidget.cpp \
    Widgets/managerwidget.cpp\
    SearchReplace/searchwidget.cpp



HEADERS += \
    Widgets/sourcefilewidget.h \
        mainwindow.h \
    editor/codeeditor.h \
    editor/myhighlighter.h \
    editor/typedef.h \
    cmdPart/cmdpart.h \
    Widgets/bottomwidget.h \
    Widgets/editorwidget.h \
    Widgets/mainwidget.h \
    Widgets/managerwidget.h\
    SearchReplace/searchwidget.h

FORMS += \
        mainwindow.ui \
        search.ui

INCLUDEPATH += ./Widgets ./Editor ./cmdPart ./SearchReplace

CONFIG += warn_off
QMAKE_CXXFLAGS += -Wall
QMAKE_CXXFLAGS += -Wno-deprecated-copy

RESOURCES += \
    Source/Images/images.qrc

DISTFILES += \
    CKeyWords

macx: LIBS += -L$$PWD/Plugins/ -lqscintilla2_qt5_debug

INCLUDEPATH += $$PWD/Plugins/Qsci
DEPENDPATH += $$PWD/Plugins/Qsci
