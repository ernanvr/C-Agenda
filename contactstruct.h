#ifndef CONTACTSTRUCT_H
#define CONTACTSTRUCT_H
#include "typedef.h"

#define MAXPHONE 10

typedef struct Contact{
    FIRSTNAME firstName;
    LASTNAME lastName;
    PHONE phone_1;
    PHONE phone_2;
    PHONE phone_3;
    PHONE phone_4;
    PHONE phone_5;
    PHONE phone_6;
    PHONE phone_7;
    PHONE phone_8;
    PHONE phone_9;
    PHONE phone_10;
    int phoneQty;
    int head;
    int id;
    struct Contact * next;
} CONTACT;

typedef struct Global
{
    CONTACT * headNodes;
    int idsequence;
    short qtyContacts;
    unsigned short saved;
}GLOBAL;

#endif
