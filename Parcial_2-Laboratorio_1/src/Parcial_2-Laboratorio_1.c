#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Controller.h"
#include "LinkedList.h"
#include "utn.h"

#define MINIMA_OPCION_MENU 1
#define MAXIMA_OPCION_MENU 7
#define MAXIMA_OPCION_MENU_CIFRAS 1

int main(void) {
	setbuf(stdout,NULL);

	LinkedList* listaServicios;
	int opcionMenu;
	int banderaOpcionUno;
	int banderaOpcionCuatro;

	banderaOpcionUno = 0;
	banderaOpcionCuatro=0;
	listaServicios = ll_newLinkedList();

	do{
		printf("---------------------Menu-----------------------\n"
			"1. Cargar archivo (modo CSV)\n"
			"2. Imprimir lista\n"
			"3. Asignar totales\n"
			"4. Filtrar por tipo\n"
			"5. Mostrar servicios\n"
			"6. Guardar servicios\n"
			"7. Salir\n\n");


		if(!utn_GetIntRango(&opcionMenu, "Elija una opcion: ", "El dato ingresado es invalido. Ingrese una opcion correcta: ", MINIMA_OPCION_MENU, MAXIMA_OPCION_MENU, MAXIMA_OPCION_MENU_CIFRAS))
		{
			switch(opcionMenu)
			{
				case 1:
					if(!banderaOpcionUno || banderaOpcionCuatro)
					{
						if(banderaOpcionCuatro)
						{
							banderaOpcionCuatro = 0;
							ll_clear(listaServicios);
						}
						switch(Controller_loadFromText(listaServicios, 1))
						{
							case 0:
								printf("\n\nSe cargaron con exito todos los Servicios\n\n");
								banderaOpcionUno=1;
								break;

							case 1:
								printf("\n\nNo se pudo leer el archivo\n\n");
								break;

							case 2:
								printf("\n\nNo se pudieron cargar algunos de los servicios\n\n");
								banderaOpcionUno=1;
								break;
						}
					}
					else
					{
						printf("\n\nNo se pueden cargar los servicios debido a que todavia no los volvieste a guardar");
					}

					break;

				case 2:
					if(banderaOpcionUno)
					{
						switch(Controller_ListServicios(listaServicios))
						{
							case 0:
								printf("\n\nSe mostraron con exito todos los Servicios");
								banderaOpcionUno=1;
								break;

							case 1:
								printf("\n\nNo se pudieron listar los servicio");
								break;

							case 2:
								printf("\n\nNo se pudieron mostrar algunos de los servicios");
								banderaOpcionUno=1;
								break;
						}
					}
					else
					{
						printf("\n\nNo se pueden mostrar los servicios porque no se cargo ninguno");
					}
					break;

				case 3:
					if(banderaOpcionUno)
					{
						listaServicios = Controller_AsignarTotales(listaServicios);

						if(listaServicios == NULL)
						{
							printf("\n\nNo se pueden asignar los totales debido a que la lista elejida no tiene servicios");
						}
					}
					else
					{
						printf("\n\nNo se pueden asignar los totales debido a que no se cargo ningun servicio");
					}
					break;

				case 4:
					if(banderaOpcionUno)
					{
						banderaOpcionCuatro =1;
						switch(Controller_FiltrarPorTipo(listaServicios))
						{
							case 0:
								printf("\n\nSe guardaron con exito todos los servicios filtrados");
								break;

							case 1:
								printf("\n\nNo se pudieron guardar los archivo debido a que el puntero es nulo");
								break;

							case 2:
								printf("\n\nAlgunos pasajeros no se pudieron guardar");
								break;
						}

					}
					else
					{

					}
					break;

				case 5:
					break;

				case 6:
					break;

				case 7:
					break;
			}
			printf("\n\n");
		}
	}while(opcionMenu != 7);

	return EXIT_SUCCESS;
}
