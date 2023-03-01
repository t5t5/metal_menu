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
    menumodelindex.cpp \
    menuvalue_ip.cpp \
    menuvalue_ip2.cpp \
    menuview.cpp

HEADERS += \
    abstractmenuitemdelegate.h \
    flag.h \
    keyevent.h \
    menu_main.h \
    menuaction_function.h \
    menudefines.h \
    menudialog.h \
    menumodel.h \
    menumodelindex.h \
    menuvalue_abstractsimple.h \
    menuvalue_enum.h \
    menuvalue_enumkey.h \
    menuvalue_float.h \
    menuvalue_ip.h \
    menuvalue_ip2.h \
    menuvalue_number.h \
    menuvalue_text.h \
    menuview.h

FORMS += \
    menudialog.ui
