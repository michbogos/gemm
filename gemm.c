#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<immintrin.h>
#include<omp.h>

#define NTHREADS 8

float randf(){
    return (float)rand()/(float)RAND_MAX;
}

int main(){
    int N, M, K;

    N = 1023;
    M = 1023;
    K = 1023;

    // FILE* fileptr;

    // fileptr = fopen("test.txt", "r");  // Open the file in binary mode
    // if(fileptr == NULL){
    //     return 0;
    // }
    // int res = fscanf(fileptr, "%d %d %d", &N, &M, &K);
    // if(res != 3) return 0;
    printf("%d %d %d\n", N, M, K);
    float* mat1 =   _mm_malloc(N*M*sizeof(float), 64);
    float* mat2 =   _mm_malloc(M*K*sizeof(float), 64);
    float* mat3 =   _mm_malloc(N*K*sizeof(float), 64);
    float* matref = _mm_malloc(N*K*sizeof(float), 64);

    for(int i = 0; i < N*M; i++){
        // fscanf(fileptr, "%f", &mat1[i]);
        mat1[i] = randf();
    }

    for(int i = 0; i < M*K; i++){
        // fscanf(fileptr, "%f", &mat2[i]);
        mat2[i] = randf();
    }

    // for(int i = 0; i < N*K; i++){
    //     // fscanf(fileptr, "%f", &matref[i]);
    // }
    clock_t ticref, tocref;
    ticref = clock();
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            for(int k = 0; k < K; k++){
                matref[i*K+k] += mat1[i*M+j]*mat2[j*K+k];
            }
        }
    }
    tocref = clock();

    int masks[16];
    for(int i = 0; i < 8; i++){
        masks[i] = ~(0);
    }
    for(int i = 8; i < 16; i++){
        masks[i] = 0;
    }

    __m256i large_masks[8];
    for(int i = 0; i < 8; i++){
        large_masks[i] = _mm256_set_epi32(masks[i+7], masks[i+6],masks[i+5],masks[i+4],masks[i+3],masks[i+2],masks[i+1],masks[i+0]);
    }

    __m256i mask;


    clock_t tic, toc;
    tic = clock();
    #pragma omp parallel for num_threads(NTHREADS) schedule(static)
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            __m256 a = _mm256_set1_ps(mat1[i*M+j]);
            for(int k = 0; k < (K/8)*8; k+=8){
                // mask = K-k < 8 ? large_masks[8-(K-k)]:large_masks[0];
                _mm256_storeu_ps(&mat3[i*K+k], _mm256_fmadd_ps(a, _mm256_loadu_ps(&mat2[j*K+k]),_mm256_loadu_ps(&mat3[i*K+k])));
                // mat3[i*K+k] += mat1[i*M+j]*mat2[j*K+k];
            }
        }
    }
    if(K%8!=0){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                __m256 a = _mm256_set1_ps(mat1[i*M+j]);
                int k = (K/8)*8;
                mask = large_masks[8-(K-k)];
                _mm256_maskstore_ps(&mat3[i*K+k], mask, _mm256_fmadd_ps(a, _mm256_maskload_ps(&mat2[j*K+k], mask),_mm256_maskload_ps(&mat3[i*K+k], mask)));
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
    printf("Reference      GFLOPS/S     : %f\n", 2*N*K*M/(((double)tocref-(double)ticref)/(double)CLOCKS_PER_SEC)/1000000000.0);
    printf("Implementation GFLOPS/S     : %f\n", (2*N*K*M/(((double)toc-(double)tic)/((double)CLOCKS_PER_SEC))/1000000000.0)*NTHREADS);
    // fclose(fileptr);
    return 0;
}