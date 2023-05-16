from ast import arg
from operator import truediv

import sys
import numpy as np

import eliminacion_gauss

arg_path = ""
arg_p = 0
N = 0
M = 0

def parse():
    if len(sys.argv) != 3:
        print("Necesito argumentos:")
        print("1. input path")
        print("2. p")
        sys.exit()

    global arg_path
    arg_path = sys.argv[1]
    global arg_p
    arg_p = float(sys.argv[2])

    file = open(arg_path, 'r')
    global N
    N = int(file.readline())  #paginas
    global M
    M = int(file.readline())  #links

    dimensiones = (N,N)
    W = np.zeros(dimensiones)

    link = 0
    leyendoA = True
    leyendoB = False

    while link < M:
        line = file.readline()
        pag_i = ""
        pag_j = ""

        for char in line:

            if leyendoA:
                pag_i+=char
            elif leyendoB:
                if char != '\n':
                    pag_j+=char

            if char == ' ':
                leyendoA = False
                leyendoB = True
            elif char == '\n':
                leyendoA = True
                leyendoB = False

        W[int(pag_j)-1][int(pag_i)-1] = 1
        link += 1
    file.close()

    return W

def write_output(res):
    file = open(arg_path+"_py_output_p_"+str(arg_p)+".txt", 'w')

    file.write(str(arg_p)+"\n")

    for elem in res:
        file.write(str(elem[0])+"\n")

    file.close()

W = parse()
print("W parseada: ")
print(W)
print("")

dimensiones = (N,N)
D = np.zeros(dimensiones)

for col in range(N):
    sum = 0
    for fila in range(N):
        if W[fila][col] == 1:
            sum += 1

    if sum != 0:
        D[col][col] = 1/sum
    else:
        D[col][col] = 0


#print("D: ")
#print(D)
#print("")

WD = np.matmul(W, D)

#print("WD: ")
#print(WD)
#print("")

pWD = arg_p * WD
#print("pWD: ")
#print(pWD)
#print("")

I = np.eye(N)
I_menos_pWD = I - pWD
#print("I - pWD: ")
#print(I_menos_pWD)
#print("")

ampliada = np.lib.pad(I_menos_pWD, ((0,0),(0,1)), 'constant', constant_values=(1))
print("ampliada: ")
print(ampliada)
print("")

ampliada_post_gauss = eliminacion_gauss.eliminacionGauss(ampliada)
print("ampliada pos gauss: ")
print(ampliada_post_gauss)
print("")

res = eliminacion_gauss.vector_res(ampliada_post_gauss)
print("res: ")
print(res)
print("")

res_norm = eliminacion_gauss.normalizar_vec(res)
print("res_norm: ")
print(res_norm)
print("")

e = np.ones((N,1))
print("e: ")
print(e)
print("")

z_t = np.zeros((1,N))
for col in range(N):
    sum = 0
    for fila in range(N):
        if W[fila][col] == 1:
            sum += 1

    if sum != 0:
        z_t[0][col] = (1-arg_p)/N
    else:
        z_t[0][col] = 1/N
print("z_t: ")
print(z_t)
print("")

ez_t = np.matmul(e,z_t)
print("ez_t: ")
print(ez_t)
print("")

A = pWD + ez_t
print("A: ")
print(A)
print("")

x_res_numpy = np.linalg.solve(A, res_norm)
print("X resuelto por nummpy: ")
print(x_res_numpy)
print("")

Ax = np.matmul(A, x_res_numpy)
print("Ax: ")
print(Ax)
print("")

Ax_menos_x = Ax - x_res_numpy
print("Ax-x: ")
print(Ax_menos_x)
print("")

print("|Ax-x| = ", np.sqrt(np.sum(Ax_menos_x**2)))

write_output(x_res_numpy)