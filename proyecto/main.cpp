#include <iostream>
#include <fstream>
#include <iomanip>
#include "radar.h"

template <typename T>
void ordenarVehiculosPorVelocidad(vehiculo<T>* arreglos, UT1 tamaño) {
    for (UT1 i = 0; i < tamaño - 1; ++i) {
        for (UT1 j = 0; j < tamaño - i - 1; ++j) {
            //Comparamos los valores
            if(arreglos[j].esMasRapidoQue(arreglos[j+1])){
                vehiculo<T> temp1 = arreglos[j];
                arreglos[j] = arreglos[j + 1];
                arreglos[j + 1] = temp1;
            }
        }
    }
}

template <typename T>
struct SistemaMonitoreo {
    T2 limite;

    SistemaMonitoreo(T2 lim) : limite(lim) {
        std::cout <<"[SistemaMonitoreo] Inicializacion con limite de: " << limite << " m/s" << std::endl;
    }
    ~SistemaMonitoreo() {
        std::cout <<"[SistemaMonitoreo] Destructor invocado de manera segura (RAII)" << std::endl;
    }
    void procesarYReportar(vehiculo<T> listaAutos[], T1 cantidad) {
        std::cout << " Reporte de trafico y captura de infractores" << std::endl;
        std::cout << std::left << std::setw(6) << "ID" << std::setw(12) << "PLACA" << std::setw(10) << "VELOCIDAD" << "ESTADO\n";
        std::cout << std::endl;

        for (T1 i = 0; i < cantidad; ++i) {
        listaAutos[i].mostrarFilaReporte(limite);
    }
    std::cout << std::endl;
  }
}; 

void generarArchivoTrafico() {
    std::ofstream archivo("trafico.txt");
    if (archivo.is_open()) {
        archivo << "4\n";
        archivo << "1 100.0 4.0 ABC1234\n";
        archivo << "2 150.0 3.0 XYZ5678\n";
        archivo << "3 120.0 5.0 DEF9012\n";
        archivo << "4 200.0 2.0 GHI3456\n";
        archivo.close();
        std::cout<<"[Disco] Archivo 'trafico.txt' generado correctamente."<<std::endl;
    } else {
        std::cout<< "[Error] No se pudo generar el archivo 'trafico.txt'." << std::endl;
    }   
}
template <typename T>
void ejecutarFlujoSimulacion(T2 limiteVelocidadLegal) {
    std::cout << "\n>>> [Modulo Control] Iniciando orquestacion de componentes <<<\n";

    generarArchivoTrafico();

    T1 cantidadDetectados = 0;
    vehiculo<T> loteVehiculos[max_vehiculos];
    vehiculo<T>* ptrLote = loteVehiculos;

    std::cout << "[Modulo Control] Leyendo flujo desde 'trafico.txt'...\n";
    ptrLote->capturarTraficoSimulado(loteVehiculos, &cantidadDetectados);
    std::cout << "[Modulo Control] Sincronizacion exitosa. Vehiculos detectados: " << cantidadDetectados << "\n";
    std::cout << "[Modulo Control] Delegando ordenamiento al algoritmo Bubble Sort...\n";
    ordenarVehiculosPorVelocidad(ptrLote, cantidadDetectados);
    SistemaMonitoreo<T> monitor(limiteVelocidadLegal);
        monitor.procesarYReportar(ptrLote, cantidadDetectados);
    
    std::cout << ">>> [Modulo Control] Flujo finalizado correctamente. Liberando recursos <<<\n";
}

bool verificarIntegridadDelRadar() {
    std::cout << "[Hardware] Realizando test de estres en los sensores de barrido...\n";
    std::ifstream prueba("trafico.txt");
    if (!prueba.good()) {
        std::cerr << "[CRITICAL] Fallo de hardware: El sensor fisico no responde.\n";
        return false;
    }
    prueba.close();
    std::cout << "[Hardware] Canal I/O operativo. Sensor calibrado al 100%.\n";
    return true;
}

void despacharSistemaMonitoreo() {
    std::cout << "========================================================\n";
    std::cout << "  SISTEMA AUTOMATIZADO DE SEGURIDAD VIAL UNI-CC112\n";
    std::cout << "========================================================\n";

    generarArchivoTrafico();

    if (verificarIntegridadDelRadar()) {
        ejecutarFlujoSimulacion<double>(30.0);
    } else {
        std::cerr << "[Core] Abortando secuencia por falla en infraestructura.\n";
    }

    std::cout << "\n[Estatus] Saliendo del subproceso de monitoreo de manera limpia.\n";
}
int main() {
    despacharSistemaMonitoreo();
    return 0;
}