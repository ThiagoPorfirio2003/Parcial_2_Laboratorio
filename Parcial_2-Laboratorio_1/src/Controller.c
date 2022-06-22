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

#define MINIMA_OPCION_FILTRACION 1
#define MAXIMA_OPCION_FILTRACION 3
#define MAXIMA_OPCION_FILTRACION_CIFRAS 1

#define MINIMA_OPCION_ABRIR_ARCHIVO 1
#define MAXIMA_OPCION_ABRIR_ARCHIVO 4
#define MAXIMA_OPCION_ABRIR_ARCHIVO_CIFRAS 1

#define MINIMA_OPCION_GUARDAR_ARCHIVO 1
#define MAXIMA_OPCION_GUARDAR_ARCHIVO 4

#define CANTIDAD_CARACTERES_NOMBRE_ARCHIVO_ALMACENADOR 20


int static Controller_getFileName(int opcionArchivo, char* nombreArchivo)
{
	int retorno;

	retorno =1;

	if(nombreArchivo != NULL)
	{
		retorno =0;
		switch(opcionArchivo)
		{
			case 1:
				strcpy(nombreArchivo, "data_minorista.csv");
				break;

			case 2:
				strcpy(nombreArchivo, "data_mayorista.csv");
				break;

			case 3:
				strcpy(nombreArchivo, "data_exportador.csv");
				break;

			case 4:
				strcpy(nombreArchivo, "data.csv");
				break;

			default:
				retorno =1;
				break;
		}
	}
	return retorno;
}

int static Controller_choseFile(char* nombreArchivo, char* mensaje, char* mensajeError, int minimaOpcionArchivo, int maximaOpcionArchivo, int maximaOpcionAbrirArchivoCifras)
{
	int retorno;
	int opcionArchivo;

	retorno =1;

	if(nombreArchivo != NULL && mensaje != NULL && mensajeError != NULL && maximaOpcionAbrirArchivoCifras>0 && minimaOpcionArchivo<=maximaOpcionArchivo)
	{
		if(!utn_GetIntRango(&opcionArchivo, mensaje, mensajeError, minimaOpcionArchivo, maximaOpcionArchivo, MAXIMA_OPCION_ABRIR_ARCHIVO_CIFRAS))
		{
			retorno =  Controller_getFileName(opcionArchivo, nombreArchivo);
		}
	}
	return retorno;
}

int Controller_loadFromText(LinkedList* this)
{
	int retorno;
	char nombreDelArchivo[CANTIDAD_CARACTERES_NOMBRE_ARCHIVO_ALMACENADOR];
	FILE* pFile;

	retorno =1;

	if(this != NULL)
	{
		if(!Controller_choseFile(nombreDelArchivo, "\nArchivos a abrir:\n 1- Minoristas\n 2- Mayoristas\n 3- Exportadores\n 4- Todos los servicios\nElija una opcion: ", "El dato ingresado es invalido. Elija una opcion correcta: ", MINIMA_OPCION_ABRIR_ARCHIVO, MAXIMA_OPCION_ABRIR_ARCHIVO, MAXIMA_OPCION_ABRIR_ARCHIVO_CIFRAS))
		{
			pFile = fopen(nombreDelArchivo, "r");

			retorno = parser_ServiciosFromText(pFile, this);

			while(!fclose(pFile));
		}
	}

	return retorno;
}

int Controller_SaveTxt(LinkedList* this, int opcionArchivoAGuardar)
{
	int retorno;
	FILE* pFile;
	char nombreArchivoAlmacenador[CANTIDAD_CARACTERES_NOMBRE_ARCHIVO_ALMACENADOR];

	retorno =1;
	pFile= NULL;

	if(this != NULL && opcionArchivoAGuardar > MINIMA_OPCION_GUARDAR_ARCHIVO -1 && opcionArchivoAGuardar < MAXIMA_OPCION_GUARDAR_ARCHIVO +1)
	{
		if(!Controller_getFileName(opcionArchivoAGuardar, nombreArchivoAlmacenador))
		{
			pFile = fopen(nombreArchivoAlmacenador, "w");

			retorno = Servicios_SaveTxt(pFile, this, 1);

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
				servicioAMostrar = (eServicios*) ll_get(this,i);
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

LinkedList* Controller_AsignarTotales(LinkedList* this)
{
	if(this != NULL)
	{
		this = ll_map(this, Servicios_CalcularPrecioTotal);
	}

	return this;
}

int Controller_FiltrarPorTipo(LinkedList* this)
{
	int retorno;
	LinkedList* listaFiltrada;
	int opcionFiltracion;
	int (*pFuncFiltradora)(void* pElemento);

	retorno=1;
	listaFiltrada = NULL;
	pFuncFiltradora = NULL;

	if(this != NULL)
	{

		if(!utn_GetIntRango(&opcionFiltracion, "\nOpciones de filtrado:\n 1- Minorista\n 2- Mayorista\n 3- Exportador\nElija una opcion: ", "El dato ingresado es invalido. Ingrese una opcion correcta: ", MINIMA_OPCION_FILTRACION, MAXIMA_OPCION_FILTRACION, MAXIMA_OPCION_FILTRACION_CIFRAS))
		{
			switch(opcionFiltracion)
			{
				case 1:
					pFuncFiltradora = Servicios_FiltrarPorMinorista;
					break;

				case 2:
					pFuncFiltradora = Servicios_FiltrarPorMayorista;
					break;

				case 3:
					pFuncFiltradora = Servicios_FiltrarPorExportador;
					break;
			}
			listaFiltrada = ll_filter(this, pFuncFiltradora);

			retorno = Controller_SaveTxt(listaFiltrada, opcionFiltracion);
		}
	}
	return retorno;
}

int Controller_SortPorDescripcion(LinkedList* this)
{
	int retorno;

	retorno=1;
	if(this != NULL)
	{
		retorno = ll_sort(this, Servicios_OrdernarPorDescripcion,1);
	}

	return retorno;
}
