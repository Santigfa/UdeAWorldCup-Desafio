#ifndef VECTOR_DINAMICO_H
#define VECTOR_DINAMICO_H

#include <cstdlib>

template <typename T>
class VectorDinamico {
private:
    T* datos;
    int capacidad;
    int tamano;
    
    void redimensionar(int nuevaCapacidad) {
        T* nuevo = new T[nuevaCapacidad];
        for (int i = 0; i < tamano; i++) {
            nuevo[i] = datos[i];
        }
        delete[] datos;
        datos = nuevo;
        capacidad = nuevaCapacidad;
    }
    
public:
    VectorDinamico() : datos(nullptr), capacidad(0), tamano(0) {}
    
    ~VectorDinamico() {
        delete[] datos;
    }
    
    VectorDinamico(const VectorDinamico& other) 
        : capacidad(other.capacidad), tamano(other.tamano) {
        datos = new T[capacidad];
        for (int i = 0; i < tamano; i++) {
            datos[i] = other.datos[i];
        }
    }
    
    VectorDinamico& operator=(const VectorDinamico& other) {
        if (this != &other) {
            delete[] datos;
            capacidad = other.capacidad;
            tamano = other.tamano;
            datos = new T[capacidad];
            for (int i = 0; i < tamano; i++) {
                datos[i] = other.datos[i];
            }
        }
        return *this;
    }
    
    void push_back(const T& elemento) {
        if (tamano >= capacidad) {
            int nuevaCap = (capacidad == 0) ? 2 : capacidad * 2;
            redimensionar(nuevaCap);
        }
        datos[tamano++] = elemento;
    }
    
    T& operator[](int indice) {
        return datos[indice];
    }
    
    const T& operator[](int indice) const {
        return datos[indice];
    }
    
    int size() const { 
        return tamano; 
    }
    
    bool empty() const { 
        return tamano == 0; 
    }
    
    void clear() {
        delete[] datos;
        datos = nullptr;
        tamano = 0;
        capacidad = 0;
    }
};

#endif