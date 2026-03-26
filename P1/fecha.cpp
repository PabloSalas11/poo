#include "fecha.hpp"
#include <iostream>
#include <ctime>

using namespace std;

Fecha::Fecha(int dia, int mes, int anno) : dia_{dia}, mes_{mes}, anno_{anno},actual{false} {
    if(dia_ == 0 || mes_ == 0 || anno_ == 0) {   
        time_t t = time(nullptr); 
        tm* now = localtime(&t);
        
        if(dia_ == 0 ) dia_= now->tm_mday;   
        if (mes_ == 0 ) mes_ = now->tm_mon + 1;
        if (anno_ == 0) anno_ = now->tm_year + 1900; 
    } 
    if (!valida()) {
        throw Invalida("Fecha no válida");
    }
    if(anno_<AñoMinimo||anno_>AñoMaximo){
        throw Invalida("Año fuera de limites");
    }
}

Fecha::Fecha(const char* cadena): actual{false}{
	int dia, mes, anno;

    if(sscanf(cadena,"%d/%d/%d",&dia,&mes,&anno)!= 3) {
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
    if(anno_<AñoMinimo||anno_>AñoMaximo){
        throw Invalida("Año fuera de limites");
    }
}

bool Fecha::valida() const { 
    if ( mes_ < 1 || mes_ > 12 || dia_ < 1) return false;
    
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

bool operator==(const Fecha& f1, const Fecha& f2) {
    return f1.dia_ == f2.dia_ && f1.mes_ == f2.mes_ && f1.anno_ == f2.anno_;
}

bool operator<(const Fecha& f1, const Fecha& f2) {
    if (f1.anno_ != f2.anno_) return f1.anno_ < f2.anno_;
    if (f1.mes_ != f2.mes_)   return f1.mes_ < f2.mes_;
    return f1.dia_ < f2.dia_;
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

    if(!valida()) {
        throw Invalida("Fecha no válida");
    }
    if(anno_<AñoMinimo||anno_>AñoMaximo){
        throw Invalida("Año fuera de limites");
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

const char * Fecha::cadena()const{
    if(!actual){
        std::tm tiempo{};
        tiempo.tm_mday= dia_;
        tiempo.tm_mon=mes_-1;
        tiempo.tm_year=anno_-1900;

        std::mktime(&tiempo);
        std::setlocale(LC_ALL,"es_ES.UTF-8");

        std::strftime(crep, sizeof(crep),"%A %d de %B de %Y", &tiempo);

        actual=true;
    }
    return crep;
}


//practica 1
std::ostream& operator<<(std::ostream& os,const Fecha& f){
    os<<f.cadena();
    return os;
}

std::istream& operator>>(std::istream& is, Fecha& f) {
    char cadena[11]; // Reservamos espacio para "DD/MM/AAAA"
    is.width(11);
    
    is >> cadena;    // Leemos la palabra del flujo
    
    try {
        f = Fecha(cadena); 
    } catch (const Fecha::Invalida& e) {
        // Si la fecha era incorrecta, el constructor lanzó la excepción y caemos aquí.
        is.setstate(std::ios::failbit); // Marcamos el flujo con error como pide el PDF.
        throw; // Volvemos a lanzar la excepción hacia arriba.
    }
    
    return is;
}


