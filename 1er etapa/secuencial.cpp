#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace chrono;

// llenar matriz con numeros aleatorios
void cargarMatrizAleatoria(vector<vector<int>>& matriz) {

    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[i].size(); j++) {

            matriz[i][j] = rand() % 10;
        }
    }
}

int main(int argc, char* argv[]) {

    // Verificar parametros
    if (argc != 4) {

        cout << "Uso: ./programa M R N\n";
        cout << "A = MxR\n";
        cout << "B = RxN\n";

        return 1;
    }

    //dimensiones dadas
    int M = atoi(argv[1]);
    int R = atoi(argv[2]);
    int N = atoi(argv[3]);

    // Semilla fija
    srand(1234);

    //Crear matrices
    vector<vector<int>> A(M, vector<int>(R));
    vector<vector<int>> B(R, vector<int>(N));
    vector<vector<int>> C(M, vector<int>(N, 0));

    //cargar matrices aleatorias con numeros
    cargarMatrizAleatoria(A);
    cargarMatrizAleatoria(B);

    //inicio medicion
    auto inicio = high_resolution_clock::now();

    //multiplicacion matruces
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < R; k++) {

                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    //fin medicion
    auto fin = high_resolution_clock::now();

    //Tiempo total
    duration<double> tiempo = fin - inicio;

    cout << "\n Matriz A: " << M << "x" << R << endl;
    cout << "Matriz B: " << R << "x" << N << endl;

    cout << "\n Tiempo de ejecucion: "
         << tiempo.count()
         << " segundos \n";

    return 0;
}
