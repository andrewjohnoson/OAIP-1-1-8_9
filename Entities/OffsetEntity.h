#ifndef OFFSET_H
#define OFFSET_H

#include "./PatientEntity.h"

struct Offset {
    int idOffset, lastNameOffset, firstNameOffset, secondNameOffset, adressOffset,
        cardNumberOffset, polisNumberOffset;
};

void calculateLastNameOffset (int, struct Patient*, struct Offset&);
void calculateFirstNameOffset (int, struct Patient*, struct Offset&);
void calculateSecondNameOffset (int, struct Patient*, struct Offset&);
void calculateAdressOffset (int, struct Patient*, struct Offset&);
void calculateOtherOffsets (struct Offset&);

#endif