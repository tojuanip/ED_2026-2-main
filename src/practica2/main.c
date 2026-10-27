#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iostring.h"
#include "ListaD.h"
#include "cancion.h"

void imprimirEstado(ListaD lista, Nodod *actual, int bucle);

int main(void)
{
	system("cls");
    int option, corre_programa, bucle, id_cancion, pos, pos_elim, idx, j;
    Canciones canciones;
    ListaD cola;
    Nodod *actual, *aux, *borrar;

    bucle = 0;
    canciones = cargarCanciones();
    cola = inicializarListaD();
    actual = NULL;
    corre_programa = 1;
    
    while(corre_programa)
    {
        imprimirEstado(cola, actual, bucle);
        printf("\n\r BUCLE ESTA: %s", bucle ? "ACTIVADO" : "DESACTIVADO");
        printf("\n\r");
        printf("\n\r [0] BUCLE");
        printf("\n\r [1] ANTERIOR");
        printf("\n\r [2] SIGUIENTE");
        printf("\n\r [3] AGREGAR CANCION");
        printf("\n\r [4] MOSTRAR LISTA DE REPRODUCCION");
        printf("\n\r [5] QUITAR CANCION");
        printf("\n\r [6] REINICIAR REPRODUCCION");
        printf("\n\r [7] TERMINAR PROGRAMA");

        printf("\n\r Escoge opcion: ");
        scanf("%d", &option);
        clear_buffer();
        
        switch(option)
        {
			case 0:
				bucle = !bucle;
				break;
				
			case 1:
				if (actual) 
				{
					if (actual->ant)
					{
						actual = actual->ant;
					}
					else if (bucle && cola.fin) 
					{
						actual = cola.fin;
					}
				}
				break;
				
			case 2:
				if (actual) 
				{
					if (actual->sig) actual = actual->sig;
					else if (bucle && cola.inicio) actual = cola.inicio;
				}
				break;
				
			case 3:
				imprimirCanciones(canciones);
				printf("\n\nIngrese el ID de la cancion a agregar: ");
				scanf("%d", &id_cancion);
				clear_buffer();
				
				if(id_cancion >= 0 && (size_t)id_cancion < canciones.cant) 
				{
					printf("Ingrese la posicion (0 a %lu): ", (unsigned long)cola.cant);
					scanf("%d", &pos);
					clear_buffer();
					
					if(pos >= 0 && (size_t)pos <= cola.cant) 
					{
						insertarPosicionD(&cola, &canciones.cancion[id_cancion], pos);
						if (!actual) actual = cola.inicio;
						printf("\nCancion agregada\n");
					} 
					else 
					{
						printf("\nPosicion no invalida\n");
					}
				} 
				else 
				{
					printf("\nID invalido\n");
				}
				break;
				
			case 4:
				if (cola.cant == 0) 
				{
					printf("\nLa lista de reproduccion esta vacia\n");
				} 
				else 
				{
					aux = cola.inicio;
					idx = 0;
					while(aux) 
					{
						printf("\n[%d] ", idx++);
						imprimirCancion(aux->dato);
						if(aux == actual)
						{
							printf("  <");
						}
						
						aux = aux->sig;
					}
					printf("\n");
				}
				break;
				
			case 5:
				if (cola.cant == 0) 
				{
					printf("\nNo hay canciones para quitar\n");
					break;
				}
				
				aux = cola.inicio;
				idx = 0;
				
				while(aux) 
				{
					printf("\n[%d] ", idx++);
					imprimirCancion(aux->dato);
					aux = aux->sig;
				}
				
				printf("\n\nIngrese el ID de la lista a eliminar: ");
				scanf("%d", &pos_elim);
				clear_buffer();
				
				if (pos_elim >= 0 && (size_t)pos_elim < cola.cant)
				{
					borrar = cola.inicio;
					for(j = 0; j < pos_elim; j++) borrar = borrar->sig;
					
					if (borrar == actual)
					{
						if (actual->sig)
						{
							actual = actual->sig;
						}
						else if (bucle && cola.cant > 1)
						{
							actual = cola.inicio;
						}
						else 
						{
							actual = actual->ant; 
						}
					}
					
					eliminarPosicionD(&cola, pos_elim);
					if (cola.cant == 0)
					{	
						actual = NULL;
					}
					
					printf("\nCancion eliminada\n");
				} 
				else 
				{
					printf("\nIndice noinvalido\n");
				}
				break;
				
			case 6:
				actual = cola.inicio;
				break;
				
			case 7:
				corre_programa = 0;
				break;
				
			default:
				printf("\nOpcion no valida\n");
				break;
		}
			
		printf("\n\nPresione enter para continuar...");
		getchar();
		system("cls");
    }
    
    printf("\n FIN DE PROGRAMA \n\r");
    return 0;
}



void imprimirEstado(ListaD lista, Nodod *actual, int bucle) 
{
    Cancion *can_act = NULL;
    Cancion *canod_ant = NULL;
    Cancion *canod_sig = NULL;
    Nodod *nod_ant = NULL;
    Nodod *nod_sig = NULL;

    if (!actual) 
	{
        printf("Ninguna <<-- Ninguna -->> Ninguna\n");
        return;
    }
    
    can_act = (Cancion*)actual->dato;
    nod_ant = actual->ant;
    nod_sig = actual->sig;

    if (!nod_ant && bucle) 
	{
		nod_ant = lista.fin;
	}
	
    if (!nod_sig && bucle)
	{
		nod_sig = lista.inicio;
	}
	

    if (nod_ant)
	{
		canod_ant = (Cancion*)nod_ant->dato;
	}
	
	if (nod_sig)
	{
		canod_sig = (Cancion*)nod_sig->dato;
	}

    printf("%s <<-- %s -->> %s\n",	canod_ant ? canod_ant->nombre : "Ninguna",
									can_act->nombre,
									canod_sig ? canod_sig->nombre : "Ninguna");
}