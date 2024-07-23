QT += core gui widgets openglwidgets

QMAKE_CXXFLAGS += -std=c++17
QMAKE_CFLAGS += -Wpedantic 

LIBS += -lm

SOURCES +=                           \
    ../main.cpp                       \
    *.cpp                              \
    C_module/matrix_core/*.c            \
    C_module/wireframe_and_parser/*.c    \
    C_module/affine_transformations/*.c   \
    gifmaker/*.c                           \
    gifmaker/*.cpp

HEADERS +=                           \
    *.hpp                             \
    Styles/*.hpp                       \
    C_module/*.h                        \                   
    C_module/matrix_core/*h              \
    C_module/wireframe_and_parser/*.h     \
    C_module/affine_transformations/*.h    \
    gifmaker/*.h

TARGET = viewer3D