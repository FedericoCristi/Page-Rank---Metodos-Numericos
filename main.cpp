#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>

#include "headers/definiciones.h"
#include "headers/parser.h"
#include "headers/matriz_coo.h"
#include "headers/matriz_csr.h"
#include "headers/eliminacion_gaussiana.h"
#include "headers/writer.h"

int N;
int M;
int* links;
double P;
char* filePath;
bool debug = false;

void tests();

int main(int argc, char** argv){

    char* p_param;

    //Son 3 parametros, "./programa" "archivo" "p"
    if(argc != 3){  
        printf("Quiero 2 parametros:\n1. path\n2. p\n");
        exit(1);
    } else {
        filePath = argv[1];
        p_param = argv[2];
    }

    //pasar "p" de string a int
    P = atof(p_param);
    
    //entrada
    matriz_coo W_coo = parseToCoo(filePath);                        //nxn
    matriz_csr W_csr = W_coo.convert_coo_to_csr(); 
    
    //armo D:   (D es diagonal, podemos aprovechar eso y usar un vector antes q una matriz)
   /*
    matriz_coo D_coo(W_coo.cant_filas(), W_coo.cant_columnas());    //nxn
    for (int j = 1; j <= D_coo.cant_filas(); j++){
        int grado_j = W_coo.calcularGrado(j);
        if(grado_j != 0){
            double djj = 1/(double)grado_j;
            D_coo.set(j,j, djj);
        }
    }
    */
    
    //armo D:
    std::vector<double> D((W_coo.cant_columnas()), 0);    //nxn
    for (int j = 1; j <= W_coo.cant_filas(); j++){
        int grado_j = W_coo.calcularGrado(j);
        if(grado_j != 0){
            double djj = 1/(double)grado_j;
            D[j-1] = djj;
        }
    }

    matriz_csr WD_csr = W_csr.mult_d(D);
    matriz_csr pWD_csr = WD_csr.mult_por_escalar(P);
    matriz_csr I = matriz_csr(W_coo.cant_filas());
    matriz_csr I_menos_pWD_csr = I.restar(&pWD_csr);
    matriz_vectores_t I_menos_pWD_matriz_vectores = I_menos_pWD_csr.csr_a_matriz_vectores();
    
    int sizeVector = I_menos_pWD_matriz_vectores.size();
    std::vector<double> vB = std::vector<double>(sizeVector, 1); //vector B

    matriz_vectores_t elim_gauss_I_menos_pWD_matriz = eliminacionGauss(I_menos_pWD_matriz_vectores, vB);
    
    std::vector<double> res_I_menos_pWD_matriz = resolverSistema(elim_gauss_I_menos_pWD_matriz);
    normalizarVector(res_I_menos_pWD_matriz);

    matriz_coo e = matriz_coo(N, 1);
    for (size_t i = 1; i <= e.cant_filas(); i++){
        e.set(i, 1, 1);
    }
    
    matriz_coo z_t = matriz_coo(1, N);
    for (size_t j = 1; j <= N; j++)
    {
        int c_grado = W_coo.calcularGrado(j);
        if(c_grado != 0){
            z_t.set(1, j, (1-P)/(double)N);
        } else {
            z_t.set(1, j , 1/(double)N);
        }
    }

    //e y z traspuesta
    matriz_csr e_csr = e.convert_coo_to_csr();
    matriz_csr z_t_csr = z_t.convert_coo_to_csr();
    //e*z  y  calculo  -e*z para sumar despues
    matriz_csr ez_t_csr = e_csr.multiplicar_por(&z_t_csr);
    matriz_csr menos_ez_t_csr = ez_t_csr.mult_por_escalar(-1);   
    //A= pWD--e*z
    matriz_csr A_csr = pWD_csr.restar(&menos_ez_t_csr);
    //Res es un vector --> lo paso a coo --> lo paso a csr
    matriz_coo res_coo = matriz_coo(N, 1);
    for (size_t i = 0; i < N; i++){
        res_coo.set(i+1, 1, res_I_menos_pWD_matriz[i]);
    }
    matriz_csr res_csr = res_coo.convert_coo_to_csr();
    //Ax
    matriz_csr Ax_csr = A_csr.multiplicar_por(&res_csr);
    matriz_csr Ax_menos_x = Ax_csr.restar(&res_csr);

    double error = Ax_menos_x.dist_al_origen();

    //tests();

    if(debug){
        //prueba que imprime la COO 
        
        printf("\n");
        printf("W coo parseada:\n");
        W_coo.imprimir_debug();

        printf("\n");
        printf("W coo convertida a CSR:\n");
        W_csr.imprimir_debug();

        //printf("\n");
        //printf("D coo:\n");
        //D_coo.imprimir_debug();

        //printf("\n");
        //printf("D csr:\n");
        //D_csr.imprimir_debug();

        printf("\n");
        printf("WD csr:\n");
        WD_csr.imprimir_debug();

        printf("\n");
        printf("P = %f \n", P);

        printf("\n");
        printf("pWD csr:\n");
        pWD_csr.imprimir_debug();

        printf("\n");
        printf("I csr:\n");
        I.imprimir_debug();
        
        printf("\n");
        printf("I-pWD csr:\n");
        I_menos_pWD_csr.imprimir_debug();

        printf("\n");
        printf("I-pWD matriz de vectores \n");
        imprimir_matriz_vectores(I_menos_pWD_matriz_vectores);

        printf("\n");
        printf("ElimGauss --> I-pWD \n");
        imprimir_matriz_vectores(elim_gauss_I_menos_pWD_matriz); 

        printf("\n RES: Vector Normalizado: \n");
        printf("[ ");
        for (int i =0;i< res_I_menos_pWD_matriz.size();i++){
            printf("%f", res_I_menos_pWD_matriz[i]);
            if (i != res_I_menos_pWD_matriz.size()-1){
                    printf(", ");
            }
        }    
        printf(" ]\n");

        printf("\n");
        printf("e coo:\n");
        e.imprimir_debug();

        printf("\n");
        printf("zt coo:\n");
        z_t.imprimir_debug();

        printf("\n");
        printf("e por zt:\n");
        ez_t_csr.imprimir_debug();

        printf("\n");
        printf("res coo:\n");
        res_coo.imprimir_debug();

        printf("\n");
        printf("Ax:\n");
        Ax_csr.imprimir_debug();

        printf("\n");
        printf("x:\n");
        res_csr.imprimir_debug();

        printf("\n");
        printf("Ax-x:\n");
        Ax_menos_x.imprimir_debug();


        //imprimir_matriz_vectores(AVec);

    }

    printf("\n");
    printf("Error absoluto |Ax-x|: %.17g\n", error);


    //escribimos el output
    writer(filePath, res_I_menos_pWD_matriz);

    delete[] links;

    return 0;
}

