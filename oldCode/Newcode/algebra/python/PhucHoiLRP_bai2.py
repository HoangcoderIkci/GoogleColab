import numpy as np


DEGREE = 3
CHARACTER = 2
SIZEPOLE = 8
hsPole = 11
arrMultiple = [[0] * SIZEPOLE for i in range(SIZEPOLE)]
arrInverseSubtraction = [0] * SIZEPOLE


def multipleTwoElementField(a, b):
    if a == 0 or b == 0:
        return 0
    result = 0
    temp = 1 << DEGREE
    a_cp = 0
    k = 0
    t = 0
    while b != 0:
        if b & 0x1:
            t = k
            a_cp = a
            while t:
                a_cp <<= 1
                t -= 1
                if a_cp & temp:
                    a_cp ^= hsPole
            result ^= a_cp
        k += 1
        b >>= 1
    return result


def createArrayMult():
    temp = 0
    for i in range(SIZEPOLE):
        for j in range(i, SIZEPOLE):
            temp = multipleTwoElementField(i, j)
            arrMultiple[i][j] = temp
            arrMultiple[j][i] = temp
            if temp == 1:
                arrInverseSubtraction[i] = j
                arrInverseSubtraction[j] = i


def createArrayMultModule(module):
    temp = 0
    for i in range(module):
        for j in range(i, module):
            temp = (i * j) % module
            arrMultiple2[i][j] = temp
            arrMultiple2[j][i] = temp
            if temp == 1:
                arrInverseSubtraction2[i] = j
                arrInverseSubtraction2[j] = i


module = int(input("Nhập module của Pole: "))
# createMatrixAndColumn([0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1], 6)
# module = 5
arrMultiple2 = [[0] * module for i in range(module)]
arrInverseSubtraction2 = [0] * module
createArrayMultModule(module=module)


def PhucHoiLRP(lst_hs, lst_curr_u, curr_id, target_id, mod):
    if lst_hs[0] == 0:
        print("matrix khong nghich dao\n")
        return
    distance = curr_id - target_id
    deg = len(lst_hs) - 1
    col_first = np.array(lst_hs.copy()[1:-1])
    print(col_first)
    col_first = np.append(col_first, 1)
    recip_f = arrInverseSubtraction2[lst_hs[0]]
    for id in range(len(col_first)):
        col_first[id] = (mod - arrMultiple2[col_first[id]][recip_f]) % mod
    for i in range(deg - 1):
        new_col = np.zeros(deg)
        new_col[i] = 1
        col_first = np.column_stack((col_first, new_col))
    print(col_first)
    row_u = lst_curr_u
    res = []
    for turn in range(distance):
        for k in range(deg):
            temp = 0
            for j in range(deg):
                temp = (temp + arrMultiple2[row_u[j]][int(col_first[j][k])]) % mod
            # print(temp)
            res.append(temp)
        row_u = res.copy()
        print("luot : ", turn)
        print(res)
        print()
        res = []
    print(row_u)


##################### Bài 2 #####################################

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
vitrihientai = int(
    input(
        "Vị trí hiện tại (trong ví dụ là 2*m nhập là 12 chứ không được nhập 2*6 nhé!!!) : "
    )
)
# lst_hs = [4, 2, 4, 1, 0, 4, 1]
# lst_curr_hs = [1, 0, 4, 2, 4, 2]
PhucHoiLRP(lst_hs, lrp_u, vitrihientai, 0, mod=module)
