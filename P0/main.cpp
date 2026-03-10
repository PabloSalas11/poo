#include "cadena.hpp"
#include "fecha.hpp"

using namespace std;

int main() {
    Cadena c("Hola, mundo!");
    cout << "La longitud es:" << c.length() << " y la cadena es: ";
    c.imprimir();

    Cadena c2 = c.substr(1,6);
    cout << "Subcadena: ";
    c2.imprimir();

    
    Fecha f1;
    cout << "Fecha: " << f1.dia() << "/" << f1.mes() << "/" << f1.anno() << endl;
    return 0;
    
}