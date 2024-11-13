#include <stdio.h>

// 1.verificar si un número es par
int par(int numero) {
    return (numero % 2 == 0) ? 1 : 0;
}

// 2. calcular la media de dos números
float media2(float a, float b) {
    return (a + b) / 2;
}

// 3. calcular la media de tres números y mostrarla
void media3(float a, float b, float c) {
    float media = (a + b + c) / 3;
    printf("La media de los tres numeros es: %.2f\n", media);
}

// 4. mostrar un saludo
void saludo() {
    printf("Hola\n");
}

// 5.verificar si un número es negativo
int negativo(int numero) {
    return (numero < 0) ? 1 : 0;
}

// 6. Realizar operaciones matemáticas y retornar el resultado
float suma(float a, float b) {
    return a + b;
}

float resta(float a, float b) {
    return a - b;
}

float multiplicacion(float a, float b) {
    return a * b;
}

float division(float a, float b) {
    if (b != 0) {
        return a / b;
    }
    else {
        printf("Error: Division por cero\n");
        return 0;
    }
}

// 7. operaciones matemáticas sin retornar nada
void suma_interna() {
    float a = 10;
    float b = 5;
    printf("Suma: %.2f\n", a + b);
}

void resta_interna() {
    float a = 10;
    float b = 5;
    printf("Resta: %.2f\n", a - b);
}

void multiplicacion_interna() {
    float a = 10;
    float b = 5;
    printf("Multiplicacion: %.2f\n", a * b);
}

void division_interna() {
    float a = 10;
    float b = 5;
    if (b != 0) {
        printf("Division: %.2f\n", a / b);
    }
    else {
        printf("Error: Division por cero\n");
    }
}

// Función principal para pruebas
int main() {
    
    printf("Es par (4): %d\n", par(4));
    printf("Media de 3.5 y 7.2: %.2f\n", media2(3.5, 7.2));
    media3(3.0, 4.5, 5.5);
    saludo();
    printf("Es negativo (-5): %d\n", negativo(-5));

    printf("Suma: %.2f\n", suma(10, 5));
    printf("Resta: %.2f\n", resta(10, 5));
    printf("Multiplicacion: %.2f\n", multiplicacion(10, 5));
    printf("Division: %.2f\n", division(10, 5));

    suma_interna();
    resta_interna();
    multiplicacion_interna();
    division_interna();

    return 0;
}
