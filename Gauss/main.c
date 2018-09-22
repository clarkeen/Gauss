/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: desktop
 *
 * Created on 17 de septiembre de 2018, 17:03
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX_EQUACIONES 100
#define MIN_EQUACIONES 2
#define FILA (MAX_EQUACIONES)
#define COLUMNA (FILA) + 1

int numeroDeEcuaciones;
void resultado(double matriz[FILA][COLUMNA]);
void tamanioMatriz(double matriz[FILA][COLUMNA]);
void mostrarFila(double x[FILA], int numeroDeEcuaciones);
void mostrarMatriz(double matriz[FILA][COLUMNA], int numeroDeEcuaciones);
void leerArchivo(double matriz[FILA][COLUMNA]);
void eliminacionGaussSimple(double matriz[FILA][COLUMNA], double x[FILA], int numeroDeEcuaciones);
void eliminacionGaussDirecto(double matriz[FILA][COLUMNA], double x[FILA], int numeroDeEcuaciones);

/*
 * 
 */
int main(int argc, char** argv) {
    int opcion;
    double matriz[FILA][COLUMNA];
    switch (argc) {
        case 1:
        do {
            printf("1 Matriz ingresada por teclado.\n"
                    "2 Matriz ingresada por el archivo \"matrizAumentada.txt\"\n"
                    "0 salir\n"
                    "Ingrese un opción: ");
            scanf("%d", &opcion);
            switch (opcion) {
                case 1:
                    puts("La matriz aumentada dada por el usuario.");
                    tamanioMatriz(matriz);
                    resultado(matriz);
                    break;
                case 2:
                    puts("La matriz aumentada tomada del archivo.");
                    leerArchivo(matriz);
                    resultado(matriz);
                    break;
                default:
                    puts("- ERROR -\nIngrese una opción valida");
                    break;
            }
        } while (opcion != 0);
        break;
        case 2:
        switch (*argv[1]) {
            case '1':
                puts("La matriz aumentada dada por el usuario.");
                tamanioMatriz(matriz);
                resultado(matriz);
                break;
            case '2':
                puts("La matriz aumentada tomada del archivo.");
                leerArchivo(matriz);
                resultado(matriz);
                break;
            default:
                puts("- ERROR -\nIngrese una opción valida");
                break;
        }
        break;
    }
    return (EXIT_SUCCESS);
}

void resultado(double matriz[FILA][COLUMNA]) {
    double x[FILA];
    int opcion;

    printf("1 Eliminacion de Gauss directo.\n"
            "2 Eliminacion de Gauss simple.\n"
            "Ingrese un opción: ");
    scanf("%d", &opcion);
    switch (opcion) {
        case 1:
            mostrarMatriz(matriz, numeroDeEcuaciones);
            puts("Eliminacion de Gauss directo");
            eliminacionGaussDirecto(matriz, x, numeroDeEcuaciones);
            mostrarMatriz(matriz, numeroDeEcuaciones);
            puts("resultado de las x");
            mostrarFila(x, numeroDeEcuaciones);
            break;
        case 2:
            mostrarMatriz(matriz, numeroDeEcuaciones);
            puts("Eliminacion de Gauss simple");
            eliminacionGaussSimple(matriz, x, numeroDeEcuaciones);
            mostrarMatriz(matriz, numeroDeEcuaciones);
            puts("resultado de las x");
            mostrarFila(x, numeroDeEcuaciones);
            break;
        default:
            puts("- ERROR -\nIngrese una opción valida");
            break;
    }

}

