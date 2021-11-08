#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "network.h"

// Compilar con: gcc main.c network.c analysis.c -o network
//C:\Users\Usuario\source\repos\Projectsl\Project\ips.txt
int main() {
    printf("Bienvenido al programa de Comandos. Elije una de las siguientes opciones insertando el numero:\n");
    printf("1. Mostrar las maquinas que responden a un ping de una red\n");
    printf("2. Muestra la configuracion de red de la maquina local\n");
    printf("3. Lanzar pings a dos dns y mostrar cual de las dos responde antes\n");
    int option;
    scanf("%d", &option);
    
    switch (option) {
    case 1: {
        //Pedimos que se introduzca la ruta del archivo que se desea
        printf("Inserta una ruta valida en la que tengas tu documento con IPs: \n");
        char ipfile[] = "";
        scanf("%s", &ipfile);

        //Mostramos por pantalla el contenido del archivo
        showFile(ipfile);
        printf("\n");

        //Lanzamos la funcion que va a lanzar el ping
        checkPing(ipfile);
        break;
    }

    case 2: {
        //Primero mostramos los adaptadores de red
        char netsh[] = "netsh interface ipv4 show interfaces";
        system(netsh);

        //Introducimos el adaptador de red del que deseemos ver más datos
        char adapter[100] = "";
        leecad(adapter, 100);

        //Llamamos a la funcion checkNet y desde ahí ya nos va a imprimir los resultados de la búsqueda
        checkNet(adapter);
        break;
    }

    case 3: {
        //Primero insertamos los dos dns que queremos comparar
        char dns1[] = "";
        char dns2[] = "";

        printf("Inserta el valor dns1: \n");
        scanf("%s", &dns1);
        printf("Inserta el valor dns2: \n");
        scanf("%s", &dns2);

        //Y luego lanzamos la funcion que los va a comparar
        compareVelocity(dns1, dns2);
        break;
    }

    default:
        //Por si el usuario introduce una opcion que no existe
        printf("La opcion no existe");
        break;
    }

    return 0;
}
