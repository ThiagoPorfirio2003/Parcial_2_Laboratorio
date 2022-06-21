#include "LinkedList.h"

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

int Controller_loadFromText(LinkedList* this, int mostrarPasajero);

int Controller_ListServicios(LinkedList* this);

LinkedList* Controller_AsignarTotales(LinkedList* this);

int Controller_FiltrarPorTipo(LinkedList* this);


#endif /* CONTROLLER_H_ */
