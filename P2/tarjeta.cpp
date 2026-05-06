#include "tarjeta.hpp"
#include <iostream>
#include <iomanip>
#include <cctype>


bool luhn(const Cadena& numero);

Numero::Numero(const Cadena& num) : numero_(num) {
    char limpio[64];
    size_t j = 0;

    const char* original = numero_.operator const char *();

    for (size_t i = 0; original[i] != '\0'; i++) {
        if (std::isspace(original[i])) {
            limpio[j] = original[i];
            j++;
        }
    }
    limpio[j] = '\0';

    // 1. Validar longitud (entre 13 y 19 dígitos)
    if (strlen(limpio) < 13 || strlen(limpio) > 19) {
        throw Incorrecto(LONGITUD);
    }

    // 2. Validar que todos los caracteres sean dígitos
    for (size_t i = 0; limpio[i] != '\0'; i++) {
        if (!std::isdigit(limpio[i])) {
            throw Incorrecto(DIGITOS);
        }
    }

    Cadena numero_limpio(limpio);
    if (!luhn(numero_limpio)) {
        throw Incorrecto(NO_VALIDO);
    }

    numero_ = numero_limpio;
}

Numero::operator const char*() const {
    // Llamamos explícitamente al operador de conversión de Cadena
    return numero_.operator const char *();
}

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

bool operator <(const Numero& n1, const Numero& n2) {
    return strcmp(n1, n2) < 0;
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