QT += core gui widgets

CONFIG += c++17
CONFIG -= app_bundle
CONFIG -= debug_and_release debug_and_release_target

MOC_DIR = ./tmp/moc
OBJECTS_DIR = ./tmp/obj
RCC_DIR = ./tmp/rcc
UI_DIR = ./tmp/ui
DESTDIR = $$BUILD_DIR

SOURCES += \
    abstractmenuitemdelegate.cpp \
    keyevent.cpp \
    main.cpp \
    menu_main.cpp \
    menudialog.cpp \
    menumodel.cpp \
    menuview.cpp

HEADERS += \
    abstractmenuitemdelegate.h \
    keyevent.h \
    menu_main.h \
    menudefines.h \
    menudialog.h \
    menumodel.h \
    menuview.h

FORMS += \
    menudialog.ui
