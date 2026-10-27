#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Pila.h"
#include "Cadena.h"

void menuOpciones(void);

int main(void)
{
    menuOpciones();
    printf("\n=== FIN DE PROGRAMA ===\n");
    return 0;
}

void menuOpciones(void)
{
    int opcion;
    char entrada[100];

    do
    {
        printf("\n\nMENU PRINCIPAL\n");
        printf("1. Palindromo\n");
        printf("2. Verificacion de parentesis\n");
        printf("3. Ordenar pila\n");
        printf("4. Terminar ejecucion\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
            case 1:
                printf("\nIngrese palabra: ");
                scanf("%s", entrada);
                if (esPalindromo(entrada))
                {
                    printf("%s ES un palindromo\n", entrada);
                }
                else
                {
                    printf("%s NO es un palindromo\n", entrada);
                }
                break;

            case 2:
                printf("\nIngrese expresion: ");
                scanf("%s", entrada);
                if (verificarParentesis(entrada))
                {
                    printf("Resultado: %s es Valido\n", entrada);
                }
                else
                {
                    printf("Resultado: %s es Invalido\n", entrada);
                }
                break;

            case 3:
                printf("\nIngrese numeros: ");
                scanf("%s", entrada);
                ordenarPila(entrada);
                break;

            case 4:
                printf("\nSaliendo\n");
                break;

            default:
                printf("\nOpcion no valida\n");
                break;
        }
    } while (opcion != 4);
}