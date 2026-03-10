#include "cadena.hpp"

using namespace std;


Cadena::Cadena(size_t n, char c): vacia{'\0'}, tam_{n}, s_{new char[n+1]} {
    for(size_t i = 0; i < tam_; ++i)
        s_[i] = c;
    s_[tam_] = '\0';
}

Cadena::Cadena(const char* a): vacia{'\0'}, tam_{strlen(a)}, s_{new char[tam_+1]} {
    strcpy(s_, a);
}

char Cadena::at(size_t indice)const {
    if (indice >= tam_) {
        throw out_of_range("Índice fuera de rango");
    }
    return s_[indice];
}

char* Cadena::substr(size_t indice, size_t tam) const {
    cout << "indice: " << indice << " tam: " << tam << endl;
    if (indice >= tam_ || indice + tam > tam_) {
        throw out_of_range("Índice o tamaño fuera de rango");
    }
    
    char* subcadena = new char [tam + 1];
    for(size_t i = 0; i < tam; ++i){
         subcadena[i] = s_[indice + i];
    }
    subcadena[tam] = '\0';
    return (subcadena);
}