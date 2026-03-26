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

    // Solo declaramos las "bases" como friend para que tengan acceso a los datos privados
    friend bool operator==(const Fecha& f1, const Fecha& f2);
    friend bool operator<(const Fecha& f1, const Fecha& f2);

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

// Operadores relacionales basados en == y <
inline bool operator!=(const Fecha& f1, const Fecha& f2) { 
    return !(f1 == f2); 
}

inline bool operator>(const Fecha& f1, const Fecha& f2) { 
    return f2 < f1; 
}

inline bool operator<=(const Fecha& f1, const Fecha& f2) { 
    return !(f2 < f1); // O también: return !(f1 > f2);
}

inline bool operator>=(const Fecha& f1, const Fecha& f2) { 
    return !(f1 < f2);
}

#endif