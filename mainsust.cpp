// programa que tenga herencia, polimorfismo, no tipos nativos, control compilacion duplicada.
// que se note polimorfismo, que se noten los datos de tipos, que de un guardia se derive a otro y cosas asi

#include <iostream>
#include "uni.h"

using namespace std;

int main() {
    Ubicacion fc = {"Facultad de Ciencias - Aula R-201", -12.0163, -77.0498};
    Ubicacion puerta3 = {"Puerta de Ingreso Nro 5", -12.0185, -77.0491};
    Ubicacion campusCentral = {"Facultad de Ciencias UNI", -12.0172, -77.0505};

    TI totalComunidad = 3;
    Persona** comunidadUNI = new Persona*[totalComunidad];

    comunidadUNI[0] = new Profesor("Ernesto Cuadros", 19951042, fc, "Fundamentos de la Programacion");
    comunidadUNI[1] = new Seguridad("Don Juan", 994012, puerta3, "Noche");
    comunidadUNI[2] = new SupervisorSeguridad("Comandante Flores", 991204, campusCentral, "Mañana", "Motocicleta UNI-05");

    cout << "=== MONITOREO EN TIEMPO REAL - Facultad de Ciencias UNI ===\n\n";

    for (int i = 0; i < totalComunidad; ++i) {
        comunidadUNI[i]->reportarActividad();
    }

    cout << "\n------------------------------------------------------------\n";

    for (int i = 0; i < totalComunidad; ++i) {
        delete comunidadUNI[i]; 
    }
    delete[] comunidadUNI;
    comunidadUNI = nullptr;

    return 0;
}