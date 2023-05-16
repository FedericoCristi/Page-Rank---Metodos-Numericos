OUT= tp1
INC=-I /headers

main: main.cpp matriz_coo.cpp matriz_csr.cpp parser.cpp eliminacion_gaussiana.cpp writer.cpp
	g++ $^ $(INC) -o $(OUT) 

clean:
	rm -f *.o
	rm -f *.out
	rm -f $(OUT)