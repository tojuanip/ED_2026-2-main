#include "arbol.h"
#include <ctype.h>
#include <math.h>

size_t altura(Arbol arbol)
{
	Arbol arbol_izq,arbol_dch;
	size_t hd,hi;
	if(!arbol.raiz) 
		return 0;
	if(!arbol.raiz->izq && !arbol.raiz->dch)
		return 1;
	arbol_izq.raiz = arbol.raiz->izq;
	arbol_dch.raiz = arbol.raiz->dch;
	hi = altura(arbol_izq);
	hd = altura(arbol_dch);
	if( hi>hd )
		return hi + 1;
	else
		return hd + 1;
}

size_t alturaI(Arbol arbol)
{
	size_t max_altura = 0;
	
	if (!arbol.raiz)
		return max_altura;

	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol.raiz;
	Nodoa *ultimo_visitado = NULL;

	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			//SE RECORREN LOS HIJOS IZQUIERDOS
			// Apilar nodo padre antes del bajar
			push(&pila, actual);
			
			// Actualizar la altura máxima según la profundidad de la pila
			if (pila.cant > max_altura)
				max_altura = pila.cant;
			
			actual = actual->izq;
		}
		else
		{
			//Se consulta el padre
			Nodoa *padre = peek(pila);
			
			// Si existe hijo derecho y aún no lo hemos visitado, recorrer
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
			{
				actual = padre->dch;
			}
			else
			{
				// Remover si ya se recorrieron los hijos
				ultimo_visitado = pop(&pila);
			}
		}
	}

	return max_altura;
}

void preordenI(Arbol arbol,fn_imprimir imprimir)
{
	if (!arbol.raiz)
		return ;
	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol.raiz;
	Nodoa *ultimo_visitado = NULL;

	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			printf(" ");
			imprimir(actual->dato);
			push(&pila, actual);
			actual = actual->izq;
		}
		else
		{
			Nodoa *padre = peek(pila);			
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
				actual = padre->dch;
			else
				ultimo_visitado = pop(&pila);
		}
	}
}

void ordenI(Arbol arbol,fn_imprimir imprimir)
{
	if (!arbol.raiz)
		return ;
	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol.raiz;
	Nodoa *ultimo_visitado = NULL;

	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			push(&pila, actual);
			actual = actual->izq;
		}
		else
		{
			Nodoa *padre = pop(&pila);			
			printf(" ");
			imprimir(padre->dato);
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
				actual = padre->dch;
			else
				ultimo_visitado = padre;
		}
	}
}

void postordenI(Arbol arbol,fn_imprimir imprimir)
{
	if (!arbol.raiz)
		return ;
	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol.raiz;
	Nodoa *ultimo_visitado = NULL;

	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			push(&pila, actual);
			actual = actual->izq;
		}
		else
		{
			Nodoa *padre = peek(pila);			
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
				actual = padre->dch;
			else
			{
				printf(" ");
				imprimir(padre->dato);
				ultimo_visitado = pop(&pila);
			}
		}
	}
}

void preorden(Nodoa *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	printf(" ");
	imprimir(raiz->dato);
	preorden(raiz->izq,imprimir);
	preorden(raiz->dch,imprimir);
}

void orden(Nodoa *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	orden(raiz->izq,imprimir);
	printf(" ");
	imprimir(raiz->dato);
	orden(raiz->dch,imprimir);	
}

void inverso(Nodoa *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	inverso(raiz->dch,imprimir);	
	printf(" ");
	imprimir(raiz->dato);
	inverso(raiz->izq,imprimir);
}

void postorden(Nodoa *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	postorden(raiz->izq,imprimir);
	postorden(raiz->dch,imprimir);
	printf(" ");
	imprimir(raiz->dato);	
}

void imprimirOrden(Arbol arbol,fn_imprimir imprimir,int opcion)
{
	switch(opcion)
	{
		case PREORDEN: 
			//preorden(arbol.raiz,imprimir);
			preordenI(arbol,imprimir);
			break;
		case ORDEN: 
			//orden(arbol.raiz,imprimir);
			ordenI(arbol,imprimir);
			break;
		case INVERSO: 
			inverso(arbol.raiz,imprimir);
			break;
		case POSTORDEN: 
			//postorden(arbol.raiz,imprimir);			
			postordenI(arbol,imprimir);
			break;
	}
}

