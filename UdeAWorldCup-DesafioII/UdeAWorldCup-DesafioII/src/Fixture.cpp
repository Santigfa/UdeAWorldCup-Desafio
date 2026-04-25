#include "Fixture.h"
#include "Constants.h"
#include <iostream>
using namespace std;

Fixture::Fixture() : partidoTercerPuesto(nullptr), partidoFinal(nullptr) {}

Fixture::~Fixture() {
    limpiarLista(partidosR16);
    limpiarLista(partidosR8);
    limpiarLista(partidosQF);
    limpiarLista(partidosSF);

    if (partidoTercerPuesto) delete partidoTercerPuesto;
    if (partidoFinal) delete partidoFinal;
}

void Fixture::limpiarLista(ListaEnlazada<Partido*>& lista) {
    auto it = lista.getIterador();

    while (it.hayMas()) {
        Partido* p = it.obtener();
        if (p) delete p;
        it.siguiente();
    }
}

void Fixture::construirR16(Equipo** clasificados, int cantidadClasificados) {
    for (int i = 0; i < cantidadClasificados - 1; i += 2) {
        if (clasificados[i] && clasificados[i + 1]) {
            Partido* p = new Partido(clasificados[i], clasificados[i + 1],
                                     FECHA_INICIO_ELIMINATORIAS,
                                     "00:00",
                                     "nombreSede");
            partidosR16.agregar(p);
        }
    }
}

void Fixture::construirSiguienteRonda(ListaEnlazada<Partido*>& entrada,
                                      ListaEnlazada<Partido*>& salida) {
    int contador = 0;
    Equipo* ganadores[32];

    auto it = entrada.getIterador();

    while (it.hayMas()) {
        Partido* p = it.obtener();

        if (p && p->getGanador()) {
            ganadores[contador++] = p->getGanador();
        }

        it.siguiente();
    }

    for (int i = 0; i < contador - 1; i += 2) {
        Partido* nuevoPartido = new Partido(ganadores[i],
                                            ganadores[i + 1],
                                            FECHA_INICIO_ELIMINATORIAS,
                                            "00:00",
                                            "nombreSede");
        salida.agregar(nuevoPartido);
    }
}

void Fixture::simularRonda(ListaEnlazada<Partido*>& partidos,
                           const char* nombreEtapa) {
    auto it = partidos.getIterador();

    while (it.hayMas()) {
        Partido* p = it.obtener();

        if (p) {
            p->simular();

            if (p->hayEmpate()) {
                p->resolverEmpate();
            }

            p->actualizarEstadisticasPostPartido();
        }

        it.siguiente();
    }

    imprimirEtapa(nombreEtapa, partidos);
}

void Fixture::simularTodo() {
    cout << "\n========== SIMULANDO DIECISEISAVOS (R16) ==========" << endl;
    simularRonda(partidosR16, "Dieciseisavos");

    construirSiguienteRonda(partidosR16, partidosR8);
    cout << "\n========== SIMULANDO OCTAVOS (R8) ==========" << endl;
    simularRonda(partidosR8, "Octavos");

    construirSiguienteRonda(partidosR8, partidosQF);
    cout << "\n========== SIMULANDO CUARTOS (QF) ==========" << endl;
    simularRonda(partidosQF, "Cuartos");

    construirSiguienteRonda(partidosQF, partidosSF);
    cout << "\n========== SIMULANDO SEMIFINALES (SF) ==========" << endl;
    simularRonda(partidosSF, "Semifinales");

    auto it = partidosSF.getIterador();

    Equipo* finalista1 = nullptr;
    Equipo* finalista2 = nullptr;
    Equipo* perdedor1 = nullptr;
    Equipo* perdedor2 = nullptr;

    if (it.hayMas()) {
        Partido* sf1 = it.obtener();
        finalista1 = sf1->getGanador();

        if (sf1->getEquipo1() == finalista1) {
            perdedor1 = sf1->getEquipo2();
        } else {
            perdedor1 = sf1->getEquipo1();
        }

        it.siguiente();
    }

    if (it.hayMas()) {
        Partido* sf2 = it.obtener();
        finalista2 = sf2->getGanador();

        if (sf2->getEquipo1() == finalista2) {
            perdedor2 = sf2->getEquipo2();
        } else {
            perdedor2 = sf2->getEquipo1();
        }
    }

    if (perdedor1 && perdedor2) {
        partidoTercerPuesto = new Partido(perdedor1,
                                          perdedor2,
                                          FECHA_INICIO_ELIMINATORIAS,
                                          "00:00",
                                          "nombreSede");

        partidoTercerPuesto->simular();

        if (partidoTercerPuesto->hayEmpate()) {
            partidoTercerPuesto->resolverEmpate();
        }

        partidoTercerPuesto->actualizarEstadisticasPostPartido();

        cout << "\n========== PARTIDO TERCER PUESTO ==========" << endl;
        cout << *partidoTercerPuesto << endl;
    }

    if (finalista1 && finalista2) {
        partidoFinal = new Partido(finalista1,
                                   finalista2,
                                   FECHA_INICIO_ELIMINATORIAS,
                                   "00:00",
                                   "nombreSede");

        partidoFinal->simular();

        if (partidoFinal->hayEmpate()) {
            partidoFinal->resolverEmpate();
        }

        partidoFinal->actualizarEstadisticasPostPartido();

        cout << "\n========== FINAL DEL MUNDIAL ==========" << endl;
        cout << *partidoFinal << endl;
    }
}

void Fixture::imprimirEtapa(const char* nombre,
                            ListaEnlazada<Partido*>& partidos) {
    cout << "\n--- " << nombre << " ---" << endl;

    int i = 1;
    auto it = partidos.getIterador();

    while (it.hayMas()) {
        Partido* p = it.obtener();

        if (p) {
            cout << "Partido " << i++ << ": ";
            cout << p->getEquipo1()->getPais() << " "
                 << p->getGolesEq1() << " - "
                 << p->getGolesEq2() << " "
                 << p->getEquipo2()->getPais();

            if (p->getGanador()) {
                cout << " -> Gana: " << p->getGanador()->getPais();
            }

            cout << endl;
        }

        it.siguiente();
    }
}

Equipo* Fixture::getCampeon() {
    return partidoFinal ? partidoFinal->getGanador() : nullptr;
}

Equipo* Fixture::getSubcampeon() {
    if (!partidoFinal) return nullptr;

    Equipo* ganador = partidoFinal->getGanador();

    if (ganador == partidoFinal->getEquipo1()) {
        return partidoFinal->getEquipo2();
    }

    return partidoFinal->getEquipo1();
}

Equipo* Fixture::getTercerPuesto() {
    return partidoTercerPuesto ? partidoTercerPuesto->getGanador() : nullptr;
}

Equipo* Fixture::getCuartoPuesto() {
    if (!partidoTercerPuesto) return nullptr;

    Equipo* ganador = partidoTercerPuesto->getGanador();

    if (ganador == partidoTercerPuesto->getEquipo1()) {
        return partidoTercerPuesto->getEquipo2();
    }

    return partidoTercerPuesto->getEquipo1();
}

void Fixture::getGoleadoresPorEtapa(const char* etapa,
                                    int& maxGoles,
                                    int& numeroCamiseta,
                                    Equipo*& equipo) {
    maxGoles = 0;
    numeroCamiseta = 0;
    equipo = nullptr;
}
