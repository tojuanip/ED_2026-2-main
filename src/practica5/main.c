#include <stdio.h>
#include <stdlib.h>
#include <iostring.h>
#include <arbol.h>
#include <Nodo.h>

int *crearEntero(int);
void imprimir(void*);
int comparar(void*, void*);

int main(void)
{
	int num, numIns, opc = 0;
	int *existe = NULL;
	
	Nodoa *raiz = crearNodoa(crearEntero(8));

	raiz->izq = crearNodoa(crearEntero(7));
	raiz->izq->izq = crearNodoa(crearEntero(6));
	raiz->izq->izq->izq = crearNodoa(crearEntero(4));
	raiz->izq->izq->izq->izq = crearNodoa(crearEntero(1));
	raiz->izq->izq->izq->dch = crearNodoa(crearEntero(5));
	
	raiz->dch = crearNodoa(crearEntero(10));
	raiz->dch->izq = crearNodoa(crearEntero(9));
	raiz->dch->dch = crearNodoa(crearEntero(11));
	
	Arbol arbol;
	arbol.raiz = raiz;
	arbol.cant = 9;
	arbol.comparar = comparar;
	arbol.orden = ASC;

	printf("\n Altura %lld", (long long)altura(arbol));
	printf("\n Altura %lld", (long long)alturaI(arbol));
	printf("\n PREORDEN");
	imprimirOrden(arbol, imprimir, PREORDEN);
	printf("\n ORDEN");
	imprimirOrden(arbol, imprimir, ORDEN);
	printf("\n POSTORDEN");
	imprimirOrden(arbol, imprimir, POSTORDEN);
	
	do
	{	
		printf("\n\n 1. Insertar");
		printf("\n 2. Buscar");
		printf("\n 3. Flip");
		printf("\n 4. Borrar");
		printf("\n 5. Equilibrar");
		printf("\n 6. Imprimir");
		printf("\n 0. Salir");
		printf("\nSeleccione: ");
		scanf("%d", &opc);
		switch(opc)
		{
			case 1:
				printf("\n\n Insertar el: ");
				scanf("%d", &numIns);
				printf("\n Antes:\n");
				imprimirArbol(arbol, imprimir);
				insertarArbolO(&arbol, crearEntero(numIns));
				printf("\n\n Despues:\n");
				imprimirArbol(arbol, imprimir);
				break;
			
			case 2:
				printf("\n\n Ingresa lo que quieres buscar: ");
				scanf("%d", &num);
				existe = (int*)buscarArbol(&arbol, &num);
				if (existe)
					printf(" Si existe");
				else
					printf(" No existe");
				break;
			
			case 3:
				printf("\n\nnormal:\n");
				imprimirArbol(arbol, imprimir);
				flipArbol(&arbol);
				printf("\n\nflip:\n");
				imprimirArbol(arbol, imprimir);
				break;
				
			case 4:
				printf("\n\n Eliminar el: ");
				scanf("%d", &num);
				printf("\n Antes:\n");
				imprimirArbol(arbol, imprimir);
				if (eliminarArbol(&arbol, &num))
				{
					printf("\n\n Elemento eliminado:\n");
					imprimirArbol(arbol, imprimir);
				}
				else
				{
					printf("\n\n no esta el elemento");
				}
				break;
				
			case 5:
				printf("\n Antes de equilibrar:\n");
				imprimirArbol(arbol, imprimir);
				equilibrarArbol(&arbol);
				printf("\n Despues de equilibrar:\n");
				imprimirArbol(arbol, imprimir);
				break;
				
			case 6:
				imprimirArbol(arbol, imprimir);
				break;
				
			case 0:
				printf("\n\n FIN DE PROGRAMA\n\n");
				break;
		}
	} while (opc != 0);	
	
	return 0;
}

int *crearEntero(int num)
{
	int *dato = calloc(1, sizeof(int));
	*dato = num;
	return dato;
}


void imprimir(void *dato)
{
	printf("%d ", *(int*)dato);
}

int comparar(void *a, void *b)
{
	int valA = *(int*)a;
	int valB = *(int*)b;
	
	if (valA < valB)
		return -1;
	else if (valA > valB)
		return 1;
	return 0;
}
