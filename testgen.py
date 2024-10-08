import numpy as np

N = 512
M = 512
K = 512

mat1 = np.random.rand(N, M)
mat2 = np.random.rand(M, K)
mat3 = mat1@mat2

with open("test.txt", "w") as f:
    f.write(" ".join([str(i) for i in [N, M, K]])+"\n")
    for i in range(N):
        f.write("\n".join([str(mat1[i][j]) for j in range(M)])+"\n")
    
    for i in range(M):
        f.write("\n".join([str(mat2[i][j]) for j in range(K)])+"\n")
    
    for i in range(N):
        f.write("\n".join([str(mat3[i][j]) for j in range(K)])+"\n")
