#ifndef GRUPO_H
#define GRUPO_H

#include "Partido.h"
#include "Constants.h"

class Grupo {
private:
    char letra;
    Equipo* equipos[4];
    Partido* partidos[6];
    int puntos[4];
    int diferenciaGoles[4];
    int golesAFavor[4];
    
    void limpiarArrays();
    void ordenarClasificacion(int* indices);
    int compararEquipos(int idx1, int idx2);
    
public:
    Grupo(char l);
    ~Grupo();
    
    void agregarEquipo(Equipo* equipo, int posicion);
    void generarFixture();
    void simularPartidos();
    void calcularClasificacion();
    
    int getCantidadClasificados();
    int getClasificados(Equipo** salida);
    int getTerceros(Equipo** salida);
    
    Equipo* getEquipo(int posicion) const;
    Partido* getPartido(int idx) const;
    char getLetra() const { return letra; }
    int getPuntos(int posicion) const { return puntos[posicion]; }
    
    friend ostream& operator<<(ostream& os, const Grupo& g);
};

#endif