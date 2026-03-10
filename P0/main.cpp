#include "cadena.hpp"
#include "fecha.hpp"

using namespace std;

int main() {
    Cadena c;
    cout << "Cadena: " << c.length() << " y la cadena es: ";
    c.imprimir();

    Fecha fecha;
    cout << "Fecha: " << fecha.dia() << "/" << fecha.mes() << "/" << fecha.anno() << endl;
    return 0;
    
}