#ifndef FUNCIONES_GRUPO_H_INCLUDED
#define FUNCIONES_GRUPO_H_INCLUDED
#include "estructuras.h"
/*
Aquí deben hacer los includes de sus archivos individuales, por ejemplo:
#include "funciones_rufino.h"
 */

int solucion(int argc, char* argv[]);

char* BuscarImagenBMP(int argc, char* argv[]); //Busca el nombre de archivo. Me devuelve el puntero al nombre de la imagen, o NULL si no recibio nada

int ExisteArchivo(char* nombre_imagen); //Chequeo si tengo el archivo en carpeta

void LeerEncabezadoBMP(char* nombre_imagen, t_metadata* meta); //Leo header y saco data mas importante

t_pixel** CrearMatriz(int alto, int ancho, int profundidad); //Creo la matriz dinamica

void CargarMatriz(char* nombre_imagen, t_pixel** matriz, t_metadata meta);

//DESTRUIR MATRIZ, hay que meter esa funcion o explota todo

#endif // FUNCIONES_GRUPO_H_INCLUDED
