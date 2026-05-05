#ifndef articulo_hpp
#define articulo_hpp
#include "cadena.hpp"
#include "fecha.hpp"

class Articulo {
public:
    Articulo(const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, double precio, size_t stock = 0);
    
    const Cadena& referencia() const { return referencia_; }
    const Cadena& titulo() const { return titulo_; }
    const Fecha& f_publi() const { return f_publi_; }
    size_t stock() const { return stock_; }
    double precio() const { return precio_; }

    double& precio() { return precio_; }
    size_t& stock() { return stock_; }

    friend std::ostream& operator<<(std::ostream& os, const Articulo& a);
private:
    const Cadena referencia_;
    const Cadena titulo_;
    const Fecha f_publi_;
    double precio_;
    size_t stock_;
};

#endif

