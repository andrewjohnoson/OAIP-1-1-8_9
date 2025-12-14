#include "./StructArrayEntity.h"
#include "./BufferEntity.h"
#include "./MenuEntity.h"
#include "./InputEntity.h"
#include "./OffsetEntity.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <locale>
#include <sstream>
#include <fstream>

int structArraySize = 0;

struct Patient* patientList = nullptr;
struct Offset offset {};

void inputStructArray (void) {
    if (patientList != nullptr) {
        delete []patientList;
        patientList = nullptr;
    }
    
    std::cout << "Введите число структур, которое хотите ввести: ";

    structArraySize = inputNatural();
    std::cout << std::endl;

    patientList = new struct Patient[structArraySize];

    for (int i = 0; i < structArraySize; i++) {

        patientList[i].id = i + 1;

        std::cout << "Введите фамилию " << i + 1 << "-го пациента: ";
        patientList[i].lastName = inputNames();
        
        std::cout << "Введите имя " << i + 1 << "-го пациента: ";
        patientList[i].firstName = inputNames();

        std::cout << "Введите отчество " << i + 1 << "-го пациента: ";
        patientList[i].secondName = inputNames();

        std::cout << "Введите адрес " << i + 1 << "-го пациента (улица): ";
        patientList[i].patientAdress.street = inputNames();

        std::cout << " (номер дома) ";
        patientList[i].patientAdress.houseNumber = inputInteger();
        std::cout << " (номер квартиры) ";
        patientList[i].patientAdress.flatNumber = inputInteger();

        std::cout << "Введите номер медицинской карты: " << i + 1 << "-го пациента: ";
        patientList[i].cardNumber = inputInteger();

        std::cout << "Введите номер стархового полиса: " << i + 1 << "-го пациента: ";
        patientList[i].polisNumber = inputInteger();
        std::cout << std::endl;
    }
    
    std::cout << std::endl;
    return;
}

void removeStructFromArray (void) {
    if (structArraySize == 0) {
        std::cout << "В массиве нету элементов." << std::endl << std::endl;
        return;
    }

    std::cout << "В массиве есть структуры со следующими ID: ";
    for (int i = 0; i < structArraySize; i++) {
        std::cout << patientList[i].id << " ";
    }

    std::cout << std::endl;

    int idOfStruct;

    std::cout << "Какую хотите удалить? Ответ: ";

    std::cin >> idOfStruct;
    clearCinBuffer();
    
    if (idOfStruct < 1) {
        std::cout << "В массиве не может быть структуры с таким ID." << std::endl;
        return;
    }

    int posOfStruct = findStructByID(idOfStruct);

    if (posOfStruct == -1) {
        std::cout << "В массиве нет структуры с таким ID." << std::endl;
        return;
    }

    struct Patient *tempArray = new struct Patient[structArraySize - 1];
    
    for (int i = 0; i < posOfStruct; i++) {
        tempArray[i] = patientList[i];
    }

    for (int i = posOfStruct; i < structArraySize - 1; i++) {
        tempArray[i] = patientList[i + 1];
    }

    structArraySize--;

    delete []patientList;
    patientList = tempArray;
    tempArray = nullptr;

    return;
}

void calculateOffsets (void) {
    calculateLastNameOffset(structArraySize, patientList, offset);
    calculateFirstNameOffset(structArraySize, patientList, offset);
    calculateSecondNameOffset(structArraySize, patientList, offset);
    calculateAdressOffset(structArraySize, patientList, offset);
    calculateOtherOffsets(offset);

    return;
}

void outputStructArray (void) {
    setlocale(LC_ALL, "ru_RU");

    if (structArraySize == 0) {
        std::cout << "В массиве нету элементов." << std::endl << std::endl;
        return;
    }

    calculateOffsets();
                
    std::cout << std::left << std::setw(offset.idOffset) << "ID" << " | " <<
                std::setw(offset.lastNameOffset) << "Lastname" << " | " <<
                std::setw(offset.firstNameOffset) << "First name" << " | " <<
                std::setw(offset.secondNameOffset) << "Second name" << " | " <<
                std::setw(offset.adressOffset) << "Adress" << " | " <<
                std::setw(offset.cardNumberOffset) << "Card number" << " | " <<
                std::setw(offset.polisNumberOffset) << "Polis number";

    std::cout << std::endl; 

    int n = offset.idOffset + offset.lastNameOffset + offset.firstNameOffset +
            offset.secondNameOffset + offset.adressOffset + offset.cardNumberOffset + offset.polisNumberOffset;

    n += 18;

    for (int i = 0; i < n; i++) {
        std::cout << "-";
    }

    std::cout << std::endl;

    for (int i = 0; i < structArraySize; i++) {
        std::ostringstream adressString;
        adressString << patientList[i].patientAdress.street << ", " << patientList[i].patientAdress.houseNumber << ", "
            << patientList[i].patientAdress.flatNumber;

        std::cout << std::left << std::setw(offset.idOffset) << patientList[i].id << " | " <<
                    std::setw(offset.lastNameOffset) << patientList[i].lastName << " | " <<
                    std::setw(offset.firstNameOffset) << patientList[i].firstName << " | " <<
                    std::setw(offset.secondNameOffset) << patientList[i].secondName << " | ";
        std::cout << std::left << std::setw(offset.adressOffset) << adressString.str() << " | ";
        std::cout << std::left << std::setw(offset.cardNumberOffset) << patientList[i].cardNumber << " | "
                << std::setw(offset.polisNumberOffset) << patientList[i].polisNumber;
        std::cout << std::endl;
    } 
    
    std::cout << std::endl;
    
    return;
}

