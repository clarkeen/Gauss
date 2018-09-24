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
#include <stdbool.h>
#define MAX_EQUACIONES 100
#define MIN_EQUACIONES 2
#define FILA (MAX_EQUACIONES)
#define COLUMNA (FILA) + 1
#define limpiar_salto_linea() while (getchar() != '\n')
#define error(x) printf("\n- ERROR -, %s\n\n", x)

int numeroDeEcuaciones;
void pausa(void);
int validar_numero_entre(char texto[], int num_min, int num_max);
bool esCeroMatrizDiagonal(double matriz[FILA][COLUMNA], int numeroDeEcuaciones);
void resultado(double matriz[FILA][COLUMNA]);
void tamanioMatriz(double matriz[FILA][COLUMNA]);
void ordenarMatrizDiagonal(double matriz[FILA][COLUMNA], int numeroDeEcuaciones);
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
                opcion = validar_numero_entre("1 Matriz aumentada ingresada por teclado.\n"
                        "2 Matriz aumentada ingresada por el archivo \"matrizAumentada.txt\"\n"
                        "0 salir\n", 0, 2);
                switch (opcion) {
                    case 1:
                        puts("Matriz aumentada dada por el usuario.");
                        tamanioMatriz(matriz);
                        resultado(matriz);
                        break;
                    case 2:
                        puts("Matriz aumentada tomada del archivo.");
                        leerArchivo(matriz);
                        resultado(matriz);
                        break;
                }
            } while (opcion != 0);
            break;
        case 2:
            switch (*argv[1]) {
                case '1':
                    puts("Matriz aumentada dada por el usuario.");
                    tamanioMatriz(matriz);
                    resultado(matriz);
                    break;
                case '2':
                    puts("Matriz aumentada tomada del archivo.");
                    leerArchivo(matriz);
                    resultado(matriz);
                    break;
            }
            break;
    }
    return (EXIT_SUCCESS);
}

void pausa(void) {
    char i = '\0';
    puts("Presione ENTER para continuar...");
    scanf("%c", &i);
    system("clear");
}

int validar_numero_entre(char texto[], int num_min, int num_max) {
    int num, encontro;
    printf("%s\nIngrese un opción: ", texto);
    scanf("%d", &num);
    do {
        encontro = 0;
        limpiar_salto_linea();
        if (num < num_min || num > num_max) {
            system("clear");
            printf("%s", texto);
            error("ingrese un número valida.");
            printf("Ingrese un opción: ");
            scanf("%d", &num);
        } else
            encontro++;
    } while (encontro != 1);
    system("clear");
    return num;
}

void resultado(double matriz[FILA][COLUMNA]) {
    double x[FILA];
    int opcion;
    system("clear");
    puts("Matriz aumentada");
    mostrarMatriz(matriz, numeroDeEcuaciones);
    ordenarMatrizDiagonal(matriz, numeroDeEcuaciones);
    mostrarMatriz(matriz, numeroDeEcuaciones);

    opcion = validar_numero_entre("1 Eliminacion de Gauss directo.\n"
            "2 Eliminacion de Gauss simple.\n", 1, 2);
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
    }
    pausa();
}

void ordenarMatrizDiagonal(double matriz[FILA][COLUMNA], int numeroDeEcuaciones) {
    int i, j, k;
    double aux[FILA] = {0};
    do {
        for (i = 0; i < numeroDeEcuaciones; i++) {
            for (j = 0; j < numeroDeEcuaciones; j++) {
                if (matriz[i][i] == 0) {
                    for (k = 0; k < numeroDeEcuaciones + 1; k++) {
                        aux[k] = matriz[i][k];
                        matriz[i][k] = matriz[j][k];
                        matriz[j][k] = aux[k];
                    }
                }
            }
        }
    } while (esCeroMatrizDiagonal(matriz, numeroDeEcuaciones) == true);
}

bool esCeroMatrizDiagonal(double matriz[FILA][COLUMNA], int numeroDeEcuaciones) {
    int i;
    bool esCero = false;
    for (i = 0; i < numeroDeEcuaciones; i++) {
        if (matriz[i][i] == 0)
            esCero = true;
    }
    return esCero;
}

void tamanioMatriz(double matriz[FILA][COLUMNA]) {
    int i, j;
    printf("Numero de ecuaciones:");
    scanf("%d", &numeroDeEcuaciones);
    
    if (numeroDeEcuaciones > MAX_EQUACIONES)
        numeroDeEcuaciones = MAX_EQUACIONES;
    else if (numeroDeEcuaciones < MIN_EQUACIONES)
        numeroDeEcuaciones = MIN_EQUACIONES;

    for (i = 0; i < numeroDeEcuaciones; i++) {
        printf("\nECUACION %d\n", i + 1);
        for (j = 0; j < numeroDeEcuaciones; j++) {
            printf("Coeficiente %d: ", j + 1);
            scanf("%lf", &matriz[i][j]);
        }
        printf("Termino Independiente %d: ", j + 1);
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
    for (i = 0; i < numeroDeEcuaciones; i++)
        printf(" %10.6lf |", x[i]);
    puts("\n");
}

void mostrarMatriz(double matriz[FILA][COLUMNA], int numeroDeEcuaciones) {
    int i, j;
    puts("");
    for (i = 0; i < numeroDeEcuaciones; i++) {
        printf("|");
        for (j = 0; j < numeroDeEcuaciones + 1; j++)
            printf(" %10.6lf |", matriz[i][j]);
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
            matriz[i][j] /= (factor != 1) ? factor : 1;
        }

        k = (i + 1 < numeroDeEcuaciones) ? i + 1 : numeroDeEcuaciones;
        
        for (m = k; m < numeroDeEcuaciones; m++) {
            primeraColumna = matriz[m][i];
            for (n = 0; n < numeroDeEcuaciones + 1; n++)
                matriz[m][n] = matriz[m][n] - (primeraColumna * matriz[i][n]);
        }
    }


    for (i = numeroDeEcuaciones; i >= 0; i--) {
        for (j = i - 1; j >= 0; j--) {
            x[j] = (i == numeroDeEcuaciones) ? matriz[j][i] : x[j] - matriz[j][i] * x[i];
        }
    }
}

void eliminacionGaussDirecto(double matriz[FILA][COLUMNA], double x[FILA], int numeroDeEcuaciones) {
    int i, j, k;
    double primeraColumna;
    for (i = 0; i < numeroDeEcuaciones; i++) {
        for (j = i + 1; j < numeroDeEcuaciones; j++) {
            primeraColumna = matriz[j][i];
            for (k = 0; k < numeroDeEcuaciones + 1; k++)
                matriz[j][k] = matriz[j][k] - (matriz[i][k] / matriz[i][i]) * primeraColumna;
        }
    }

    for (i = numeroDeEcuaciones; i >= 0; i--) {
        for (j = 0; j < i; j++) {
            x[j] = (i == numeroDeEcuaciones) ? matriz[j][i] : x[j] - matriz[j][i] * x[i];
            x[j] /= (j == i - 1) ? matriz[j][j] : 1;
        }
    }
}

