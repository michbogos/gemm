#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<immintrin.h>

int main(){
    int N, M, K;

    FILE* fileptr;

    fileptr = fopen("test.txt", "r");  // Open the file in binary mode
    if(fileptr == NULL){
        return 0;
    }
    int res = fscanf(fileptr, "%d %d %d", &N, &M, &K);
    if(res != 3) return 0;
    printf("%d %d %d\n", N, M, K);
    float mat1[N*M];
    float mat2[M*K];
    float mat3[N*K];
    float matref[N*K];

    for(int i = 0; i < N*M; i++){
        fscanf(fileptr, "%f", &mat1[i]);
    }

    for(int i = 0; i < M*K; i++){
        fscanf(fileptr, "%f", &mat2[i]);
    }

    for(int i = 0; i < N*K; i++){
        fscanf(fileptr, "%f", &matref[i]);
    }

    __m256 a;
    __m256 b;
    __m256 c;


    clock_t tic, toc;
    tic = clock();
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            for(int k = 0; k < K; k+=8){
                _mm256_store_ps(mat3+i*K+k, _mm256_add_ps(_mm256_load_ps(mat3+i*K+k),_mm256_mul_ps(_mm256_set1_ps(mat1[i*M+j]), _mm256_load_ps(mat2+j*K+k))));

                // mat3[i*K+k] += mat1[i*M+j]*mat2[j*K+k];
            }
        }
    }
    toc = clock();
    for(int i = 0; i < N; i++){
        for(int j = 0; j < K; j++){
            if(fabsf(mat3[i*K+j]-matref[i*K+j]) > 0.001){
                printf("Matmul error: %f %f\n", mat3[i*K+j], matref[i*K+j]);
                return 1;
            }
        }
    }
    printf("GFLOPS/S: %f\n", N*K*M/(((float)toc-(float)tic)/(float)CLOCKS_PER_SEC)/1000000000);
    fclose(fileptr);
    return 0;
}