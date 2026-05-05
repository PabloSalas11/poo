#include "tarjeta.hpp"
#include <iostream>
#include <iomanip>
#include <cctype>

// Implementación del constructor
Tarjeta::Tarjeta(const Numero& num, Usuario& user, const Fecha& cadu)
    : numero_(num), titular_(&user), caducidad_(cadu) 
{
    // 1. Validar caducidad frente a la fecha actual
    if (cadu < Fecha()) {
        throw Caducada(cadu);
    }

    // 2. Determinar el tipo de tarjeta según el primer dígito
    // (Nota: Esto suele implementarse con lógica de prefijos, 
    // pero aquí asignamos un tipo por defecto o según el enunciado)
    switch (numero_[0]) {
        case '3': tipo_ = (numero_[1] == '4' || numero_[1] == '7') ? JCB : Diners; break;
        case '4': tipo_ = VISA; break;
        case '5': tipo_ = Mastercard; break;
        case '6': tipo_ = Maestro; break;
        default:  tipo_ = VISA; // Valor por defecto
    }

    // 3. Generar el titular_facial en mayúsculas
    Cadena facial = user.nombre() + " " + user.apellidos();
    for (size_t i = 0; i < facial.length(); ++i) {
        facial[i] = std::toupper(facial[i]);
    }
    titular_facial_ = facial;

    // 4. Establecer relación bidireccional
    user.es_titular_de(*this);
}

// Destructor: avisar al usuario si todavía existe
Tarjeta::~Tarjeta() {
    if (titular_) {
        titular_->no_es_titular_de(*this);
    }
}

// Operador menor-que: comparación por número de tarjeta
bool operator <(const Tarjeta& t1, const Tarjeta& t2) {
    return t1.numero() < t2.numero();
}

// Auxiliar para imprimir el tipo de tarjeta
std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tipo) {
    switch (tipo) {
        case Tarjeta::VISA:       os << "VISA"; break;
        case Tarjeta::Mastercard: os << "Mastercard"; break;
        case Tarjeta::Maestro:    os << "Maestro"; break;
        case Tarjeta::JCB:        os << "JCB"; break;
        case Tarjeta::Diners:     os << "Diners"; break;
    }
    return os;
}

// Operador de inserción principal
std::ostream& operator <<(std::ostream& os, const Tarjeta& t) {
    os << t.tipo() << "\n"
       << t.numero() << "\n"
       << t.titular_facial() << "\n"
       << "Caduca: " 
       << std::setfill('0') << std::setw(2) << t.caducidad().mes() 
       << "/" 
       << std::setw(2) << (t.caducidad().año() % 100) << "\n"; // Uso de año()
    return os;
}