QT += testlib
QT -= gui

CONFIG += qt console warn_on testcase c++11
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    tst_flashcardstest.cpp \
    ../card.cpp \
    ../deck.cpp \
    ../utils.cpp

HEADERS += \
    ../card.hh \
    ../deck.hh \
    ../utils.hh