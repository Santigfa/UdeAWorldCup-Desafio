#include "Partido.h"
#include "Constants.h"
#include <cstring>
#include <cmath>
#include <cstdlib>

void Partido::copiarCadena(char*& destino, const char* origen) {
    if (destino) {
        delete[] destino;
    }
    destino = new char[strlen(origen) + 1];
    strcpy(destino, origen);
}

Partido::Partido(Equipo* eq1, Equipo* eq2, const char* fec, const char* hor, const char* sed)
    : equipo1(eq1), equipo2(eq2), golesEq1(0), golesEq2(0), posesionEq1(50.0), prorroga(false),
      tarjetasAmarillasEq1(0), tarjetasAmarillasEq2(0), tarjetasRojasEq1(0), tarjetasRojasEq2(0),
      faltasEq1(0), faltasEq2(0) {
    copiarCadena(fecha, fec);
    copiarCadena(hora, hor);
    copiarCadena(sede, sed);
    for (int i = 0; i < 3; i++) {
        arbitros[i] = new char[20];
        strcpy(arbitros[i], "codArbitro");
    }
    for (int i = 0; i < 11; i++) {
        convocadosEq1[i] = nullptr;
        convocadosEq2[i] = nullptr;
        golesConvocadosEq1[i] = 0;
        golesConvocadosEq2[i] = 0;
    }
}

Partido::~Partido() {
    delete[] fecha;
    delete[] hora;
    delete[] sede;
    for (int i = 0; i < 3; i++) {
        delete[] arbitros[i];
    }
}

Partido::Partido(const Partido& other)
    : equipo1(other.equipo1), equipo2(other.equipo2), golesEq1(other.golesEq1), golesEq2(other.golesEq2),
      posesionEq1(other.posesionEq1), prorroga(other.prorroga),
      tarjetasAmarillasEq1(other.tarjetasAmarillasEq1), tarjetasAmarillasEq2(other.tarjetasAmarillasEq2),
      tarjetasRojasEq1(other.tarjetasRojasEq1), tarjetasRojasEq2(other.tarjetasRojasEq2),
      faltasEq1(other.faltasEq1), faltasEq2(other.faltasEq2) {
    copiarCadena(fecha, other.fecha);
    copiarCadena(hora, other.hora);
    copiarCadena(sede, other.sede);
    for (int i = 0; i < 3; i++) {
        arbitros[i] = new char[strlen(other.arbitros[i]) + 1];
        strcpy(arbitros[i], other.arbitros[i]);
    }
    for (int i = 0; i < 11; i++) {
        convocadosEq1[i] = other.convocadosEq1[i];
        convocadosEq2[i] = other.convocadosEq2[i];
        golesConvocadosEq1[i] = other.golesConvocadosEq1[i];
        golesConvocadosEq2[i] = other.golesConvocadosEq2[i];
    }
}

Partido& Partido::operator=(const Partido& other) {
    if (this != &other) {
        delete[] fecha;
        delete[] hora;
        delete[] sede;
        copiarCadena(fecha, other.fecha);
        copiarCadena(hora, other.hora);
        copiarCadena(sede, other.sede);
        
        equipo1 = other.equipo1;
        equipo2 = other.equipo2;
        golesEq1 = other.golesEq1;
        golesEq2 = other.golesEq2;
        posesionEq1 = other.posesionEq1;
        prorroga = other.prorroga;
        tarjetasAmarillasEq1 = other.tarjetasAmarillasEq1;
        tarjetasAmarillasEq2 = other.tarjetasAmarillasEq2;
        tarjetasRojasEq1 = other.tarjetasRojasEq1;
        tarjetasRojasEq2 = other.tarjetasRojasEq2;
        faltasEq1 = other.faltasEq1;
        faltasEq2 = other.faltasEq2;
    }
    return *this;
}

double Partido::calcularGolesEsperados(Equipo* A, Equipo* B) {
    double gfA = A->getPromedioGolesAFavor();
    double gcB = B->getPromedioGolesEnContra();
    
    if (gfA < 0.01) gfA = 0.5;
    if (gcB < 0.01) gcB = 0.5;
    
    double lambda = MU * pow(gfA / MU, ALFA) * pow(gcB / MU, BETA);
    return lambda;
}

int Partido::simularGoles(double lambda) {
    double L = exp(-lambda);
    double p = 1.0;
    int k = 0;
    do {
        k++;
        p *= (double)rand() / RAND_MAX;
    } while (p > L);
    return k - 1;
}

void Partido::simularTarjetas(Jugador** convocados, int& amarillas, int& rojas) {
    for (int i = 0; i < 11 && convocados[i]; i++) {
        if ((double)rand() / RAND_MAX < PROB_PRIMERA_AMARILLA) {
            convocados[i]->sumarTarjetaAmarilla();
            amarillas++;
            
            if ((double)rand() / RAND_MAX < PROB_SEGUNDA_AMARILLA) {
                convocados[i]->sumarTarjetaRoja();
                rojas++;
            }
        }
    }
}

