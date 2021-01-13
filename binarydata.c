#include "binarydata.h"
#include "contactstruct.h"
#include "registers.h"
#include <stdlib.h>
#include <stdio.h>

extern GLOBAL global;

int save(){
	CONTACT *start, *current;
	short contactsQuantity = 0;
	start = global.headNodes;
	current = start;
	
	// saving global variable
	FILE * globalVar;
	if (( globalVar = fopen("globalVariable.dat","w")) == NULL ) {
		printf("Program couldn't save data\n");
		return -1;
	} else {
	fwrite(&global, sizeof(global), 1, globalVar);
	contactsQuantity = global.qtyContacts;
	fclose(globalVar);
	}

	//Saving contacts		
	FILE * contactsFile;
	if (( contactsFile = fopen("contacts.dat","w")) == NULL ) {
		printf("Program couldn't save data\n");
		return -1;
	} else {
		while(contactsQuantity){
		fwrite(current,sizeof(CONTACT), 1, contactsFile);
		current = current->next;
		contactsQuantity--;
		}
		
		printf("%d contacts saved\n", global.qtyContacts);
		fclose(contactsFile);
	}

	global.saved = 1;

	return 0;
}


int chargeData(){
	CONTACT *current = NULL, *start = NULL;
	short contactCounter;

	FILE * globalVar;
	FILE * contactsFile; 


	if (( globalVar = fopen("globalVariable.dat","r")) == NULL ) {
		printf("Program couldn't charge contacts.dat\n");
		global.headNodes = NULL;
		return -1;
	} else {
		fread(&global,sizeof(global),1,globalVar);
		fclose(globalVar);
		printf("Contacts # %d, Sequence # %d\n", global.qtyContacts, global.idsequence);
	}


	if (( contactsFile = fopen("contacts.dat","r")) == NULL ) {
		printf("Program couldn't charge globalVariable.dat\n");
		global.qtyContacts = 0;
		global.idsequence = 0;
		global.headNodes = NULL;
		return -1;
	} else {
		contactCounter = global.qtyContacts;

		while(contactCounter){
			if(start == NULL){
				 if( ( start = malloc(sizeof(CONTACT)))==NULL ){ 
					printf("It couldn't be possible to allocate the memory\n");
					return -1;
				} else {
					fread(start, sizeof(CONTACT), 1, contactsFile);
					current = start;
					start->head = 1;
					global.headNodes = start;
				}

			} else {
				 if( ( current->next = malloc(sizeof(CONTACT)))==NULL ){ 
					printf("It couldn't be possible to allocate the memory\n");
					return -1;
				} else {
					current= current->next;
					fread(current, sizeof(CONTACT),1, contactsFile);
				}
			}

			contactCounter--;
		}
			fclose(contactsFile);
			current ->next = NULL;
	}

	global.saved = 1;
	
	return 0;
    
}
