#include <stdio.h>
#include <stdlib.h>
#include "t1.h"

/* Funcion que calcula el duplicado mas largo que aparece al final de x
La logica es la siguiente:
Se tomaran secuencias s de largo ls = 1, 2, ..., 32, para eso, se
consideraran los 2 * ls ultimos bits, esperando que sea una secuencia duplicada ss,
al realizar shift a la derecha en ls bits, se consigue la secuencia s, y para verificar
que efectivamente es una secuencia duplicada, se debe cumplir que la suma al realizar
shifteo izq y shifteo der debe ser igual al primer numero calculado.
Para retornar lo pedido, el valor del largo de s debe estar shifteado a la izq en 32 bits
y la secuencia s se le debe sumar a lo anterior. */
unsigned long long dupMasLargo(unsigned long long x) {
    unsigned long long ss;
    unsigned long long s;
    unsigned long long num;
    unsigned long long max_largo = 0;

    for (int largo = 1; largo <= 32; largo++) {
        ss = (x << (64 - (largo << 1))) >> (64 - (largo << 1)); // Secuencia que se espera duplicada ss
        s = ss >> largo; // Secuencia s
        num = s << largo; 
        if (num + s == ss) { // Si ocurre esto se encontro una secuencia duplicada
            max_largo = largo;
        }
    }
    
    ss = (x << (64 - (max_largo << 1))) >> (64 - (max_largo << 1));
    return max_largo != 0 ? (max_largo << 32) + (ss >> max_largo) : 0;
}