#include <iostream>
#include <thread>

const int n = 1000;

int A[n][n];
int B[n][n];
int C[n][n];
int D[n][n];

int Q[n][n];
int R[n][n];

void multiply() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Q[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                Q[i][j] += C[i][k] * D[k][j];
            }
        }
    }
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);

    std::srand(std::time(nullptr));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int randomValue1 = std::rand() % (n+1);
            int randomValue2 = std::rand() % (n+1);
            A[i][j] = C[i][j] = randomValue1;
            B[i][j] = D[i][j] = randomValue2;
        }
    }

    clock_t start1 = clock();
    multiply();
    printf("Time taken by single thread: %.10f seconds\n", (double)(clock() - start1)/CLOCKS_PER_SEC);

    std::thread t1([](){
        for (int i = 0; i < 250; ++i) {
            for (int j = 0; j < 250; ++j) {
                R[i][j] = 0;
                for (int k = 0; k < n; ++k) {
                    R[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    });

    std::thread t2([](){
        for (int i = 250; i < 500; ++i) {
            for (int j = 250; j < 500; ++j) {
                R[i][j] = 0;
                for (int k = 0; k < n; ++k) {
                    R[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    });

    std::thread t3([](){
        for (int i = 500; i < 750; ++i) {
            for (int j = 500; j < 750; ++j) {
                R[i][j] = 0;
                for (int k = 0; k < n; ++k) {
                    R[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    });

    std::thread t4([](){
        for (int i = 750; i < 1000; ++i) {
            for (int j = 750; j < 1000; ++j) {
                R[i][j] = 0;
                for (int k = 0; k < n; ++k) {
                    R[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    });

    clock_t start2 = clock();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    printf("Time taken by 4 threads: %.10f seconds\n", (double)(clock() - start2)/CLOCKS_PER_SEC);

    return 0;
}
