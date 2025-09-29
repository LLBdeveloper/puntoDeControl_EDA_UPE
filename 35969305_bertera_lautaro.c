/////////////////////////////////////////////////////////////////////////////
// Archivo: 35969305_BERTERA_LAUTARO.c
// Materia: Estructura de Datos y Algoritmos I
// Trabajo: Punto de Control - Sistema de Gestion de Personajes
//
// Alumno: Lautaro BERTERA - 35969305
// Docentes: ING. Muriel CUCCETTI | TEC. Darío LALANNE | Delfina GÓMEZ
//
// Cuatrimestre: 2° Cuatrimestre 2025
// Comision: Jueves Noche
// Fecha de entrega: 01/10/2025
//
// DESCRIPCION: Sistema de gestion de personajes para juego de cartas.
//              Permite crear personajes, mejorar atributos y simular
//              combates utilizando memoria dinámica y validación de datos.
/////////////////////////////////////////////////////////////////////////////




#include <stdio.h>
#include <stdlib.h>

struct Personaje {
    int id;              //Numero unico que identifica al personaje
    char nombre[30];    //Nombre del personaje (no puede repetirse)
    int nivel = 1;
    int vida = 10;
    int ataque = 1;
    int defensa = 1;
    int puntosMejora;   //Puntos disponibles para asignar a atributos
};



int main(){

    int contadorPersonajes;

    //pedimos un maximo de personajes y lo almacenamos en el heap
    printf("Cuantos personajes como maximo se podran registrar???  \n");
    int* maxHeap = (int*)malloc(sizeof(int));
    if (maxHeap == NULL) {
        printf("Error: No hay memoria disponible\n");
        return 1;
    }
    scanf("%d", maxHeap);
    printf("El maximo de personajes para este juego es: %d \n", *maxHeap);






}
