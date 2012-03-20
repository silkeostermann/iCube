TEMPLATE = lib
CONFIG      += plugin
INCLUDEPATH += ../../src
HEADERS     = DynamicPinguin.h
SOURCES     = DynamicPinguin.cpp
TARGET      = $$qtLibraryTarget(cubes_dynpinguin)
DESTDIR     = ../../build/modules