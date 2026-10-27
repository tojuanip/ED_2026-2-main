#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "alumno.h"

void mostrarMenu(); 

int main(void) 
{
    Lista listaAlumnos;
    listaAlumnos.inicio = listaAlumnos.fin = NULL;
    listaAlumnos.cant = 0;
    listaAlumnos.orden = ASCENDENTE;

    fn_comparar funcCompActual = compAlumMat; 
    int opcion;

    do 
	{
        mostrarMenu();
        scanf("%d", &opcion); 

        switch(opcion) 
        {
            case 1: 
            {
                unsigned int mat;
                char nom[64];
                int sem;
                float prom;

                printf("Matricula: ");
                scanf("%u", &mat);

                Alumno tempMatricula;
                tempMatricula.matricula = mat;

                if (buscarDato(listaAlumnos, &tempMatricula, compAlumMat)) 
                {
                    printf("Ya hay un alumno con la matricula %u.\n", mat);
                    break;
                }
                
                printf("Nombre: ");
                scanf(" %s", nom); 
                printf("Semestres: ");
                scanf("%d", &sem);
                printf("Promedio: ");
                scanf("%f", &prom);

                Alumno* nuevo = crearAlumno(mat, nom, sem, prom);
                insertarOrdenado(&listaAlumnos, nuevo, funcCompActual);
                printf("Alumno registrado!\n");
                break;
            }
            case 2:
                imprimirLista(listaAlumnos, imprimirAlumno);
                break;
            case 3:
            { 
                int opcOrden;
                int opcDireccion;
                Orden dirSeleccionada = ASCENDENTE;

                printf("Reordenar por: \n 1.Matricula \n 2.Nombre \n 3.Semestres \n 4.Promedio \n Opcion: ");
                scanf("%d", &opcOrden);
                
                switch(opcOrden) 
                {
                    case 1: 
                        funcCompActual = compAlumMat; 
                        break;
                    case 2: 
                        funcCompActual = compAlumNom;
                        break;
                    case 3: 
                        funcCompActual = compAlumSem; 
                        break;
                    case 4: 
                        funcCompActual = compAlumProm;
                        break;
                    default:
                        printf("\nOpcion no valida"); 
                        break;
                }
                
                printf("\nOrden: \n 1.Ascendente \n 2.Descendente \n Seleccione: ");
                scanf("%d", &opcDireccion);

                if(opcDireccion == 2) 
                {
                    dirSeleccionada = DESCENDENTE;
                } 
                else if (opcDireccion == 1) 
                {
                    dirSeleccionada = ASCENDENTE;
                }
                else 
                {
                    printf("\nOrden no valida\n");
                }
                
                ordenarLista(&listaAlumnos, funcCompActual, dirSeleccionada);
                printf("\nLista reordenada\n");
                break;
            }
            case 4:
            {
                int opcBusqueda;
                printf("Buscar por: \n 1.Matricula \n 2.Nombre \n 3.Semestres \n 4.Promedio \n Opcion: ");
                scanf("%d", &opcBusqueda);
                
                Alumno tempBusqueda; 
                fn_comparar funcBusqueda = NULL;
                
                switch(opcBusqueda)
                {
                    case 1:
                        printf("Matricula: ");
                        scanf("%u", &tempBusqueda.matricula);
                        funcBusqueda = compAlumMat;
                        break;
                    case 2:
                        printf("Nombre: ");
                        scanf(" %[^\n]", tempBusqueda.nombre);
                        funcBusqueda = compAlumNom;
                        break;
                    case 3:
                        printf("Semestres: ");
                        scanf("%d", &tempBusqueda.semestres);
                        funcBusqueda = compAlumSem;
                        break;
                    case 4:
                        printf("Promedio: ");
                        scanf("%f", &tempBusqueda.promedio);
                        funcBusqueda = compAlumProm;
                        break;
                    default:
                        printf("\nOpcion no valida\n");
                        continue;
                }
                
                Nodo* aux = listaAlumnos.inicio;
                int encontrado = 0;
                while(aux) 
				{
                    if(funcBusqueda(&tempBusqueda, aux->dato) == 0) 
					{
                        imprimirAlumno(aux->dato);
                        encontrado = 1;
                    }
                    aux = aux->sig;
                }
               
				if(!encontrado)
				{
					printf("\nAlumno no encontrado.\n");
				}
                break;
            }
            case 5:
			{
                unsigned int matElim;
                printf("Ingrese la matricula del alumno a eliminar: ");
                scanf("%u", &matElim);
                
                Alumno tempElim;
                tempElim.matricula = matElim;
                
                if(buscarDato(listaAlumnos, &tempElim, compAlumMat)) 
				{
                    eliminarDato(&listaAlumnos, &tempElim, compAlumMat);
                    printf("Alumno borrado.\n");
                } 
				else 
				{
                    printf("No se encontro la matricula.\n");
                }
                break;
			}
            case 6:
                printf("\n fin :p \n");
                eliminarLista(&listaAlumnos);
                break;
            default:
                printf("\nOpcion invalida.");
                break;
        } 
        
    } while (opcion != 6); 

    return 0;
}

void mostrarMenu() 
{
    printf("\n\n MENU");
    printf("\n1. Registrar Alumno");
    printf("\n2. Desplegar Alumnos");
    printf("\n3. Reordenar");
    printf("\n4. Buscar Alumno");
    printf("\n5. Borrar Alumno");
    printf("\n6. Finalizar programa");
    printf("\nSeleccione una opcion: ");
}