# import pyfiglet
from sympy import *

x = symbols("x")
# print(
#     "================================================================================================"
# )

# big_font = pyfiglet.Figlet()
# font = pyfiglet.Figlet(font="standard")
# print(font.renderText("Copyright@ By HoangCoder "))
# print(
#     "================================================================================================\n\n"
# )


def tim_gcd(lst_hs_f, lst_ham_tao, mod):
    A = sum(lst_hs_f[i] * x**i for i in range(len(lst_hs_f)))
    B = sum(lst_ham_tao[i] * x**i for i in range(len(lst_ham_tao)))
    D = 1
    Q = 0
    A_cp = A
    B_cp = B
    while D:
        Q, D = div(A, B, domain=GF(mod))
        print()
        print(f"{A} = ({B}) * ({Q}) + ({D})")
        print()
        A = B
        B = D
    gcd_A_B = gcd(A_cp, B_cp, domain=GF(mod))

    return A_cp, gcd_A_B


def Tim_ham_tao(lst_hs_f, lst_u, module):
    """_summary_
    tìm hàm khởi tạo của chuỗi u theo E^F(X)
    hệ số của lst_hs_f nhập theo thứ tự sau:
    vd : x^3 - 2x -5
    [-5,0,-2,1]
    còn u vẫn theo thứ tự ban đầu
    Args:
        lst_hs_f (_type_): hs of function
        lst_u (_type_): LRP
        module : GF(module)
    Returns:
        list[int]: list hs of hàm tạo
    """
    for i in range(len(lst_hs_f)):
        lst_hs_f[i] %= module
    for i in range(len(lst_u)):
        lst_u[i] %= module

    m = len(lst_hs_f) - 1
    lst_matrix = [[0] * m for i in range(m)]
    for i in range(1, m + 1):
        for j in range(i, m):
            lst_matrix[i - 1][j - i] = (lst_hs_f[j]) % module
        lst_matrix[i - 1][m - i] = 1
    r = [0] * m
    print("Matrix : ")
    # print(lst_matrix[0])
    for i in range(0, m):
        print(lst_matrix[i])
    for col in range(m):
        for row in range(m):
            r[col] = (r[col] + lst_matrix[row][col] * lst_u[row]) % module
            # print(r[col] % module)
    # r = [elem % module for elem in r]
    print("ham tao: ")
    for bac in range(m - 1):
        print(f"{r[bac]}x^{bac} + ", end="")
    print(f"{r[-1]}x^{m-1}")
    print("tim gcd: \n")
    A, gcd = tim_gcd(lst_hs_f, r, module)
    print("gcd: ", gcd)
    print("ham min: ")
    print(div(A, gcd, domain=GF(module))[0])


################################################################ bai 4 ##############
module = int(input("Nhập module của Pole: "))
degre = int(input("enter deg of function: "))
print("Nhap he so ham so f(x) theo thu tu tu f_0 to f_n:")
temp = 0

lst_hs = []
for i in range(degre + 1):
    temp = (int(input(f"He so cua f_{i} : "))) % module
    lst_hs.append(temp)
print("your f(x) : ", lst_hs)

lrp_u = []
for i in range(degre):
    temp = int(input(f"U[{i}]"))
    lrp_u.append(temp)
print("your LRP :  ", lrp_u)
# lst_hs = [6, 6, 0, 6, 5, 1, 4, 1]
# lrp_u = [2, 1, 3, 2, 3, 2, 1]
# module = 7
Tim_ham_tao(lst_hs, lrp_u, module)
