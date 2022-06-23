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
	int banderaOpcionSeis;
	int opcionReCargarDatos;
	int quedarseEnPrograma;

	banderaOpcionUno = 0;
	banderaOpcionSeis =0;
	opcionReCargarDatos =0;
	quedarseEnPrograma=1;

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
					if(banderaOpcionUno && !utn_GetIntRango(&opcionReCargarDatos, "\nSi queres volver a cargar los datos, todos los no guardados se perderan. Elije 1 para aceptar o 0 para cancelar: ", "El dato ingresado es invalido. Elije 1 para aceptar o 0 para cancelar:  ", 0, 1, 1) && opcionReCargarDatos)
					{
						ll_clear(listaServicios);
					}

					if(opcionReCargarDatos || !banderaOpcionUno)
					{
						switch(controller_AbrirArchivoElejido(listaServicios))
						{
							case 0:
								printf("\n\nSe cargaron con exito todos los Servicios");
								banderaOpcionUno=1;
								break;

							case 1:
								printf("\n\nNo se pudo leer el archivo\n\n");
								break;

							case 2:
								printf("\n\nNo se pudieron cargar algunos de los servicios");
								banderaOpcionUno=1;
								break;
						}
					}

					break;

				case 2:
					if(banderaOpcionUno)
					{
						switch(Controller_ListServicios(listaServicios))
						{
							case 0:
								printf("\n\nSe mostraron con exito todos los Servicios");
								break;

							case 1:
								printf("\n\nNo se pudieron listar los servicio");
								break;

							case 2:
								printf("\n\nNo se pudieron mostrar algunos de los servicios");
								break;
						}
					}
					else
					{
						printf("\n\nNo se puede acceder a esta opcion porque todavia no hay ningun servicio cargado");
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
						else
						{
							printf("\n\nLa asignacion de totales se realizo con exito");
						}
					}
					else
					{
						printf("\n\nNo se puede acceder a esta opcion porque todavia no hay ningun servicio cargado");
					}
					break;

				case 4:
					if(banderaOpcionUno)
					{
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
						printf("\n\nNo se puede acceder a esta opcion porque todavia no hay ningun servicio cargado");
					}
					break;

				case 5:
					if(banderaOpcionUno)
					{
						if(Controller_SortPorDescripcion(listaServicios))
						{
							printf("\n\nHa ocurrido un error en el ordamiento");
						}
						else
						{
							printf("\n\nSe ordenaron con exito los servicios");
						}

						switch(Controller_ListServicios(listaServicios))
						{
							case 0:
								printf("\n\nSe mostraron con exito todos los Servicios");
								break;

							case 1:
								printf("\n\nNo se pudieron listar los servicio");
								break;

							case 2:
								printf("\n\nNo se pudieron mostrar algunos de los servicios");
								break;
						}

					}
					else
					{
						printf("\n\nNo se puede acceder a esta opcion porque todavia no hay ningun servicio cargado");
					}
					break;

				case 6:
					if(banderaOpcionUno)
					{
						switch(Controller_SaveTxt(listaServicios, "data.csv"))
						{
							case 0:
								printf("\n\nSe guardaron con exito todos los servicios ");
								break;

							case 1:
								printf("\n\nNo se pudieron guardar los archivo debido a que el puntero es nulo");
								break;

							case 2:
								printf("\n\nAlgunos servicios no se pudieron guardar");
								break;
						}
						banderaOpcionSeis=1;
					}
					else
					{
						printf("\n\nNo se puede acceder a esta opcion porque todavia no hay ningun servicio cargado");
					}
					break;

				case 7:
					if(banderaOpcionSeis)
					{
						quedarseEnPrograma=0;
						printf("\n\nSaliendo...\n\n");
						while(ll_deleteLinkedList(listaServicios));
					}
					else
					{
						printf("\n\nNO PUEDE salir del programa sin antes haber guardado el archivo\n\n");
					}
					break;
			}
			printf("\n\n");
		}
	}while(quedarseEnPrograma);

	return EXIT_SUCCESS;
}
