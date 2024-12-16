#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limpiar_pantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void entrada_combinacion(char combinacion[], size_t size) {
    printf("Jugador 1, introduce tu combinacion (4 numeros del 1 al 4, sin repeticiones): ");
    scanf_s("%4s", combinacion, size);
    limpiar_pantalla();
}

void adivinar_combinacion(const char combinacion[], size_t size, int* intentos) {
    char adivinanza[5];
    int acertado = 0;

    while (!acertado) {
        (*intentos)++;
        printf("Jugador 2, introduce tu combinacion: ");
        scanf_s("%4s", adivinanza, (unsigned)_countof(adivinanza));

        if (strlen(adivinanza) != 4 || strspn(adivinanza, "1234") != 4) {
            printf("Por favor, introduce una combinacion valida (4 numeros del 1 al 4, sin repeticiones).\n");
            continue;
        }

        if (strcmp(adivinanza, combinacion) == 0) {
            acertado = 1;
            printf("¡Felicidades! Has acertado la combinacion en %d intentos.\n", *intentos);
        }
        else {
            int posiciones_correctas = 0;
            for (int i = 0; i < 4; i++) {
                if (adivinanza[i] == combinacion[i]) {
                    posiciones_correctas++;
                }
            }
            printf("Tienes %d posiciones correctas.\n", posiciones_correctas);
        }
    }
}

int main() {
    char combinacion[5];
    int intentos = 0;

    entrada_combinacion(combinacion, sizeof(combinacion));
    adivinar_combinacion(combinacion, sizeof(combinacion), &intentos);

    return 0;
}
