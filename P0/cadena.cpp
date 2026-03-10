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

Cadena::Cadena(const Cadena& c) : vacia{'\0'}, tam_{c.tam_}, s_{new char[c.tam_ + 1]} {
    strcpy(s_, c.s_); 
}

char Cadena::at(size_t indice)const {
    if (indice >= tam_) {
        throw out_of_range("Índice fuera de rango");
    }
    return s_[indice];
}

Cadena Cadena::substr(size_t indice, size_t tam) const {
    cout << "indice: " << indice << " tam: " << tam << endl;
    if (indice >= tam_ || indice + tam > tam_) {
        throw out_of_range("Índice o tamaño fuera de rango");
    }
    
    char* aux = new char[tam + 1];
    for(size_t i = 0; i < tam; ++i){
         aux[i] =s_[indice + i];
    }

    aux[tam] = '\0';
    Cadena subcadena(aux);
    delete[] aux;

    return subcadena;
}

Cadena& Cadena::operator=(const Cadena& c) {
    if (this != &c) { // Evitar auto-asignación
        delete[] s_; 
        tam_ = c.tam_;
        s_ = new char[tam_ + 1];
        strcpy(s_, c.s_);
    }
    return *this;
}

Cadena::~Cadena() { delete[] s_; }