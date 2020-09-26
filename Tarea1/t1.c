#include <stdio.h>
#include <stdlib.h>
#include "t1.h"

// ---------------------------------------------------------------------
// Funcion que calcula el duplicado mas largo que aparece al final de x
unsigned long long dupMasLargo(unsigned long long x) {
    unsigned long long ss;
    unsigned long long s;
    unsigned long long num;
    unsigned long long max_largo = 0;

    for (int largo = 1; largo <= 32; largo++) {
        ss = (x << (64 - (largo << 1))) >> (64 - (largo << 1));
        s = ss >> largo;
        num = s << largo; 
        if ((num | s) == ss) {
            max_largo = largo;
        }
    }
    
    ss = (x << (64 - (max_largo << 1))) >> (64 - (max_largo << 1));
    return max_largo != 0 ? (max_largo << 32) | (ss >> max_largo) : 0;
}