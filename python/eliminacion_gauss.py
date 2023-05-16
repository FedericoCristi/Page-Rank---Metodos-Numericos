# Importing NumPy Library
import numpy as np
#import copy

def eliminacionGauss(a):

    #print("Matriz original ")
    #print(a)

    # cant filas
    filas = len(a)
    cols = len(a[0])

    # registro de permutaciones de columna
    #p = np.zeros(n)

    #for i in range(n):
    #    p[i] = i

    #para cada fila
    for i in range(filas):

        # caso 0 en diagonal, permuto fila
        #if a[i][i] == 0.0:
        #    for j in range(i+1, len(a)):
        #        if a[j][i] != 0.0:
        #            m = copy.copy(a[i])
        #            a[i] = a[j]
        #            a[j] = m   
            
            # si no encuentro fila para permutar, permuto columna
        #    if a[i][i] == 0:
        #        for j in range(i, len(a)):
        #            if a[i][j] != 0.0:
        #                for k in range(j+1,n):
        #                    m = copy.copy(a[k][i])
        #                    a[k][i] = a[k][j]
        #                    a[k][j] = m

        #                    mp = copy.copy(p[i])
        #                    p[i] = p[j]
        #                    p[j] = mp

        #para cada fila debajo de la pivote
        for j in range(i+1, filas):
        
            ratio = a[j][i]/a[i][i]
            #print("Ratio j: ", ratio, " = ", a[j][i], " / ", a[i][i])
            #print("Resta = : ", ratio * a[i][i])
            
            for k in range(cols):
                a[j][k] = a[j][k] - ratio * a[i][k]

        #Matriz triangulada
        #print("Asi queda la matriz triangulada para fila i: ")
        #print(a)

    #print("Vector de permutaciones: ")
    #print(p)
    
    return a


def vector_res(a):
    cant_filas = len(a)
    cant_cols = len(a[0])-1 #le resto 1 ya que esta ampliada 

    dimension = (cant_filas, 1)

    res = np.zeros(dimension)

    for i in reversed(range(cant_filas)):   # i: n-1 --> 0
        res[i] = a[i][cant_filas]             #elemento i b


        cant = cant_cols-i
        for k in range(i+1, cant_filas, 1):
            res[i] = res[i] - a[i][k]*res[k]
        
        res[i]=res[i]/a[i][i]

    return res

def normalizar_vec(vec):
    suma = 0

    for i in range(len(vec)):
        suma = suma + vec[i]

    for i in range(len(vec)):
        vec[i] = vec[i] / suma

    return vec

# Reading number of unknowns
#n = int(input('Poner dimesnión de Matriz: '))
# Making numpy array of n x n+1 size and initializing 
# to zero for storing augmented matrix
#a = np.zeros((n,n))

# Reading augmented matrix coefficients
#print('Poner coeficientes: ')
#for i in range(n):
#    for j in range(n):
#        a[i][j] = double(input( 'a['+str(i)+']['+ str(j)+']='))


#eliminacionGauss(a)
