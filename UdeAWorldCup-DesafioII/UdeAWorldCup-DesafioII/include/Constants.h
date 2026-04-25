#ifndef CONSTANTS_H
#define CONSTANTS_H

// Constantes de simulacion
const double ALFA = 0.6;
const double BETA = 0.4;
const double MU = 1.35;

// Probabilidades para simulacion
const double PROB_GOL_POR_JUGADOR = 0.04;
const double PROB_PRIMERA_AMARILLA = 0.06;
const double PROB_SEGUNDA_AMARILLA = 0.0115;
const double PROB_PRIMERA_FALTA = 0.13;
const double PROB_SEGUNDA_FALTA = 0.0275;
const double PROB_TERCERA_FALTA = 0.007;

// Fechas del torneo
static const char* FECHA_INICIO_MUNDIAL = "20-06-2026";
static const char* FECHA_INICIO_ELIMINATORIAS = "10-07-2026";

const int DIAS_FASE_GRUPOS = 19;
const int MAX_PARTIDOS_POR_DIA = 4;
const int DIAS_DESCANSO_ENTRE_PARTIDOS = 3;

// Cantidades del torneo
const int CANTIDAD_EQUIPOS = 48;
const int CANTIDAD_GRUPOS = 12;
const int EQUIPOS_POR_GRUPO = 4;
const int JUGADORES_POR_EQUIPO = 26;
const int CONVOCADOS_POR_PARTIDO = 11;
const int PARTIDOS_POR_GRUPO = 6;

// Etapas del torneo
static const char* NOMBRES_ETAPAS[] = {
    "Dieciseisavos (R16)",
    "Octavos (R8)",
    "Cuartos (QF)",
    "Semifinales (SF)",
    "Final"
};

#endif
