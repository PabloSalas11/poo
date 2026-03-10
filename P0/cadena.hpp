#ifndef CADENA_HPP
#define CADENA_HPP
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <cstring>

class Cadena {
public:
    explicit Cadena(size_t n=0, char c='\0');
    Cadena(const char* a ); 
    Cadena(const Cadena& c);
    
    size_t length() const { return tam_; }
    void imprimir() const { std::cout << s_ << std::endl; }
    Cadena substr(size_t indice, size_t tam) const;
    char at(size_t indice) const;

    Cadena& operator=(const Cadena& c);
    friend bool operator==(const Cadena& c1, const Cadena& c2) { return strcmp(c1.s_, c2.s_) == 0; }
    friend bool operator<(const Cadena& c1, const Cadena& c2) { return strcmp(c1.s_, c2.s_) < 0; }
   
    ~Cadena();
    
private:
    char vacia[1];
    size_t tam_;
    char* s_;
};

inline bool operator!=(const Cadena& c1, const Cadena& c2) { return !(c1 == c2);}
inline bool operator>(const Cadena& c1, const Cadena& c2) { return c2 < c1; }
inline bool operator<=(const Cadena& c1, const Cadena& c2) { return !(c2 < c1);}
inline bool operator>=(const Cadena& c1, const Cadena& c2) { return !(c1 < c2);}

#endif 