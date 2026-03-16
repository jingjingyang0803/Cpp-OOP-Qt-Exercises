TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        card.cpp \
        cli.cpp \
        deck.cpp \
        deckmanager.cpp \
        main.cpp \
        utils.cpp

HEADERS += \
    card.hh \
    cli.hh \
    deck.hh \
    deckmanager.hh \
    utils.hh
