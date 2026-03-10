#ifndef FECHA_HPP 
#define FECHA_HPP

#include <iostream>
#include <cstddef> 
#include <ctime>

class Fecha {
public:
    explicit Fecha(int dia=0, int mes=0, int anno=0);
    int dia() const { return dia_; }
    int mes() const { return mes_; }
    int anno() const { return anno_; }
    static const int AñoMinimo = 1902;
    static const int AñoMaximo = 2037;

    friend bool operator==(const Fecha& f1, const Fecha& f2);
    friend bool operator<(const Fecha& f1, const Fecha& f2);

    class Invalida{
        public:
            Invalida(const char* m): mensaje{m} {}
            const char* por_que() const { return mensaje; }
        private:
            const char* mensaje;
    };

private:
    bool valida() const;
    int dia_, mes_, anno_;
};

inline bool operator!=(const Fecha& f1, const Fecha& f2) { return !(f1 == f2); }
inline bool operator>(const Fecha& f1, const Fecha& f2) { return f2 < f1; }
inline bool operator<=(const Fecha& f1, const Fecha& f2) { return !(f2 < f1); }
inline bool operator>=(const Fecha& f1, const Fecha& f2) { return !(f1 < f2); }

#endif