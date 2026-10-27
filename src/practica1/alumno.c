#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostring.h>
#include "alumno.h"

Alumno *crearAlumno(unsigned int matricula, const char* nombre, int semestres, float promedio)
{
	Alumno *nuevo = (Alumno*)calloc(1,sizeof(Alumno));
    
	if(nuevo)
    {
        nuevo->matricula = matricula;
        strncpy(nuevo->nombre, nombre, 63);
        nuevo->nombre[63] = '\0';
        nuevo->semestres = semestres;
        nuevo->promedio = promedio;
    }
	
    return nuevo;
}


void imprimirAlumno(void* dato)
{
    Alumno* a = (Alumno*)dato;
printf("\nMatricula: %u  |  Nombre: %s  |  Semestre: %d  |  Promedio %.2f", a->matricula, a->nombre, a->semestres, a->promedio);
}


int compAlumMat(void* a, void* b)
{
    Alumno* alA = (Alumno*)a;
    Alumno* alB = (Alumno*)b;
    if(alA->matricula > alB->matricula) return 1;
    else if(alA->matricula < alB->matricula) return -1;
    return 0;
}

int compAlumNom(void* a, void* b)
{
    Alumno* alA = (Alumno*)a;
    Alumno* alB = (Alumno*)b;
    return strcmpIC(alA->nombre, alB->nombre);
}

int compAlumSem(void* a, void* b)
{
    Alumno* alA = (Alumno*)a;
    Alumno* alB = (Alumno*)b;
    if(alA->semestres > alB->semestres) return 1;
    else if(alA->semestres < alB->semestres) return -1;
    return 0;
}

int compAlumProm(void* a, void* b)
{
    Alumno* alA = (Alumno*)a;
    Alumno* alB = (Alumno*)b;
    if(alA->promedio > alB->promedio) return 1;
    else if(alA->promedio < alB->promedio) return -1;
    return 0;
}