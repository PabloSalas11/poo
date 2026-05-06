#ifndef USUARIO_HPP
#define USUARIO_HPP

#include "cadena.hpp"
#include "articulo.hpp"
#include <map>
#include <set>

// Declaraciones adelantadas para evitar inclusiones circulares[cite: 3]
class Tarjeta;
class Numero;

class Clave {
public:
    enum Razon { CORTA, ERROR_CRYPT };
    class Incorrecta {
    public:
        Incorrecta(Razon r) : r_(r) {}
        Razon razon() const { return r_; }
    private:
        Razon r_;   
    };

    Clave(const char* clave);
    Cadena clave() const { return clave_; } // Solo una declaración[cite: 5]
    bool verifica(const char* claro);

private:
    Cadena clave_;
    static const char caracteres_validos[];
};



class Usuario {
public:
    class Id_duplicado {
    public:
        Id_duplicado(const Cadena& id) : id_(id) {}
        const Cadena& id() const { return id_; }
    private:
        Cadena id_;
    };

    typedef std::map<Articulo*, unsigned int> Articulos;
    typedef std::map<Numero, Tarjeta*> Tarjetas;

    static std::set<Cadena> Usuarios_; // Registro de IDs[cite: 5]

    Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, 
            const Cadena& direccion, const Clave& clave);

    // Prohibición de copia[cite: 14]
    Usuario(const Usuario&) = delete;
    Usuario& operator =(const Usuario&) = delete;

    // Métodos de relación y carrito
    void compra(Articulo& a, unsigned int cantidad = 1);
    void es_titular_de(Tarjeta& t);
    void no_es_titular_de(Tarjeta& t);

    // Observadores[cite: 5, 14]
    const Cadena& id() const { return id_; }
    const Cadena& nombre() const { return nombre_; }
    const Cadena& apellidos() const { return apellidos_; }
    const Cadena& direccion() const { return direccion_; }
    const Tarjetas& tarjetas() const { return tarjetas_; }
    size_t n_articulos() const { return carrito_.size(); }
    Articulos carrito() const { return carrito_; }

    ~Usuario();

    friend std::ostream& operator <<(std::ostream& os, const Usuario& u);
    

private:
    Cadena id_, nombre_, apellidos_, direccion_;
    Clave password_;
    Articulos carrito_;
    Tarjetas tarjetas_;
};

std::ostream& mostrar_carro(std::ostream& os, const Usuario& u);

#endif