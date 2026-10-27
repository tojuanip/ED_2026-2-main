#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Cadena.h"
#include "Pila.h"

int esPalindromo(char *cadena)
{
    Pila pila;
    int i;
    int len;
    int esValido;
    char filtrada[100];
    char *caracterPila;

    pila = inicializarPila(-1);
    len = 0;
    esValido = 1;

    for (i = 0; cadena[i] != '\0'; i++)
    {
        filtrada[len] = (char)tolower((unsigned char)cadena[i]);
        push(&pila, (void *)&filtrada[len]);
        len++;
    }
    filtrada[len] = '\0';

    for (i = 0; i < len; i++)
    {
        caracterPila = (char *)pop(&pila);
        if (caracterPila == NULL || *caracterPila != filtrada[i])
        {
            esValido = 0;
            break;
        }
    }

    eliminarPila(&pila, NULL);
    return esValido;
}

int verificarParentesis(char *cadena)
{
    Pila pila;
    int i;
    int balanceado;
    char actual;
    char *apertura;

    pila = inicializarPila(-1);
    balanceado = 1;

    for (i = 0; cadena[i] != '\0'; i++)
    {
        actual = cadena[i];

        if (actual == '(' || actual == '[' || actual == '{')
        {
            push(&pila, (void *)&cadena[i]);
        }
        else if (actual == ')' || actual == ']' || actual == '}')
        {
            if (pilaVacia(pila))
            {
                balanceado = 0;
                break;
            }

            apertura = (char *)pop(&pila);

            if ((actual == ')' && *apertura != '(') ||
                (actual == ']' && *apertura != '[') ||
                (actual == '}' && *apertura != '{'))
            {
                balanceado = 0;
                break;
            }
        }
    }

    if (!pilaVacia(pila))
    {
        balanceado = 0;
    }

    eliminarPila(&pila, NULL);
    return balanceado;
}

void ordenarPila(char *cadena)
{
    Pila pila;
    Pila pilaAux;
    int i;
    int len;
    char *temp;
    char *topeAux;
    char *elem;

    pila = inicializarPila(-1);
    pilaAux = inicializarPila(-1);
    len = (int)strlen(cadena);

    for (i = len - 1; i >= 0; i--)
    {
        push(&pila, (void *)&cadena[i]);
    }

    while (!pilaVacia(pila))
    {
        temp = (char *)pop(&pila);

        while (!pilaVacia(pilaAux))
        {
            topeAux = (char *)peek(pilaAux);
            if (*topeAux > *temp)
            {
                push(&pila, pop(&pilaAux));
            }
            else
            {
                break;
            }
        }

        push(&pilaAux, (void *)temp);
    }

    while (!pilaVacia(pilaAux))
    {
        push(&pila, pop(&pilaAux));
    }

    printf("Resultado: cima");
    while (!pilaVacia(pila))
    {
        elem = (char *)pop(&pila);
        printf(" -> %c", *elem);
    }
    printf("\n");


}