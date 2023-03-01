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
    eventbus.cpp \
    eventhandler.cpp \
    main.cpp \
    menu_main.cpp \
    menudialog.cpp \
    menumodel.cpp \
    menumodelindex.cpp \
    menuvalue_ip.cpp \
    menuvalue_ip2.cpp \
    menuview.cpp \
    parameter_ipaddress.cpp \
    parameters.cpp

HEADERS += \
    abstractmenuitemdelegate.h \
    event.h \
    eventbus.h \
    eventhandler.h \
    flag.h \
    menu_main.h \
    menuaction_function.h \
    menuaction_setvalue_number.h \
    menudefines.h \
    menudialog.h \
    menumodel.h \
    menumodelindex.h \
    menuvalue_abstractsimple.h \
    menuvalue_enum.h \
    menuvalue_enumkey.h \
    menuvalue_floatconst.h \
    menuvalue_ip.h \
    menuvalue_ip2.h \
    menuvalue_number.h \
    menuvalue_textconst.h \
    menuview.h \
    parameter.h \
    parameter_ipaddress.h \
    parameter_number.h \
    parameters.h

FORMS += \
    menudialog.ui