void outputStruct (int posOfStruct) {
    std::cout << "ID: " << patientList[posOfStruct].id<< std::endl;
    std::cout << "Фамилия: " << patientList[posOfStruct].lastName << std::endl;
    std::cout << "Имя: " << patientList[posOfStruct].firstName << std::endl;
    std::cout << "Отчество: " << patientList[posOfStruct].secondName << std::endl;
    std::cout << "Адрес: (улица) " << patientList[posOfStruct].patientAdress.street <<
            " (дом) "  << patientList[posOfStruct].patientAdress.houseNumber <<
            " (квартира) " << patientList[posOfStruct].patientAdress.flatNumber << std::endl;
    std::cout << "Номер медицинской карты: " << patientList[posOfStruct].cardNumber << std::endl;
    std::cout << "Номер страхового полиса: " << patientList[posOfStruct].polisNumber << std::endl;
    std::cout << std::endl;

    return;
}

void sortStructArray (void) {
    if (structArraySize == 0) {
        std::cout << "В массиве нету элементов." << std::endl << std::endl;
        return;
    }

    for (int i = 0; i < structArraySize - 1; i++) {
        for (int j = i + 1; j < structArraySize; j++) {
            if (patientList[i].lastName[0] > patientList[j].lastName[0]) {
                struct Patient temp = patientList[j];
                patientList[j] = patientList[i];
                patientList[i] = temp;
            }
        }
    }

    return;
}

void findInStructArray (void) {
    if (structArraySize == 0) {
        std::cout << "В массиве нету элементов." << std::endl << std::endl;
        return;
    }

    do {
        switch (searchMenu()) {
            case 1:
                findStructByLastname();
                break;
            case 2:
                findStructByFirstname();
                break;
            case 3:
                findStructBySecondname();
                break;
            case 4:
                findStructByAdress();
                break;
            case 5:
                findStructByCardNumber();
                break;
            case 6:
                findStructByPolisNumber(); 
                break;
            case 7:
                std::cout << "Выход." << std::endl;
                return;
        }
    } while (1);

    std::cout << std::endl;
    
    return;
}

void changeStructArray (void) {
    if (structArraySize == 0) {
        std::cout << "В массиве нету элементов." << std::endl << std::endl;
        return;
    }

    std::cout << "В массиве есть структуры со следующими ID: ";
    for (int i = 0; i < structArraySize; i++) {
        std::cout << patientList[i].id << " ";
    }

    std::cout << std::endl;

    int idOfStruct;

    std::cout << "Какую хотите изменить? Ответ: ";
    
    std::cin >> idOfStruct;
    clearCinBuffer();

    if (idOfStruct < 1) {
        std::cout << "В массиве не может быть структуры с таким ID." << std::endl;
        return;
    }

    int posOfStruct = findStructByID(idOfStruct);

    if (posOfStruct == -1) {
        std::cout << "В массиве нет элемента с данным ID.";
        return;
    }

    do {
        switch (editingMenu()) {
            case 1:
                std::cout << "Введите фамилию пациента: ";
                std::cin.get(patientList[posOfStruct].lastName, 31);
                
                std::cout << std::endl;
                
                clearCinBuffer();
                break;
            case 2:
                std::cout << "Введите имя пациента: ";
                std::cin.get(patientList[posOfStruct].firstName, 31);

                std::cout << std::endl;

                clearCinBuffer();
                break;
            case 3:
                std::cout << "Введите отчество пациента: ";
                std::cin.get(patientList[posOfStruct].secondName, 31);

                std::cout << std::endl;

                clearCinBuffer();
                break;
            case 4:
                std::cout << "Введите адрес пациента (улциа): ";
                std::cin.get(patientList[posOfStruct].patientAdress.street, 31);

                std::cout << " (номер дома) ";
                std::cin >> patientList[posOfStruct].patientAdress.houseNumber;

                std::cout << " (номер квартиры) ";
                std::cin >> patientList[posOfStruct].patientAdress.flatNumber;

                std::cout << std::endl;

                clearCinBuffer();
                break;
            case 5:
                std::cout << "Введите номер медицинской карты пациента: ";
                std::cin >> patientList[posOfStruct].cardNumber;

                std::cout << std::endl;

                clearCinBuffer();
                break;
            case 6:
                std::cout << "Введите номер страхового полиса пациента: ";
                std::cin >> patientList[posOfStruct].polisNumber;

                std::cout << std::endl;

                clearCinBuffer();
                break;
            case 7:
                std::cout << "Выход." << std::endl;
                return;
            }
    } while (1);

    return;
}

