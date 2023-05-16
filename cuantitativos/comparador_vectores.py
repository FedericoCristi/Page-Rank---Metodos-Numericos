from ast import arg
from operator import truediv

import sys
import numpy as np

arg_path_1 = ""
arg_path_2 = ""

def parse():
    if len(sys.argv) != 3:
        print("Necesito argumentos:")
        print("1. input path comparar 1")
        print("2. input path comparar 2")
        sys.exit()

    arg_path_1 = sys.argv[1]
    arg_path_2 = sys.argv[2]

    file_1 = open(arg_path_1, 'r')
    contenidos_1 = []
    contenidos_1 = file_1.readlines()

    dimension = (len(contenidos_1)-7, 1)
    vec1 = np.zeros(dimension)
    for elem in range(7, len(contenidos_1)):
        vec1[elem-7] = float(contenidos_1[elem])
    file_1.close()


    file_2 = open(arg_path_2, 'r')
    contenidos_2 = []
    contenidos_2 = file_2.readlines()

    dimension = (len(contenidos_2)-7, 1)
    vec2 = np.zeros(dimension)
    for elem in range(7, len(contenidos_2)):
        vec2[elem-7] = float(contenidos_2[elem])
    file_2.close()

    return (vec1, vec2)

cont = parse()

vec1 = cont[0]
vec2 = cont[1]
vec3 = np.zeros(((vec1).shape))

#print(vec3)

for i in range(0, len(vec1)):
    #vec3[i] = vec1[i] - vec2[i]
    vec3[i][0] = vec1[i][0] - vec2[i][0]
    
error = 0
suma = 0

for i in vec3:
    suma = suma + i[0] * i[0]

norma = np.sqrt(suma)

print("norma = ")
print(norma)