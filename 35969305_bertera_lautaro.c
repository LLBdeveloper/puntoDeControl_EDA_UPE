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
struct Personaje* buscarPorId(struct Personaje* personajes, int cantidadTotal, int id);
void mostrarPersonaje(struct Personaje* personajes, int cantidadTotal);
void mostrarTodos(struct Personaje* personajes, int cantidadTotal);
void luchar(struct Personaje* personajes, int cantidadTotal);



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
        printf("\033[34m1 - Crear personaje\n\033[0m");
        printf("\033[34m2 - Mejorar personaje\n\033[0m");
        printf("\033[34m3 - Luchar\n\033[0m");
        printf("\033[34m4 - Buscar y ver personaje\n\033[0m");
        printf("\033[34m5 - Ver todos los personajes\n\033[0m");
        printf("\033[34m0 - Salir\n\033[0m");
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
                luchar(personajes, *pContadorPersonajes);
                break;

            case 4:
                mostrarPersonaje(personajes,*pContadorPersonajes);
                break;

            case 5:
                mostrarTodos(personajes,*pContadorPersonajes);
                break;

            case 0:
                printf("EXIT\n");
                botonMenu = 0;
                break;


            default:
                printf("- ERROR - Ingreso invalido\n");
                break;
        }
    } while (botonMenu != 0);

    free(maxCharacters);
    free(personajes);

    return 0;
}

/////////////////////////
// Funciones
/////////////////////////

