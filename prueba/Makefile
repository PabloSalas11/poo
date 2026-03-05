programa: x.o y.o z.o
	c++ -o programa x.o y.o z.o
x.o: x.cpp x.hpp xy.hpp
	c++ -c x.cpp
y.o: y.cpp xy.hpp
	c++ -c y.cpp
z.o: z.cpp 
	c++ -c z.cpp