#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

struct Aspirasi {
    char nim[20];
    char keluhan[255];
    Aspirasi* next;
};
Aspirasi* headAspirasi = NULL;

struct Beasiswa {
    char nim[20];
    char nama[50];
    float ipk;
    int urgensi;
    Beasiswa* next;
};
Beasiswa* headBeasiswa = NULL;
Beasiswa* tailBeasiswa = NULL;






int main(int argc, char **argv)
{
	
	return 0;
}

