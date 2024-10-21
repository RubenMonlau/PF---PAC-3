#include <iostream>
#include <vector>
#include <cstdlib>  // srand, rand
#include <ctime>    // time
#include <unistd.h> // fork
#include <sys/wait.h> // wait

std::vector<std::string> lista_nombres; // Variable global para almacenar nombres
std::vector<std::string> frases = {
    "Hoy es un gran día, ",
    "Sigue tus sueños, ",
    "Nunca te rindas, ",
    "El esfuerzo siempre tiene recompensa, ",
    "Cada día es una nueva oportunidad, "
}; // Lista de frases aleatorias

void añadir_nombre(const std::string& nombre) {
    lista_nombres.push_back(nombre);
}

std::string obtener_frase_aleatoria() {
    int indice_frase = rand() % frases.size();
    return frases[indice_frase];
}

int main() {
    srand(time(nullptr)); // Inicializamos la semilla para la generación de números aleatorios

    int cantidad_procesos;
    std::cout << "Introduce la cantidad de procesos a crear: ";
    std::cin >> cantidad_procesos;

    // El proceso padre añade un nombre inicial
    // Creamos la cantidad especificada de procesos
    for (int i = 0; i < cantidad_procesos; ++i) {
        pid_t pid = fork();
        if (pid == 0) { // Proceso hijo
            _exit(0); // Terminamos el proceso hijo
        }
        if (pid > 0) {
            wait(nullptr); // Esperamos a que termine el proceso hijo

            // El proceso padre recoge el nombre de cada hijo
            std::string nombre_recibido;
            std::cout << "Proceso hijo #" << i + 1 << ", introduce un nombre: ";
            std::cin >> nombre_recibido;
            añadir_nombre(nombre_recibido); // Añadimos el nombre
        }
        else {
            std::cerr << "Error al crear el proceso!" << std::endl;
            return 1;
        }
    }

    // El proceso padre muestra todos los nombres finales
    std::cout << "Lista final de nombres:\n";
    for (const auto& nombre : lista_nombres) {
        std::cout << nombre << std::endl;
    }

    // Seleccionamos un nombre y una frase aleatoria
    srand(static_cast<unsigned int>(time(nullptr)) + lista_nombres.size()); // Semilla basada en tiempo + tamaño de la lista
    std::string nombre_final = lista_nombres[rand() % lista_nombres.size()];
    std::string frase_final = obtener_frase_aleatoria();

    // Mostramos el resultado final
    std::cout << frase_final << nombre_final << std::endl;

    return 0;
}
