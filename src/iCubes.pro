TE = app
TARGET = iCubes
QT += core \
    gui
HEADERS += ConfigurationFileHelper.h \
    configure.h \
    Logic/Image.h \
    Logic/ModuleBinaryMath/BinaryMath.h \
    Logic/ModuleColorPalette/ColorPalette.h \
    Recognition/FrameProcessor.h \
    Recognition/Square.h \
    icubes.h
SOURCES += ConfigurationFileHelper.cpp \
    Logic/ModuleBinaryMath/BinaryMath.cpp \
    Logic/ModuleColorPalette/ColorPalette.cpp \
    Recognition/FrameProcessor.cpp \
    Recognition/Square.cpp \
    icubes.cpp \
    main.cpp \
    configure.cpp \
    Logic/Image.cpp
FORMS += icubes.ui \
    configure.ui
CONFIG += debug_and_release
