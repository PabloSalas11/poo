#ifndef FECHA_HPP 
#define FECHA_HPP

#include <iostream>
#include <cstddef> 
#include <ctime>

class Fecha {
public:
    explicit Fecha(int dia=0, int mes=0, int anno=0);
    Fecha(const char* fecha); 
    int dia() const { return dia_; }
    int mes() const { return mes_; }
    int año() const { return anno_; }
    
    static const int AñoMinimo = 1902;
    static const int AñoMaximo = 2037;

    bool operator==(const Fecha& f1) const;
    bool operator<(const Fecha& f1) const;
    bool operator!=(const Fecha& f1) const{return !(*this == f1);}
    bool operator>(const Fecha& f1) const{return f1 < *this;}
    bool operator<=(const Fecha& f1) const{return !(*this > f1);}
    bool operator>=(const Fecha& f1) const{return !(*this < f1);}

    Fecha& operator+=(int dias); 
    Fecha& operator-=(int dias);
    Fecha operator+(int dias) const;
    Fecha operator-(int dias) const;
    Fecha& operator++();
    Fecha operator++(int);
    Fecha& operator--();
    Fecha operator--(int);

    class Invalida{
        public:
            Invalida(const char* m): mensaje{m} {}
            const char* por_que() const { return mensaje; }
        private:
            const char* mensaje;
    };

    const char* cadena()const;

    friend std::ostream& operator<<(std::ostream& os,const Fecha& f);
    friend std::istream& operator>>(std::istream& is, Fecha& f);

private:
    bool valida() const;
    int dia_, mes_, anno_;
    mutable bool actual;
    mutable char crep[80];
};



#endif