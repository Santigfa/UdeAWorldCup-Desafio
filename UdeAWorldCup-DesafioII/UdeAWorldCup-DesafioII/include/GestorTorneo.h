#ifndef GESTOR_TORNEO_H
#define GESTOR_TORNEO_H

#include "Equipo.h"
#include "Grupo.h"
#include "Fixture.h"
#include "VectorDinamico.h"

class GestorTorneo {
private:
    VectorDinamico<Equipo> equipos;
    Grupo* grupos[12];
    Fixture fixture;
    long long contadorIteraciones;
    
    void incrementarIteraciones(long long n = 1) { contadorIteraciones += n; }
    void resetearIteraciones() { contadorIteraciones = 0; }
    
    void leerCSV(const char* archivo);
    void distribuirGolesJugadores();
    void ordenarEquiposPorRanking(Equipo** salida, int cantidad);
    void sorteoBombos(Equipo* bombos[4][12]);
    bool validarConfederaciones(Equipo* equiposGrupo[4]);
    void asignarFechasFaseGrupos();
    
public:
    GestorTorneo();
    ~GestorTorneo();
    
    void cargarDatos();
    void conformarGrupos();
    void simularFaseGrupos();
    void construirClasificacionYFixture();
    void simularEliminatorias();
    void generarEstadisticasFinales();
    void mostrarMenu();
    
    long long getIteraciones() const { return contadorIteraciones; }
    size_t calcularMemoriaTotal();
    
    void mostrarMedicionRecursos(const char* funcionalidad);
};

#endif