#ifndef CADENA_HPP
#define CADENA_HPP
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <iterator>

//practica 0
class Cadena {
public:
    explicit Cadena(size_t n=0, char c=' ');
    Cadena(const char* a ); 
    Cadena(const Cadena& c);
    
    size_t length() const { return tam_; }
    void imprimir() const { std::cout << s_ << std::endl; }
    Cadena substr(size_t indice, size_t tam) const;
    // 1. at() para lectura (devuelve copia, es const)
    char at(size_t indice) const;

    // 2. at() para escritura (devuelve referencia, NO es const)
    char& at(size_t indice);

    // 3. operador [] para lectura (devuelve copia, es const)
    char operator[](size_t indice) const;

    // 4. operador [] para escritura (devuelve referencia, NO es const)
    char& operator[](size_t indice);

    Cadena& operator=(const Cadena& c);
    friend bool operator==(const Cadena& c1, const Cadena& c2) { return strcmp(c1.s_, c2.s_) == 0; }
    friend bool operator<(const Cadena& c1, const Cadena& c2) { return strcmp(c1.s_, c2.s_) < 0; }
    
    Cadena& operator+=(const Cadena& c);

    explicit operator const char*() const;

    friend std::ostream& operator<<(std::ostream& os, const Cadena& c);
    friend std::istream& operator>>(std::istream& is, Cadena& c);

    using iterator = char*; // Le decimos a C++ que "iterator" es un alias de "char*"
    using const_iterator = const char*;
    using reverse_iterator=std::reverse_iterator<iterator>;
    using const_reverse_iterator=std::reverse_iterator<const_iterator>;

    iterator begin();       // Función que apunta al principio
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    reverse_iterator rbegin();
    reverse_iterator rend();

    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    Cadena(Cadena&& c) noexcept; // Constructor de movimiento

    Cadena& operator=(Cadena&& c) noexcept; // Asignación de movimiento

    ~Cadena();
    
private:
    static char vacia[1];
    size_t tam_;
    char* s_;
};

inline bool operator!=(const Cadena& c1, const Cadena& c2) { return !(c1 == c2);}
inline bool operator>(const Cadena& c1, const Cadena& c2) { return c2 < c1; }
inline bool operator<=(const Cadena& c1, const Cadena& c2) { return !(c2 < c1);}
inline bool operator>=(const Cadena& c1, const Cadena& c2) { return !(c1 < c2);}

Cadena operator+(const Cadena& c1, const Cadena& c2);

#endif 