void insertarArbolO(Arbol *arbol, void *dato)
{
	Nodoa *nuevo = NULL;
	Nodoa *actual = NULL;
	Nodoa *padre = NULL;
	int cmp = 0;
	int ir_izq = 0;

	nuevo = crearNodoa(dato);

	if (!arbol->raiz)
	{
		arbol->raiz = nuevo;
		arbol->cant++;
		return;
	}

	actual = arbol->raiz;
	while (actual != NULL)
	{
		padre = actual;
		cmp = arbol->comparar(dato, actual->dato);
		
		if (arbol->orden == ASC)
		{
			if (cmp < 0)
			{
				ir_izq = 1;
			}
			else
			{
				ir_izq = 0;
			}
		}
		else
		{
			if (cmp > 0)
			{
				ir_izq = 1;
			}
			else
			{
				ir_izq = 0;
			}
		}

		if (ir_izq)
		{
			actual = actual->izq;
		}
		else
		{
			actual = actual->dch;
		}
	} 

	if (ir_izq)
	{
		padre->izq = nuevo;
	}
	else
	{
		padre->dch = nuevo;
	}

	arbol->cant++;
}

void* buscarArbol(Arbol *arbol, void *dato)
{
	Nodoa *actual = NULL;
	int cmp = 0;
	int ir_izq = 0;

	if (!arbol->raiz)
	{
		return NULL;
	}

	actual = arbol->raiz;
	
	while (actual != NULL)
	{
		cmp = arbol->comparar(dato, actual->dato);
		if (cmp == 0)
		{
			return actual->dato;
		}

		if (arbol->orden == ASC)
		{
			if (cmp < 0)
			{
				ir_izq = 1;
			}
			else
			{
				ir_izq = 0;
			}
		}
		else
		{
			if (cmp > 0)
			{
				ir_izq = 1;
			}
			else
			{
				ir_izq = 0;
			}
		}

		if (ir_izq)
		{
			actual = actual->izq;
		}
		else
		{
			actual = actual->dch;
		}
	}

	return NULL;
}

void flipArbol(Arbol *arbol)
{
	Pila pila;
	Nodoa *actual = NULL;
	Nodoa *temp = NULL;

	if (!arbol->raiz)
	{
		return;
	}
	
	arbol->orden = !arbol->orden;
	
	pila = inicializarPila(-1);
	push(&pila, arbol->raiz);

	while (!pilaVacia(pila))
	{
		actual = (Nodoa*)pop(&pila);

		temp = actual->izq;
		actual->izq = actual->dch;
		actual->dch = temp;
		
		if(actual->izq != NULL)
		{
			push(&pila, actual->izq);
		}
		
		if(actual->dch != NULL)
		{
			push(&pila, actual->dch);
		}
	}
}

void imprimir_arbol(Nodoa* nodo, int nivel,fn_imprimir imprimir)
{
    int i;
    if (nodo != NULL)
    {
        printf(" ");
		imprimir(nodo->dato);
        if(nodo->dch)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->dch, nivel + 1,imprimir);
        }
        if(nodo->izq)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            { 
                printf(" |      ");
                //printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->izq, nivel + 1,imprimir);
        }
    }
}

void imprimirArbol(Arbol arbol,fn_imprimir imprimir)
{
	imprimir_arbol(arbol.raiz,0,imprimir);
}

int eliminarArbol(Arbol *arbol, void *dato)
{
	Nodoa **enlace = NULL;
	Nodoa *eliminar = NULL;
	Nodoa **sig = NULL;
	int cmp = 0;

	if (!arbol->raiz)
	{
		return 0;
	}

	enlace = &arbol->raiz;
	while (*enlace != NULL)
	{
		cmp = arbol->comparar(dato, (*enlace)->dato);
		if (cmp == 0)
		{
			break;
		}

		if ((arbol->orden == ASC && cmp < 0) || (arbol->orden == DSC && cmp > 0))
		{
			enlace = &(*enlace)->izq;
		}
		else
		{
			enlace = &(*enlace)->dch;
		}
	}

	if (*enlace == NULL)
	{
		return 0;
	}

	eliminar = *enlace;

	if (eliminar->izq != NULL && eliminar->dch != NULL)
	{
		sig = &eliminar->dch;
		while ((*sig)->izq != NULL)
		{
			sig = &(*sig)->izq;
		}
		eliminar->dato = (*sig)->dato;
		eliminar = *sig;
		*sig = (*sig)->dch;
	}
	else
	{
		*enlace = (eliminar->izq != NULL) ? eliminar->izq : eliminar->dch;
	}

	free(eliminar);
	arbol->cant--;
	return 1;
}

