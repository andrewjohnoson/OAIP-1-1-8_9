#include "./InputEntity.h"
#include "./BufferEntity.h"

#include <iostream>
#include <string>

int inputNatural (void) {
    int x;

    while (!(std::cin >> x) || std::cin.peek() != '\n' || x < 1) {
        std::cout << "Введите натуральное число." << std::endl;
        clearCinBuffer();
    }

    clearCinBuffer();
    return x;
}

int inputInteger (void) {
    int x;

    while (!(std::cin >> x) || std::cin.peek() != '\n') {
        std::cout << "Введите натуральное число." << std::endl;
        clearCinBuffer();
    }

    clearCinBuffer();
    return x;
}

char* inputNames (int size) {
    char temp[31];
    while (1) {
        bool haveIncorrectSymbols = false;

        std::cin.getline(temp, size);

        for (int i = 0; i < strlen(temp); i++) {
            if ((temp[i] >= '0' && temp[i] <= '9') || (temp[i] >= '!' && temp[i] <= ',') ||
                (temp[i] >= '[' && temp[i] <= '_') || (temp[i] == '.' || temp[i] == '/') ||
                (temp[i] >= ':' && temp[i] <= '@')) {
                haveIncorrectSymbols = true;
                break;
            }
        }

        if (haveIncorrectSymbols) {
            std::cout << "Некорректный ввод." << std::endl;
        } else {
            break;
        }
    }

    char* str = new char[strlen(temp) + 1];
    strcpy(str, temp);
    
    return str;
}

char* inputNamesFromFile (std::ifstream& inFile, char delimiter, int size) {
    char temp[31];
    inFile.getline(temp, size, delimiter);

    char* str = new char[strlen(temp) + 1];
    strcpy(str, temp);

    checkForStringMistakes(str);

    return str;
}

void checkForStringMistakes(char *str) {
    bool haveIncorrectSymbol = false;

    for (int i = 0; i < strlen(str); i++) {
        if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= '!' && str[i] <= ',') ||
                (str[i] >= '[' && str[i] <= '_') || (str[i] == '.' || str[i] == '/') ||
                (str[i] >= ':' && str[i] <= '@')) {
            haveIncorrectSymbol = true;
            break;
        }
    }

    if (haveIncorrectSymbol) {
        delete[] str;
        str = nullptr;
    }
    return;
}

int inputNaturalFromFile (std::ifstream& inFile, char delimiter) {
    char strNumber[66];

    if (!(inFile.getline(strNumber, 66, delimiter))) {
        return -1;
    }

    int number = atoi(strNumber);

    if (number < 1) {
        return -1;
    }

    return number;
}