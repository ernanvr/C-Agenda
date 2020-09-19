#include "mainmenu.h"
#include "contactstruct.h"
#include "staff_functions.h"
#include "registers.h"
#include "binarydata.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void showMainMenu(){
        BUFFER buffer;
    int validationString, number, goOn= 1;

    printf("\t\t\t\t\t AGENDA\t\t\n");
    printf("\t\t     Digite el número de opción que desea utilizar\t\t\n");
    printf("+=======================================================================================+\n");
    printf("|\t1. Crear nuevo registro\t\t\t\t");
    printf("5. Mostrar contactos\t\t|\n");
    printf("|\t2. Borrar Registro\t\t\t\t");
    printf("6. Guardar\t\t\t|\n");
    printf("|\t3. Buscar Registro\t\t\t\t");
    printf("7. Salir\t\t\t|\n");
    printf("|\t4. Modificar Registro\t\t\t\t");
    printf("8. Exportar\t\t\t|\n");
    printf("+=======================================================================================+\n");

do
{
    captureData(sizeof(NUMBER),&buffer);
    number = getNumber(buffer);
    switch (number)
    {
    case 1:
        createRegister();
	showMainMenu();
        break;
    case 2:
        deleteRegister();
	showMainMenu();
        break;
    case 3:
        seekRegister();
	showMainMenu();
        break;
    case 4:
        modifyRegister();
	showMainMenu();
        break;
    case 5:
        showRegistry(global.headNodes);
	showMainMenu();
        break;
    case 6:
        save();
	showMainMenu();
        break;
    case 7:
        exitProgram();
        break;
    case 8:
        exportdata();
	showMainMenu();
        break;
    default:
        printf("\033[0;31m");
        printf("Error: usted ha ingresado una opción inválida. Inténtelo de nuevo\n");
        printf("\033[0m");
        break;
    }
} while (goOn);
}
