#include "./BufferEntity.h"

#include <iostream>

void clearCinBuffer(void) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}