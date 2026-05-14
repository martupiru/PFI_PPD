#include <iostream>
#include <vector>

using namespace std;

int main() {

    int M, R, N;

    cout << "Ingrese cantidad de filas de A: ";
    cin >> M;

    cout << "Ingrese cantidad de columnas de A / filas de B: ";
    cin >> R;

    cout << "Ingrese cantidad de columnas de B: ";
    cin >> N;

    vector<vector<int>> A(M, vector<int>(R));
    vector<vector<int>> B(R, vector<int>(N));
    vector<vector<int>> C(M, vector<int>(N, 0));

    cout << "\n Ingrese matriz A: \n";
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < R; j++) {
            cin >> A[i][j];
        }
    }

    cout << "\n Ingrese matriz B: \n";
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < N; j++) {
            cin >> B[i][j];
        }
    }

    // multiplicacion de matrices
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < R; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    cout << "\n Matriz resultado C: \n";

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}