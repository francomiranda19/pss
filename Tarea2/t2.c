#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t2.h"

void reducir(char *s) {
    char *p1 = s;
    char *p2 = s + 1;

    if (*s) {
        while (*p2) {
            if (*p1 != ' ' || *p2 != ' ') {
                p1++;
                *p1 = *p2;
            }
        p2++;
        }
        p1++;
        *p1 = *p2;
    }
}

char *reduccion(char *s) {
    char *p1 = s;  
    char *p2 = s;
    int largo = 1;
    
    while (*p1) {
        if (*p1 == ' ' && *p2 == ' ') {
            p2++;
        } else if (*p1 != ' ' && *p2 != ' ') {
            largo++;
            p1++;
            p2++;
        } else {
            largo++;
            p1 = p2;
        }
    }

    char *r = malloc(largo * sizeof(char));
    char *p = r;
    p1 = s;
    p2 = s;

    while (*p1) {
        if (*p1 == ' ' && *p2 == ' ') {
            p2++;
        } else if (*p1 != ' ' && *p2 != ' ') {
            *p = *p1;
            p++;
            p1++;
            p2++;
        } else {
            *p = *p1;
            p++;
            p1 = p2;
        }
    }
    *p = 0;
    return r;
}