#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h> 

std::vector<std::string> nombres;

void agregarNombre(const std::string& nombre) {
    nombres.push_back(nombre);
}

void mostrarFrase() {
    if (!nombres.empty()) {
        int indiceAleatorio = rand() % nombres.size();
        std::cout << "Hola, " << nombres[indiceAleatorio] << "!" << std::endl;
    }
    else {
        std::cout << "El array de nombres esta vacio." << std::endl;
    }
}

void simularProcesoHijo(int procesoNum) {
    std::string nombre;
    std::cout << "Ingresa un nombre para el proceso " << procesoNum << ": ";
    std::cin >> nombre;

    agregarNombre(nombre);

    mostrarFrase();
}

int main() {
    int N;
    std::cout << "Ingresa el numero de procesos que deseas crear: ";
    std::cin >> N;

    srand(time(0)); 

    for (int i = 0; i < N; ++i) {
        HANDLE hThread = CreateThread(
            NULL,          
            0,             
            (LPTHREAD_START_ROUTINE)simularProcesoHijo, 
            (LPVOID)(i + 1),
            0,              
            NULL);         

        if (hThread == NULL) {
            std::cerr << "Error al crear el hilo " << i + 1 << std::endl;
            return 1;
        }

        WaitForSingleObject(hThread, INFINITE);

        CloseHandle(hThread);
    }

    std::cout << "Nombres finales en el array:" << std::endl;
    for (const auto& nombre : nombres) {
        std::cout << nombre << std::endl;
    }

    return 0;
}
