#include<immintrin.h>
#include<stdlib.h>

int main(){
    int N = 1024;
    int M = 1024;
    int K = 1024;

    float* mat1 =   _mm_malloc(N*M*sizeof(float), 64);
    float* mat2 =   _mm_malloc(M*K*sizeof(float), 64);
    float* mat3 =   _mm_malloc(N*K*sizeof(float), 64);
    float* matref = _mm_malloc(N*K*sizeof(float), 64);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            for(int k = 0; k < (K/8)*8; k+=8){
                __m256 b = _mm256_load_ps(mat2+j*K+k);
                __m256 c = _mm256_load_ps(mat3+i*K+k);
                _mm256_store_ps(mat3+i*K+k, _mm256_fmadd_ps(_mm256_set1_ps(mat1[i*M+j]), b,c));
            }
        }
    }
    return 0;
}