void equilibrarArbol(Arbol *arbol)
{
	size_t hi = 0, hd = 0;
	int b = 0;
	Arbol arbol_izq, arbol_dch;
	void **elementos = NULL;
	Pila pila;
	Nodoa *actual = NULL;
	size_t idx = 0;
	int *rango = NULL;
	int inicio = 0, fin = 0, medio = 0;

	if (!arbol->raiz || arbol->cant <= 2)
	{
		return;
	}

	arbol_izq.raiz = arbol->raiz->izq;
	arbol_dch.raiz = arbol->raiz->dch;
	hi = alturaI(arbol_izq);
	hd = alturaI(arbol_dch);
	b = (int)hd - (int)hi;

	if (b >= -1 && b <= 1)
	{
		printf("\n Arbol equilibrado\n");
		return;
	}

	elementos = (void**)malloc(sizeof(void*) * arbol->cant);
	if (!elementos)
		return;

	pila = inicializarPila(-1);
	actual = arbol->raiz;

	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			push(&pila, actual);
			actual = (arbol->orden == ASC) ? actual->izq : actual->dch;
		}
		else
		{
			actual = (Nodoa*)pop(&pila);
			elementos[idx++] = actual->dato;
			actual = (arbol->orden == ASC) ? actual->dch : actual->izq;
		}
	}

	arbol->raiz = NULL;
	arbol->cant = 0;

	rango = (int*)malloc(2 * sizeof(int));
	rango[0] = 0;
	rango[1] = (int)idx - 1;
	push(&pila, rango);

	while (!pilaVacia(pila))
	{
		rango = (int*)pop(&pila);
		inicio = rango[0];
		fin = rango[1];
		free(rango);

		if (inicio <= fin)
		{
			medio = (inicio +1+ fin) / 2;
			insertarArbolO(arbol, elementos[medio]);

			if (medio + 1 <= fin)
			{
				rango = (int*)malloc(2 * sizeof(int));
				rango[0] = medio + 1;
				rango[1] = fin;
				push(&pila, rango);
			}

			if (inicio <= medio - 1)
			{
				rango = (int*)malloc(2 * sizeof(int));
				rango[0] = inicio;
				rango[1] = medio - 1;
				push(&pila, rango);
			}
		}
	}

	free(elementos);
}

int prec(char simbolo)
{
	if (simbolo == '^')
	{
		return 3;
	}
	if (simbolo == '*' || simbolo == '/')
	{
		return 2;
	}
	if (simbolo == '+' || simbolo == '-')
	{
		return 1;
	}
	return 0;
}

void infixAPostfix(const char *inf, char *post)
{
	Pila p = inicializarPila(-1);
	int i = 0, k = 0;
	char *tope;

	while (inf[i] != '\0')
	{
		if (inf[i] == ' ')
		{
			i++;
			continue;
		}

		if (inf[i] == '(')
		{
			push(&p, (void*)&inf[i++]);
		}
		else if (inf[i] == ')')
		{
			while (!pilaVacia(p) && *(char*)peek(p) != '(')
			{
				tope = (char*)pop(&p);
				post[k++] = *tope;
				post[k++] = ' ';
			}
			if (!pilaVacia(p))
			{
				pop(&p);
			}
			i++;
		}
		else if (prec(inf[i]))
		{
			while (!pilaVacia(p) && *(char*)peek(p) != '(' && prec(*(char*)peek(p)) >= prec(inf[i]))
			{
				tope = (char*)pop(&p);
				post[k++] = *tope;
				post[k++] = ' ';
			}
			push(&p, (void*)&inf[i++]);
		}
		else
		{
			while ((inf[i] >= '0' && inf[i] <= '9') || inf[i] == '.' || 
			       (inf[i] >= 'a' && inf[i] <= 'z') || (inf[i] >= 'A' && inf[i] <= 'Z'))
			{
				post[k++] = inf[i++];
			}
			post[k++] = ' ';
		}
	}

	while (!pilaVacia(p))
	{
		tope = (char*)pop(&p);
		post[k++] = *tope;
		post[k++] = ' ';
	}

	if (k > 0 && post[k - 1] == ' ')
	{
		k--;
	}
	post[k] = '\0';
}

