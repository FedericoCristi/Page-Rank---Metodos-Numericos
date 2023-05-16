from ast import arg
from operator import concat
import sys
import pandas as pd
import matplotlib.pyplot as plt

arg_path = ""

if len(sys.argv) != 2:
    print("Necesito 1 argumento: path")
    sys.exit()
    
arg_path = sys.argv[1]

data1 = pd.read_csv(arg_path+"_py_output_p_0.1.txt")
data2 = pd.read_csv(arg_path+"_py_output_p_0.2.txt")
data3 = pd.read_csv(arg_path+"_py_output_p_0.3.txt")
data4 = pd.read_csv(arg_path+"_py_output_p_0.4.txt")
data5 = pd.read_csv(arg_path+"_py_output_p_0.5.txt")
data6 = pd.read_csv(arg_path+"_py_output_p_0.6.txt")
data7 = pd.read_csv(arg_path+"_py_output_p_0.7.txt")
data8 = pd.read_csv(arg_path+"_py_output_p_0.8.txt")
data9 = pd.read_csv(arg_path+"_py_output_p_0.9.txt")

all_data = pd.concat([data1, data2,data3,data4,data5,data6,data7,data8,data9], axis=1)

print(all_data)

plt.plot(range(10), '.-', label="123")