// parte secuencial del ejercicio de multiplicacion de matrices. C.
#include <iostream>
#include <vector>

using namespace std;

// Funcion para cargar matrices
void cargarMatriz(vector<vector<int>>& matriz, string nombre) {

    cout << "\n=== Carga de matriz " << nombre << " ===\n";

    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[i].size(); j++) {

            while (true) {
                cout << nombre << "[" << i << "][" << j << "] = ";

                if (cin >> matriz[i][j]) {
                    break; // dato correcto
                }

                // limpiar error
                cin.clear();
                cin.ignore(1000, '\n');

                cout << "ERROR: ingrese un numero valido.\n";
            }
        }
    }
}

// Funcion para mostrar matrices
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

    int M, R, N;

    cout << "Cantidad de filas de A: ";
    cin >> M;

    cout << "Cantidad de columnas de A (y filas de B): ";
    cin >> R;

    cout << "Cantidad de columnas de B: ";
    cin >> N;

    vector<vector<int>> A(M, vector<int>(R));
    vector<vector<int>> B(R, vector<int>(N));
    vector<vector<int>> C(M, vector<int>(N, 0));

    cargarMatriz(A, "A");
    cargarMatriz(B, "B");

    // Multiplicacion
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < R; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    mostrarMatriz(A, "A");
    mostrarMatriz(B, "B");
    mostrarMatriz(C, "Resultado");

    return 0;
}