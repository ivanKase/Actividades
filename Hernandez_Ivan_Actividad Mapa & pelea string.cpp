#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <direct.h>

#define TAMANIO_MAPA 10
#define LONGITUD_MAXIMA_PALABRA 50
#define INTENTOS_MAXIMOS 6

char mapa[TAMANIO_MAPA][TAMANIO_MAPA];

// Esta es la funncuion que he creado para inicilizar el mapa
void inicializarMapa() {
    for (int i = 0; i < TAMANIO_MAPA; i++) {
        for (int j = 0; j < TAMANIO_MAPA; j++) {
            mapa[i][j] = '-';
        }
    }
}

// Función para leer posiciones desde un archivo o crearlo si no existe
void leerPosicionDesdeArchivo(const char* nombreArchivo, int* x, int* y) {
    FILE* archivo;
    fopen_s(&archivo, nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Archivo %s no encontrado. Creándolo con valores por defecto.\n", nombreArchivo);
        fopen_s(&archivo, nombreArchivo, "w");
        if (archivo == NULL) {
            printf("Error al crear el archivo %s\n", nombreArchivo);
            exit(1);
        }
        *x = rand() % TAMANIO_MAPA; // POngoo los valores por defecto 
        *y = rand() % TAMANIO_MAPA;
        fprintf(archivo, "%d %d\n", *x, *y);
        fclose(archivo);
    }
    else {
        fscanf_s(archivo, "%d %d", x, y);
        fclose(archivo);
    }
}

// Función para poder mostrar el mapa
void mostrarMapa() {
    for (int i = 0; i < TAMANIO_MAPA; i++) {
        for (int j = 0; j < TAMANIO_MAPA; j++) {
            printf("%c ", mapa[i][j]);
        }
        printf("\n");
    }
}

// Funció para jugar al ahorcado
int jugarAhorcado(const char* palabra) {
    int longitudPalabra = (int)strlen(palabra);
    char* adivinada = (char*)malloc((longitudPalabra + 1) * sizeof(char));
    if (adivinada == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }

    int intentosRestantes = INTENTOS_MAXIMOS;
    int aciertos = 0;

    for (int i = 0; i < longitudPalabra; i++) {
        adivinada[i] = '_';
    }
    adivinada[longitudPalabra] = '\0';

    while (intentosRestantes > 0 && aciertos < longitudPalabra) {
        printf("Palabra: %s\n", adivinada);
        printf("Intentos restantes: %d\n", intentosRestantes);
        printf("Introduce una letra: ");

        char letra;
        scanf_s(" %c", &letra, 1);

        int encontrada = 0;
        for (int i = 0; i < longitudPalabra; i++) {
            if (palabra[i] == letra && adivinada[i] == '_') {
                adivinada[i] = letra;
                aciertos++;
                encontrada = 1;
            }
        }

        if (!encontrada) {
            intentosRestantes--;
            printf("Letra incorrecta.\n");
        }
    }

    if (aciertos == longitudPalabra) {
        printf("\u00a1Ganaste! La palabra era: %s\n", palabra);
        free(adivinada);
        return 1;
    }
    else {
        printf("Perdiste. La palabra era: %s\n", palabra);
        free(adivinada);
        return 0;
    }
}

// Función para crear el archivo diccionario.txt y implementar todas las palabras puestas en el apartado de bibliografia del pdf
void crearDiccionario() {
    FILE* archivo;
    fopen_s(&archivo, "diccionario.txt", "w");
    if (archivo == NULL) {
        printf("Error al crear el archivo diccionario.txt\n");
        return;
    }

    const char* palabras[] = {
        "abajo", "abandonar", "abeja", "abierto", "abogado", "abrir", "abuelo", "accion", "aceite", "acelerar",
        "acento", "aceptar", "acercar", "aclarar", "acoger", "acuerdo", "adelante", "adentro", "adios", "admirar",
        "admitir", "adornar", "adulto", "afan", "afectar", "aficion", "afortunado", "afuera", "agencia", "agenda",
        "agente", "agosto", "agradable", "agradecer", "agregar", "agricultura", "agua", "agudo", "ahora", "aire",
        "alegrar", "alegria", "aleman", "alfombra", "algo", "algodon", "alguien", "almuerzo", "altura", "amar",
        "amargo", "ambicion", "amigo", "amor", "amplio", "analisis", "anciano", "animal", "aniversario", "anotar",
        "ansioso", "anterior", "antiguo", "anular", "ano", "apagar", "aparato", "aparecer", "apertura", "apetito",
        "aplaudir", "aplicar", "apoyo", "aprender", "aprobacion", "aprovechar", "arbol", "arena", "argumento", "arma",
        "armonia", "arriba", "arte", "artista", "asegurar", "asi", "asiento", "asignar", "asistir", "asociar",
        "aspecto", "aspirar", "atencion", "atentado", "atento", "atractivo", "atribuir", "aumentar", "aun", "aureola",
        "autor", "autorizado", "avance", "avanzar", "aventura", "averiguar", "ayuda", "azucar", "baile", "bailar",
        "bajar", "balanza", "balcon", "banco", "bandera", "bano", "barato", "barrera", "basico", "bastante", "bebe",
        "bebida", "belleza", "beneficio", "besar", "bien", "biblioteca", "bicho", "blanco", "bloque", "boca", "boda",
        "bolsa", "bomba", "bonito", "bosque", "brazos", "brillante", "broma", "bueno", "buscar", "caballo", "cabeza",
        "cabo", "cabra", "cacao", "cafe", "caida", "caja", "calle", "calma", "calor", "calvo"
    };

    for (int i = 0; i < sizeof(palabras) / sizeof(palabras[0]); i++) {
        fprintf(archivo, "%s\n", palabras[i]);
    }

    fclose(archivo);
    printf("El archivo diccionario.txt ha sido creado correctamente.\n");
}

