#ifndef PARTIDO_H
#define PARTIDO_H

#include "Equipo.h"

class Partido {
private:
    char* fecha;
    char* hora;
    char* sede;
    Equipo* equipo1;
    Equipo* equipo2;
    char* arbitros[3];
    int golesEq1;
    int golesEq2;
    float posesionEq1;
    bool prorroga;
    Jugador* convocadosEq1[11];
    Jugador* convocadosEq2[11];
    int golesConvocadosEq1[11];
    int golesConvocadosEq2[11];
    int tarjetasAmarillasEq1;
    int tarjetasAmarillasEq2;
    int tarjetasRojasEq1;
    int tarjetasRojasEq2;
    int faltasEq1;
    int faltasEq2;
    
    void copiarCadena(char*& destino, const char* origen);
    double calcularGolesEsperados(Equipo* A, Equipo* B);
    int simularGoles(double lambda);
    void simularTarjetas(Jugador** convocados, int& amarillas, int& rojas);
    void simularFaltas(Jugador** convocados, int& totalFaltas);
    void simularGolesJugadores(Jugador** convocados, int* golesArray, int golesEquipo);
    void calcularPosesion();
    
public:
    Partido(Equipo* eq1, Equipo* eq2, const char* fec, const char* hor, const char* sed);
    ~Partido();
    Partido(const Partido& other);
    Partido& operator=(const Partido& other);
    
    void simular();
    void resolverEmpate();
    void actualizarEstadisticasPostPartido();
    
    Equipo* getGanador();
    bool hayEmpate() const;
    void setFecha(const char* fec);
    void setHora(const char* hor);
    
    int getGolesEq1() const { return golesEq1; }
    int getGolesEq2() const { return golesEq2; }
    Equipo* getEquipo1() const { return equipo1; }
    Equipo* getEquipo2() const { return equipo2; }
    const char* getFecha() const { return fecha; }
    
    friend ostream& operator<<(ostream& os, const Partido& p);
};

#endif