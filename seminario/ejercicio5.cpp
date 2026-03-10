#include <iostream>

class C{
    public:
        C();
        C(int a, int b, int c, int d);
        int f1(int i) const;
        int f2(int i);
        void f3() {m = h;} //Error al ser una funcion estatica y no recibir el puntero this no se puede acceder a los miembros no estaticos, por lo que se debe cambiar a static void f3() {m = 0;} o se le quita el static a la funcion
        static int n;
    private:
        mutable int h;
        mutable int i; //si se modifica en una funcion const, al ser mutable, se puede modificar
        const int j;
        mutable int k;
        static int m;
};

int C::f1(int i) const{ //Error 1: al ser constante no se puede modificar el valor de h al ser declarado como int h (o se pone mutable int h o se le quita el const a la funcion)
    h = i; k=i; return 0;
}

C::C(): h{0}, j{0}, k{0} {} //Error 2: j es cont y se modifica dentro del cuerpo del constructor, se debe inicializar en la lista de inicializacion del constructor, por lo que se debe cambiar a C::C(): h{0}, j{0}, k{0} {}
C::C(int a, int b, int c, int d): h{a}, i{b}, j{c}, k{d} {}
int C::f2(int i){
    k=i; h=i; return 0;
}

int main(){
    C c1, c2; 
    C::n=3; //esta asignacion a un metodo estatico hay que hacerla de forma global
    c1.n=4;//esta asignacion a un metodo estatico hay que hacerla de forma global, por lo que se debe cambiar a C::n=4; o se le quita el static a la variable n
    std::cout << C::n << " " << c2.n << std::endl; //por la misma razon, se debe cambiar a std::cout << C::n << " " << C::n << std::endl; o se le quita el static a la variable n
}

