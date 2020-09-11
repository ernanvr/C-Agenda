#ifndef SHOWREGISTRY_H
#define SHOWREGISTRY_H
#include "contactstruct.h"

void createRegister();
CONTACT * createNode(char * name, char * lastname, char phoneArray[MAXPHONE][sizeof(PHONE)], int phoneCounter, int id);
void showRegistry();
void seekRegister();
void deleteRegister();
void modifyRegister();
void exportdata();

#endif 
