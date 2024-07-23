#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <string>
#include <iostream>
using namespace std;

int n_nombres = 0;
int n_partidos = 0;
int n_cedulas = 0;
string nombres[20];
string partidos[20];
string cedulas[200];
int votos[20] = {0};
int votos_nulos = 0;

/********************************************************************************************/

void ingresar_candidato() {
    char agregar, continuar;
    string nombre, partido, cedula;

    do {
        system("cls");

        printf("Ingrese el nombre del candidato: ");
        cin >> nombre;
        printf("Ingrese la cedula del candidato: ");
        cin >> cedula;
        printf("Ingrese el nombre del partido politico: ");
        cin >> partido;

        system("cls");

        printf("\nCandidato %s", nombre.c_str());
        printf("\nCedula %s", cedula.c_str());
        printf("\nDel partido %s", partido.c_str());

        do {
            printf("Desea agregar a este candidato: S/N\n");
            agregar = getch();
        } while (toupper(agregar) != 'S' && toupper(agregar) != 'N');

        if (toupper(agregar) == 'S') {
            nombres[n_nombres] = nombre;
            n_nombres++;
            partidos[n_partidos] = partido;
            n_partidos++;
        }
        do {
            printf("\n¿Desea continuar?: S/N\n");
            continuar = getch();
        } while (toupper(continuar) != 'S' && toupper(continuar) != 'N');
        
    } while (toupper(continuar) == 'S');
}

/********************************************************************************************/

void votar() {
    string nombre, cedula;
    char opcion;
    bool ya_voto = false;

    do {
        system("cls");
        
        if(n_nombres == 0){
            printf("No hay partidos politicos registrados aun\nIntentelo mas tarde");
            getch();
            break;
        }

        printf("Ingrese su nombre: ");
        cin >> nombre;
        printf("Ingrese su cedula: ");
        cin >> cedula;

        for (int i = 0; i < n_cedulas; i++) {
            if (cedulas[i] == cedula) {
                ya_voto = true;
                break;
            }
        }

        if (ya_voto) {
            printf("Ya ha votado anteriormente.\n");
            getch();
            break;
        }

        printf("\nLista de candidatos:\n");
        for (int i = 0; i < n_nombres; i++) {
            printf("[%d] %s - %s\n", i + 1, nombres[i].c_str(), partidos[i].c_str());
        }
        printf("[%d] Voto nulo\n", n_nombres + 1);

        int candidato;
        printf("\nIngrese el numero del candidato por el que desea votar: ");
        cin >> candidato;

        if (candidato < 1 || candidato > n_nombres + 1) {
            printf("Candidato no registrado.\n");
            getch();
        } else {
            do {
                printf("\n¿Desea guardar su voto?: S/N\n");
                opcion = getch();
            } while (toupper(opcion) != 'S' && toupper(opcion) != 'N');

            if (toupper(opcion) == 'S') {
                cedulas[n_cedulas] = cedula;
                n_cedulas++;
                if (candidato == n_nombres + 1) {
                    votos_nulos++;
                    printf("Ha votado nulo.\n");
                } else {
                    votos[candidato - 1]++;
                    printf("Gracias por votar por %s!!\n", nombres[candidato - 1].c_str());
                }
                getch();
            }
        }
    } while (toupper(opcion) == 'N');
}

/********************************************************************************************/

void mostrar_resultados() {
    system("cls");
    printf("***** RESULTADOS DE LA VOTACION *****\n");

    int total_votos = votos_nulos;
    for (int i = 0; i < n_nombres; i++) {
        total_votos += votos[i];
    }

    for (int i = 0; i < n_nombres; i++) {
        double porcentaje = (total_votos > 0) ? (votos[i] * 100.0 / total_votos) : 0;
        printf("Candidato: %s\n", nombres[i].c_str());
        printf("Partido: %s\n", partidos[i].c_str());
        printf("Votos: %d\n", votos[i]);
        printf("Porcentaje: %.2f%%\n\n", porcentaje);
    }

    double porcentaje_nulo = (total_votos > 0) ? (votos_nulos * 100.0 / total_votos) : 0;
    printf("Votos nulos: %d\n", votos_nulos);
    printf("Porcentaje de votos nulos: %.2f%%\n\n", porcentaje_nulo);

    int max_votos = -1;
    int indice_ganador = -1;
    for (int i = 0; i < n_nombres; i++) {
        if (votos[i] > max_votos) {
            max_votos = votos[i];
            indice_ganador = i;
        }
    }

    if (indice_ganador != -1) {
        printf("***** GANADOR DE LAS VOTACIONES *****\n");
        printf("Candidato: %s\n", nombres[indice_ganador].c_str());
        printf("Partido: %s\n", partidos[indice_ganador].c_str());
        printf("Votos: %d\n", votos[indice_ganador]);
        printf("Porcentaje: %.2f%%\n", (max_votos * 100.0 / total_votos));
    } else {
        printf("No hay votos registrados.\n");
    }

    getch();
}

/********************************************************************************************/

void menu() {
    char continuar, opcion;
    bool salir = false;

    do {
        system("cls");

        printf("***** MENU PRINCIPAL DEL PROGRAMA *****");
        printf("\n [1] INGRESAR CANDIDATO");
        printf("\n [2] VOTAR");
        printf("\n [3] RESULTADOS");
        printf("\n [4] SALIR");
        printf("\n\nIngrese un numero: ");
        opcion = getch();

        switch (opcion) {
            case '1': ingresar_candidato(); break;
            case '2': votar(); break;
            case '3': mostrar_resultados(); break;
            case '4':
                
                system("cls");
                
                printf("Desea salir del programa S/N");
                continuar = getch();
                if (continuar == 'N' || continuar == 'n')
                    opcion = '0';
                else if (continuar == 'S' || continuar == 's')
                    salir=true;
                break;
        }

    } while (!salir);
}

/********************************************************************************************/

int main() {
    menu();
    return 0;
}
