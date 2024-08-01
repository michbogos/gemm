#include<stdio.h>
#include<stdlib.h>

int main(){
    int N, M, K;

    FILE* fileptr;

    fileptr = fopen("tst.txt", "r");  // Open the file in binary mode
    // fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
    // filelen = ftell(fileptr);             // Get the current byte offset in the file
    // rewind(fileptr);                      // Jump back to the beginning of the file

    // buffer = (char *)malloc(filelen * sizeof(char)); // Enough memory for the file
    // fread(buffer, filelen, 1, fileptr); // Read in the entire file
    // fclose(fileptr); // Close the file

    int res = fscanf(fileptr, "%d %d %d", &N, &M, &K);
    if(res != 3) return 0;
    printf("%d %d %d\n", N, M, K);
    float mat1[3*N*M];
    float mat2[M*K];
    float mat3[N][K];

    char buf[256];

    for(int i = 0; i < 3*N*M; i++){
        fscanf(fileptr, "%f", mat1+i);
    }

    // for(int i = 0; i < M*K; i++){
    //     fgets(buf, 256, fileptr);
    //     sscanf(buf, "%f", mat2+i);
    // }


    // for(int i = 0; i < N; i++){
    //     for(int j = 0; j < M; j++){
    //         for(int k = 0; k < K; k++){
    //             mat3[i][k] += mat1[i*M+j]*mat2[j*K+k];
    //         }
    //     }
    // }
    // for(int i = 0; i < N; i++){
    //     for(int j = 0; j < K; j++){
    //         printf("%1.1f ", mat3[i][j]);
    //     }
    //     printf("\n");
    // }

    fclose(fileptr);
    return 0;
}