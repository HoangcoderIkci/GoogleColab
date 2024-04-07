from sympy import symbols, Poly
from sympy.abc import x
from sympy.matrices import Matrix

# Define the variable for polynomial
var = symbols('x')
arrNghichDao = [0,1,3,2,4]
# Define the field GF(5)
GF5 = lambda poly: Poly(poly, var).set_domain('GF(5)')
def tru_2_matrix(A,B):
    print(A)
    print(B)
    return Matrix(A.shape[0], A.shape[1],lambda i, j: A[i, j] - B[i, j])
def process(A):
    num_row,num_col = A.shape
    # Tạo ma trận đơn vị cùng kích thước với A
    # Tính Ex - A
    Ex_minus_A = A
    rank = 0
    while rank < num_row:
        for i in range(rank,num_row):
            if not Ex_minus_A[i,rank].has(x):
                Ex_minus_A[rank,:],Ex_minus_A[i,:] = Ex_minus_A[i,:],Ex_minus_A[rank,:]
                #print(Ex_minus_A)
                Ex_minus_A[rank,:] = Ex_minus_A[rank,:] * arrNghichDao[Ex_minus_A[rank,rank]]
                break
        for i in range(rank+1,num_row):
            if Ex_minus_A[i,rank]:
                Ex_minus_A[i,:] = tru_2_matrix(Ex_minus_A[i,:],Ex_minus_A[rank,:]* Ex_minus_A[i,rank])
               # Ex_minus_A[i,:] = Ex_minus_A[i,:] - Ex_minus_A[rank,:] * Ex_minus_A[i,rank]
        for j in range(rank+1,num_col):
            Ex_minus_A[rank,j] = 0
        rank += 1
        print(Ex_minus_A)
# Create a matrix with polynomial elements in GF(5)
E = Matrix([
    [GF5(x), GF5(0)],
    [GF5(0), GF5(x)]
])
A = Matrix([
    [GF5(1), GF5(2)],
    [GF5(0), GF5(4)]
])
# Tính hiệu của hai ma trận E và A theo từng phần tử
matrix_GF5_difference_elementwise = Matrix(E.shape[0], E.shape[1], 
                                           lambda i, j: E[i, j] - A[i, j])

print(matrix_GF5_difference_elementwise)
process(matrix_GF5_difference_elementwise)
