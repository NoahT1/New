TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

# SFML include directory
INCLUDEPATH += "C:/SFML-2.5.1/include"

# SFML library directory
LIBS += -L"C:/SFML-2.5.1/lib"

# Link with the appropriate SFML libraries depending on debug or release build
CONFIG(debug, debug|release) {
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

# Source files
SOURCES += \
    AmmoPickup.cpp \
    Asteroid.cpp \
    AsteroidSpawner.cpp \
    Blackhole.cpp \
    Bullet.cpp \
    Game.cpp \
    HealthBar.cpp \
    MedicPickup.cpp \
    Opponent.cpp \
    Player.cpp \
    WelcomeScreen.cpp \
    main.cpp

# Header files
HEADERS += \
    AmmoPickup.h \
    Asteroid.h \
    AsteroidSpawner.h \
    Blackhole.h \
    Bullet.h \
    Game.h \
    GameObject.h \
    HealthBar.h \
    MedicPickup.h \
    Opponent.h \
    Player.h \
    WelcomeScreen.h
