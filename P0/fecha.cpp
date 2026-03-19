#include "fecha.hpp"
#include <iostream>
#include <ctime>

using namespace std;

Fecha::Fecha(int dia, int mes, int anno) : dia_{dia}, mes_{mes}, anno_{anno} {
    if(dia_ == 0 || mes_ == 0 || anno_ == 0) {   
        time_t t = time(0); 
        tm* now = localtime(&t);
        
        if(dia_ == 0 ) dia_= now->tm_mday;   
        if (mes_ == 0 ) mes_ = now->tm_mon + 1;
        if (anno_ == 0) anno_ = now->tm_year + 1900; 
    } 
    if (!valida()) {
        throw Invalida("Fecha no válida");
    }
}

Fecha::Fecha(const char* cadena){
	int dia, mes, anno;
	int campos_leidos = sscanf(cadena,"%d/%d/%d",&dia,&mes,&anno);
	
    if(campos_leidos != 3) {
        throw Invalida("Formato de fecha no válido");
    }
    
    dia_=dia;
	mes_=mes;
	anno_=anno;

    time_t t = time(0); 
    tm* now = localtime(&t);
    if(dia_ == 0 ) dia_= now->tm_mday;   
    if (mes_ == 0 ) mes_ = now->tm_mon + 1;
    if (anno_ == 0) anno_ = now->tm_year + 1900;

    if(!valida()) {
        throw Invalida("Fecha no válida");
    }
}

bool Fecha::valida() const { 
    if (anno_ < AñoMinimo || anno_ > AñoMaximo || mes_ < 1 || mes_ > 12 || dia_ < 1 || dia_ > 31) return false;
    
    int dias_en_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((anno_ % 4 == 0 && anno_ % 100 != 0) || (anno_ % 400 == 0)) dias_en_mes[1] = 29;

    switch (mes_)
    {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        if (dia_ > dias_en_mes[mes_ - 1]) return false;
        break;
    case 2:
        if(dia_ > dias_en_mes[1]) return false;
        break;
    default:
        if(dia_ > dias_en_mes[mes_ - 1]) return false;
        break;
    };
    
    return dia_ <= dias_en_mes[mes_ - 1];
}

bool Fecha::operator==(const Fecha& f1) const{
    return f1.dia_ == this->dia_ && f1.mes_ == this->mes_ && f1.anno_ == this->anno_;
}

bool Fecha::operator<(const Fecha& f) const {
    if (anno_ != f.anno_) return anno_ < f.anno_;
    if (mes_ != f.mes_)   return mes_ < f.mes_;
    return dia_ < f.dia_;
}

Fecha& Fecha::operator+=(int dias){
    tm fecha_tm = {};
    fecha_tm.tm_mday = dia_ + dias;
    fecha_tm.tm_mon = mes_ - 1;
    fecha_tm.tm_year = anno_ - 1900;

    mktime(&fecha_tm);
    
    dia_ = fecha_tm.tm_mday;
    mes_ = fecha_tm.tm_mon + 1; 
    anno_ = fecha_tm.tm_year + 1900;

    if(!valida()){
        throw Invalida("Fecha Invalida");
    }

    return *this;
}

Fecha& Fecha::operator-=(int dias){
    return *this += -dias;
}

Fecha Fecha::operator+(int dias) const{
    Fecha result = *this;
    return result += dias;
}

Fecha Fecha::operator-(int dias) const{
    Fecha result = *this;
    return result -= dias;
}

Fecha& Fecha::operator++() {
    return *this += 1;
}

Fecha Fecha::operator++(int) {
    Fecha result = *this;
    ++(*this);
    return result;
}

Fecha& Fecha::operator--() {
    return *this -= 1;
}

Fecha Fecha::operator--(int) {
    Fecha result = *this;
    --(*this);
    return result;
}

// Definición de los arrays (fuera de la clase, sin 'static' aquí)
const char* Fecha::DIAS[] = {
    "domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"
};

const char* Fecha::MESES[] = {
    "enero", "febrero", "marzo", "abril", "mayo", "junio",
    "julio", "agosto", "setiembre", "octubre", "noviembre", "diciembre"
};

ostream& operator <<(ostream& os, const Fecha& f) {
    tm fecha_tm = {};
    fecha_tm.tm_mday = f.dia();
    fecha_tm.tm_mon = f.mes() - 1;
    fecha_tm.tm_year = f.anno() - 1900;

    mktime(&fecha_tm);

    os << Fecha::DIAS[fecha_tm.tm_wday] << " " << f.dia() << " de " << Fecha::MESES[fecha_tm.tm_mon] << " de " << f.anno();
    return os;
}

istream& operator >>(istream& is, Fecha& f) {
    int d, m, a;
    char c1, c2;
    if (is >> d >> c1 >> m >> c2 >> a) {
        if (c1 != '/' || c2 != '/') {
            is.setstate(ios::failbit);
            throw Fecha::Invalida("Formato incorrecto");
        }
        f = Fecha(d, m, a); // El constructor ya valida d, m, a
    } else {
        is.setstate(ios::failbit);
    }
    return is;
}

// istream& operator >>(istream& is, Fecha& f){
//     char c1, c2;
//     is >> f.dia_ >> c1 >> f.mes_ >> c2 >> f.anno_;
//     if(!f.valida()|| c1 != '/' || c2 != '/') {
//         throw Fecha::Invalida("Fecha Invalida");
//     }
//     return is;
// }

Fecha::~Fecha() {}
