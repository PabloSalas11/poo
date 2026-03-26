#include "cadena.hpp"

using namespace std;

char Cadena::vacia[1] = {'\0'};

Cadena::Cadena(size_t n, char c): tam_{n}, s_{n == 0 ? vacia : new char[n+1]} {
    for(size_t i = 0; i < tam_; ++i)
        s_[i] = c;
    s_[tam_] = '\0';
}

Cadena::Cadena(const char* a): tam_{strlen(a)} {
    if(tam_==0){
        s_ = vacia;
    }
    else{
        s_=new char[tam_ + 1];
        strcpy(s_, a);
    }
}

Cadena::Cadena(const Cadena& c) : tam_{c.tam_} {
    if(tam_==0){
        s_ = vacia;
    }
    else{
        s_=new char[tam_ + 1];
        strcpy(s_, c.s_);
    }
}

// 1. at() para LECTURA (const, devuelve copia)
char Cadena::at(size_t indice) const {
    if (indice >= tam_) {
        throw out_of_range("Índice fuera de rango");
    }
    return s_[indice];
}

// 2. at() para ESCRITURA (no const, devuelve referencia)
char& Cadena::at(size_t indice) {
    if (indice >= tam_) {
        throw out_of_range("Índice fuera de rango");
    }
    return s_[indice];
}

// 3. operator[] para LECTURA (const, devuelve copia, sin comprobar)
char Cadena::operator[](size_t indice) const {
    return s_[indice];
}

// 4. operator[] para ESCRITURA (no const, devuelve referencia, sin comprobar)
char& Cadena::operator[](size_t indice) {
    return s_[indice];
}

Cadena Cadena::substr(size_t indice, size_t tam) const {
    if (indice >= tam_ || tam>tam_-indice) {
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
    if (this != &c) {
        // 1. Compramos el piso nuevo PRIMERO
        char* nuevo_s = (c.tam_ == 0) ? vacia : new char[c.tam_ + 1];
        
        // 2. Hacemos la mudanza de los muebles (si la otra cadena no está vacía)
        if (c.tam_ > 0) {
            strcpy(nuevo_s, c.s_);
        }
        
        // 3. AHORA SÍ, si todo ha ido bien, entregamos las llaves viejas
        if (tam_ > 0) {
            delete[] s_;
        }
        
        // 4. Actualizamos nuestros papeles
        tam_ = c.tam_;
        s_ = nuevo_s;
    }
    return *this;
}

Cadena& Cadena::operator+=(const Cadena& c){
    if (c.tam_== 0) return *this;

    size_t nuevo_tam = tam_ + c.tam_;
    char* nuevo_s = new char[nuevo_tam + 1];
    strcpy(nuevo_s,s_);
    strcat(nuevo_s, c.s_);

    if(tam_>0) delete[] s_;
    
    s_=nuevo_s;
    tam_=nuevo_tam;

    return *this;
}

Cadena operator+(const Cadena& c1, const Cadena& c2){
    Cadena nueva = c1;
    nueva += c2;
    return nueva;
}

Cadena::operator const char*() const {
    return s_;
}

std::ostream& operator<<(std::ostream& os, const Cadena& c) {
    os << c.s_;
    return os;
}

std::istream& operator>>(std::istream& is, Cadena& c){
    char buffer[33];
    is.width(33); //controlo q solo entren 32+\0
    is>>buffer;
    c=buffer;
    return is;
}

Cadena::iterator Cadena::begin() {return s_;}
Cadena::iterator Cadena::end(){return s_+tam_;}

Cadena::const_iterator Cadena::begin() const {return s_;}
Cadena::const_iterator Cadena::end() const {return s_ + tam_;}
Cadena::const_iterator Cadena::cbegin() const {return s_;}
Cadena::const_iterator Cadena::cend() const {return s_ + tam_;}

Cadena::reverse_iterator Cadena::rbegin(){return reverse_iterator(end());}
Cadena::reverse_iterator Cadena::rend(){return reverse_iterator(begin());}

Cadena::const_reverse_iterator Cadena::rbegin() const{return const_reverse_iterator(end());}
Cadena::const_reverse_iterator Cadena::rend() const{return const_reverse_iterator(begin());}
Cadena::const_reverse_iterator Cadena::crbegin() const{return const_reverse_iterator(cend());}
Cadena::const_reverse_iterator Cadena::crend() const{return const_reverse_iterator(cbegin());}

Cadena::Cadena(Cadena&& c) noexcept : tam_{c.tam_}, s_{c.s_} {
    c.tam_ = 0;
    c.s_ = vacia;
}

Cadena& Cadena::operator=(Cadena&& c) noexcept {
    if (this != &c) {
        if (tam_ != 0) {  //se prepara los atributos de nuestra clase previamente al copiado de nuestro objeto c
            delete[] s_;
        }
        
        tam_ = c.tam_; //copiado a atributos de la clase
        s_ = c.s_;
        
        c.tam_ = 0; //se vacia los rvalues del objeto c
        c.s_ = vacia;
    }
    return *this;
}

Cadena::~Cadena() { 
    if (tam_ != 0) {
        delete[] s_; 
    }
}