Nodoa* crearArbolExpresion(const char *post)
{
	Pila p = inicializarPila(-1);
	int i = 0, j, ini;
	char *dato;
	Nodoa *nuevo, *dch, *izq;

	while (post[i] != '\0')
	{
		if (post[i] == ' ')
		{
			i++;
			continue;
		}

		if (prec(post[i]))
		{
			dato = (char*)malloc(2);
			dato[0] = post[i++];
			dato[1] = '\0';
			nuevo = crearNodoa(dato);

			dch = (Nodoa*)pop(&p);
			izq = (Nodoa*)pop(&p);
			nuevo->dch = dch;
			nuevo->izq = izq;
			push(&p, nuevo);
		}
		else
		{
			ini = i;
			while ((post[i] >= '0' && post[i] <= '9') || post[i] == '.' ||
			       (post[i] >= 'a' && post[i] <= 'z') || (post[i] >= 'A' && post[i] <= 'Z'))
			{
				i++;
			}

			dato = (char*)malloc(i - ini + 1);
			for (j = 0; ini < i; j++, ini++)
			{
				dato[j] = post[ini];
			}
			dato[j] = '\0';

			nuevo = crearNodoa(dato);
			push(&p, nuevo);
		}
	}

	return (Nodoa*)pop(&p);
}

void pedirVariables(Nodoa *raiz, char vars[], float vals[], int *total)
{
	Pila p = inicializarPila(-1);
	Nodoa *act = raiz;
	int i, yaExiste;
	char *texto;

	while (act != NULL || !pilaVacia(p))
	{
		if (act != NULL)
		{
			push(&p, act);
			act = act->izq;
		}
		else
		{
			act = (Nodoa*)pop(&p);
			texto = (char*)act->dato;

			if (!prec(texto[0]) && ((texto[0] >= 'a' && texto[0] <= 'z') || (texto[0] >= 'A' && texto[0] <= 'Z')))
			{
				yaExiste = 0;
				for (i = 0; i < *total; i++)
				{
					if (vars[i] == texto[0])
					{
						yaExiste = 1;
						break;
					}
				}
				if (!yaExiste)
				{
					printf("%s = ", texto);
					scanf("%f", &vals[*total]);
					vars[*total] = texto[0];
					(*total)++;
				}
			}
			act = act->dch;
		}
	}
}

float evaluarArbol(Nodoa *raiz)
{
	if (!raiz)
	{
		return 0;
	}

	char vars[64];
	float vals[64];
	int totalVars = 0, j;

	pedirVariables(raiz, vars, vals, &totalVars);

	Pila pilaArbol = inicializarPila(-1);
	Pila pilaValores = inicializarPila(-1);
	Nodoa *actual = raiz;
	Nodoa *ultimo_visitado = NULL;
	char *texto;
	float *val, *valDer, *valIzq, res;

	while (actual != NULL || !pilaVacia(pilaArbol))
	{
		if (actual != NULL)
		{
			push(&pilaArbol, actual);
			actual = actual->izq;
		}
		else
		{
			Nodoa *padre = (Nodoa*)peek(pilaArbol);

			if (padre->dch != NULL && ultimo_visitado != padre->dch)
			{
				actual = padre->dch;
			}
			else
			{
				ultimo_visitado = (Nodoa*)pop(&pilaArbol);
				texto = (char*)ultimo_visitado->dato;

				if (!prec(texto[0]))
				{
					val = (float*)malloc(sizeof(float));
					if ((texto[0] >= 'a' && texto[0] <= 'z') || (texto[0] >= 'A' && texto[0] <= 'Z'))
					{
						*val = 0;
						for (j = 0; j < totalVars; j++)
						{
							if (vars[j] == texto[0])
							{
								*val = vals[j];
								break;
							}
						}
					}
					else
					{
						*val = atof(texto);
					}
					push(&pilaValores, val);
				}
				else
				{
					valDer = (float*)pop(&pilaValores);
					valIzq = (float*)pop(&pilaValores);
					res = 0;

					switch (texto[0])
					{
						case '+': 
							res = *valIzq + *valDer; 
							break;
						case '-': 
							res = *valIzq - *valDer;
							break;
						case '*': 
							res = *valIzq * *valDer; 
							break;
						case '/': 
							res = (*valDer != 0) ? (*valIzq / *valDer) : 0; 
							break;
						case '^': 
							res = pow(*valIzq, *valDer); 
						break;
					}

					free(valDer);
					free(valIzq);

					val = (float*)malloc(sizeof(float));
					*val = res;
					push(&pilaValores, val);
				}
			}
		}
	}

	val = (float*)pop(&pilaValores);
	res = *val;
	free(val);

	return res;
}