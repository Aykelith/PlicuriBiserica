#-------------------------------------------------
#
# Project created by QtCreator 2014-12-27T10:15:22
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlicuriBiserica
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        SelectareLunaFereastra.cpp \
    LunaFereastra.cpp \
    TabelFereastra.cpp \
    AdaugareFereastra.cpp

HEADERS  += SelectareLunaFereastra.hpp \
    LunaFereastra.hpp \
    Database.hpp \
    Global.hpp \
    Useful.hpp \
    TabelFereastra.hpp \
    AdaugareFereastra.hpp
