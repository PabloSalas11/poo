#include "cadena.hpp"

using namespace std;


Cadena::Cadena(size_t n=0, char c='\0'): vacia{'\0'}, tam_{n}, s_{new char[n+1]} {
    for(size_t i = 0; i < tam_; ++i)
        s_[i] = c;
    s_[tam_] = '\0';
}

Cadena::Cadena(const char* a): vacia{'\0'}, tam_{strlen(a)}, s_{new char[tam_+1]} {
    strcpy(s_, a);
}