#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"
#include "Cadena.h"

void imprimirTexto(void *dato)
{
	printf("%s", (char*)dato);
}

void liberarNodos(Nodoa *raiz)
{
	if (!raiz)
	{
		return;
	}
	liberarNodos(raiz->izq);
	liberarNodos(raiz->dch);
	free(raiz->dato);
	free(raiz);
}

int main(void)
{
	int opc = 0;
	char inf[128] = "";
	char post[256] = "";
	Arbol arbolExp;

	arbolExp.raiz = NULL;
	arbolExp.cant = 0;
	arbolExp.comparar = NULL;
	arbolExp.orden = ASC;

	do
	{
		printf("\nEXPRESION: %s", (arbolExp.raiz != NULL) ? inf : "");
		printf("\n[0] CAPTURAR EXPRESION");
		printf("\n[1] IMPRIMIR ARBOL DE EXPRESION");
		printf("\n[2] EVALUAR EXPRESION");
		printf("\n[3] TERMINAR PROGRAMA");
		printf("\nSeleccione: ");
		scanf("%d", &opc);

		switch (opc)
		{
			case 0:
				printf("\nIngrese la expresion: ");
				scanf("%s", inf);

				if (verificarParentesis(inf))
				{
					if (arbolExp.raiz)
					{
						liberarNodos(arbolExp.raiz);
						arbolExp.raiz = NULL;
					}

					infixAPostfix(inf, post);
					arbolExp.raiz = crearArbolExpresion(post);
				}
				else
				{
					printf("\nfaltan parentesis\n");
					inf[0] = '\0';
					liberarNodos(arbolExp.raiz);
					arbolExp.raiz = NULL;
				}
				break;

			case 1:
				printf("\nRepresentacion del arbol:\n");
				imprimirArbol(arbolExp, imprimirTexto);
				printf("\n");
				break;

			case 2:
				double res = evaluarArbol(arbolExp.raiz);
				printf("\nResultado = %g\n", res);
				break;

			case 3:
				liberarNodos(arbolExp.raiz);
				arbolExp.raiz = NULL;
				printf("\n\n FIN DE PROGRAMA\n\n");
				break;

			default:
				printf("\nOpcion no valida.\n");
				break;
		}
	} while (opc != 3);

	return 0;
}