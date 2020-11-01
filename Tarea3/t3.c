#include <stdio.h>
#include <stdlib.h>
#include "t3.h"

void desbalancear(Nodo **pa, Nodo **pult) {
    Nodo *a = *pa;

    // Árbol vacío
    if (a == NULL) {
        *pult = NULL;
    }
    // Un solo nodo
    else if (a -> izq == NULL && a -> der == NULL) {
        *pult = a;
    }
    // Subárbol izquierdo vacío
    else if (a -> izq == NULL) {
        desbalancear(&a -> der, pult);
    }
    // Subárbol derecho vacío
    else if (a -> der == NULL) {
        Nodo *I = a -> izq;
        Nodo *UI;
        desbalancear(&I, &UI);
        UI -> der = a;
        a -> izq = NULL;
        *pa = I;
        *pult = a;
    }
    // Ningún subárbol vacío
    else {
        Nodo *I = a -> izq, *D = a -> der;
        Nodo *UI, *UD;
        desbalancear(&I, &UI);
        desbalancear(&D, &UD);
        UI -> der = a;
        a -> izq = NULL;
        a -> der = D;
        *pa = I;
        *pult = UD;
    }
}

Nodo *desbalanceado(Nodo *a, Nodo **pult) {
    Nodo *m = malloc(sizeof(Nodo));

    // Árbol vacío
    if (a == NULL) {
        *pult = NULL;
        m = NULL;
    }
    // Un solo nodo
    else if (a -> izq == NULL && a -> der == NULL) {
        Nodo n = { a -> id, a -> hash, NULL, NULL };
        *pult = m;
        *m = n;
    }
    // Subárbol izquierdo vacío
    else if (a -> izq == NULL) {
        Nodo n = { a -> id, a -> hash, NULL, desbalanceado(a -> der, pult) };
        *m = n;
    }
    // Subárbol derecho vacío
    else if (a -> der == NULL) {
        Nodo *UI;
        Nodo *I = desbalanceado(a -> izq, &UI);
        Nodo n = { a -> id, a -> hash, NULL, NULL };
        *m = n;
        UI -> der = m;
        *pult = m;
        m = I;
    }
    // Ningún subárbol vacío
    else {
        Nodo *UI, *UD;
        Nodo *I = desbalanceado(a -> izq, &UI), *D = desbalanceado(a -> der, &UD);
        Nodo n = { a -> id, a -> hash, NULL, D };
        *m = n;
        UI -> der = m;
        *pult = UD;
        m = I;
    }
    return m;
}