void Partido::simularFaltas(Jugador** convocados, int& totalFaltas) {
    for (int i = 0; i < 11 && convocados[i]; i++) {
        int faltasJugador = 0;
        if ((double)rand() / RAND_MAX < PROB_PRIMERA_FALTA) {
            faltasJugador++;
            if ((double)rand() / RAND_MAX < PROB_SEGUNDA_FALTA) {
                faltasJugador++;
                if ((double)rand() / RAND_MAX < PROB_TERCERA_FALTA) {
                    faltasJugador++;
                }
            }
        }
        for (int f = 0; f < faltasJugador; f++) {
            convocados[i]->sumarFalta();
            totalFaltas++;
        }
    }
}

void Partido::simularGolesJugadores(Jugador** convocados, int* golesArray, int golesEquipo) {
    for (int i = 0; i < 11 && convocados[i]; i++) {
        golesArray[i] = 0;
    }
    
    int golesAsignados = 0;
    while (golesAsignados < golesEquipo) {
        for (int i = 0; i < 11 && golesAsignados < golesEquipo; i++) {
            if ((double)rand() / RAND_MAX < PROB_GOL_POR_JUGADOR) {
                golesArray[i]++;
                convocados[i]->sumarGol();
                golesAsignados++;
            }
        }
    }
}

void Partido::calcularPosesion() {
    int rank1 = equipo1->getRanking();
    int rank2 = equipo2->getRanking();
    
    posesionEq1 = 50.0 + (rank2 - rank1) * 0.2;
    if (posesionEq1 < 35) posesionEq1 = 35;
    if (posesionEq1 > 65) posesionEq1 = 65;
}

void Partido::simular() {
    equipo1->seleccionarJugadoresAleatorios(convocadosEq1);
    equipo2->seleccionarJugadoresAleatorios(convocadosEq2);
    
    calcularPosesion();
    
    double lambda1 = calcularGolesEsperados(equipo1, equipo2);
    double lambda2 = calcularGolesEsperados(equipo2, equipo1);
    
    golesEq1 = simularGoles(lambda1);
    golesEq2 = simularGoles(lambda2);
    
    simularGolesJugadores(convocadosEq1, golesConvocadosEq1, golesEq1);
    simularGolesJugadores(convocadosEq2, golesConvocadosEq2, golesEq2);
    
    simularTarjetas(convocadosEq1, tarjetasAmarillasEq1, tarjetasRojasEq1);
    simularTarjetas(convocadosEq2, tarjetasAmarillasEq2, tarjetasRojasEq2);
    
    simularFaltas(convocadosEq1, faltasEq1);
    simularFaltas(convocadosEq2, faltasEq2);
    
    for (int i = 0; i < 11; i++) {
        if (convocadosEq1[i]) convocadosEq1[i]->sumarMinutos(90);
        if (convocadosEq2[i]) convocadosEq2[i]->sumarMinutos(90);
        if (convocadosEq1[i]) convocadosEq1[i]->sumarPartidoJugado();
        if (convocadosEq2[i]) convocadosEq2[i]->sumarPartidoJugado();
    }
}

void Partido::resolverEmpate() {
    prorroga = true;
    
    int rank1 = equipo1->getRanking();
    int rank2 = equipo2->getRanking();
    
    double probGana1 = (double)rank2 / (rank1 + rank2);
    double random = (double)rand() / RAND_MAX;
    
    if (random < probGana1) {
        golesEq1++;
    } else {
        golesEq2++;
    }
    
    for (int i = 0; i < 11; i++) {
        if (convocadosEq1[i]) convocadosEq1[i]->sumarMinutos(30);
        if (convocadosEq2[i]) convocadosEq2[i]->sumarMinutos(30);
    }
}

void Partido::actualizarEstadisticasPostPartido() {
    equipo1->actualizarEstadisticas(golesEq1, golesEq2, 
                                     tarjetasAmarillasEq1, tarjetasRojasEq1, faltasEq1);
    equipo2->actualizarEstadisticas(golesEq2, golesEq1,
                                     tarjetasAmarillasEq2, tarjetasRojasEq2, faltasEq2);
}

Equipo* Partido::getGanador() {
    if (golesEq1 > golesEq2) return equipo1;
    if (golesEq2 > golesEq1) return equipo2;
    return nullptr;
}

bool Partido::hayEmpate() const {
    return golesEq1 == golesEq2;
}

void Partido::setFecha(const char* fec) {
    copiarCadena(fecha, fec);
}

void Partido::setHora(const char* hor) {
    copiarCadena(hora, hor);
}

ostream& operator<<(ostream& os, const Partido& p) {
    os << p.fecha << " " << p.hora << " - " << p.sede << endl;
    os << p.equipo1->getPais() << " " << p.golesEq1 << " - " << p.golesEq2 << " " << p.equipo2->getPais();
    if (p.prorroga) os << " (prorroga)";
    os << endl;
    os << "Posesion: " << p.posesionEq1 << "% - " << (100 - p.posesionEq1) << "%" << endl;
    return os;
}