// Función para elegir una palabra aleatoria del archivo: diccionario.txt
void elegirPalabraAleatoria(const char* nombreArchivo, char* palabra) {
    FILE* archivo;
    fopen_s(&archivo, nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        exit(1);
    }

    char palabras[500][LONGITUD_MAXIMA_PALABRA];
    int cantidad = 0;

    while (fgets(palabras[cantidad], LONGITUD_MAXIMA_PALABRA, archivo)) {
        palabras[cantidad][strcspn(palabras[cantidad], "\n")] = '\0'; // Eliminar salto de línea
        cantidad++;
    }

    fclose(archivo);

    srand((unsigned int)time(NULL));
    strcpy_s(palabra, LONGITUD_MAXIMA_PALABRA, palabras[rand() % cantidad]);
}

int main() {
    srand((unsigned int)time(NULL)); // Semilla para valores aleatorios
    int jugadorX, jugadorY;
    int enemigoX, enemigoY;

    inicializarMapa();
    leerPosicionDesdeArchivo("Posicion.txt", &jugadorX, &jugadorY);
    leerPosicionDesdeArchivo("PosicionEnemigo.txt", &enemigoX, &enemigoY);

    mapa[jugadorX][jugadorY] = 'X';
    mapa[enemigoX][enemigoY] = 'E';

    while (1) {
        mostrarMapa();

        printf("Introduce un movimiento (WASD para mover, Q para salir): ");
        char movimiento;
        scanf_s(" %c", &movimiento, 1);

        mapa[jugadorX][jugadorY] = '-';

        if (movimiento == 'W' || movimiento == 'w') jugadorX--;
        else if (movimiento == 'A' || movimiento == 'a') jugadorY--;
        else if (movimiento == 'S' || movimiento == 's') jugadorX++; // Movimiento hacia abajo
        else if (movimiento == 'D' || movimiento == 'd') jugadorY++;
        else if (movimiento == 'Q' || movimiento == 'q') {
            printf("Saliendo del juego...\n");
            break;
        }

        if (jugadorX < 0) jugadorX = 0;
        if (jugadorX >= TAMANIO_MAPA) jugadorX = TAMANIO_MAPA - 1;
        if (jugadorY < 0) jugadorY = 0;
        if (jugadorY >= TAMANIO_MAPA) jugadorY = TAMANIO_MAPA - 1;

        if (jugadorX == enemigoX && jugadorY == enemigoY) {
            printf("\u00a1Has encontrado al enemigo! Inicia el ahorcado.\n");

            // Crear el archivo diccionario.txt
            crearDiccionario();

            char palabra[LONGITUD_MAXIMA_PALABRA];
            elegirPalabraAleatoria("diccionario.txt", palabra);

            if (jugarAhorcado(palabra)) {
                printf("\u00a1Has derrotado al enemigo!\n");
                leerPosicionDesdeArchivo("Posicion.txt", &jugadorX, &jugadorY);
                leerPosicionDesdeArchivo("PosicionEnemigo.txt", &enemigoX, &enemigoY);
                inicializarMapa();
                mapa[enemigoX][enemigoY] = 'E';
            }
            else {
                printf("El juego ha terminado.\n");
                break;
            }
        }

        mapa[jugadorX][jugadorY] = 'X';
    }

    return 0;
}