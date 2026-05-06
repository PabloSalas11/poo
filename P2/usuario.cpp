#include "usuario.hpp"
#include "tarjeta.hpp"
#include <unistd.h> // Para crypt()[cite: 3]
#include <random>
#include <cstring>
#include <iomanip>

// Inicialización del atributo estático[cite: 3]
std::set<Cadena> Usuario::Usuarios_;

// --- Implementación de Clave ---
const char Clave::caracteres_validos[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";

Clave::Clave(const char* claro) {
    if (std::strlen(claro) < 5) throw Incorrecta(CORTA);

    static std::random_device rd;
    static std::mt19937 gna(rd());
    std::uniform_int_distribution<size_t> dist(0, 63);

    char sal[3] = { caracteres_validos[dist(gna)], caracteres_validos[dist(gna)], '\0' };
    
    char* cifrada = crypt(claro, sal);
    if (!cifrada) throw Incorrecta(ERROR_CRYPT);
    clave_ = cifrada;
}

bool Clave::verifica(const char* claro) {
    char* cifrada = crypt(claro, clave_.operator const char *());
    return cifrada && clave_ == cifrada;
}

// --- Implementación de Usuario ---
Usuario::Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, 
                 const Cadena& direccion, const Clave& clave)
    : id_(id), nombre_(nombre), apellidos_(apellidos), direccion_(direccion), password_(clave) 
{
    if (!Usuarios_.insert(id).second) throw Id_duplicado(id);
}

Usuario::~Usuario() {
    for (auto& par : tarjetas_) {
        par.second->titular(nullptr); // Desvincula la tarjeta[cite: 3]
    }
    Usuarios_.erase(id_);
}

void Usuario::compra(Articulo& a, unsigned int cantidad) {
    if (cantidad == 0) carrito_.erase(&a);
    else carrito_[&a] = cantidad;
}

void Usuario::es_titular_de(Tarjeta& t) {
    tarjetas_.insert(std::make_pair(t.numero(), &t));
}

void Usuario::no_es_titular_de(Tarjeta& t) {
    tarjetas_.erase(t.numero());
}

std::ostream& operator <<(std::ostream& os, const Usuario& u) {
    os << u.id_ << " [" << u.password_.clave() << "] " << u.nombre_ << " " << u.apellidos_ << "\n"
       << u.direccion_ << "\n"
       << "Tarjetas:\n";
    for (auto const& par : u.tarjetas_) {
        os << *par.second << "\n";
    }
    return os;
}

std::ostream& mostrar_carro(std::ostream& os, const Usuario& u) {
    os << "Carrito de la compra de " << u.id() << "[Articulos: " << u.n_articulos() << "]\n";
    os << "Cant. Articulo\n";
    os <<"============================================\n";
    for (auto const& par : u.carrito()) {
        os << std::setw(4)<<par.second << " " << *par.first << "\n";
    }
    return os;
}