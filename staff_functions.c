#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contactstruct.h"
#include "mainmenu.h"
#include "staff_functions.h"

int getNumber(char * word){
    char * wordEnd;
    int number;
    number = strtol(word,&wordEnd,10);
    
    return number;
}

void captureData(int typeSize, BUFFER * buffer){
	int localbuffer = sizeof(BUFFER);
	int firstname = sizeof(FIRSTNAME), lastname = sizeof(LASTNAME), \
			    phone = sizeof(PHONE), number = sizeof(NUMBER);
	int validateString;
    
    if (typeSize == firstname)
    {
        printf("\033[0;34m");
        printf("Digite el nombre (máx 21 carácteres)\n");
        printf("\033[0m");
        scanf(" %21[^\n]%*[^\n]%*s",*buffer);
    }
    else if (typeSize == lastname)
    {
        printf("\033[0;34m");
        printf("Digite el apellido (máx 20 carácteres)\n");
        printf("\033[0m");
        scanf(" %20[^\n]%*[^\n]%*s",*buffer);
    }
    else if (typeSize == phone)
    {
        printf("\033[0;34m");
        printf("Digite el teléfono (máx 20 carácteres)\n");
        printf("\033[0m");
        scanf(" %13[^\n]%*[^\n]%*s",*buffer);
    }
    else if (typeSize == localbuffer)
    {
        scanf(" %21[^\n]%*[^\n]%*s",*buffer);
    }
    else if (typeSize == number)
    {
        do
        {
            printf("Digite un número (máx 9 carácteres)\n");
            scanf(" %9[^\n]%*[^\n]%*s",*buffer);
            validateString = isString(*buffer);
            if (validateString)
            {
                printf("\033[0;31m");
                printf("Error: usted ha ingresado texto. Inténtelo de nuevo\n");
                printf("\033[0m");
            }
        } while (isString(*buffer));

    } else
    {
        printf("A problem have happened\n");
        exit(-1);
    }
}

int isString(char * word){
    char * wordEnd;
    strtol(word,&wordEnd,10);
    if (strlen(wordEnd)==0)
    {
        return 0;
    } else
    {
        return 1;
    }
}

void printNodesWphones(CONTACT * nodeHead){
    CONTACT * current = nodeHead;

    if (!nodeHead)
    {
        printf("There is no register to show\n");
    } else
    {
        while (current)
        {
            printf("[Id: %d] %s %s | phone numbers: \n", current->id, current->firstName, current->lastName);
            switch (current->phoneQty)
            {
            case 10:
                printf("-10-: %s\n",current->phone_10);
            case 9:
                printf("-9-: %s\n",current->phone_9);
            case 8:
                printf("-8-: %s\n",current->phone_8);
            case 7:
                printf("-7-: %s\n",current->phone_7);
            case 6:
                printf("-6-: %s\n",current->phone_6);
            case 5:
                printf("-5-: %s\n",current->phone_5);
            case 4:
                printf("-4-: %s\n",current->phone_4);
            case 3:
                printf("-3-: %s\n",current->phone_3);
            case 2:
                printf("-2-: %s\n",current->phone_2);
            case 1:
                printf("-1-: %s\n",current->phone_1);
                break;
            default:
                printf("Error!\n");
                exit(-1);
                break;
            }
            current = current->next;
        }
    }
   
}

void printNodesWophones(CONTACT * nodeHead){
    CONTACT * current = nodeHead;

    if (!nodeHead)
    {
        printf("There is no register to show\n");
    } else
    {
        while (current)
        {
            printf("[Id: %d] %s %s | Qty of phone numbers: %d\n", current->id, current->firstName, current->lastName, current->phoneQty);
            current = current->next;
        }
    }
}

void exitProgram(){
	BUFFER buffer;
	int loopEnd = 0;
	if(global.saved==0){
		printf("Cambios no han sido guardados \n ¿Está seguro de continuar? (y/N)\n");
		while(!loopEnd){
			captureData(sizeof(BUFFER),&buffer);
			if(!strcmp(buffer,"y")){
				exit(0);
			} else if(!strcmp(buffer,"N")){
				showMainMenu();
			} else {
				printf("Has ingresado una opción inválida. Intenta de nuevo\n");
			}
		}
	} else {
		exit(0);
	}
}

void setColorText(char color[12]){
	if (!strcmp(color,"Red")) {
		printf("\033[0;31m");
	} else if(!strcmp(color,"Bold Red")){
		printf("\033[1;31m");
	} else if(!strcmp(color,"Green")){
		printf("\033[0;32m");
	} else if(!strcmp(color,"Bold Green")){
		printf("\033[1;32m");
	} else if(!strcmp(color,"Yellow")){
		printf("\033[0;33m");
	} else if(!strcmp(color,"Bold Yellow")){
		printf("\033[01;33m");
	} else if(!strcmp(color,"Blue")){
		printf("\033[0;34m");
	} else if(!strcmp(color,"Bold Blue")){
		printf("\033[1;34m");
	} else if(!strcmp(color,"Magenta")){
		printf("\033[0;35m");
	} else if(!strcmp(color,"Bold Magenta")){
		printf("\033[1;35m");
	} else if(!strcmp(color,"Cyan")){
		printf("\033[0;36m");
	} else if(!strcmp(color,"Bold Cyan")){
		printf("\033[1;36m");
	} else if(!strcmp(color,"Reset")){
		printf("\033[0m");
	} else {
		printf("Input color is wrong\n");
	}
}

