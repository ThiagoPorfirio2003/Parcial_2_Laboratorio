#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Servicios.h"
#include "Parser.h"
#include "LinkedList.h"
#include "utn.h"

#define CANTIDAD_CARACTERES_DESCRIPCION_SERVICIO 50
#define CANTIDAD_CARACTERES_ID_SERVICIO 15
#define CANTIDAD_CARACTERES_TIPO 20
#define CANTIDAD_CARACTERES_PRECIO_UNITARIO 30
#define CANTIDAD_CARACTERES_CANTIDAD 20
#define CANTIDAD_CARACTERES_TOTAL_SERVICIO 50

int Controller_loadFromText(LinkedList* this, int mostrarPasajero)
{
	int retorno;
	int archivoAUsar;
	char nombreDelArchivo[50];
	FILE* pFile;

	retorno =1;

	if(this != NULL && (mostrarPasajero == 0 || mostrarPasajero == 1))
	{
		if(!utn_GetIntRango(&archivoAUsar, "\nArchivos a abrir:\n 1- Todos los servicios\nElija una opcion: ", "El dato ingresado es invalido. Elija una opcion correcta", 1, 1, 1))
		{
			switch(archivoAUsar)
			{
				case 1:
					strcpy(nombreDelArchivo, "data.csv");
					break;
			}

			pFile = fopen(nombreDelArchivo, "r");

			retorno = parser_ServiciosFromText(pFile, this, mostrarPasajero);

			while(!fclose(pFile));

		}
	}

	return retorno;
}

int Controller_ListServicios(LinkedList* this)
{
	int retorno;
	int cantidadServiciosAMostrar;
	int estadoMostrar;
	int banderaRetorno;
	eServicios* servicioAMostrar;

	retorno =1;
	banderaRetorno =1;

	if(this != NULL)
	{
		cantidadServiciosAMostrar = ll_len(this);

		if(cantidadServiciosAMostrar > 0)
		{
			printf("\n\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
			printf("|%*s|%*s|%*s|$%*s|%*s|%*s|\n", -CANTIDAD_CARACTERES_ID_SERVICIO, "ID SERVICIO", -CANTIDAD_CARACTERES_DESCRIPCION_SERVICIO, "DESCRIPCION", -CANTIDAD_CARACTERES_TIPO, "TIPO DE SERVICIO", -CANTIDAD_CARACTERES_PRECIO_UNITARIO, "PRECIO UNITARIO", -CANTIDAD_CARACTERES_CANTIDAD, "CANTIDAD", -CANTIDAD_CARACTERES_TOTAL_SERVICIO, "PRECIO TOTAL");
			printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

			for(int i=0; i<cantidadServiciosAMostrar; i++)
			{
				servicioAMostrar = ll_get(this,i);
				if(servicioAMostrar != NULL)
				{
					estadoMostrar = Servicios_MostrarUnServicio(servicioAMostrar);

					if(banderaRetorno == 1)
					{
						if(estadoMostrar ==2)
						{
							retorno =2;
							banderaRetorno =0;
						}
						else
						{
							retorno = estadoMostrar;
						}
					}
				}
			}

			printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
		}
	}

	return retorno;
}
