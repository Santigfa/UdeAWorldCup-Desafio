# =======================================================
# UdeAWorldCup-DesafioII.pro
# Proyecto: Simulador Mundial FIFA 2026
# Informática II - 2026-1
# =======================================================

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

# Nombre del ejecutable
TARGET = UdeAWorldCup

# Carpeta donde están los archivos .h
INCLUDEPATH += include

# Archivos fuente (.cpp)
SOURCES += \
    src/main.cpp \
    src/Jugador.cpp \
    src/Equipo.cpp \
    src/Partido.cpp \
    src/Grupo.cpp \
    src/Fixture.cpp \
    src/GestorTorneo.cpp

# Archivos de cabecera (.h)
HEADERS += \
    include/Constants.h \
    include/VectorDinamico.h \
    include/ListaEnlazada.h \
    include/Jugador.h \
    include/Equipo.h \
    include/Partido.h \
    include/Grupo.h \
    include/Fixture.h \
    include/GestorTorneo.h

# Configuración para evitar warnings innecesarios
QMAKE_CXXFLAGS += -Wall -Wextra -Wno-unused-parameter

# Para Linux/Mac: medición de memoria
unix:!macx {
    LIBS += -lstdc++
}

# Para Windows
win32 {
    LIBS += -lstdc++
}

# Limpiar al compilar
QMAKE_CLEAN += $$TARGET
