#ifndef FIXTURE_H
#define FIXTURE_H

#include "Partido.h"
#include "ListaEnlazada.h"

class Fixture {
private:
    ListaEnlazada<Partido*> partidosR16;
    ListaEnlazada<Partido*> partidosR8;
    ListaEnlazada<Partido*> partidosQF;
    ListaEnlazada<Partido*> partidosSF;
    Partido* partidoTercerPuesto;
    Partido* partidoFinal;
    
    void construirSiguienteRonda(ListaEnlazada<Partido*>& entrada, ListaEnlazada<Partido*>& salida);
    void limpiarLista(ListaEnlazada<Partido*>& lista);
    
public:
    Fixture();
    ~Fixture();
    
    void construirR16(Equipo** clasificados, int cantidadClasificados);
    void simularRonda(ListaEnlazada<Partido*>& partidos, const char* nombreEtapa);
    void simularTodo();
    void imprimirEtapa(const char* nombre, ListaEnlazada<Partido*>& partidos);
    
    Equipo* getCampeon();
    Equipo* getSubcampeon();
    Equipo* getTercerPuesto();
    Equipo* getCuartoPuesto();
    
    void getGoleadoresPorEtapa(const char* etapa, int& maxGoles, int& numeroCamiseta, Equipo*& equipo);
};

#endif