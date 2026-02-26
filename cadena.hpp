#ifndef CADENA.HPP
#define CADENA.HPP

#include <iostream>

class Cadena {
public:
    Cadena(char& caracter_externo) : c(caracter_externo), tam(0) {}

private:
    std::size_t tam;
    char& c; 
    char c[1];
};

#endif