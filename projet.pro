QT += widgets
QT += xml

SOURCES += \
    main.cpp \
    autocell.cpp \
    automaton.cpp \
    autocell2d.cpp \
    simulator.cpp \
    autofeu.cpp \
    xml_dom.cpp \
    interface.cpp \
    state.cpp

HEADERS += \
    autocell.h \
    automaton.h \
    simulator.h \
    autocell2d.h \
    autofeu.h \
    xml_dom.h \
    interface.h \
    state.h

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11
