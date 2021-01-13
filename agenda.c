/* Agenda: utilización de listas enlazadas y manejo de ficheros binarios */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contactstruct.h"
#include "mainmenu.h"
#include "binarydata.h"

GLOBAL global; 

void clearScreen();

int main(void){
    chargeData();
    showMainMenu();
    return 0;
}

