#ifndef __WRITER_H__
#define __WRITER_H__

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>

extern char* filePath;
extern double P;

void writer(char* path, std::vector<double> res);


#endif