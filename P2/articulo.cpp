#include "articulo.hpp"
#include <iomanip>

Articulo::Articulo(const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, double precio, size_t stock)
    : referencia_(referencia), titulo_(titulo), f_publi_(f_publi), precio_(precio), stock_(stock) {}

std::ostream& operator<<(std::ostream& os, const Articulo& a) {
    os <<"[" << a.referencia() << "] \"" << a.titulo() << "\", " << a.f_publi().año() << ". " << std::fixed << std::setprecision(2) << a.precio() << " €";
    return os;
}