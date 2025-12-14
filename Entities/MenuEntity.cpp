#include "./MenuEntity.h"
#include "./BufferEntity.h"

#include <iostream>

int menu (void) {
    std::cout << "Выберите действие, которое хотите совершить:" << std::endl;
    std::cout << "1 - Ввод массива структур из файла" << std::endl <<
        "2 - Ввод массива структур." << std::endl <<
        "3 - Добавить структуру в массив" << std::endl <<
        "4 - Сортировка массива структур" << std::endl << 
        "5 - Поиск в массиве структур по заданному параметру" << std::endl <<
        "6 - Изменение заданной структуры." << std::endl <<
        "7 - Удаление структуры из массива." << std::endl <<
        "8 - Сохранить массив в файл." << std::endl <<
        "9 - Вывод на экран массива структур." << std::endl <<
        "10 - Выход." << std::endl;
    
    std::cout << std::endl;
    std::cout << "Введите число (от 1 до 10): ";

    int menuValue = inputMenuValue();
    std::cout << std::endl;

    return menuValue;
}

int inputMenuValue (void) {
    int value;
    while (!(std::cin >> value) || std::cin.peek() != '\n' || value > 10 || value < 1) {
        std::cout << "Число должно быть от 1 до 10. Повторите ввод." << std::endl;
        clearCinBuffer();
    }
    
    clearCinBuffer();
    return value;
}

int inputOtherMenusValue (void) {
    int value;
    while (!(std::cin >> value) || std::cin.peek() != '\n' || value > 7 || value < 1) {
        std::cout << "Число должно быть от 1 до 7. Повторите ввод." << std::endl;
        clearCinBuffer();
    }
    
    clearCinBuffer();
    return value;
}

int editingMenu (void) {
    std::cout << "Выберите поле которое хотите изменить: " << std::endl;
    std::cout << "1 - Фамилия пациента" << std::endl <<
                "2 - Имя пациента" << std::endl <<
                "3 - Отчество пациента" << std::endl <<
                "4 - Адрес пациента" << std::endl <<
                "5 - Номер медицинской карты пациента" << std::endl <<
                "6 - Номер страхового полиса пациента" << std::endl <<
                "7 - Выход" << std::endl;

    std::cout << std::endl;

    std::cout << "Введите число (от 1 до 7): ";

    int editingMenuValue = inputOtherMenusValue();
    std::cout << std::endl;

    return editingMenuValue;
}

int searchMenu (void) {
    std::cout << "Выберите параметр по которому необходимо искать структуру: " << std::endl;
    std::cout << "1 - Фамилия пациента" << std::endl <<
                "2 - Имя пациента" << std::endl <<
                "3 - Отчество пациента" << std::endl <<
                "4 - Адрес пациента" << std::endl <<
                "5 - Номер медицинской карты пациента" << std::endl <<
                "6 - Номер страхового полиса пациента" << std::endl <<
                "7 - Выход" << std::endl;

    std::cout << std::endl;

    std::cout << "Введите число (от 1 до 7): ";

    int searchMenuValue = inputOtherMenusValue();
    std::cout << std::endl;

    return searchMenuValue;
    
}