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




/////////////////////////
// Librerías
/////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/////////////////////////
// Declaracion de structs
/////////////////////////
struct Personaje {
    int id;              // Numero unico que identifica al personaje
    char nombre[30];     // Nombre del personaje (no puede repetirse)
    int nivel;
    int vida;
    int ataque;
    int defensa;
    int puntosMejora;    // Puntos disponibles para asignar a atributos
};


/////////////////////////
// Prototipos de funciones
/////////////////////////
void crearPersonaje(struct Personaje* listaPersonajes, int* cantidadTotal);
void mejorarPersonaje(struct Personaje* listaPersonajes, int cantidadTotal);
struct Personaje* buscarPorNombre(struct Personaje* personajes, int cantidadTotal, char* nombre);


/////////////////////////
// MAIN
/////////////////////////
int main() {
    int contadorPersonajes = 0;
    int* pContadorPersonajes = &contadorPersonajes;

    // pedimos un maximo de personajes y lo almacenamos en el heap
    printf("Cuantos personajes como maximo se podran registrar???\n");
    int* maxCharacters = (int*)malloc(sizeof(int));
    if (maxCharacters == NULL) {
        printf("Error: No hay memoria disponible\n");
        return 1;
    }
    scanf("%d", maxCharacters);
    printf("El maximo de personajes para este juego es: %d\n", *maxCharacters);

    // reservamos espacio en el heap para el vector de estructuras Personaje
    struct Personaje* personajes = (struct Personaje*)malloc(*maxCharacters * sizeof(struct Personaje));
    if (personajes == NULL) {
        printf("Error: No se cargo a listado de personajes\n");
        return 1;
    }

    // menu
    int botonMenu;
    do {
        printf("\n\n\n\n--- MENU ---\n\n\n");
        printf("\033[34m1. Crear personaje\n\033[0m");
        printf("\033[34m2. Mejorar personaje\n\033[0m");
        printf("\033[34m3. Luchar\n\033[0m");
        printf("\033[34m4. Salir\n\033[0m");
        printf("\n Elige una opcion: ");
        scanf("%d", &botonMenu);

        switch (botonMenu) {
            case 1:
                if (*pContadorPersonajes < *maxCharacters) {
                    crearPersonaje(personajes, pContadorPersonajes);
                } else {
                    printf("No hay mas lugar para personajes");
                }
                break;

            case 2:
                mejorarPersonaje(personajes, *pContadorPersonajes);
                break;

            case 3:
                printf("fight (a implementar)\n");
                break;

            case 4:
                printf("EXIT\n");
                botonMenu = 4;
                break;

            default:
                printf("- ERROR - Ingreso invalido\n");
                break;
        }
    } while (botonMenu != 4);

    free(maxCharacters);
    free(personajes);

    return 0;
}

/////////////////////////
// Funciones
/////////////////////////

