#ifndef EQUIPO_H
#define EQUIPO_H

#include "Jugador.h"
#include "VectorDinamico.h"
#include <iostream>
using namespace std;

class Equipo {
private:
    char* pais;
    char* confederacion;
    char* directorTecnico;
    int rankingFIFA;
    VectorDinamico<Jugador> jugadores;
    int golesAFavor;
    int golesEnContra;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;
    
    void copiarCadena(char*& destino, const char* origen);
    
public:
    Equipo();
    ~Equipo();
    Equipo(const Equipo& other);
    Equipo& operator=(const Equipo& other);
    
    void actualizarEstadisticas(int gf, int gc, int am, int rj, int f);
    void agregarJugador(const Jugador& jugador);
    void generarJugadoresSinteticos(int golesHistoricosEquipo);
    Jugador* getJugadorPorNumero(int numero);
    void seleccionarJugadoresAleatorios(Jugador* salida[11]);
    
    double getPromedioGolesAFavor() const;
    double getPromedioGolesEnContra() const;
    
    // Getters
    const char* getPais() const { return pais; }
    const char* getConfederacion() const { return confederacion; }
    const char* getDirectorTecnico() const { return directorTecnico; }
    int getRanking() const { return rankingFIFA; }
    int getGolesAFavor() const { return golesAFavor; }
    int getGolesEnContra() const { return golesEnContra; }
    int getPartidosGanados() const { return partidosGanados; }
    int getPartidosEmpatados() const { return partidosEmpatados; }
    int getPartidosPerdidos() const { return partidosPerdidos; }
    int getPuntos() const { return partidosGanados * 3 + partidosEmpatados; }
    int getDiferenciaGoles() const { return golesAFavor - golesEnContra; }
    VectorDinamico<Jugador>& getJugadores() { return jugadores; }
    
    // Setters
    void setPais(const char* p);
    void setConfederacion(const char* c);
    void setDirectorTecnico(const char* dt);
    void setRanking(int r);
    void setGolesHistoricos(int gf, int gc);
    
    friend ostream& operator<<(ostream& os, const Equipo& e);
    bool operator<(const Equipo& other) const;
};

#endif