#include "LinkedList.h"

#define CANTIDAD_CARACTERES_DESCRIPCION_SERVICIO 50

#ifndef SERVICIOS_H_
#define SERVICIOS_H_

typedef struct{

	int id_Servicio;
	char descripcion[CANTIDAD_CARACTERES_DESCRIPCION_SERVICIO];
	int tipo;
	float precioUnitario;
	int cantidad;
	float totalServicio;

} eServicios;

#endif /* SERVICIOS_H_ */

eServicios* Servicios_new();

eServicios* Servicios_newParametros(int id_Servicio, char* descripcion, int tipo, float precioUnitario, int cantidad, float totalServicio);

int Servicios_delete(eServicios* servicioAEliminar);


int Servicios_setId(eServicios* this,int id_Servicio);
int Servicios_getId(eServicios* this,int* id_Servicio);

int Servicios_setDescripcion(eServicios* this,char* descripcion);
int Servicios_getDescripcion(eServicios* this,char* descripcion);

int Servicios_setTipo(eServicios* this,int tipo);
int Servicios_getTipo(eServicios* this,int* tipo);

int Servicios_setPrecioUnitario(eServicios* this,float precioUnitario);
int Servicios_getPrecioUnitario(eServicios* this,float* precioUnitario);

int Servicios_setCantidad(eServicios* this,int cantidad);
int Servicios_getCantidad(eServicios* this,int* cantidad);

int Servicios_setTotalServicio(eServicios* this,float totalServicio);
int Servicios_getTotalServicio(eServicios* this,float* totalServicio);


int Servicios_setAll(eServicios* this, int id_Servicio, char* descripcion, int tipo, float precioUnitario, int cantidad, float totalServicio);
int Servicios_getAll(eServicios* this, int* id_Servicio, char* descripcion, int* tipo, float* precioUnitario, int* cantidad, float* totalServicio);


int Servicios_verificarYTransfomarTipoStringAInt(char* tipoString, int* tipoNumerico);
int Servicios_verificarYTransfomarTipoIntAString(char* tipoString, int tipoNumerico);

int Servicios_MostrarUnServicio(eServicios* this);

void Servicios_CalcularPrecioTotal(void* peServicios)
;
int Servicios_FiltrarPorMinorista(void* peServicios);
int Servicios_FiltrarPorMayorista(void* peServicios);
int Servicios_FiltrarPorExportador(void* peServicios);

int Servicios_SaveTxt(FILE* pFile, LinkedList* listaServicios, int guardarEncabezado);