// crea un nuevo struct Personaje y lo almacena directamente en el heap
void crearPersonaje(struct Personaje* listaPersonajes, int* cantidadTotal) {
    struct Personaje* nuevo = listaPersonajes + *cantidadTotal;
    char nombreIngresado[30];
    int valido = 0;

    // validar nombre unico
    while (!valido) {
        printf("Ingrese el nombre para su nuevo personaje: ");
        scanf("%s", nombreIngresado);

        valido = 1;
        for (int i = 0; i < *cantidadTotal; i++) {
            if (strcmp((listaPersonajes + i)->nombre, nombreIngresado) == 0) {
                printf("Ya existe un personaje con ese nombre. Usa otro.\n");
                valido = 0;
            }
        }
    }
    strcpy(nuevo->nombre, nombreIngresado);

    // asignar id y atributos por defecto
    nuevo->id = *cantidadTotal + 1;
    nuevo->nivel = 1;
    nuevo->vida = 10;
    nuevo->ataque = 1;
    nuevo->defensa = 1;
    nuevo->puntosMejora = 10;

    // distribuir los puntos de mejora iniciales
    int opcion;
    while (nuevo->puntosMejora > 0) {
        printf("\nDistribuir los puntos de mejora (%d restantes):\n", nuevo->puntosMejora);
        printf("1 - Agregar en Vida (actual: %d)\n", nuevo->vida);
        printf("2 - Agregar en ataque (actual: %d)\n", nuevo->ataque);
        printf("3 - Agregar en defensa (actual: %d)\n", nuevo->defensa);
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                nuevo->vida++;
                nuevo->puntosMejora--;
                break;
            case 2:
                nuevo->ataque++;
                nuevo->puntosMejora--;
                break;
            case 3:
                nuevo->defensa++;
                nuevo->puntosMejora--;
                break;
            default:
                printf("- ERROR - \nOpcion invalida, selecciona entre los numeros 1 / 2 / 3 \n");
                break;
        }
    }

    (*cantidadTotal)++;
    printf("\nPersonaje '%s' creado con exito! (ID: %d)\n", nuevo->nombre, nuevo->id);
    printf("Stats finales -> Vida: %d, Ataque: %d, Defensa: %d, Nivel: %d\n",
           nuevo->vida, nuevo->ataque, nuevo->defensa, nuevo->nivel);
}

// asigna lospuntos de mejora a un personaje buscado por nombre
void mejorarPersonaje(struct Personaje* listaPersonajes, int cantidadTotal) {
    char buscado[30];
    int auxEleccion;

    printf("Ingrese el nombre del personaje a mejorar: ");
    scanf("%s", buscado);

    struct Personaje* personajeActual = buscarPorNombre(listaPersonajes, cantidadTotal, buscado);

    if (personajeActual == NULL) {
        printf("\nNo existe un personaje con ese nombre.\n");
        return;
    }

    if (personajeActual->puntosMejora <= 0) {
        printf("\n%s No tiene puntos de mejora disponibles\n", personajeActual->nombre);
        return;
    }

    do {
        printf("\n%s tiene %d puntos de mejora disponibles\n", personajeActual->nombre, personajeActual->puntosMejora);
        printf("1 - Agregar en VIDA\n");
        printf("2 - Agregar en ATAQUE\n");
        printf("3 - Agregar en DEFENSA\n");
        printf("Elige una opcion: ");
        scanf("%d", &auxEleccion);

        switch (auxEleccion) {
            case 1:
                personajeActual->vida++;
                personajeActual->puntosMejora--;
                break;
            case 2:
                personajeActual->ataque++;
                personajeActual->puntosMejora--;
                break;
            case 3:
                personajeActual->defensa++;
                personajeActual->puntosMejora--;
                break;
            default:
                printf("Opcion invalida, elige 1, 2 o 3\n");
                break;
        }
    }while(personajeActual->puntosMejora > 0);

    printf("\nProceso de mejora finalizado para %s\n", personajeActual->nombre);
}

// busca personaje por nombre con aritmetica de punt
struct Personaje* buscarPorNombre(struct Personaje* personajes, int cantidadTotal, char* nombre) {
    struct Personaje* procesado = personajes;
    struct Personaje* encontrado = NULL;

    for (int i = 0; i < cantidadTotal; i++){
        if (strcmp((procesado + i)->nombre, nombre) ==0){
            encontrado = (procesado + i);
        }
    }
    return encontrado;
}


/*

consigna

void crearPersonaje(Personaje* personajes, int* cantidad);

void mejorarPersonaje(Personaje* personajes, int cantidad);

void luchar(Personaje* personajes, int cantidad);

Personaje* buscarPorNombre(Personaje* personajes, int
cantidad,  char* nombre);

Personaje* buscarPorId(Personaje* personajes, int cantidad,
int id);

void mostrarPersonaje(Personaje p);

void mostrarTodos(Personaje* personajes, int cantidad);

*/

















