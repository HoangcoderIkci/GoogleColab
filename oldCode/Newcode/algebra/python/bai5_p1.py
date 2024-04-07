from sympy import *

x = symbols("x")
module = int(input("enter module Pole GF:"))
degre = int(input("enter deg of function: "))
print("Nhap he so ham so f(x) theo thu tu tu f_0 to f_n:")
temp = 0

coefficients = []
for i in range(degre + 1):
    temp = (int(input(f"He so cua f_{i} : "))) % module
    coefficients.append(temp)

# coefficients = [4, 3, 2, 1]
A = sum(coefficients[i] * x**i for i in range(len(coefficients)))
print("Đa thức của bạn là :", A)

# # B = 3 + 2 * x**1 + 3 * x**2 + 4 * x**3 + 2 * x**4 + 2 * x**5 + 2 * x**6
# # gcd_A_B = gcd(A, B, domain=GF(7))
# # quo, rem = div(A, gcd_A_B, domain=GF(7))


# A = x**4 - 5 * x**3 + 5 * x**2 + 5 * x - 6
factors = factor(A, domain=GF(module))
print("Phân tích đa thức thành nhân tử:", factors)


# print((3**i + 2 * 2**i + 1 + (-1) ** i) % 2609)
