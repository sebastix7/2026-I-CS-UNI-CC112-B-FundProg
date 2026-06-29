#ifndef RADAR_H
#define RADAR_H
#include "types1.h"
#include <cstddef> //Para el size_t
#include <fstream> // Para el ifstream

//Suponemos que el hardware tiene un alcance de 50 metros 
//Por ende en un carril tiene como capacidad máxima de 12 vehículos
const T1 max_vehiculos = 10;

//Creamos un struct
//Usamos templates para variar los valores de la velocidad si queremos que sea mas exacto usamos double y sino un float
template <typename T>
struct vehiculo {
    private:
        T1 id;
        T velocidadActual;
        char placa[8];
    
    public:
        //Constructor
        vehiculo() {
            id = 0;
            velocidadActual = 0.0f;
            placa[0] = '\0';
        }

        void llenarDatos(T1 m_id, T m_velocidad, const char* m_placa){
            id = m_id;
            velocidadActual = m_velocidad;
            for(size_t i = 0; i < 7; i++){
                *(placa + i) = m_placa[i];
            }
            *(placa + 7) = '\0';
        }

        //Declaramos las funciones
        //Nos acordamos que la formula para calcular la velocidad es variación de la posición sobre la variación del tiempo
        void calcularVelocidad(const T* deltaX, const T* deltaT, T* velocidadResultado);
        void capturarTraficoSimulado(vehiculo<T> listaAutos[], T1* cantidadDetectados);
};

//Definimos las funciones
//Calculamos la velocidad de cada vehículo
template <typename T>
void vehiculo<T>::calcularVelocidad(const T* deltaX, const T* deltaT, T* velocidadResultado){
    if(deltaT != nullptr && *deltaT > 0.0f){ //el denominador no debe ser 0, por teoria
        *velocidadResultado = (*deltaX)/(*deltaT);
    }
    else{
        *velocidadResultado = 0;
    }
}

//Al no tener un sensor para saber la distancia y tiempo recorrido de los autos 
//Hacemos que esta función lea un archivo el cual ya contiene los datos de cada auto
template <typename T>
void vehiculo<T>:: capturarTraficoSimulado(vehiculo<T> listaAutos[], T1* cantidadDetectados){
    //Inicializamos
    *cantidadDetectados = 0;

    //Abrimos el archivo de texto
    std::ifstream archivo("trafico.txt");

    //Nos fijamos si el archivo existe
    if(!archivo.is_open()){
        return;
    }

    //Inicializamos el contador del total de autos en el archivo
    T1 totalAutosEnArchivo = 0;
    archivo >> totalAutosEnArchivo; //Leemos la primera linea

    //Creamos variables para absorver los datos de cada fila
    T1 temp_id;
    T temp_dX;
    T temp_dT;
    char temp_placa[8];
    T velocidadCalculada;

    //Creamos un bucle para leer cada fila
    while(*cantidadDetectados < max_vehiculos && *cantidadDetectados < totalAutosEnArchivo){
        //Leemos 
        //Usamos el if como seguridad para fijarnos si aun se pueden leer valores
        if(archivo >> temp_id >> temp_dX >> temp_dT >> temp_placa){
            //Calculamos la velocidad del auto
            calcularVelocidad(&temp_dX, &temp_dT, &velocidadCalculada);

            //Guardamos los datos
            listaAutos[*cantidadDetectados].llenarDatos(temp_id, velocidadCalculada, temp_placa);

            //Incrementamos
            (*cantidadDetectados)++;
        }
        
        else{
            break;
        }
    }

    //Cerramos el archivpo
    archivo.close();
}

#endif 