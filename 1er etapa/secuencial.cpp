#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

// llenar matriz con numeros aleratorios 
void cargarMatrizAleatoria(vector<vector<int>>& matriz) {

    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[i].size(); j++) {

            matriz[i][j] = rand() % 10; //numeros entre 0 y 9
        }
    }
}

// para prueba con mattrices pequeas
void mostrarMatriz(const vector<vector<int>>& matriz, string nombre) {

    cout << "\nMatriz " << nombre << ":\n";

    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[i].size(); j++) {

            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}

int main() {

    srand(time(0));

    // Tamaño fijo de matrices
    int M = 5000;
    int R = 5000;
    int N = 5000;

    vector<vector<int>> A(M, vector<int>(R));
    vector<vector<int>> B(R, vector<int>(N));
    vector<vector<int>> C(M, vector<int>(N, 0));

    // Carga automática
    cargarMatrizAleatoria(A);
    cargarMatrizAleatoria(B);

    // Inicio medicion de tiempo
    auto inicio = high_resolution_clock::now();

    // Multiplicacion de matrices
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < R; k++) {

                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Fin medicion
    auto fin = high_resolution_clock::now();

    // Tiempo en segundos
    duration<double> tiempo = fin - inicio;

    cout << "\nTiempo de ejecucion: "
         << tiempo.count()
         << " segundos\n";

    // mostrarMatriz(C, "Resultado");

    return 0;
}
