
import numpy as np
import scipy
import scipy.linalg

n = int(input('Poner tamaño: '))

a = np.zeros((n,n))

x = np.zeros(n)

# Reading augmented matrix coefficients
print('Coeficientes:')
for i in range(n):
    for j in range(n+1):
        a[i][j] = double(input( 'a['+str(i)+']['+ str(j)+']='))

P, L, U = scipy.linalg.lu(a)

print(P)

print(L)

print(U)