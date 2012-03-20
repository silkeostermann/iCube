TE = app
TARGET = iCubes
QT += core \
    gui
HEADERS += ConfigurationFileHelper.h \
    configure.h \
    Logic/ModuleInterface.h \
    Logic/Image.h \
    Logic/ModuleBinaryMath/BinaryMath.h \
    Logic/ModuleColorPalette/ColorPalette.h \
    Logic/ModulePinguinFlight/PinguinFlight.h \
    Recognition/FrameProcessor.h \
    Recognition/Square.h \
    icubes.h
SOURCES += ConfigurationFileHelper.cpp \
    Recognition/FrameProcessor.cpp \
    Recognition/Square.cpp \
    icubes.cpp \
    main.cpp \
    configure.cpp \
    Logic/Image.cpp \
    Logic/ModuleBinaryMath/BinaryMath.cpp \
    Logic/ModuleColorPalette/ColorPalette.cpp \
    Logic/ModulePinguinFlight/PinguinFlight.cpp \
    ModuleConfig.cpp
FORMS += icubes.ui \
    configure.ui
LIBS += -lopencv_highgui \
        -lopencv_core \
        -lopencv_imgproc
CONFIG += debug_and_release
DESTDIR = ../build