int findStructByID (int idOfStruct) {
    int posOfStruct = -1;

    for (int i = 0; i < structArraySize; i++) {
        if (patientList[i].id == idOfStruct) {
            posOfStruct = i;
            break;
        }
    }
    
    return posOfStruct;
}

void findStructByLastname (void) {
    int posOfStruct = -1;

    std::cout << "Введите фамилию, по которой хотим найти пациента: ";

    char lastname[31];
    std::cin.getline(lastname, 31);

    std::cout << std::endl;

    for (int i = 0; i < structArraySize; i++) {
        if (strcmp(patientList[i].lastName, lastname) == 0) {
            posOfStruct = i;
            break;
        }
    }

    if (posOfStruct == -1) {
        std::cout << "Нету пациента с такой фамилией." << std::endl;
    } else {
        outputStruct(posOfStruct);
    }

    std::cout << std::endl;

    return;
}

void findStructByFirstname (void) {
    int posOfStruct = -1;

    std::cout << "Введите имя, по которому хотим найти пациента: ";

    char firstname[31];
    std::cin.getline(firstname, 31);

    std::cout << std::endl;

    for (int i = 0; i < structArraySize; i++) {
        if (strcmp(patientList[i].firstName, firstname) == 0) {
            posOfStruct = i;
            break;
        }
    }

    if (posOfStruct == -1) {
        std::cout << "Нету пациента с таким именемы." << std::endl;
    } else {
        outputStruct(posOfStruct);
    }

    std::cout << std::endl;

    return;
}

void findStructBySecondname (void) {
    int posOfStruct = -1;

    std::cout << "Введите отчество, по которому хотим найти пациента: ";

    char secondname[31];
    std::cin.getline(secondname, 31);

    std::cout << std::endl;

    for (int i = 0; i < structArraySize; i++) {
        if (strcmp(patientList[i].secondName, secondname) == 0) {
            posOfStruct = i;
            break;
        }
    }

    if (posOfStruct == -1) {
        std::cout << "Нету пациента с таким отчеством." << std::endl;
    } else {
        outputStruct(posOfStruct);
    }

    std::cout << std::endl;

    return;
}

void findStructByAdress (void) {
    int posOfStruct = -1;
    char street[31];
    int houseNumber, flatNumber;

    std::cout << "Введите адрес, по которому хотим найти: (улица) ";
    std::cin.getline(street, 31);
    
    std::cout << " (дом) ";
    std::cin >> houseNumber;

    std::cout << " (квартира) ";
    std::cin >> flatNumber;

    std::cout << std::endl;

    for (int i = 0; i < structArraySize; i++) {
        if (strcmp(patientList[i].patientAdress.street, street) == 0 &&
                patientList[i].patientAdress.houseNumber == houseNumber &&
                patientList[i].patientAdress.flatNumber == flatNumber) {
            posOfStruct = i;
            break;
        }
    }

    if (posOfStruct == -1) {
        std::cout << "Нету пациента с такой фамилией." << std::endl;
    } else {
        outputStruct(posOfStruct);
    }

    std::cout << std::endl;

    return;
}

void findStructByCardNumber (void) {
    int posOfStruct = -1;

    std::cout << "Введите номер медицинской карты, по которому хотим найти пациента: ";

    int cardNumber;
    std::cin >> cardNumber;

    std::cout << std::endl;

    for (int i = 0; i < structArraySize; i++) {
        if (patientList[i].cardNumber == cardNumber) {
            posOfStruct = i;
            break;
        }
    }

    if (posOfStruct == -1) {
        std::cout << "Нету пациента с таким номером медицинской карты." << std::endl;
    } else {
        outputStruct(posOfStruct);
    }

    std::cout << std::endl;

    return;
}

