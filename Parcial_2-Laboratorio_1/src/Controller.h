#include "LinkedList.h"

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

int Controller_loadFromText(LinkedList* this, char* nombreArchivo);

int Controller_SaveTxt(LinkedList* this, char* nombreArchivo);

int controller_AbrirArchivo(LinkedList* this);

int Controller_ListServicios(LinkedList* this);

LinkedList* Controller_AsignarTotales(LinkedList* this);

int Controller_FiltrarPorTipo(LinkedList* this);


int Controller_SortPorDescripcion(LinkedList* this);

#endif /* CONTROLLER_H_ */
