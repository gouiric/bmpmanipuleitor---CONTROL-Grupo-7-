/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------
    Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------
	Apellido:
    Nombre:
    DNI:
    Entrega:
    -----------------
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones_grupo.h"

int solucion(int argc, char* argv[])
{

    char* nombre_imagen = BuscarImagenBMP(argc, argv);

    t_metadata meta; //Aca guardo toda la metadata del header

    if(nombre_imagen == NULL)
    {
        printf("ERROR: No se ingreso ninguna imagen .bmp\n");

        return 1;
    }

    if(ExisteArchivo(nombre_imagen)==0)
    {
        printf("ERROR: El archivo %s no existe en la carpeta.\n", nombre_imagen);

        return 1;
    }

    LeerEncabezadoBMP(nombre_imagen, &meta);

    t_pixel** matriz = CrearMatriz(meta.alto, meta.ancho, meta.profundidad);

    if(matriz == NULL)
    {
        printf("ERROR: Sin memoria para la ejecucion del programa.\n");
        return 1;
    }

    CargarMatriz(nombre_imagen, matriz, meta);



    //GuardarImagenModificada

    //DESTRUIR MATRIZ

    return 0;

}

char* BuscarImagenBMP(int argc, char* argv[])
{
    int i;

    for(i = 1; i < argc; i++) //Recorro desde 1 para saltar el nombre del ejecutable
    {
        if(strstr(argv[i], ".bmp"))
        {
            return argv[i]; //Me devuelve el nombre de la imagen
        }
    }

    return NULL; //Si llego al final de argv y no encuentro nada
}

int ExisteArchivo(char* nombre_imagen)
{
    FILE* archivo = fopen(nombre_imagen, "rb"); //

    if(archivo==NULL)
    {
        return 0;//No existe el archivo en carpeta
    }

    fclose(archivo);
    return 1;
}

void LeerEncabezadoBMP(char* nombre_imagen, t_metadata* meta)
{
    unsigned char filler[4]; //Para meter el relleno del header que no sirve. Como el salto de filler mas grande que voy a tener es de 4 bytes, uso ese tamanio

    FILE* archivo = fopen(nombre_imagen, "rb");

    fread(filler, 1, 2, archivo);
    fread(&meta->tamArchivo, 1, 4, archivo);
    fread(filler, 1, 4, archivo);
    fread(&meta->tamEncabezado, 1, 4, archivo);
    fread(filler, 1, 4, archivo);
    fread(&meta->ancho, 1, 4, archivo);
    fread(&meta->alto, 1, 4, archivo);
    fread(filler, 1, 2, archivo);
    fread(&meta->profundidad, 1, 2, archivo);

    printf("Ancho: %u px - Alto: %u px - Profundidad: %u bits\n", meta->ancho, meta->alto, meta->profundidad);

    fclose(archivo);
}

t_pixel** CrearMatriz(int alto, int ancho, int profundidad)
{
    int i;

    t_pixel** matriz = malloc(alto * sizeof(t_pixel*)); //Como aca van a ir las direcciones de memoria en las que cuelgo las columnas necesito 8 bytes, por eso t_pixel*.

    if(matriz == NULL)
    {
        return NULL;
    }

    for(i=0; i < alto; i++) //Aca guardo los pixeles reales, necesito los 3 colores (3 bytes) asi que no hace falta sizeof t_pixel*, con el tamanio real de 3 bytes estoy bien
    {
        matriz[i] = malloc(ancho * (profundidad/8));

        if(matriz[i] == NULL)
        {
            return NULL;
        }
    }

    return matriz; //Devuelvo matriz dinamica creada
}


void CargarMatriz (char* nombre_imagen, t_pixel** matriz, t_metadata meta) //Hago una copia de la foto, pero por ahora sigue en RAM
{
    unsigned char filler[200]; //El header de un BMP nunca va a superar esto

    unsigned int i,j;

    FILE* archivo = fopen(nombre_imagen, "rb");

    fread(filler, 1, meta.tamEncabezado, archivo); //Voy leyendo y me detengo en el primer pixel para empezar a recorrer la matriz

    for(i=0; i<meta.alto; i++)
    {
        for(j=0; j<meta.ancho; j++)
    {
        fread(matriz[i][j].pixel, 1, 3, archivo); //Guardo los 3 bytes de color en el casillero
    }
    }

    fclose(archivo);
}

GuardarImagenModificada