void tests(){
    printf("\n======= Empiezan los tests =======:\n");
    
    matriz_csr I = matriz_csr(3);
    matriz_csr I_escalada = I.mult_por_escalar(4.56);
    printf("\nI*4.56:\n");
    I_escalada.imprimir_debug();

    matriz_csr I_multiplicada = I.multiplicar_por(&I);
    printf("\nI*I:\n");
    I_multiplicada.imprimir_debug();

    matriz_csr I_por_I_escalada = I.multiplicar_por(&I_escalada);
    printf("\nI * 4.56I:\n");
    I_por_I_escalada.imprimir_debug();

    matriz_coo A = matriz_coo(3, 3);
    A.set(1,1,1);
    A.set(1,2,-2);
    A.set(1,3,-3);

    A.set(2,1,0);
    A.set(2,2,2);
    A.set(2,3,-3);
    
    A.set(3,1,0);
    A.set(3,2,0);
    A.set(3,3,3);
    
    matriz_coo B = matriz_coo(3, 3);
    B.set(1,1,5);
    B.set(1,2,0);
    B.set(1,3,0);

    B.set(2,1,4);
    B.set(2,2,-3);
    B.set(2,3,0);
    
    B.set(3,1,-2);
    B.set(3,2,1);
    B.set(3,3,5);
    
    matriz_csr A_csr = A.convert_coo_to_csr();
    matriz_csr B_csr = B.convert_coo_to_csr();
    matriz_csr A_por_B = A_csr.multiplicar_por(&B_csr);

    printf("\nA:\n");
    A_csr.imprimir_debug();

    printf("\nB:\n");
    B_csr.imprimir_debug();

    printf("\nA * B:\n");
    A_por_B.imprimir_debug();

    printf("\nI - I:\n");
    matriz_csr I_menos_I = I.restar(&I);
    I_menos_I.imprimir_debug();

    printf("\n4.56 I - I:\n");
    matriz_csr I_menos_I_escalada1 = I_escalada.restar(&I);
    I_menos_I_escalada1.imprimir_debug();

    printf("\nI - 4.56 I:\n");
    matriz_csr I_menos_I_escalada2 = I.restar(&I_escalada);
    I_menos_I_escalada2.imprimir_debug();

    matriz_coo cinco_puntos = matriz_coo(5, 5);
    cinco_puntos.set(1,1,1);
    cinco_puntos.set(1,5,1);
    cinco_puntos.set(3,3,1);
    cinco_puntos.set(5,1,1);
    cinco_puntos.set(5,5,1);
    matriz_csr cinco_puntos_csr = cinco_puntos.convert_coo_to_csr();
    printf("\nMatriz de 5 puntos:\n");
    cinco_puntos_csr.imprimir_debug();

    //punto1
    matriz_coo punto_1 = matriz_coo(5, 5);
    punto_1.set(1,1,1);
    matriz_csr punto_1_csr = punto_1.convert_coo_to_csr();
    //punto2
    matriz_coo punto_2 = matriz_coo(5, 5);
    punto_2.set(1,5,1);
    matriz_csr punto_2_csr = punto_2.convert_coo_to_csr();
    //punto3
    matriz_coo punto_3 = matriz_coo(5, 5);
    punto_3.set(3,3,1);
    matriz_csr punto_3_csr = punto_3.convert_coo_to_csr();
    //punto4
    matriz_coo punto_4 = matriz_coo(5, 5);
    punto_4.set(5,1,1);
    matriz_csr punto_4_csr = punto_4.convert_coo_to_csr();
    //punto5
    matriz_coo punto_5 = matriz_coo(5, 5);
    punto_5.set(5,5,1);
    matriz_csr punto_5_csr = punto_5.convert_coo_to_csr();
    
    printf("\nRestando punto 1:\n");
    matriz_csr op1 = cinco_puntos_csr.restar(&punto_1_csr);
    op1.imprimir_debug();

    printf("\nRestando punto 1 de nuevo:\n");
    matriz_csr op2 = op1.restar(&punto_1_csr);
    op2.imprimir_debug();

    printf("\nSumando punto 2:\n");
    matriz_csr temp1 = punto_2_csr.mult_por_escalar(-1);
    matriz_csr op3 = op2.restar(&temp1);
    op3.imprimir_debug();

    printf("\nRestando punto 3:\n");
    matriz_csr op4 = op3.restar(&punto_3_csr);
    op4.imprimir_debug();

    printf("\nSumando punto 4:\n");
    matriz_csr temp2 = punto_4_csr.mult_por_escalar(-1);
    matriz_csr op5 = op4.restar(&temp2);
    op5.imprimir_debug();

    printf("\nRestando punto 5:\n");
    matriz_csr op6 = op5.restar(&punto_5_csr);
    op6.imprimir_debug();

    printf("\n======= Terminan los tests =======:\n");

}
