TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    creditaccount.cpp \
    main.cpp \
    account.cpp \
    timedepositaccount.cpp

HEADERS += \
    account.hh  \
    creditaccount.hh \
    timedepositaccount.hh

