#include "types.h"

struct Vehiculo {
    STR placa;
    T2 x0, x1, t, velocidad;

    Vehiculo() : placa(""), x0(0), x1(0), t(0), velocidad(0) {}

    Vehiculo(STR p, T2 pos0, T2 pos1, T2 tiempo) 
        : placa(p), x0(pos0), x1(pos1), t(tiempo) {
        velocidad = (x1 - x0) / t;
        } 
};

bool operator>(const Vehiculo& v, T2 limite) {
    return v.velocidad > limite;
}

struct Radar {
    Vehiculo* registros;
    UT1 capacidad;
    UT1 cantidad; 
    Radar(UT1 cap) : capacidad(cap), cantidad(0) {
        registros = new Vehiculo[capacidad];
    }
    ~Radar() {
        delete[] registros;
    }
    void registrar(const Vehiculo& v) {
        if (cantidad < capacidad) {
            registros[cantidad++] = v;
        }
    }
    void mostrarInfractores(T2 limite) {
        for (UT1 i = 0; i < cantidad; ++i) {
            if (registros[i] > limite) {
                std::cout << "Placa: " << registros[i].placa 
                          << ", Velocidad: " << registros[i].velocidad 
                          << std::endl;
            }
        }
    }
struct SistemaMonitoreo {
    Radar* radar;
    T2 limite;
    SistemaMonitoreo(UT1 cap, T2 lim) : limite(lim) {
        radar = new Radar(cap);
    }
    ~SistemaMonitoreo() {
        delete radar;
    }
void procesarFlujo(const Vehiculo* flujo, UT1 tamaño) {
        for (UT1 i = 0; i < tamaño; ++i) {
            radar->registrar(flujo[i]);
        }
    }
    void reportar() const {
        radar->mostrarInfractores(limite);
    }
};
void ordenarVehiculosPorVelocidad(Vehiculo* arreglos, UT1 tamaño) {
    for (UT1 i = 0; i < tamaño - 1; ++i) {
        for (UT1 j = 0; j < tamaño - i - 1; ++j) {
            if (arreglos[j+1].velocidad > arreglos[j].velocidad) {
                Vehiculo temp = arreglos[j];
                arreglos[j] = arreglos[j + 1];
                arreglos[j + 1] = temp;
            }
        }
    }
}