//funcion
// crea un nuevo struct Personaje y lo almacena directamente en el heap
void crearPersonaje(struct Personaje* listaPersonajes, int* cantidadTotal) {
    printf("\n\n\n\n\n\n");

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

    //asignar id y atributos por defecto
    nuevo->id = *cantidadTotal + 1;
    nuevo->nivel = 1;
    nuevo->vida = 10;
    nuevo->ataque = 1;
    nuevo->defensa = 1;
    nuevo->puntosMejora = 10;

    //distribuir los puntos de mejora iniciales
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



//funcion
//asigna lospuntos de mejora a un personaje buscado por nombre
void mejorarPersonaje(struct Personaje* listaPersonajes, int cantidadTotal) {
    char buscado[30];
    int auxEleccion;
    printf("\n\n\n\n\n\n");
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



//funcion
//busca personaje por nombre con aritmetica de punt
struct Personaje* buscarPorNombre(struct Personaje* personajes, int cantidadTotal, char* nombre) {
    struct Personaje* pProcesado = personajes;
    struct Personaje* encontrado = NULL;

    for (int i = 0; i < cantidadTotal; i++){
        if (strcmp((pProcesado + i)->nombre, nombre) ==0){
            encontrado = (pProcesado + i);
        }
    }
    return encontrado;
}


//funcion
//busca personaje por ID
struct Personaje* buscarPorId(struct Personaje* personajes, int cantidadTotal, int id){
    struct Personaje* pProcesado = personajes;
    struct Personaje* encontrado = NULL;

    for (int i = 0; i < cantidadTotal; i++){
        if ((pProcesado + i)->id == id){
            encontrado = (pProcesado + i);
        }
    }
    return encontrado;
}



//funcion
//mostrar personaje buscado por id
void mostrarPersonaje(struct Personaje* personajes, int cantidadTotal){
    printf("\n\n\n\n\n\n");

    int auxId;
    printf("Ingrese ID del personaje que quiere ver:");
    scanf("%d",&auxId);

    struct Personaje* encontrado = buscarPorId(personajes, cantidadTotal, auxId);
    if (encontrado == NULL){
        printf("ERROR: Personaje con ID %d no encontrado\n", auxId);
    }else{
        printf("\n - PERSONAJE ENCONTRADO!! -\n");
        printf("ID: %d\n", encontrado->id);
        printf("Nombre: %s\n", encontrado->nombre);
        printf("Nivel: %d\n", encontrado->nivel);
        printf("Vida: %d\n", encontrado->vida);
        printf("Ataque: %d\n", encontrado->ataque);
        printf("Defensa: %d\n", encontrado->defensa);
        printf("Puntos de Mejora: %d\n", encontrado->puntosMejora);
    }
}

//funcion
//mostrar todos los personajes
void mostrarTodos(struct Personaje* personajes, int cantidadTotal){

    if (cantidadTotal == 0) {
        printf("No hay personajes creados\n");
        return;
    }

    printf("\n\n- TODOS LOS PERSONAJES - \n\n");

    for(int i=0; i < cantidadTotal; i++){
        printf("ID: %d\n", (personajes + i)->id);
        printf("Nombre: %s\n", (personajes + i)->nombre);
        printf("Nivel: %d\n", (personajes + i)->nivel);
        printf("Vida: %d\n", (personajes + i)->vida);
        printf("Ataque: %d\n", (personajes + i)->ataque);
        printf("Defensa: %d\n", (personajes + i)->defensa);
        printf("Puntos de Mejora: %d\n\n\n", (personajes + i)->puntosMejora);
    }
}



//funcion
//muestra todos los personajes y se eligen dos  para ejecutar la pelea
void luchar(struct Personaje* personajes, int cantidadTotal){
    printf("\n\n\n\n\n\n");
    //verificamos que tengamos personajes creados
    if (cantidadTotal < 2) {
        printf("No hay un minimo de dos personajes creados\n");
        return;
    }
    // mostramos todos los existentes
    mostrarTodos(personajes, cantidadTotal);

    //pedimos al usuario los id
    int auxIdAtacante;
    int auxIdDefensor;
    printf("\n\n\n Seleccione dos personajes para luchar: \n\n");
    printf("\nIngrese ID del personaje que sera asignado ATACANTE:\n");
    scanf("%d", &auxIdAtacante);
    printf("\nIngrese ID del personaje que sera asignado DEFENSOR:\n");
    scanf("%d", &auxIdDefensor);
    //verifiamos que no ingrese el mismo
    if (auxIdAtacante == auxIdDefensor) {
        printf("ERROR: No se puede elegir el mismo personaje dos veces\n");
        return;
    }
    //capturamos los dos personajes que el usuario selecciona y se presentan los luchadores
    struct Personaje* atacante = buscarPorId(personajes, cantidadTotal, auxIdAtacante);
    struct Personaje* defensor = buscarPorId(personajes, cantidadTotal, auxIdDefensor);
    printf("\n\n\n\n");
    printf("\033[31m\n\n    - - - - - - - -  %s  vs %s  - - - - - - - - -\n\n\033[0m\n",atacante->nombre,defensor->nombre);


    printf("\033[32m\n\nATRIBUTOS DEL JUGADOR ATACANTE\n\n\033[0m\n");
    printf("Nombre: %s\n", atacante->nombre);
    printf("Nivel: %d\n", atacante->nivel);
    printf("Vida: %d\n", atacante->vida);
    printf("Ataque: %d\n", atacante->ataque);
    printf("Defensa: %d\n", atacante->defensa);

    printf("\033[32m\n\nATRIBUTOS DEL JUGADOR DEFENSOR\n\n\033[0m\n");
    printf("Nombre: %s\n", defensor->nombre);
    printf("Nivel: %d\n", defensor->nivel);
    printf("Vida: %d\n", defensor->vida);
    printf("Ataque: %d\n", defensor->ataque);
    printf("Defensa: %d\n", defensor->defensa);

    printf("\033[31m\n\n           !!!! ARRANCA LA PELEA !!!!  \n\n\033[0m\n",atacante->nombre,defensor->nombre);


    printf("\n\n\n\n\n\n");
    int danio = (atacante->ataque - defensor->defensa);
    defensor->vida = defensor->vida - danio;
    printf("\033[35m\n\n----- DANIO TOTAL %d ------\n\n\n\n\n \033[0m\n", danio);


    if(danio<=0){
        printf("\033[33m\nGana el defensor llamado %s!!!!!!!!!!!\n\n Recibe +2 puntos de mejora\n\033[0m\n", defensor->nombre);
        printf("\033[32mEl defensor recibe +2 puntos de mejora\n");
        defensor->puntosMejora += 2;
    }else{
        if(defensor->vida > 0){
            printf("\033[33mGana el atacante de nombre %s!!!!!!!!!!!\n\n\033[0m\n",atacante->nombre);

            printf("\033[32mEl atacante recibe +1 punto demejora\n\033[0m\n");
            atacante->puntosMejora += 1;

            printf("\033[31m\n\n\n\nSe le resta el danio a la vida del defensor! \nVida actual del defensor: %d \n\033[0m\n", defensor->vida);
            defensor->vida = defensor->vida - danio;


        }else{
            printf("\033[33m\nGana atacante de nombre %s y muere el defensor de nombre %s!!!!!!!!!!!\n\n\033[0m\n",atacante->nombre, defensor->nombre);

            printf("\033[32m El atacante de nombre %srecibe +3 puntos de mejora y sube de nivel\n\033[0m\n",atacante->nombre); //cuando muere el def
            atacante->puntosMejora += 3;
            atacante->nivel += 1;

            printf("\033[31m\n\n\n\nSe le resta el danio a la vida del defensor \nVida actual del defensor: %d \n\033[0m\n", defensor->vida);
            defensor->vida = defensor->vida - danio;
        }
    }
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

















