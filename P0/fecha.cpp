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

bool Fecha::valida() const { //reviar por si hay fallo
    if (anno_ < AñoMinimo || anno_ > AñoMaximo || mes_ < 1 || mes_ > 12 || dia_ < 1 || dia_ > 31) return false;
    
    int dias_en_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((anno_ % 4 == 0 && anno_ % 100 != 0) || (anno_ % 400 == 0)) dias_en_mes[1] = 29;

    switch (mes_)
    {
    case 1:case3:case5:case7:case8:case10:case12: 
        if(dia_ > dias_en_mes[mes_ - 1]) return false;
        break;
    case 2:
        if (dia_> dias_en_mes[1]) return false;
        break;
    case 4:case6:case9:case11:
        if (dia_ > dias_en_mes[mes_ - 1]) return false;
        break;
    }
    
    return dia_ <= dias_en_mes[mes_ - 1];
}

bool operator==(const Fecha& f1, const Fecha& f2){
    return f1.dia() == f2.dia() && f1.mes() == f2.mes() && f1.anno() == f2.anno();
}

bool operator<(const Fecha& f1, const Fecha& f2){
    if (f1.anno() != f2.anno()) return f1.anno() < f2.anno();
    if (f1.mes() != f2.mes()) return f1.mes() < f2.mes();
    return f1.dia() < f2.dia();
}
