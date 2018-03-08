TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Exception.cpp \
    Object.cpp

HEADERS += \
    SmartPointer.h \
    Exception.h \
    Object.h \
    List.h \
    SequenceList.h \
    StaticList.h \
    DynamicList.h \
    Array.h \
    StaticArray.h \
    DynamicArray.h \
    LinkList.h \
    StaticLink.h \
    Pointer.h \
    SharedPointer.h \
    CircleList.h \
    DualLinkList.h \
    LinuxList.h \
    DualCircleLinkList.h
