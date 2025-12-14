#include "./OffsetEntity.h"
#include "./PatientEntity.h"

#include <string>

const int FIXED_NAMES_OFFSET = 2;
const int FIXED_ADRESS_OFFSET = 4;
const int ID_FIELD_OFFSET = 4;
const int ADRESS_FIELD_LENGTH = 8;
const int SECONDNAME_FIELD_LENGTH = 13;
const int FIRSTNAME_FIELD_LENGTH = 12;
const int LASTNAME_FIELD_LENGTH = 10;
const int CARDNUMBER_FIELD_LENGTH = 13;
const int POLISNUMBER_FIELD_LENGTH = 14;

void calculateLastNameOffset (int n, struct Patient *patientList, struct Offset &offset) {
    offset.lastNameOffset = LASTNAME_FIELD_LENGTH;

    for (int i = 0; i < n; i++) {
        int totalLength = strlen(patientList[i].lastName);

        if (totalLength > offset.lastNameOffset) {
            offset.lastNameOffset = totalLength;
        }
    }

    offset.lastNameOffset += FIXED_NAMES_OFFSET;

    return;
}

void calculateFirstNameOffset (int n, struct Patient *patientList, struct Offset &offset) {
    offset.firstNameOffset = FIRSTNAME_FIELD_LENGTH;

    for (int i = 0; i < n; i++) {
        int totalLength = strlen(patientList[i].firstName);

        if (totalLength > offset.firstNameOffset) {
            offset.firstNameOffset = totalLength;
        }
    }

    offset.firstNameOffset += FIXED_NAMES_OFFSET;

    return;
}

void calculateSecondNameOffset (int n, struct Patient *patientList, struct Offset &offset) {
    offset.secondNameOffset = SECONDNAME_FIELD_LENGTH;

    for (int i = 0; i < n; i++) {
        int totalLength = strlen(patientList[i].secondName);
        if (totalLength > offset.secondNameOffset) {
            offset.secondNameOffset = totalLength;
        }
    }

    offset.secondNameOffset += FIXED_NAMES_OFFSET;

    return;
}

void calculateAdressOffset (int n, struct Patient *patientList, struct Offset &offset) {
    offset.adressOffset = ADRESS_FIELD_LENGTH;

    for (int i = 0; i < n; i++) {
        int totalLength = strlen(patientList[i].patientAdress.street) +
                    std::to_string(patientList[i].patientAdress.houseNumber).length() + 
                    std::to_string(patientList[i].patientAdress.flatNumber).length();
        if (totalLength > offset.adressOffset) {
            offset.adressOffset = totalLength;
        }
    }

    offset.adressOffset += FIXED_ADRESS_OFFSET;

    return;
}

void calculateOtherOffsets (struct Offset &offset) {
    offset.idOffset = ID_FIELD_OFFSET;
    offset.cardNumberOffset = CARDNUMBER_FIELD_LENGTH;
    offset.polisNumberOffset = POLISNUMBER_FIELD_LENGTH;

    return;
}