void findStructByPolisNumber (void) {
    int posOfStruct = -1;

    std::cout << "Введите номер страхового полиса, по которому хотим найти пациента: ";

    int polisNumber;
    std::cin >> polisNumber;

    std::cout << std::endl;

    for (int i = 0; i < structArraySize; i++) {
        if (patientList[i].polisNumber == polisNumber) {
            posOfStruct = i;
            break;
        }
    }

    if (posOfStruct == -1) {
        std::cout << "Нету пациента с таким номером страхового полиса." << std::endl;
    } else {
        outputStruct(posOfStruct);
    }

    std::cout << std::endl;

    return;
}

void addStructInArray(void) {
    structArraySize++;

    struct Patient *tempArray = new struct Patient[structArraySize];

    for (int i = 0; i < structArraySize - 1; i++) {
        tempArray[i] = patientList[i];
    }

    patientList[structArraySize - 1].id = structArraySize;

    std::cout << "Введите фамилию " << structArraySize + 1 << "-го пациента: ";
    patientList[structArraySize - 1].lastName = inputNames();
    
    std::cout << "Введите имя " << structArraySize << "-го пациента: ";
    patientList[structArraySize - 1].firstName = inputNames();

    std::cout << "Введите отчество " << structArraySize << "-го пациента: ";
    patientList[structArraySize - 1].secondName = inputNames();

    std::cout << "Введите адрес " << structArraySize << "-го пациента (улица): ";
    patientList[structArraySize - 1].patientAdress.street = inputNames();

    std::cout << " (номер дома) ";
    patientList[structArraySize - 1].patientAdress.houseNumber = inputInteger();
    std::cout << " (номер квартиры) ";
    patientList[structArraySize - 1].patientAdress.flatNumber = inputInteger();

    std::cout << "Введите номер медицинской карты: " << structArraySize << "-го пациента: ";
    patientList[structArraySize - 1].cardNumber = inputInteger();

    std::cout << "Введите номер стархового полиса: " << structArraySize << "-го пациента: ";
    patientList[structArraySize - 1].polisNumber = inputInteger();
    std::cout << std::endl;


    return;
}

void addStructInArrayFromFile (struct Patient inputPatient) {
    // if (inputPatient.lastName == nullptr || inputPatient.firstName == nullptr || inputPatient.secondName == nullptr ||
    //     inputPatient.patientAdress.street == nullptr || inputPatient.patientAdress.houseNumber == -1 ||
    //     inputPatient.patientAdress.flatNumber == -1 || inputPatient.cardNumber == -1 || inputPatient.polisNumber == -1) {
    //         std::cout << "Одна из записей не корректна" << std::endl << std::endl;
    //         return;
    //     }

    structArraySize++;
    struct Patient* tempArray = new struct Patient[structArraySize];
    
    for (int i = 0; i < structArraySize - 1; i++) {
        tempArray[i] = patientList[i];
    }
    
    inputPatient.id = structArraySize;

    tempArray[structArraySize - 1] = inputPatient;

    delete[] patientList;
    patientList = tempArray;
    tempArray = nullptr;

    return;
}

void inputStructArrayFromFile (void) {
    std::ifstream inFile("files/input.txt");
    
    if (!inFile.is_open()) {
        std::cout << "Не удалось открыть файл." << std::endl;
        return;
    }
    
    struct Patient inputPatient;

    while (inFile.peek() != EOF) {
        inputPatient.lastName = inputNamesFromFile(inFile);
        inputPatient.firstName = inputNamesFromFile(inFile);
        inputPatient.secondName = inputNamesFromFile(inFile);

        inputPatient.patientAdress.street = inputNamesFromFile(inFile);
        inputPatient.patientAdress.houseNumber = inputNaturalFromFile(inFile);
        inputPatient.patientAdress.flatNumber = inputNaturalFromFile(inFile);
        inputPatient.cardNumber = inputNaturalFromFile(inFile);
        inputPatient.polisNumber = inputNaturalFromFile(inFile);
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        addStructInArrayFromFile(inputPatient);
    }

    inFile.close();
    return;
}

void saveStructAraryInFile (void) {
    std::ofstream outFile("files/input.txt", std::ios::app);

    for (int i = 0; i < structArraySize; i++) {
        outFile << patientList[i].lastName << ";" << patientList[i].firstName << ";" << patientList[i].secondName << ";" <<
                patientList[i].patientAdress.street << ";" << patientList[i].patientAdress.houseNumber << ";" <<
                patientList[i].patientAdress.flatNumber << ";" << patientList[i].cardNumber << ";" << 
                patientList[i].polisNumber << "\n";
    }

    outFile.close();
    return;
}