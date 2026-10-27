#ifndef ALUMNO_H
#define ALUMNO_H

typedef struct
{
	unsigned int matricula;
	char nombre[64];
	int semestres;
	float promedio;
} Alumno;

Alumno* crearAlumno(unsigned int matricula, const char* nombre, int semestres, float promedio);
void imprimirAlumno(void* dato);

// comparaciones
int compAlumMat(void* a, void* b);
int compAlumNom(void* a, void* b);
int compAlumSem(void* a, void* b);
int compAlumProm(void* a, void* b);

#endif