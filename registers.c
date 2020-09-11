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
					printf("[Id: %d] %s %s \n",\
							current->id, current->firstName,current->lastName);
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
	CONTACT *current=NULL;
	PHONE phones[10]={0};
	BUFFER buffer;
	int id=0, option=0;
	
	if(global.qtyContacts){
		current= global.headNodes;

		setColorText("Bold Red");
		printf("Bienvenido al submenú de modificación de registros\n");
		setColorText("Reset");
		
		setColorText("Cyan");
		printf("Introduzca ID del contacto que desea modificar\n");
		captureData(sizeof(NUMBER), &buffer);
		id = getNumber(buffer);
		setColorText("Reset");

		while (current) {
			if(current->id == id){
				break;	
			} else {
				current = current->next;
			}
		}
		
		if (!current) {
			printf("Register not found\n");
		} else {
			printf("El Id pertenece al contacto %s %s\n", current->firstName, current->lastName);
			setColorText("Cyan");
			printf("1. Cambiar nombre, 2. Cambiar Apellido, 3. Agregar Número, 4. Eliminar número, 5. Modificar número\
					, 6. Cancelar\n");
			captureData(sizeof(NUMBER), &buffer);
			option = getNumber(buffer);
			setColorText("Reset");

			switch (option) {
				case 1:
					captureData(sizeof(FIRSTNAME), &buffer);
					strcpy(current->firstName,buffer);
					break;
				case 2:
					captureData(sizeof(LASTNAME), &buffer);
					strcpy(current->lastName,buffer);
					break;
				case 3:
					switch (current->phoneQty) {
						case 10:
							printf("Max qty phones reached\n");
							break;
						case 9:
							captureData(sizeof(PHONE), &buffer);
							strcpy(current->phone_10, buffer);
							current->phoneQty++;
							printf("Nuevo número de teléfono guardado: %s\n", current->phone_10);
							break;
						case 8:
							captureData(sizeof(PHONE), &buffer);
							strcpy(current->phone_9, buffer);
							current->phoneQty++;
							printf("Nuevo número de teléfono guardado: %s\n", current->phone_9);
							break;
						case 7:
							captureData(sizeof(PHONE), &buffer);
							strcpy(current->phone_8, buffer);
							current->phoneQty++;
							printf("Nuevo número de teléfono guardado: %s\n", current->phone_8);
							break;
						case 6:
							captureData(sizeof(PHONE), &buffer);
							strcpy(current->phone_7, buffer);
							current->phoneQty++;
							printf("Nuevo número de teléfono guardado: %s\n", current->phone_7);
							break;
						case 5:
							captureData(sizeof(PHONE), &buffer);
							strcpy(current->phone_6, buffer);
							current->phoneQty++;
							printf("Nuevo número de teléfono guardado: %s\n", current->phone_6);
							break;
						case 4:
							captureData(sizeof(PHONE), &buffer);
							strcpy(current->phone_5, buffer);
							current->phoneQty++;
							printf("Nuevo número de teléfono guardado: %s\n", current->phone_5);
							break;
						case 3:
							captureData(sizeof(PHONE), &buffer);
							strcpy(current->phone_4, buffer);
							current->phoneQty++;
							printf("Nuevo número de teléfono guardado: %s\n", current->phone_4);
							break;
						case 2:
							captureData(sizeof(PHONE), &buffer);
							strcpy(current->phone_3, buffer);
							current->phoneQty++;
							printf("Nuevo número de teléfono guardado: %s\n", current->phone_3);
							break;
						case 1:
							captureData(sizeof(PHONE), &buffer);
							strcpy(current->phone_2, buffer);
							current->phoneQty++;
							printf("Nuevo número de teléfono guardado: %s\n", current->phone_2);
							break;
					}
					break;
				case 4:
					current->phoneQty--;
					break;
				case 5:
					printf("Cuál teléfono desea cambiar\n");
					switch (current->phoneQty) {
						case 10:
							strcpy(phones[9],current->phone_10);
						case 9:
							strcpy(phones[8],current->phone_9);
						case 8:
							strcpy(phones[7],current->phone_8);
						case 7:
							strcpy(phones[6],current->phone_7);
						case 6:
							strcpy(phones[5],current->phone_6);
						case 5:
							strcpy(phones[4],current->phone_5);
						case 4:
							strcpy(phones[3],current->phone_4);
						case 3:
							strcpy(phones[2],current->phone_3);
						case 2:
							strcpy(phones[1],current->phone_2);
						case 1:
							strcpy(phones[0],current->phone_1);
							break;

					for (int i; i<current->phoneQty; i++) {
						printf("Phone [%d]: %s\n",i+1,phones[i]);
					}	
					
					captureData(sizeof(NUMBER), &buffer);
					option = getNumber(buffer);

							
					}
					break;

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
