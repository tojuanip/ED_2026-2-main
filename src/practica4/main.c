#include <stdio.h>
#include <stdlib.h>
#include <Pila.h>
#include <iostring.h>
#include "Laberinto.h"
#include <windows.h>

Pila* resolverLab(Laberinto lab, Coordenada origen,Coordenada destino);

int main(void)
{
    Laberinto lab = crear_laberinto();
	Coordenada origen = {1,1}; 
	Coordenada destino = {25,24};
	unsigned int nuevasCoor = 0;	
	inputEnteroSinSigno("\n Nuevas coordenadas? (1:SI 0:NO) : ",&nuevasCoor);
	
	if(nuevasCoor)
	{
		inputEntero("\n Captura Origen X: ",&origen.x);
		inputEntero(" Captura Origen Y: ",&origen.y);
		inputEntero("\n Captura Destino X: ",&destino.x);
		inputEntero(" Captura Destino Y: ",&destino.y);
	}
	setOrigen(lab,origen);
	setDestino(lab,destino);	
	
	Pila *pila = resolverLab(lab,origen,destino);

	imprimirLab(lab);
	liberarLaberinto(lab);
	eliminarPila(pila,free);
	free(pila);
	
    printf("\n\n FIN DE PROGRAMA\n\n");
    return 0;
}


Pila* resolverLab(Laberinto lab, Coordenada origen, Coordenada destino)
{
    Pila *pila = crearPila();
    *pila = inicializarPila(-1);	
    
    //PUSH INICIAL DEL ORIGEN
    Coordenada *punto = crearCoordenada(origen.x, origen.y);
    push(pila, punto);	
    
    //CICLO PRINCIPAL
    while (!pilaVacia(*pila))
    {
		system("cls");
        imprimirLab(lab);		

        Coordenada *actual = (Coordenada*)peek(*pila);

        //Si la cima alcanza el destino, terminamos
        if (actual->x == destino.x && actual->y == destino.y)
        {
            printf("\n\n Ruta encontrada\n");
            break;
        }

        Movimientos mov = movimientosPosibles(lab, *actual);

        int coordx = actual->x;
        int coordy = actual->y;

        //DERECHA
        if (mov.right)
        {
            coordy++;
        }
		//IZQUIERDA
        else if (mov.left)
        {
            coordy--;
        }
		//ABAJO
        else if (mov.down)
        {
            coordx++;
        }
		//ARRIBA
        else if (mov.up)
        {
            coordx--;
        }
		
        if (coordx != actual->x || coordy != actual->y)
        {
            if (lab[coordx][coordy] != 'B')
            {
                lab[coordx][coordy] = '.';
            }
            push(pila, crearCoordenada(coordx, coordy));
        }
        else
        {
            Coordenada *basura = (Coordenada*)pop(pila);
            if (lab[basura->x][basura->y] != 'A' && lab[basura->x][basura->y] != 'B')
            {
                lab[basura->x][basura->y] = 'o';
            }
            free(basura);
        }
		
		Sleep(10);
    }

    return pila;
}


