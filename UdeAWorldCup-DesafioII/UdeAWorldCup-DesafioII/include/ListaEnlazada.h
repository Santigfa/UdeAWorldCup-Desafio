#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

template <typename T>
class ListaEnlazada {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(const T& d) : dato(d), siguiente(nullptr) {}
    };
    
    Nodo* cabeza;
    int longitud;
    
public:
    ListaEnlazada() : cabeza(nullptr), longitud(0) {}
    
    ~ListaEnlazada() {
        while (cabeza) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
    
    ListaEnlazada(const ListaEnlazada& other) : cabeza(nullptr), longitud(0) {
        Nodo* actual = other.cabeza;
        while (actual) {
            agregar(actual->dato);
            actual = actual->siguiente;
        }
    }
    
    ListaEnlazada& operator=(const ListaEnlazada& other) {
        if (this != &other) {
            while (cabeza) {
                Nodo* temp = cabeza;
                cabeza = cabeza->siguiente;
                delete temp;
            }
            longitud = 0;
            Nodo* actual = other.cabeza;
            while (actual) {
                agregar(actual->dato);
                actual = actual->siguiente;
            }
        }
        return *this;
    }
    
    void agregar(const T& elemento) {
        Nodo* nuevo = new Nodo(elemento);
        if (!cabeza) {
            cabeza = nuevo;
        } else {
            Nodo* actual = cabeza;
            while (actual->siguiente) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
        longitud++;
    }
    
    bool eliminar(const T& elemento) {
        if (!cabeza) return false;
        
        if (cabeza->dato == elemento) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            longitud--;
            return true;
        }
        
        Nodo* actual = cabeza;
        while (actual->siguiente && !(actual->siguiente->dato == elemento)) {
            actual = actual->siguiente;
        }
        
        if (actual->siguiente) {
            Nodo* temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            delete temp;
            longitud--;
            return true;
        }
        
        return false;
    }
    
    void recorrer(void (*funcion)(T&)) {
        Nodo* actual = cabeza;
        while (actual) {
            funcion(actual->dato);
            actual = actual->siguiente;
        }
    }
    
    int size() const { 
        return longitud; 
    }
    
    bool empty() const { 
        return cabeza == nullptr; 
    }
    
    class Iterador {
    private:
        Nodo* actual;
    public:
        Iterador(Nodo* inicio) : actual(inicio) {}
        bool hayMas() const { return actual != nullptr; }
        void siguiente() { if (actual) actual = actual->siguiente; }
        T& obtener() { return actual->dato; }
    };
    
    Iterador getIterador() const {
        return Iterador(cabeza);
    }
};

#endif