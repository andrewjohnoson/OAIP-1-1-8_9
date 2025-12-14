#ifndef LISTARRAY_H
#define LISTARRAY_H

#include "./AdressEntitiy.h"

struct Patient {
    int id;
    char* lastName;
    char* firstName;
    char* secondName;
    struct Adress patientAdress;
    int cardNumber;
    int polisNumber;
};

#endif