void tamanioMatriz(double matriz[FILA][COLUMNA]) {
    int i, j;
    printf("Numero de ecuaciones:");
    scanf("%d", &numeroDeEcuaciones);
    printf("\n");
    if (numeroDeEcuaciones > MAX_EQUACIONES) {
        numeroDeEcuaciones = MAX_EQUACIONES;

    } else if (numeroDeEcuaciones < MIN_EQUACIONES) {
        numeroDeEcuaciones = MIN_EQUACIONES;
    }

    for (i = 0; i < numeroDeEcuaciones; i++) {
        printf("ECUACION %d\n", i + 1);
        for (j = 0; j < numeroDeEcuaciones; j++) {
            printf("\nCoeficiente %d: ", j + 1);
            scanf("%lf", &matriz[i][j]);
        }
        printf("\nTermino Independiente %d: ", j + 1);
        scanf("%lf", &matriz[i][j]);
    }
}

void leerArchivo(double matriz[FILA][COLUMNA]) {
    FILE* f;
    int i, j;
    double num;
    f = fopen("matrizAumentada.txt", "r");
    fscanf(f, "%d", &numeroDeEcuaciones);
    for (i = 0; i < numeroDeEcuaciones; i++) {
        for (j = 0; j < numeroDeEcuaciones + 1; j++) {
            fscanf(f, "%lf", &num);
            matriz[i][j] = num;
        }
    }
    fclose(f);
}

void mostrarFila(double x[FILA], int numeroDeEcuaciones) {
    int i;
    puts("");
    printf("|");
    for (i = 0; i < numeroDeEcuaciones; i++) {
        printf(" %10.6lf |", x[i]);
    }
    puts("\n");
}

void mostrarMatriz(double matriz[FILA][COLUMNA], int numeroDeEcuaciones) {
    int i, j;
    puts("");
    for (i = 0; i < numeroDeEcuaciones; i++) {
        printf("|");
        for (j = 0; j < numeroDeEcuaciones + 1; j++) {
            printf(" %10.6lf |", matriz[i][j]);
        }
        puts("");
    }
    puts("");
}

void eliminacionGaussSimple(double matriz[FILA][COLUMNA], double x[FILA], int numeroDeEcuaciones) {

    int i, j, k, m, n;
    double factor, primeraColumna;

    for (i = 0; i < numeroDeEcuaciones; i++) {
        factor = matriz[i][i];
        for (j = i; j < numeroDeEcuaciones + 1; j++) {
            if (factor != 1) {
                matriz[i][j] = matriz[i][j] / factor;
            }
        }
        if (i + 1 < numeroDeEcuaciones) {
            k = i + 1;
        } else {
            k = numeroDeEcuaciones;
        }
        for (m = k; m < numeroDeEcuaciones; m++) {
            primeraColumna = matriz[m][i];
            for (n = 0; n < numeroDeEcuaciones + 1; n++) {
                matriz[m][n] = matriz[m][n] - (primeraColumna * matriz[i][n]);
            }
        }
    }


    for (i = numeroDeEcuaciones; i >= 0; i--) {
        for (j = i - 1; j >= 0; j--) {
            if (i == numeroDeEcuaciones) {
                x[j] = matriz[j][i];
            } else {
                x[j] -= matriz[j][i] * x[i];
            }
        }
    }
}

void eliminacionGaussDirecto(double matriz[FILA][COLUMNA], double x[FILA], int numeroDeEcuaciones) {
    int i, j, k;
    double primeraColumna;
    for (i = 0; i < numeroDeEcuaciones; i++) {
        for (j = i + 1; j < numeroDeEcuaciones; j++) {
            primeraColumna = matriz[j][i];
            for (k = 0; k < numeroDeEcuaciones + 1; k++) {
                matriz[j][k] = matriz[j][k] - (matriz[i][k] / matriz[i][i]) * primeraColumna;
            }
        }
    }

    for (i = numeroDeEcuaciones; i >= 0; i--) {
        for (j = 0; j < i; j++) {
            if (i == numeroDeEcuaciones) {
                x[j] = matriz[j][i];
            } else {
                x[j] -= matriz[j][i] * x[i];
            }
            if (j == i - 1) {
                x[j] /= matriz[j][j];
            }
        }
    }
}

