#include "../Entities/MenuEntity.h"
#include "../Entities/StructArrayEntity.h"

#include <iostream>

int main()
{
    setlocale(LC_ALL, "ru_RU");

    do {
        switch (menu()) {
            case 1:
                inputStructArrayFromFile();
                break;
            case 2:
                inputStructArray();
                break;
            case 3:
                addStructInArray();
                break;
            case 4:
                sortStructArray(); 
                break;
            case 5:
                findInStructArray();
                break;
            case 6:
                changeStructArray();
                break;
            case 7:
                removeStructFromArray();
                break;
            case 8:
                saveStructAraryInFile();
                break;
            case 9:
                outputStructArray();
                break;
            case 10:
                std::cout << "Завершение программы.";
                return 0;
        }
    } while(1);

    return 0;
}

