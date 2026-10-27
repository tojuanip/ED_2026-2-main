#include "Lista.h"

void imprimirLista(Lista lista,fn_imprimir imprimir)
{
	Nodo *aux;
	if(!lista.inicio)
	{
		printf("\n Lista vacia");
		return;
	}	
	printf("\n [CANT %lld]Lista: ",lista.cant);
	aux = lista.inicio;
	while( aux )
	{
		imprimir(aux->dato);
		printf(" -> ");
		aux = aux->sig;
	}
}

void eliminarLista(Lista *lista)
{
	if( !lista->inicio) return;
	Nodo *aux;
	while( lista->inicio)
	{
		aux = lista->inicio;
		lista->inicio = lista->inicio->sig;
		free(aux);
	}
	lista->fin = lista->inicio;
	lista->cant = 0;
}

void insertarFinal(Lista *lista,void *dato)
{
	if(!lista->inicio)
	{
		lista->inicio = lista->fin = crearNodo(dato);
		lista->cant++;
		return;
	}
	lista->fin->sig = crearNodo(dato);
	lista->fin = lista->fin->sig;
	lista->cant++;
}

void eliminarDato(Lista *lista,void *dato,fn_comparar comparar)
{	
	if(!lista->inicio)
		return;
	
	for(Nodo *ant=NULL,*elim=lista->inicio ; elim ; ant = elim , elim = elim->sig)
	{
		if( comparar( dato , elim->dato ) == 0)
		{
			if( lista->inicio == elim)
				lista->inicio = elim->sig;
			else
				ant->sig = elim->sig;
			if( lista->fin == elim)
				lista->fin = ant;
			free(elim);
			lista->cant--;
			return;
		}
	}	
}

int buscarDato(Lista lista,void *dato,fn_comparar comparar)
{
	if(!lista.inicio)
		return 0;
	while(lista.inicio)
	{
		if(comparar( dato, lista.inicio->dato ) == 0)
			return 1;
		lista.inicio = lista.inicio->sig;
	}
	
	return 0;
}

void swapNodo(Nodo *a, Nodo *b)
{
	void *temp = a->dato;
	a->dato = b->dato;
	b->dato = temp;
}

void ordenarLista(Lista *lista, fn_comparar comparar, Orden orden)
{
	lista->orden = orden;
	if(orden == NINGUNO)
	{	
		return;
	}
		
	for( Nodo *i = lista->inicio ; i ; i = i->sig)
	{
		Nodo *cmp = i;
		for( Nodo *j = i->sig ; j ; j = j->sig)
		{
			if(orden == ASCENDENTE && comparar(cmp->dato, j->dato) > 0)
			{
				cmp = j;
			}
			else if(orden == DESCENDENTE && comparar(cmp->dato, j->dato) < 0)
			{
				cmp = j;
			}
		}
		if(cmp != i)
		{
			swapNodo(i, cmp);
		}
	}
}

void insertarOrdenado(Lista *lista, void *dato, fn_comparar comparar)
{
	if (lista->orden == NINGUNO) 
	{
		insertarFinal(lista, dato);
		return;
	}

	Nodo *nuevo = crearNodo(dato);
	lista->cant++;

	if (!lista->inicio) 
	{
		lista->inicio = lista->fin = nuevo;
		return;
	}

	if ((lista->orden == ASCENDENTE && comparar(dato, lista->inicio->dato) <= 0) || (lista->orden == DESCENDENTE && comparar(dato, lista->inicio->dato) >= 0)) 
	{
		nuevo->sig = lista->inicio;
		lista->inicio = nuevo;
		return;
	}

	Nodo *actual = lista->inicio;
	
	while (actual->sig != NULL) 
	{
		if ((lista->orden == ASCENDENTE && comparar(dato, actual->sig->dato) <= 0) || (lista->orden == DESCENDENTE && comparar(dato, actual->sig->dato) >= 0)) 
		{
			break; 
		} 
		
		actual = actual->sig;
	}

	nuevo->sig = actual->sig;
	actual->sig = nuevo;

	if (nuevo->sig == NULL) 
	{
		lista->fin = nuevo;
	}
	
	//if (actual->izq != NULL)
		//{
	//		push(&pila, actual->izq);
	//	}
		
	//	if (actual->dch != NULL)
	//	{
	//		push(&pila, actual->dch);
	//	}
}