#include "headers/parser.h"

matriz_coo parseToCoo(char* path){
    std::map<int, std::map<int,double>> res;
    std::map<int,double> f1;
    
    
    FILE* file = fopen(path, "r");

    if(file == NULL){
        printf("El archivo %s no existe. \n", path);
        exit(1);
    } else {

        fscanf(file, "%i", &N); //leer N
        fscanf(file, "%i", &M); //leer M

        for(int s = 0; s < M*2; s+= 2){
            
            int i; // la i del par
            int j; // la j del par
            fscanf(file, "%i", &i); 
            fscanf(file, "%i", &j);

            std::map<int,std::map<int,double>>::iterator itfila=res.find(j); //veo si en la estructura ya esta la fila j 
            
            if(itfila != res.end()){ //si ya está la fila en el dicc, solo falta agregar el par con (i, 1) en el dicc adentro de la fila j
                std::pair<int,double> t;
                t.first = i;
                t.second = 1.0;
                (itfila->second).insert(t); 

            } else {  // si no está la fila en el dicc, tengo que armar el diccionario interior y el par a agregar en el dicc exterior
                std::pair<int, std::map<int, double>> t2;
                std::map<int, double> aAgregarinterior;
                aAgregarinterior.insert({i, 1.0});
                t2.first = j;
                t2.second = aAgregarinterior;
                res.insert(t2);
                
            }
        }
    return matriz_coo(N, M, res);
    }
}

int parse(char* path){
    
    FILE* file = fopen(path, "r");
    
    if(file == NULL){
        printf("El archivo %s no existe. \n", path);
        exit(1);
    } else {

        fscanf(file, "%i", &N); //leer N
        fscanf(file, "%i", &M); //leer M

        links = new int[2*M];

        for (unsigned int i = 0; i < 2*M; i+=2) {
            fscanf(file, "%i", &links[i]); //leer primera linea
            fscanf(file, "%i", &links[i+1]); //leer 2 primera linea
        }
        
        fclose(file);
    }

    printf("N = %d \n", N);
    printf("M = %d \n", M);
  
    /*for (unsigned int i = 0; i < 2*M; i+=2) {
    
        printf("Link de %d -> ", links[i]);
        printf("Hacia %d \n", links[i+1]);
    }*/
    return 1;

}

/*

archivo entrada: 
En la primera lı́nea un entero N: la cantidad total de páginas. 
En la segunda lı́nea un entero M: la cantidad total de links.

Luego siguen M lı́neas, cada una con dos enteros i j separados por un
espacio (1 ≤ i, j ≤ N ), indicando que hay un link de la página i a la
página j.

archivo de salida: La primera lı́nea deberá contener el valor de p utilizado.
Luego, deberán seguir N lı́neas, donde la lı́nea i contiene el valor del
ranking de Page para la página i.


*/