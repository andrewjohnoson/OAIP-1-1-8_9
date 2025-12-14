#ifndef STRUCTARRAY_H
#define STRUCTARRAY_H

#include "./PatientEntity.h"

extern struct Patient* patientList;

void inputStructArray (void);
void inputStructArrayFromFile (void);
void saveStructAraryInFile (void);
void removeStructFromArray (void);
void calculateOffsets (void);
void outputStructArray (void);
void outputStruct (int);
void sortStructArray (void);
void findInStructArray (void);
void changeStructArray (void);
void addStructInArray (void);
void addStructInArrayFromFile (struct Patient);
int findStructByID (int);
void findStructByLastname (void);
void findStructByFirstname (void);
void findStructBySecondname (void);
void findStructByAdress (void);
void findStructByCardNumber (void);
void findStructByPolisNumber (void);

#endif