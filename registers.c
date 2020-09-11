#include "registers.h"
#include "contactstruct.h"
#include "staff_functions.h"
#include "mainmenu.h"
#include "typedef.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void createRegister(){
    FIRSTNAME name; 
    LASTNAME lastname;
    CONTACT * start , * current; 
    char phoneArray[MAXPHONE][sizeof(PHONE)];
    BUFFER buffer;
    int phoneCounter = 0, goOn,number;

    if (global.qtyContacts == 0)
    {
        start = NULL;
    }
    
    captureData(sizeof(FIRSTNAME), &buffer);
    strcpy(name,buffer);
    captureData(sizeof(LASTNAME), &buffer);
    strcpy(lastname,buffer);
    
    do
    {
        captureData(sizeof(PHONE), &buffer);
        strcpy(phoneArray[phoneCounter],buffer);
        goOn = 0;
        if (phoneCounter<9)
        {
            printf("¿Desea ingresar otro número?(1 para continuar, cualquier número para cancelar)\n");
            captureData(sizeof(NUMBER), &buffer);
            (number = getNumber(buffer)) == 1 ? (goOn = 1) : (goOn = 0);
        }
        phoneCounter++;
        printf("Phone numbers recorded: %d\n",phoneCounter);
    } while (goOn);

    global.idsequence == 0 ? (global.idsequence = 1) : (global.idsequence++);
    if (!start)
    {
        start = createNode(name, lastname, phoneArray, phoneCounter, 0);
        global.headNodes = start;
        global.headNodes->head = 1;
    } else
    {
        start = global.headNodes;
        current = start;
        while (current->next)
        {
            current = current->next;
        }
        current->next = createNode(name, lastname, phoneArray, phoneCounter, 0);
    }
    
    printf("Register recorded:\n");
    printNodesWphones(start);
    printf("\n\n");
    
    showMainMenu();
}

CONTACT * createNode(char * name, char * lastname, char phoneArray[MAXPHONE][sizeof(PHONE)], int phoneCounter, int id){
    CONTACT * newContact = (CONTACT *) malloc(sizeof(CONTACT));
    if(newContact == NULL){
	    printf("There is not enough memory\n");
	    exit(-1);
    }
    strcpy(newContact->firstName,name);
    strcpy(newContact->lastName,lastname);
    newContact->phoneQty = phoneCounter;
    id != 0 ? (newContact->id = id) : (newContact->id = global.idsequence);

    switch (phoneCounter)
    {
    case 10:
        sprintf(newContact->phone_10,"%s",phoneArray[9]);
    case 9:
        sprintf(newContact->phone_9,"%s",phoneArray[8]);
    case 8:
        sprintf(newContact->phone_8,"%s",phoneArray[7]);
    case 7:
        sprintf(newContact->phone_7,"%s",phoneArray[6]);
    case 6:
        sprintf(newContact->phone_6,"%s",phoneArray[5]);
    case 5:
        sprintf(newContact->phone_5,"%s",phoneArray[4]);
    case 4:
        sprintf(newContact->phone_4,"%s",phoneArray[3]);
    case 3:
        sprintf(newContact->phone_3,"%s",phoneArray[2]);
    case 2:
        sprintf(newContact->phone_2,"%s",phoneArray[1]);
    case 1:
        sprintf(newContact->phone_1,"%s",phoneArray[0]);
        break;
    default:
        printf("Error en createNode!\n");
        exit(-1);
        break;
    }
    
    newContact->next = NULL;
    global.qtyContacts++;

    return newContact;
}

void showRegistry(CONTACT * nodeHead){
    printNodesWophones(nodeHead);
}

void exportdata(){
	printf("Not built yet\n");
}

void seekRegister(){
	CONTACT *current = NULL;
	BUFFER buffer;
	int number;
	current = global.headNodes;	
	

	if (global.qtyContacts) {
		setColorText("Magenta");
		printf("Desea buscar por nombre o por apellido? (1. Nombre, 2. Apellido)\n");
		setColorText("Red");	
		captureData(sizeof(NUMBER), &buffer);
		number = getNumber(buffer);
		setColorText("Reset");

		if(number == 1 ) {
			setColorText("Bold Red");
			printf("Digite el nombre que desea buscar\n");
			setColorText("Cyan");
			captureData(sizeof(BUFFER), &buffer);
			setColorText("Reset");
			
			while (current)
			{
				if(strstr(current->firstName,buffer)){
					printf("[Id: %d] %s %s | Qty of phone numbers: %d\n",\
							current->id, current->firstName,current->lastName,\
							current->phoneQty);
					current = current->next;
				} else {
					current = current->next;
				}
			}
		} else if(number == 2){
			setColorText("Bold Red");
			printf("Digite el apellido que desea buscar\n");
			setColorText("Cyan");
			captureData(sizeof(BUFFER), &buffer);
			setColorText("Reset");
			
			while (current)
			{
				if(strstr(current->lastName,buffer)){
					printf("[Id: %d] %s %s | Qty of phone numbers: %d\n",\
							current->id, current->firstName,current->lastName,\
							current->phoneQty);
					current = current->next;
				} else {
					current = current->next;
				}
			}
		} else {
			printf("Ha elegido una opción incorrecta\n");

		}
	} else {
		printf("There are not contact saved \n");
	}

	setColorText("Magenta");
	printf("Búsqueda exitosa\n");
	setColorText("Reset");
}

void modifyRegister(){
	CONTACT *previous=NULL, *current=NULL;
	BUFFER buffer;
	int id, option;
	FIRSTNAME tempname;
	LASTNAME templastName;
	PHONE phoneNumber[10];


	if(global.qtyContacts){
		previous = global.headNodes;
		current= global.headNodes;

		setColorText("Bold Red");
		printf("Introduzca ID del contacto que desea modificar\n");
		setColorText("Red");
		captureData(sizeof(NUMBER), &buffer);
		id = getNumber(buffer);
		setColorText("Reset");

		while (current) {
			if(current->id == id){
				
			}	
		}
		
	} else {
		printf("Theren't contacts to modify\n");
	}

}

void deleteRegister(){
	CONTACT *previous = NULL, *current = NULL, *temp = NULL;
	BUFFER buffer;
	int id = 0, found = 0;


	if(global.qtyContacts){
		previous = global.headNodes;
		current= global.headNodes;

		setColorText("Magenta");
		printf("Introduzca ID del contacto que desea eliminar\n");
		setColorText("Red");
		captureData(sizeof(NUMBER), &buffer);
		id = getNumber(buffer);
		setColorText("Reset");

		while (current) {
			if(current->id == id){
				if(current->head == 1){
					if(global.qtyContacts == 1){
						global.headNodes = NULL;
						current = current->next;
					} else {
						current->head = 0;
						current = current->next;
						current->head = 1;
						global.headNodes = current;
						previous->next=NULL;
					}
					free(previous);
					found = 1;
					global.qtyContacts--;
				} else {
					temp = current;
					current = current->next;
					previous->next = current;
					temp->next = NULL;
					free(temp);
					found = 1;
					global.qtyContacts--;
				}
				printf("Registro #%d eliminado \n");
			} else {
				if(current->head == 1){
					current = current->next;
				} else {
					previous = previous->next;
					current = current->next;
				}
			}
		}

		if(!found){
			printf("Register doesn't exist\n");
		}
		
	} else {
		printf("Theren't contacts to modify\n");
	}
}
