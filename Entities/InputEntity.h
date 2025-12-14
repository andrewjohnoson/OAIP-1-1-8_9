#ifndef INPUT_H
#define INPUT_H

#include <fstream>

int inputNatural (void);
int inputInteger (void);
char* inputNames (int size = 31);
char* inputNamesFromFile (std::ifstream&, char delimiter = ';', int size = 31);
void checkForStringMistakes (char*);
int inputNaturalFromFile (std::ifstream&, char delimiter = ';');

#endif