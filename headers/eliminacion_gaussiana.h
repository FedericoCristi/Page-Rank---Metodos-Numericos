#ifndef __ELIM_GAUSS__
#define __ELIM_GAUSS__

#include <vector>
#include <iostream>
#include <math.h>
#include "definiciones.h"



matriz_vectores_t eliminacionGauss(matriz_vectores_t a, std::vector<double> b);
void imprimir_matriz_vectores(matriz_vectores_t a);
std::vector<double> resolverSistema(matriz_vectores_t a);
void normalizarVector(std::vector<double> &v);

#endif