#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
    int N, M, K;

    FILE* fileptr;

    fileptr = fopen("test.txt", "r");  // Open the file in binary mode
    if(fileptr == NULL){
        return 0;
    }
    // fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
    // filelen = ftell(fileptr);             // Get the current byte offset in the file
    // rewind(fileptr);                      // Jump back to the beginning of the file

    // buffer = (char *)malloc(filelen * sizeof(char)); // Enough memory for the file
    // fread(buffer, filelen, 1, fileptr); // Read in the entire file
    // fclose(fileptr); // Close the file
    // char buf[512];
    // if(fgets(buf, 511, fileptr)==NULL){
    //     return 0;
    // }
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


    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            for(int k = 0; k < K; k++){
                mat3[i*K+k] += mat1[i*M+j]*mat2[j*K+k];
            }
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < K; j++){
            if(fabsf(mat3[i*K+j]-matref[i*K+j]) > 0.001){
                printf("Matmul error: %f %f\n", mat3[i*K+j], matref[i*K+j]);
                return 1;
            }
        }
    }
    fclose(fileptr);
    return 0;
}