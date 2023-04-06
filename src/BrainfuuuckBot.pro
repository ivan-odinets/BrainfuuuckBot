QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

TARGET = brainfuuuck-bot

DEFINES += APP_NAME=\\\"BrainfuuuckBot\\\"
DEFINES += APP_VERSION=\\\"0.0.1\\\"

DESTDIR = ../bin
MOC_DIR = ../build/moc
RCC_DIR = ../build/rcc
unix:OBJECTS_DIR = ../build/o/unix
win32:OBJECTS_DIR = ../build/o/win32
macx:OBJECTS_DIR = ../build/o/mac

include(./QtTelegramBot/QtTelegramBot.pri)

CONFIG(release, debug|release) : DEFINES += QT_NO_DEBUG_OUTPUT

SOURCES += \
        AppConfig.cpp \
        BrainfuckJob.cpp \
        BrainfuckJobManager.cpp \
        BrainfuuuckBot.cpp \
        CommandLineParser.cpp \
        ProxyHelper.cpp \
        UI.cpp \
        main.cpp

HEADERS += \
    AppConfig.h \
    BrainfuckJob.h \
    BrainfuckJobManager.h \
    BrainfuuuckBot.h \
    CommandLineParser.h \
    ProxyHelper.h \
    UI.h
