#ifndef CADENA_HPP
#define CADENA_HPP
#include <cstddef>
#include <iostream>
#include <cstring>

class Cadena {
public:
    explicit Cadena(size_t n, char c);
    Cadena(const char* a); 
    size_t length() const { return tam_; }
    void imprimir() const { std::cout << s_ << std::endl; }
private:
    char vacia[1];
    size_t tam_;
    char* s_;
};



#endif 