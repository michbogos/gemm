import numpy as np
import time

N = 1024*2
M = 1024*2
K = 1024*2

for i in range(10):
    mat1 = np.random.rand(N, M)
    mat2 = np.random.rand(M, K)
    tic = time.process_time_ns()
    mat3 = mat1@mat2
    toc = time.process_time_ns()
    print(f"Time: {(toc-tic)/10**9} GFLOPS/S: {(2*M*N*K)/(toc-tic)}")