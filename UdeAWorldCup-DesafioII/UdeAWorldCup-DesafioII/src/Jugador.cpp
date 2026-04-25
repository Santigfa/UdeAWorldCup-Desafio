#include "Jugador.h"
#include <cstring>

void Jugador::copiarCadena(char*& destino, const char* origen) {
    if (destino) {
        delete[] destino;
    }
    destino = new char[strlen(origen) + 1];
    strcpy(destino, origen);
}

Jugador::Jugador() : nombre(nullptr), apellido(nullptr), numeroCamiseta(0),
                     partidosJugados(0), goles(0), minutos(0), asistencias(0),
                     tarjetasAmarillas(0), tarjetasRojas(0), faltas(0) {}

Jugador::Jugador(const char* nom, const char* ape, int num) 
    : nombre(nullptr), apellido(nullptr), numeroCamiseta(num),
      partidosJugados(0), goles(0), minutos(0), asistencias(0),
      tarjetasAmarillas(0), tarjetasRojas(0), faltas(0) {
    copiarCadena(nombre, nom);
    copiarCadena(apellido, ape);
}

Jugador::~Jugador() {
    delete[] nombre;
    delete[] apellido;
}

Jugador::Jugador(const Jugador& other) 
    : nombre(nullptr), apellido(nullptr), numeroCamiseta(other.numeroCamiseta),
      partidosJugados(other.partidosJugados), goles(other.goles), minutos(other.minutos),
      asistencias(other.asistencias), tarjetasAmarillas(other.tarjetasAmarillas),
      tarjetasRojas(other.tarjetasRojas), faltas(other.faltas) {
    copiarCadena(nombre, other.nombre);
    copiarCadena(apellido, other.apellido);
}

Jugador& Jugador::operator=(const Jugador& other) {
    if (this != &other) {
        copiarCadena(nombre, other.nombre);
        copiarCadena(apellido, other.apellido);
        numeroCamiseta = other.numeroCamiseta;
        partidosJugados = other.partidosJugados;
        goles = other.goles;
        minutos = other.minutos;
        asistencias = other.asistencias;
        tarjetasAmarillas = other.tarjetasAmarillas;
        tarjetasRojas = other.tarjetasRojas;
        faltas = other.faltas;
    }
    return *this;
}

void Jugador::actualizarEstadisticas(int g, int am, int rj, int f, int mins) {
    goles += g;
    tarjetasAmarillas += am;
    tarjetasRojas += rj;
    faltas += f;
    minutos += mins;
}

void Jugador::sumarGol() {
    goles++;
}

void Jugador::sumarTarjetaAmarilla() {
    tarjetasAmarillas++;
}

void Jugador::sumarTarjetaRoja() {
    tarjetasRojas++;
}

void Jugador::sumarFalta() {
    faltas++;
}

void Jugador::sumarMinutos(int mins) {
    minutos += mins;
}

void Jugador::sumarPartidoJugado() {
    partidosJugados++;
}

void Jugador::sumarAsistencia() {
    asistencias++;
}

void Jugador::setNombre(const char* nom) {
    copiarCadena(nombre, nom);
}

void Jugador::setApellido(const char* ape) {
    copiarCadena(apellido, ape);
}

void Jugador::setNumero(int num) {
    numeroCamiseta = num;
}

ostream& operator<<(ostream& os, const Jugador& j) {
    os << j.nombre << " " << j.apellido << " (#" << j.numeroCamiseta << ")";
    os << " - Goles: " << j.goles << ", Amarillas: " << j.tarjetasAmarillas;
    os << ", Rojas: " << j.tarjetasRojas << ", Faltas: " << j.faltas;
    return os;
}

bool Jugador::operator==(const Jugador& other) const {
    return numeroCamiseta == other.numeroCamiseta;
}