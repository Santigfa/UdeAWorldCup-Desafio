#include "Equipo.h"
#include "Constants.h"
#include <cstring>
#include <cstdlib>

void Equipo::copiarCadena(char*& destino, const char* origen) {
    if (destino) {
        delete[] destino;
    }
    destino = new char[strlen(origen) + 1];
    strcpy(destino, origen);
}

Equipo::Equipo() : pais(nullptr), confederacion(nullptr), directorTecnico(nullptr),
                   rankingFIFA(0), golesAFavor(0), golesEnContra(0),
                   partidosGanados(0), partidosEmpatados(0), partidosPerdidos(0),
                   tarjetasAmarillas(0), tarjetasRojas(0), faltas(0) {}

Equipo::~Equipo() {
    delete[] pais;
    delete[] confederacion;
    delete[] directorTecnico;
}

Equipo::Equipo(const Equipo& other) 
    : rankingFIFA(other.rankingFIFA), golesAFavor(other.golesAFavor),
      golesEnContra(other.golesEnContra), partidosGanados(other.partidosGanados),
      partidosEmpatados(other.partidosEmpatados), partidosPerdidos(other.partidosPerdidos),
      tarjetasAmarillas(other.tarjetasAmarillas), tarjetasRojas(other.tarjetasRojas),
      faltas(other.faltas), jugadores(other.jugadores) {
    copiarCadena(pais, other.pais);
    copiarCadena(confederacion, other.confederacion);
    copiarCadena(directorTecnico, other.directorTecnico);
}

Equipo& Equipo::operator=(const Equipo& other) {
    if (this != &other) {
        copiarCadena(pais, other.pais);
        copiarCadena(confederacion, other.confederacion);
        copiarCadena(directorTecnico, other.directorTecnico);
        rankingFIFA = other.rankingFIFA;
        golesAFavor = other.golesAFavor;
        golesEnContra = other.golesEnContra;
        partidosGanados = other.partidosGanados;
        partidosEmpatados = other.partidosEmpatados;
        partidosPerdidos = other.partidosPerdidos;
        tarjetasAmarillas = other.tarjetasAmarillas;
        tarjetasRojas = other.tarjetasRojas;
        faltas = other.faltas;
        jugadores = other.jugadores;
    }
    return *this;
}

void Equipo::actualizarEstadisticas(int gf, int gc, int am, int rj, int f) {
    golesAFavor += gf;
    golesEnContra += gc;
    tarjetasAmarillas += am;
    tarjetasRojas += rj;
    faltas += f;
    
    if (gf > gc) {
        partidosGanados++;
    } else if (gf < gc) {
        partidosPerdidos++;
    } else {
        partidosEmpatados++;
    }
}

void Equipo::agregarJugador(const Jugador& jugador) {
    jugadores.push_back(jugador);
}

void Equipo::generarJugadoresSinteticos(int golesHistoricosEquipo) {
    int golesPorJugador = golesHistoricosEquipo / JUGADORES_POR_EQUIPO;
    int residuo = golesHistoricosEquipo % JUGADORES_POR_EQUIPO;
    
    for (int i = 0; i < JUGADORES_POR_EQUIPO; i++) {
        char nombre[20];
        char apellido[20];
        sprintf(nombre, "nombre%d", i + 1);
        sprintf(apellido, "apellido%d", i + 1);
        
        Jugador j(nombre, apellido, i + 1);
        
        int golesJugador = golesPorJugador;
        if (i < residuo) {
            golesJugador++;
        }
        j.setGoles(golesJugador);
        
        agregarJugador(j);
    }
}

Jugador* Equipo::getJugadorPorNumero(int numero) {
    for (int i = 0; i < jugadores.size(); i++) {
        if (jugadores[i].getNumero() == numero) {
            return &jugadores[i];
        }
    }
    return nullptr;
}

void Equipo::seleccionarJugadoresAleatorios(Jugador* salida[11]) {
    bool seleccionados[JUGADORES_POR_EQUIPO] = {false};
    int contador = 0;
    
    while (contador < 11) {
        int indice = rand() % JUGADORES_POR_EQUIPO;
        if (!seleccionados[indice]) {
            seleccionados[indice] = true;
            salida[contador++] = &jugadores[indice];
        }
    }
}

double Equipo::getPromedioGolesAFavor() const {
    int partidosJugados = partidosGanados + partidosEmpatados + partidosPerdidos;
    if (partidosJugados == 0) return 0;
    return (double)golesAFavor / partidosJugados;
}

double Equipo::getPromedioGolesEnContra() const {
    int partidosJugados = partidosGanados + partidosEmpatados + partidosPerdidos;
    if (partidosJugados == 0) return 0;
    return (double)golesEnContra / partidosJugados;
}

void Equipo::setPais(const char* p) {
    copiarCadena(pais, p);
}

void Equipo::setConfederacion(const char* c) {
    copiarCadena(confederacion, c);
}

void Equipo::setDirectorTecnico(const char* dt) {
    copiarCadena(directorTecnico, dt);
}

void Equipo::setRanking(int r) {
    rankingFIFA = r;
}

void Equipo::setGolesHistoricos(int gf, int gc) {
    golesAFavor = gf;
    golesEnContra = gc;
}

ostream& operator<<(ostream& os, const Equipo& e) {
    os << e.pais << " (Ranking: " << e.rankingFIFA << ")";
    os << " - Confederacion: " << e.confederacion;
    os << " - Goles: " << e.golesAFavor << "/" << e.golesEnContra;
    os << " - Puntos: " << e.getPuntos();
    return os;
}

bool Equipo::operator<(const Equipo& other) const {
    return rankingFIFA < other.rankingFIFA;
}