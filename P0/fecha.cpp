#include "fecha.hpp"
#include <iostream>
#include <ctime>

using namespace std;

Fecha::Fecha(int dia, int mes, int anno) : dia_{dia}, mes_{mes}, anno_{anno} {
    if(dia == 0 || mes == 0 || anno == 0) {   
        time_t t = time(0); 
        tm* now = localtime(&t);
        
        if(dia_ == 0 ) { 
            dia_= now->tm_mday;   
        }
        if (mes_ == 0 ) {
            mes_ = now->tm_mon + 1;
        }
        if (anno_ == 0) {
            anno_ = now->tm_year + 1900;
        }  
    } 
}

bool Fecha::valida() const { //reviar por si hay fallo
    if (anno_ < 1 || mes_ < 1 || mes_ > 12 || dia_ < 1) {
        return false;
    }
    
    int dias_en_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Verificar si es año bisiesto
    if ((anno_ % 4 == 0 && anno_ % 100 != 0) || (anno_ % 400 == 0)) {
        dias_en_mes[1] = 29; // Febrero tiene 29 días en año bisiesto
    }
    
    return dia_ <= dias_en_mes[mes_ - 1];
}

bool operator==(const Fecha& f1, const Fecha& f2){
    return f1.dia() == f2.dia() && f1.mes() == f2.mes() && f1.anno() == f2.anno();
}


bool operator<(const Fecha& f1, const Fecha& f2){
    if (f1.anno() < f2.anno()) {
        return true;
    }
    if (f1.anno() > f2.anno()) {
        return false;
    }
    if(f1.mes() > f2.mes()) {
        return  false;
    }
    if (f1.mes() < f2.mes()) {
        return true;
    }
    return f1.dia() < f2.dia();
}
