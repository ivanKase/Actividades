#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void limpiar_pantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void inicializa_tablero(int m[4][3]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            m[i][j] = 0;
        }
    }
}

void rellenar_tablero(int m[4][3]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            m[i][j] = rand() % 9 + 1; // Generar número aleatorio entre 1 y 9
        }
    }
}

void pintar_tablero(int m[4][3]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

int cuenta_repetidos(int m[4][3]) {
    int contador[10] = { 0 }; // Contador para números del 1 al 9
    int total_repetidos = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            contador[m[i][j]]++;
        }
    }

    for (int i = 1; i <= 9; i++) {
        if (contador[i] > 1) {
            total_repetidos += (contador[i] - 1);
        }
    }

    return total_repetidos;
}

void guardar_en_fichero(int total_repetidos) {
    FILE* fichero;
    fopen_s(&fichero, "resultado.txt", "w");
    if (fichero == NULL) {
        printf("Error al abrir el fichero.\n");
        return;
    }
    fprintf(fichero, "Total de numeros repetidos en la matriz: %d\n", total_repetidos);
    fclose(fichero);
}

int main() {
    int tablero[4][3];
    char continuar;

    srand((unsigned int)time(NULL));

    do {
        inicializa_tablero(tablero);
        rellenar_tablero(tablero);
        printf("Tablero:\n");
        pintar_tablero(tablero);

        int repetidos = cuenta_repetidos(tablero);
        printf("Total de numeros repetidos en la matriz: %d\n", repetidos);

        printf("Deseas ejecutar el programa nuevamente? (s/n): ");
        scanf_s(" %c", &continuar, 1);
    } while (continuar == 's' || continuar == 'S');

    int repetidos = cuenta_repetidos(tablero);
    guardar_en_fichero(repetidos);

    return 0;
}
