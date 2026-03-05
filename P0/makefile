# 1. Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = prueba
SRCS = fecha.cpp cadena.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

# 2. Regla principal (la que se ejecuta al escribir 'make')
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# 3. Regla para convertir cada .cpp en un .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 4. Limpieza
clean:
	del /f $(TARGET).exe *.o