#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "analysis.h"

void checkPing(const char* file) {
    FILE* archivoIp;
    archivoIp = fopen(file, "r"); //Abrimos el archivo

    char ipbuf[256];
    if (archivoIp == NULL) {
        perror("Failed: ");
        return;
    }
    else {
        while (fgets(ipbuf, sizeof(ipbuf), archivoIp)) {
            ipbuf[strcspn(ipbuf, "\n")] = 0;

            //Preparamos el comando y la ruta donde vamos a guardar la informacion del archivo
            char ping[] = "ping -c1 -s %s > C:/result.txt";
            char cmd[256];
            sprintf(cmd, ping, ipbuf);
            printf(cmd);
            system(cmd);

            printf("\n");
            char found[256];
            if (findInFile("C:/result.txt", "Respuesta", found)) {//Buscamos normal con nuestra funcion findInFile generica
                printf("Contesta %s \n", ipbuf);
            } else {
                printf("No contesta %s \n", ipbuf);
            }

            fflush(stdout);
        }
    }

    fclose(archivoIp); //Cerrar el archivo
}

//Funcion para mostrar la informacion de los adaptadores de red
void checkNet(const char* adapter) {
    //Preparamos el comando y la ruta donde vamos a guardar la informacion del archivo
    char confName[] = "netsh interface ipv4 show config name = \"%s\" > C:/netshinfo.txt";
    char cmd[256];
    sprintf(cmd, confName, adapter);
    system(cmd); //Lanzamos el comando

    //Guardamos la salida en los chars y lanzamos la funcion genérica findInFile, 
    //que nos va a buscar dentro del archivo lo que le pidamos
    char ipAddress[256];
    if (findInFile("C:/netshinfo.txt", "Direcci", ipAddress)) {
        printf("%s", ipAddress);
    }
    
    char subnet[256];
    if (findInFile("C:/netshinfo.txt", "Prefijo de subred", subnet)) {
        printf("%s", subnet);
    }

    char gateway[256];
    if (findInFile("C:/netshinfo.txt", "Puerta de enlace", gateway)) {
        printf("%s", gateway);
    }

    char dns[256];
    if (findInFile("C:/netshinfo.txt", "Servidores DNS", dns)) {
        printf("%s", dns);
    }

    fflush(stdout);
}

//Funcion para comparar la velocidad de los DNS que hayamos insertado por pantalla
void compareVelocity(char* dns1, char* dns2) {
    char ping1[] = "ping -c1 -s %s > C:/result1.txt";
    char ping2[] = "ping -c1 -s %s > C:/result2.txt";
    char cmd[256];

    //Preparamos el comando, escribiendo en cmd el comando y ejecutandolo con cmd
    sprintf(cmd, ping1, dns1);
    printf(cmd);
    system(cmd);

    sprintf(cmd, ping2, dns2);
    printf("\n");
    printf(cmd);
    system(cmd);

    printf("\n");
    char delimiter[] = "= "; //Le decimos cual es el delimitador que debe buscar dentro de la linea que nos interesa
    char line1[256];//Aquí guardamos la informacion original de la linea, antes de extraer la parte que nos interesa
    long average1 = -1;
    if (findInFile("C:/result1.txt", "Media = ", line1)) { //Buscamos normal con nuestra funcion findInFile generica
        average1 = extractValue(line1, delimiter); //Con la funcion extractValue, nos va a extraer solamente el numero integer y lo almacenamos
    }
    
    char line2[256];
    long average2 = -1;
    if (findInFile("C:/result1.txt", "Media = ", line2)) {
        average2 = extractValue(line2, delimiter);
    }

    //Comprobamos que tengamos valores en las variables que vamos a comparar
    if (average1 == -1 && average2 == -1) {  
        printf("No he encontrado respuesta de los pings");
        return;
    }

    //Realizamos la comparacion entre las dos variables para saber cual es mas rapida
    char speed[] = "Esta %s es mas rapida que esta otra %s";
    if (average1 > average2) {
        printf(speed, dns2, dns1);
    }
    else {
        printf(speed, dns1, dns2);
    }
}