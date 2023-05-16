#include "headers/writer.h"

void writer(char* path, std::vector<double> res){

    strcat(filePath, ".out");
    char output_path[] = "output.txt";
    FILE* output = fopen(filePath, "w");

    if(output == NULL){
        printf("No se pudo crear output en %s . \n", output_path);
        exit(1);
    } else {

        fprintf(output, "%g\n", P);
        for (int i = 0; i < res.size(); i++)
        {
            fprintf(output, "%g\n", res[i]);
        }
        
        fclose(output);
    }

}