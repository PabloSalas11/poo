#ifndef FECHA_HPP 
#define FECHA_HPP

#include <iostream>
#include <cstddef> 
#include <ctime>

using namespace std;

class Fecha {
public:
    explicit Fecha(int dia=0, int mes=0, int anno=0) : dia_(dia), mes_(mes), anno_(anno) {};
    int dia() const { return dia_; }
    int mes() const { return mes_; }
    int anno() const { return anno_; }
    void fechasolicitada();
private:
    int dia_, mes_, anno_;
};

void Fecha::fechasolicitada () {
    time_t t = time(0); 
    tm* now = localtime(&t);
    
    if(this->dia_ == 0 && this->mes_ == 0 && this->anno_ == 0) { 
        cout << "Dia " << now->tm_mday << " del mes " << now->tm_mon + 1 << " del anno " << now->tm_year + 1900 << endl;    
    }
    else if (this->mes_ == 0 && this->anno_ == 0) {
        cout << "Dia " << this->dia_ << " del mes " << now->tm_mon + 1 << " del anno " << now->tm_year + 1900 << endl;
    }
    else if (this->anno_ == 0) {
        cout << "Dia " << this->dia_ << " del mes " << this->mes_ << " del anno " << now->tm_year + 1900 << endl;
    }
    else {
        cout << "La fecha ingresada es: " << this->dia_ << "/" << this->mes_ << "/" << this->anno_ << endl;
    }
}
#endif