#include<immintrin.h>
#include<stdlib.h>

int main(){
    int N = 9;
    int M = 9;
    int K = 9;

    float* mat1 =   aligned_alloc(32, N*M*sizeof(float));
    float* mat2 =   aligned_alloc(32, M*K*sizeof(float));
    float* mat3 =   aligned_alloc(32, N*K*sizeof(float));
    float* matref = aligned_alloc(32, N*K*sizeof(float));

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