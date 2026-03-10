#include "cadena.hpp"
#include "fecha.hpp"

using namespace std;

int main() {
    Cadena c("Hola, mundo!");
    cout << "La longitud es:" << c.length() << " y la cadena es: ";
    c.imprimir();

    c.substr(1,3);

    Fecha fecha;
    cout << "Fecha: " << fecha.dia() << "/" << fecha.mes() << "/" << fecha.anno() << endl;
    return 0;
    
}