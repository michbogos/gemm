#include<stdio.h>

int main(){
    float mat1[4][4] = {{3.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 3.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 3.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 3.0f}};
    float mat2[4][4] = {{2.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 2.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 2.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 2.0f}};
    float mat3[4][4] = {{0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}};

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                mat3[j][i] += mat1[j][k]*mat2[k][i];
            }
        }
    }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            printf("%1.1f ", mat3[i][j]);
        }
        printf("\n");
    }
    return 0;
}