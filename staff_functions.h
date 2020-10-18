#ifndef STAFF_FUNCTIONS_H
#define STAFF_FUNCTIONS_H
#include "contactstruct.h"

void captureData(int typeSize, BUFFER * buffer);
int isString(char * word);
int getNumber(char * word);
void printNodesWphones(CONTACT * nodeHead);
void printNodesWophones(CONTACT * nodeHead);
void exitProgram();
void setColorText(char color[12]);
void destroyNodes();

#endif
