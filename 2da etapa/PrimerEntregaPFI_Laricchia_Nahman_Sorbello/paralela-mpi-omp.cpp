#include <mpi.h>
#include <omp.h>

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void cargarMatrizAleatoria(vector<int>& matriz) {
    for (int i = 0; i < matriz.size(); i++) {
        matriz[i] = rand() % 10;
    }
}

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(1234);

    // Dimensiones matrices
    int M = 5000;
    int R = 5000;
    int N = 5000;

    // Cantidad de filas por proceso
    vector<int> filasPorProceso(size);
    vector<int> desplazamientos(size);

    int filasBase = M / size;
    int resto = M % size;

    int offset = 0;

    for (int i = 0; i < size; i++) {

        filasPorProceso[i] = filasBase;

        if (i < resto)
            filasPorProceso[i]++;

        desplazamientos[i] = offset;
        offset += filasPorProceso[i];
    }

    int filasLocales = filasPorProceso[rank];

    // Matrices
    vector<int> B(R * N);

    vector<int> ALocal(filasLocales * R);
    vector<int> CLocal(filasLocales * N, 0);

    vector<int> A;
    vector<int> C;

    if (rank == 0) {

        A.resize(M * R);
        C.resize(M * N);

        cargarMatrizAleatoria(A);
        cargarMatrizAleatoria(B);
    }

    // Broadcast matriz B
    MPI_Bcast(B.data(), R * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Preparar tamaños para Scatterv
    vector<int> sendCountsA(size);
    vector<int> displsA(size);

    for (int i = 0; i < size; i++) {
        sendCountsA[i] = filasPorProceso[i] * R;
        displsA[i] = desplazamientos[i] * R;
    }

    // Distribuir filas de A
    MPI_Scatterv(
        A.data(),
        sendCountsA.data(),
        displsA.data(),
        MPI_INT,
        ALocal.data(),
        filasLocales * R,
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );

    MPI_Barrier(MPI_COMM_WORLD);

    double inicio = MPI_Wtime();

   //Paralelizamos filas y columnas en el for en hilos
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < filasLocales; i++) {

        for (int j = 0; j < N; j++) {

            int suma = 0;

            for (int k = 0; k < R; k++) {

                suma +=
                    ALocal[i * R + k] * B[k * N + j];
            }

            CLocal[i * N + j] = suma;
        }
    }

    double fin = MPI_Wtime();

    // Preparar Gatherv
    vector<int> recvCountsC(size);
    vector<int> displsC(size);

    for (int i = 0; i < size; i++) {
        recvCountsC[i] = filasPorProceso[i] * N;
        displsC[i] = desplazamientos[i] * N;
    }

    // Recolectar resultados
    MPI_Gatherv(
        CLocal.data(),
        filasLocales * N,
        MPI_INT,
        C.data(),
        recvCountsC.data(),
        displsC.data(),
        MPI_INT,
        0,
        MPI_COMM_WORLD
    );

    if (rank == 0) {

        cout << "Tiempo paralelo MPI + OpenMP: "
             << (fin - inicio)
             << " segundos" << endl;
    }

    MPI_Finalize();

    return 0;
}
