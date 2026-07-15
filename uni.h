#ifndef __UNI_H__
#define __UNI_H__

#include <iostream>
#include <string>

using TS = std::string;
using TI = int;
using TD = double;

struct Ubicacion {
    TS lugar;      // Ejemplo: "Facultad de Ciencias", "Puerta 5"
    TD latitud;
    TD longitud;
};

class Persona {
protected:
    TS nombre;
    TI codigoUNI;       
    Ubicacion ubicacion; 

public:
    Persona(TS nom, TI cod, Ubicacion ub) 
        : nombre(nom), codigoUNI(cod), ubicacion(ub) {}

    virtual ~Persona() {} 
    virtual void reportarActividad() const = 0;
};


class Profesor : public Persona {
private:
    TS curso;

public:
    Profesor(TS nom, TI cod, Ubicacion ub, TS cur)
        : Persona(nom, cod, ub), curso(cur) {}

    void reportarActividad() const override {
        std::cout << "[Profesor] " << nombre << " (Cod: " << codigoUNI 
                  << ") dictando " << curso << " en el pabellon de " 
                  << ubicacion.lugar << ".\n";
    }
};
class Seguridad : public Persona {
protected:
    TS turno;

public:
    Seguridad(TS nom, TI cod, Ubicacion ub, TS tur)
        : Persona(nom, cod, ub), turno(tur) {}

    void reportarActividad() const override {
        std::cout << "[Seguridad] " << nombre << " (Turno: " << turno 
                  << ") vigilando el ingreso de estudiantes en la " 
                  << ubicacion.lugar << ".\n";
    }
};

class SupervisorSeguridad : public Seguridad {
private:
    TS vehiculoAsignado; 

public:
    SupervisorSeguridad(TS nom, TI cod, Ubicacion ub, TS tur, TS vehiculo)
        : Seguridad(nom, cod, ub, tur), vehiculoAsignado(vehiculo) {}

    void reportarActividad() const override {
        std::cout << "[Supervisor Seguridad] " << nombre << " patrullando en " 
                  << vehiculoAsignado << " por los alrededores de " 
                  << ubicacion.lugar << " (Coordenadas: " << ubicacion.latitud 
                  << ", " << ubicacion.longitud << ").\n";
    }
};

#endif // __UNI_H__
