#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

// Declaració de la variable global
vector<string> noms;

void afegirNom(const string& nom) {
    noms.push_back(nom);
}

void mostrarFraseAleatoria() {
    srand(time(nullptr));
    if (!noms.empty()) {
        int index = rand() % noms.size();
        cout << "El procés " << getpid() << " ha triat el nom: " << noms[index] << endl;
    }
}

int main() {
    srand(time(nullptr));
    int N;
    cout << "Introduïu el nombre de processos a crear: ";
    cin >> N;

    // Inicialitzar el generador de números aleatoris

    // Demanar els noms abans de crear els processos
    vector<string> nomsProc(N);
    for (int i = 0; i < N; i++) {
        cout << "Introduïu el nom per al procés " << (i + 1) << ": ";
        cin >> nomsProc[i];
    }

    // Crear els processos
    for (int i = 0; i < N; i++) {
        pid_t pid = fork();

        if (pid == 0) {  // Procés fill
            afegirNom(nomsProc[i]);  // Afegir el nom corresponent
            mostrarFraseAleatoria();  // Mostrar una frase amb un nom triat aleatòriament
            exit(0);  // Sortir del procés fill
        } else if (pid < 0) {
            cerr << "Error en crear el procés." << endl;
            exit(1);
        }
    }

    // Esperar que tots els processos fills acabin
    for (int i = 0; i < N; i++) {
        wait(NULL);
    }

    cout << "Tots els processos han acabat." << endl;
    return 0;
}