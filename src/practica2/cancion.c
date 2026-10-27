#include "cancion.h"

Canciones cargarCanciones(void)
{
    static Cancion biblioteca[] = 
    {
        {"We Are Crystal Gems", "Rebecca Sugar", 2015},
        {"Stronger Than You", "Estelle", 2015},
        {"Its Over Isnt It", "Deedee Magno", 2016},
        {"Here Comes", "Estelle", 2016},
        {"Love Like You", "Rebecca Sugar", 2016},
        {"Other Friends", "Sarah Stiles", 2019},
        {"True Kinda Love", "Estelle", 2019},
        {"Drift Away", "Sarah Stiles", 2019},
        {"The Horse", "Jorge Rivera", 2022},
        {"Just a Man", "Jorge Rivera", 2022},
        {"Full Speed Ahead", "Jorge Rivera", 2022},
        {"Open Arms", "Jorge Rivera", 2022},
        {"Warrior of Mind", "Jorge Rivera", 2022},
        {"Monster", "Jorge Rivera", 2022},
        {"Ruthlessness", "Jorge Rivera", 2022}
    };	
    static Canciones canciones;
    canciones.cancion = biblioteca;
    canciones.cant = sizeof(biblioteca)/sizeof(Cancion);
    return canciones;
}

void imprimirCanciones(Canciones canciones)
{
    int i;
    printf("\n Canciones TOTAL:%lld",canciones.cant);
    for(i = 0 ; i < canciones.cant; i++)
    {
        printf("\n[%d]", i);
        imprimirCancion(&canciones.cancion[i]);
    }
}

void imprimirCancion(void *dato)
{
    Cancion *cancion = (Cancion*)dato;
    printf(" %-20s ", cancion->nombre);
    printf("| %-20s ", cancion->autor);
    printf("| %hu ", cancion->release_date);
}

void imprimirNombre(void *dato)
{
    Cancion *cancion = (Cancion*)dato;
    printf(" %-20s ", cancion->nombre);	
}
