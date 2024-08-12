#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<immintrin.h>

float randf(){
    return (float)rand()/(float)RAND_MAX;
}

int main(){
    int N, M, K;

    N = 512*2;
    M = 512*2;
    K = 512*2;
    int BS = 8;

    // FILE* fileptr;

    // fileptr = fopen("test.txt", "r");  // Open the file in binary mode
    // if(fileptr == NULL){
    //     return 0;
    // }
    // int res = fscanf(fileptr, "%d %d %d", &N, &M, &K);
    // if(res != 3) return 0;
    printf("%d %d %d\n", N, M, K);
    float* mat1 =   aligned_alloc(32, N*M*sizeof(float));
    float* mat2 =   aligned_alloc(32, M*K*sizeof(float));
    float* mat3 =   aligned_alloc(32, N*K*sizeof(float));
    float* matref = aligned_alloc(32, N*K*sizeof(float));

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
    for(int i = 0; i < N; i+=BS){
        for(int j = 0; j < M; j+=BS){
            for(int k = 0; k < K; k += BS){
                for(int by = 0; by < BS; by++){
                        __m256 a = _mm256_load_ps(mat1+(i+by)*M+j);
                        __m256 b = _mm256_load_ps(mat2+(j+by)*K+k);
                        
                }
                // mask = K-k < 8 ? large_masks[8-(K-k)]:large_masks[0];
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
    printf("Reference      GFLOPS/S     : %f\n", N*K*M/(((float)tocref-(float)ticref)/(float)CLOCKS_PER_SEC)/1000000000);
    printf("Implementation GFLOPS/S     : %f\n", N*K*M/(((float)toc-(float)tic)/(float)CLOCKS_PER_SEC)/1000000000);
    // fclose(fileptr);
    return 0;
}