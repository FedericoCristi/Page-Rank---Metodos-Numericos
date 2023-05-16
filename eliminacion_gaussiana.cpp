//LEER PARA ENTENDER:
/*
la funcion eliminacionGauss_matriz() construye una matriz para usar en este archivo independientemente,
su función es testear la eliminacionGauss(matriz).
Implementar eliminacionGauss(matriz) de este archivo    
*/
#include "headers/eliminacion_gaussiana.h"

matriz_vectores_t eliminacionGauss(matriz_vectores_t a, std::vector<double> b){

    //tamaño
    int n = a.size();   //fila

    //para cada fila
    for (int i = 0; i < n; i++){
        //debug
        /*
        for(int h = 0; h < n; h++){
            std::cout<<a[i][h]<<" ";
        }*/
        //std::cout<<std::endl;

        //para todas las filas debajo de la fila i
        for (int j = i+1; j < n; j++){
            double ratio = a[j][i]/a[i][i];
            
            //para toda columna k de toda fila j debajo de i
            //esto funciona unicamente en matrices cuadradas
            for (int k = i; k < n; k++){
                a[j][k] = a[j][k] - (ratio * a[i][k]);
            }
            b[j] = b[j] - (ratio * b[i]);
        }
    }

    for(int i = 0; i < n; i++){
        a[i].push_back(b[i]);
    }
    //std::pair<std::vector<std::vector<double>>, std::vector<double>> res;
    //res.first = a;
    //res.second = b;
    //imprimir matriz
    
    return a;
}

std::vector<double> resolverSistema(matriz_vectores_t a){
    //cant filas
    int n = a.size();
    std::vector<double> res(a.size(),0);
    int i = n-1;

    //res[i] = a[i][n];
    //        printf("%f ", res[i]);               //make the variable to be calculated equal to the rhs of the last equation
    for (int i= n-1; i>=0;i--){                //back-substitution{                        //x is an array whose values correspond to the values of x,y,z..
        res[i]=a[i][n]; 
        for (int j=i+1;j<n;j++){
            //if (j!=i)            //then subtract all the lhs values except the coefficient of the variable whose value                                   is being calculated
            res[i]-= a[i][j]*res[j];
        }
        res[i]=res[i]/a[i][i];
    }

    return res;
}    
    /*std::vector<double> res;
    int n = a.first.size();
    for(int i = n-1; i < 0; i--){
        double A = a.second[i] / a.first[n-1][n-1];
    }
    double z = a.second[n-1] / a.first[n-1][n-1]; 
    double y =    .z/*
}



/*std::pair<std::vector<std::vector<double>>, std::vector<double>> eliminacionGauss_matriz(){
    //vector ejemplo
    //hay dos vectores a, no se cual se refiere a cual.

    std::vector<std::vector<double>> a (3, std::vector<double>(3,0));
    std::vector<double> b = {3,3,3};
    /*
    a = {{1,2,3},{1,4,2},{2,6,7}};

    //construir vector para testear
    int n;
    //cout << "poner dimensión: ";
    //cin >> n;
    vector<vector<double>> a (n, vector<double>(n,0));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout<<"a[" << i << "]["<< j << "]" << endl;
            cin>>a[i][j];
        }
    }
    return eliminacionGauss(a, b);
}*/

/*
int main(){
    eliminacionGauss_matriz();
    return 0;
}*/


void imprimir_matriz_vectores(matriz_vectores_t mat){

    for (int fila = 0; fila < mat.size(); fila++){
        
        printf("[ ");
        for (int col = 0; col < mat[fila].size(); col++){
            printf("%f", mat[fila][col]);
            if(col != mat[fila].size()-1){
                printf(", ");
            }

        }
        printf(" ]\n");
    }

   /* printf("Vector: \n");
    printf("[");

    for(int i = 0; i < p.second.size(); i++){
        printf("%f", p.second[i]);
        printf(",");
    }*/
    
    return;
}

void normalizarVector(std::vector<double> &v){
    double suma = 0;
    for(int i=0; i < v.size(); i++){
        suma = suma + v[i];
    }

    for(int i=0; i < v.size(); i++){
        v[i] = v[i]/suma;
    }

    return ;
}
