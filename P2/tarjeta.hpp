#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
#include "usuario.hpp"

class Numero;
class Usuario;

class Numero {
public:
    enum Razon { LONGITUD, DIGITOS, NO_VALIDO };
    class Incorrecto {
    public:
        Incorrecto(Razon r) : r_(r) {}
        Razon razon() const { return r_; }
    private:
        Razon r_;   
    };  
    Numero(const Cadena& num);
    operator const char*() const;
private:
    Cadena numero_;
};

bool operator <(const Numero& n1, const Numero& n2);

class Tarjeta {
public:
    // Enumeración de tipos de tarjeta
    enum Tipo { VISA, Mastercard, Maestro, JCB, Diners };

    // Clase de excepción para tarjetas caducadas
    class Caducada {
    public:
        Caducada(const Fecha& f) : fecha_(f) {}
        const Fecha& cuando() const { return fecha_; }
    private:
        Fecha fecha_;
    };

    // Constructor
    Tarjeta(const Numero& num, Usuario& user, const Fecha& cadu);

    // Prohibición de copia y asignación
    Tarjeta(const Tarjeta&) = delete;
    Tarjeta& operator =(const Tarjeta&) = delete;

    // Observadores
    const Numero& numero() const { return numero_; }
    const Usuario* titular() const { return titular_; }
    const Fecha& caducidad() const { return caducidad_; }
    Tipo tipo() const { return tipo_; }
    const Cadena& titular_facial() const { return titular_facial_; }

    // Método para modificar el titular (usado por Usuario)
    void titular(Usuario* u) { titular_ = u; }

    // Destructor
    ~Tarjeta();

private:
    const Numero numero_;
    Usuario* titular_;
    const Fecha caducidad_;
    Tipo tipo_;
    Cadena titular_facial_;
};

// Operadores externos
std::ostream& operator <<(std::ostream& os, const Tarjeta& t);
std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tipo);
bool operator <(const Tarjeta& t1, const Tarjeta& t2);

#endif