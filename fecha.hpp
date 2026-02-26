#ifndef FECHA_HPP 
#define FECHA_HPP

#include <iostream>
#include <cstddef> 

class Fecha {
public:
    Fecha(int dia=0, int mes=0, int anno=0);
private:
    int dia_, mes_, anno_;
};
#endif