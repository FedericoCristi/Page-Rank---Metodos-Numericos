#ifndef __PARSER__
#define __PARSER__

#include <map>
#include <math.h>
#include "matriz_coo.h"

extern int M;
extern int N;
extern double P;
extern int* links;   

int parse(char* path);
matriz_coo parseToCoo(char* path);

#endif