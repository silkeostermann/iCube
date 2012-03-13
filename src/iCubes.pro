TEMPLATE = app
TARGET = iCubes
QT += core \
    gui
HEADERS += Logic/Image.h \
    Logic/ModuleBinaryMath/BinaryMath.h \
    Logic/ModuleColorPalette/ColorPalette.h \
    Recognition/FrameProcessor.h \
    Recognition/Square.h \
    icubes.h \
    Quadrilateral.h
SOURCES += Logic/Image.cpp \
    Logic/ModuleBinaryMath/BinaryMath.cpp \
    Logic/ModuleColorPalette/ColorPalette.cpp \
    Recognition/FrameProcessor.cpp \
    Recognition/Square.cpp \
    main.cpp \
    icubes.cpp
FORMS += icubes.ui
RESOURCES += 
