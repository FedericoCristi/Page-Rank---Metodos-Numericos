Instrucciones:

Compilacion: make

Ejecucion:

    El programa "tp1" recibe 2 parametros
        1. el path del archivo de lectura   <arg_nombre_archivo.txt>
            L> las comillas para el path son opcionales, unicamente requeridas si el nombre del archivo de entrada tiene espacios.
        2. un valor P                       <arg_p>

    Una vez ejecutado, el programa printea en consola el error estimado |Ax-x|
    y tambien crea un archivo con el output llamado <arg_nombre_archivo.txt>.out

    Su ejecucion es la especificada por el instructivo de entrega
    ./tp1    nombre_archivo     valor_p

    ejemplos de uso:
        ./tp1       tests_catedra/test_aleatorio_desordenado.txt       0.76
            devuelve --->  tests_catedra/test_aleatorio_desordenado.txt.out

        ./tp1       "casos nuestros/caso1_linea.txt"       0.76
            devuelve --->  casos nuestros/caso1_linea.txt.out

Breve descripcion de organizacion del programa:

    casos nuestros: outputs de tests realizados por nosotros que siguen el formato "arg_nombre_archivo"+"_p"+valor_p.
        L>  simucasos: outputs de tests utilizados para simulaciones.

    inputs: entradas para nuestros tests.

    python: programa en python que resuelve sistemas y el jupiter notebook utilizado para la elaboracion del informe.