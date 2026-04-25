#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
using namespace std;

class Jugador {
private:
    char* nombre;
    char* apellido;
    int numeroCamiseta;
    int partidosJugados;
    int goles;
    int minutos;
    int asistencias;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;
    
    void copiarCadena(char*& destino, const char* origen);
    
public:
    Jugador();
    Jugador(const char* nom, const char* ape, int num);
    ~Jugador();
    Jugador(const Jugador& other);
    Jugador& operator=(const Jugador& other);
    
    void actualizarEstadisticas(int g, int am, int rj, int f, int mins);
    void sumarGol();
    void sumarTarjetaAmarilla();
    void sumarTarjetaRoja();
    void sumarFalta();
    void sumarMinutos(int mins);
    void sumarPartidoJugado();
    void sumarAsistencia();
    
    // Getters
    const char* getNombre() const { return nombre; }
    const char* getApellido() const { return apellido; }
    int getNumero() const { return numeroCamiseta; }
    int getGoles() const { return goles; }
    int getMinutos() const { return minutos; }
    int getTarjetasAmarillas() const { return tarjetasAmarillas; }
    int getTarjetasRojas() const { return tarjetasRojas; }
    int getFaltas() const { return faltas; }
    int getPartidosJugados() const { return partidosJugados; }
    
    // Setters
    void setNombre(const char* nom);
    void setApellido(const char* ape);
    void setNumero(int num);
    void setGoles(int g) { goles = g; }
    
    friend ostream& operator<<(ostream& os, const Jugador& j);
    bool operator==(const Jugador& other) const;
};

#endif