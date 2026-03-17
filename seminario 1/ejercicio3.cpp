#include <iostream> //Solucion ejercicio 3

class C{
    public: 
        C(int i=0, bool al = false): n{i}, hayAlerta{al} {}
        void  mostrar () const{ //El error esta en el const, ya que alerta() no es const, por lo que no se puede llamar a una funcion no const desde una funcion const
            if (hayAlerta) alerta();
            std::cout<< "Valor: " << n << std::endl;
        }
    private:
        int n;
        bool hayAlerta;
        void alerta() const{std::cout << "Alerta" << std::endl;} //El error tambien estaba en esta linea ya que para llamar a un objeto const, la funcion tambien debe ser const, por lo que se le agrego el const al final de la funcion
};

int main(){const C c; c.mostrar();}

// #include <iostream> (Enunciado ejercicio 3)

// class C{
//     public: 
//         C(int i=0, bool al = false): n{i}, hayAlerta{al} {}
//         void  mostrar () const{ //El error esta en el const, ya que alerta() no es const, por lo que no se puede llamar a una funcion no const desde una funcion const
//             if (hayAlerta) alerta();
//             std::cout<< "Valor: " << n << std::endl;
//         }
//     private:
//         int n;
//         bool hayAlerta;
//         void alerta() const{std::cout << "Alerta" << std::endl;} //El error tambien estaba en esta linea ya que para llamar a un objeto const, la funcion tambien debe ser const, por lo que se le agrego el const al final de la funcion
// };

// int main(){const C c; c.mostrar();}

