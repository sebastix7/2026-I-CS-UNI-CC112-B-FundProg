#ifndef __TYPES_H__
#define __TYPES_H__
#include <string>

using T1 = int; // contador y posiciones   
using T2 = float; // velocidad, tiempo y posiciones
using SUT1 = int;
using UUT1 = unsigned int; 

#define __UNIFIED__   //enciendo
#if defined(__UNIFIED__) // esta encendido?
    using UT1 = UUT1; // sin signo
#else //si esta apagado
    using UT1 = SUT1;   // con signo
#endif
using STR = std::string; // para cadenas de texto (placas)
using TP = int;          // códigos de control o peaje

#endif 