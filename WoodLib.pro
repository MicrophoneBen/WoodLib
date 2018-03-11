TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Exception.cpp \
    Object.cpp \
    WoodString.cpp

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
    DualCircleLinkList.h \
    Stack.h \
    StaticStack.h \
    LinkStack.h \
    Queue.h \
    StaticQueue.h \
    LinkQueue.h \
    StackToQueue.h \
    QueueToStack.h \
    WoodString.h
