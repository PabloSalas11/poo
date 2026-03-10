#ifndef CADENA_HPP
#define CADENA_HPP
#include <cstddef>
#include <iostream>
#include <cstring>

class Cadena {
public:
    explicit Cadena(size_t n=0, char c='\0');
    Cadena(const char* a ); 
    size_t length() const { return tam_; }
    void imprimir() const { std::cout << s_ << std::endl; }
    char* substr(size_t indice, size_t tam) const;
    char at(size_t indice) const;

   

private:
    char vacia[1];
    size_t tam_;
    char* s_;
};

    bool operator==(const Cadena& c1, const Cadena& c2) { return c1 == c2; }
    bool operator<(const Cadena& c1, const Cadena& c2) { return c1 < c2; }

    inline bool operator!=(const Cadena& c1, const Cadena& c2) { return !(c1 == c2);}
    inline bool operator>(const Cadena& c1, const Cadena& c2) { return c2 < c1; }
    inline bool operator<=(const Cadena& c1, const Cadena& c2) { return !(c2 < c1);}
    inline bool operator>=(const Cadena& c1, const Cadena& c2) { return !(c1 < c2);}

#endif 