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
//              combates utilizando memoria dinamica y validacion de datos.
/////////////////////////////////////////////////////////////////////////////



//librerias
#include <stdio.h>
#include <stdlib.h>

//declaracion de structs
struct Personaje {
    int id;              //Numero unico que identifica al personaje
    char nombre[30];     //Nombre del personaje (no puede repetirse)
    int nivel;
    int vida;
    int ataque ;
    int defensa ;
    int puntosMejora;   //Puntos disponibles para asignar a atributos
};

//prototipo de funciones
void crearPersonaje(struct Personaje* listaPersonajes, int* cantidadTotal);
void mejorarPersonaje();

/////////
//MAIN
////////
int main(){

    int contadorPersonajes=0;



    //pedimos un maximo de personajes y lo almacenamos en el heap
    printf("Cuantos personajes como maximo se podran registrar???  \n");
    int* maxCharacters = (int*)malloc(sizeof(int));
    if (maxCharacters == NULL) {
        printf("Error: No hay memoria disponible\n");
        return 1;
    }
    scanf("%d", maxCharacters);
    printf("El maximo de personajes para este juego es: %d \n", *maxCharacters);




    //reservamos espacio en el heap para el vector de estructuras Personaje
    struct Personaje* personajes = (struct Personaje*)malloc(*maxCharacters * sizeof(struct Personaje));
    if (personajes == NULL) {
        printf("Error: No se cargo a listado de personajes\n");
        return 1;
    }




    //menu
    int botonMenu;
    do{
        printf("\n\n\n\n--- MENU ---\n\n\n");
        printf("\033[34m1. Crear personaje\n\033[0m");// \033[34m \033[0m  ES SOLO PARA PONER COLOR AL PRINTF()
        printf("\033[34m2. Mejorar personaje\n\033[0m");
        printf("\033[34m3. Luchar\n\033[0m");
        printf("\033[34m4. Salir\n\033[0m");
        printf("\n Elige una opcion: \n");
        scanf("%d", &botonMenu);

        switch (botonMenu) {
            case 1:
                //aca agregar condicion de maximo
                //de personajes antes de ejecutar la funcion
                if(contadorPersonajes < *maxCharacters){
                crearPersonaje(personajes,&contadorPersonajes);
                }else{
                    printf("No hay mas lugar para personajes.");
                }
                break;

            case 2:
                printf("improve");
                break;

            case 3:
                printf("fight");
                break;

            case 4:
                printf("EXIT");
                botonMenu=4;
                break;

            default:
                printf("ERROR");
                break;
        }
    }while(botonMenu!=4);

    free(maxCharacters);
    free(personajes);


    return 0;
}


///////////////
//Funciones
//////////////


//crea un nuevo struct Personaje y lo almacena directamente en el heap
void crearPersonaje(struct Personaje* listaPersonajes, int* cantidadTotal){

    //creamos una nueva instancia de struct personaje
    struct Personaje* nuevo;
    nuevo = listaPersonajes + *cantidadTotal;

    nuevo->id = *cantidadTotal + 1;
    nuevo->nivel = 1;
    nuevo->vida = 10;
    nuevo->ataque = 1;
    nuevo->defensa = 1;
    nuevo->puntosMejora = 10;
    //pedimos nombre del personaje nuevo al usuario
    //falta cambiar scanf por fgets
    //falta verificar si no existe otro nombre igual
    printf("Ingrese el nombre para su nuevo personaje:\n");
    scanf("%s",nuevo->nombre);

    //actualizamos el total de personajes
    (*cantidadTotal)++;


    printf("cantidad actual de PJs %d\n",*cantidadTotal);


// llamar funcion mejorar pj
    mejorarPersonaje();
}


void mejorarPersonaje(){
    printf("mejorando pj, soy la funcion\n");
}






/*
(listaPersonajes + *cantidadTotal)->id = *cantidadTotal + 1;
scanf("%s", (listaPersonajes + *cantidadTotal)->nombre);
(listaPersonajes + *cantidadTotal)->nivel = 1;
(listaPersonajes + *cantidadTotal)->vida = 10;

(*cantidadTotal)++;

*/




/*

consigna

void crearPersonaje(Personaje* personajes, int* cantidad);

void mejorarPersonaje(Personaje* personajes, int cantidad);

void luchar(Personaje* personajes, int cantidad);

Personaje* buscarPorNombre(Personaje* personajes, int
cantidad, const char* nombre);

Personaje* buscarPorId(Personaje* personajes, int cantidad,
int id);

void mostrarPersonaje(Personaje p);

void mostrarTodos(Personaje* personajes, int cantidad);

*/



