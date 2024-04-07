import numpy as np


DEGREE = 2
CHARACTER = 2
SIZEPOLE = 4
hsPole = 7
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


# module = 5
# mt1 = np.array([[0, 1, 0, 1], [1, 0, 1, 0], [0, 1, 0, 1], [1, 0, 1, 0]])


def changeToBacThang(mt1):
    rank = 0
    lst_ind_basic = []
    # Lấy kích thước số hàng và cột của ma trận
    num_rows, num_cols = mt1.shape
    for col in range(num_cols):
        for row in range(rank, num_rows):
            if mt1[row][col]:
                lst_ind_basic.append(col)
                if row != rank:
                    mt1[row], mt1[rank] = mt1[rank], mt1[row]
                hs_nghich_dao = arrInverseSubtraction[mt1[rank][col]]
                # đưa hệ số về 1
                for id in range(col, num_cols):
                    mt1[rank][id] = arrMultiple[mt1[rank][id]][hs_nghich_dao]
                # ap null các rows ở dưới row rank:
                for idr in range(rank + 1, num_rows):
                    if mt1[idr][col]:
                        hs_temp = mt1[idr][col]
                        for idcl in range(col, num_cols):
                            mt1[idr][idcl] = (
                                mt1[idr][idcl] ^ arrMultiple[mt1[rank][idcl]][hs_temp]
                            )
                rank += 1
    print(mt1)
    # đưa về dạng chuẩn
    temp_r = rank - 1
    lst_temp_id_bs = lst_ind_basic
    lst_temp_id_bs.reverse()
    for id_bs in lst_temp_id_bs:
        for id_r in range(0, temp_r):
            if mt1[id_r][id_bs]:
                hs_temp = mt1[id_r][id_bs]
                mt1[id_r][id_bs] = 0
                for id_cl in range(id_bs + 1, num_cols):
                    mt1[id_r][id_cl] = (
                        mt1[id_r][id_cl] ^ arrMultiple[mt1[temp_r][id_cl]][hs_temp]
                    )
                print(mt1)
        temp_r -= 1
    print(mt1)


def changeToBacThangModule(mt1, module):
    # print(mt1)
    rank = 0
    lst_ind_basic = []
    # Lấy kích thước số hàng và cột của ma trận
    num_rows, num_cols = mt1.shape
    for col in range(num_cols):
        for row in range(rank, num_rows):
            if mt1[row][col]:
                lst_ind_basic.append(col)
                if row != rank:
                    temp_row = mt1[row].copy()
                    # print(temp_row)
                    mt1[row] = mt1[rank]
                    # print(temp_row)
                    mt1[rank] = temp_row
                    print(mt1, end="\n\n")
                    # mt1[row], mt1[rank] = mt1[rank], mt1[row]
                    # print(mt1)
                hs_nghich_dao = arrInverseSubtraction2[mt1[rank][col]]
                # đưa hệ số về 1
                for id in range(col, num_cols):
                    mt1[rank][id] = arrMultiple2[mt1[rank][id]][hs_nghich_dao]
                # ap null các rows ở dưới row rank:
                for idr in range(rank + 1, num_rows):
                    if mt1[idr][col]:
                        hs_temp = mt1[idr][col]
                        for idcl in range(col, num_cols):
                            mt1[idr][idcl] = (
                                mt1[idr][idcl] - arrMultiple2[mt1[rank][idcl]][hs_temp]
                            ) % module
                print(mt1, end="\n\n")
                rank += 1
    mt1 = mt1[0:rank, 0 : rank + 1]

    print(mt1, end="\n\n")
    num_cols = rank + 1
    rum_rows = rank
    # print()
    # đưa về dạng chuẩn
    temp_r = rank - 1
    lst_temp_id_bs = lst_ind_basic
    lst_temp_id_bs.reverse()
    for id_bs in lst_temp_id_bs:
        for id_r in range(0, temp_r):
            if mt1[id_r][id_bs]:
                hs_temp = mt1[id_r][id_bs]
                mt1[id_r][id_bs] = 0
                for id_cl in range(id_bs + 1, num_cols):
                    mt1[id_r][id_cl] = (
                        mt1[id_r][id_cl] - arrMultiple2[mt1[temp_r][id_cl]][hs_temp]
                    ) % module
                print(mt1, end="\n\n")
        temp_r -= 1
    #####  đảo hệ số từ a_i sang - a_i
    print("result: ")
    for id, elem in enumerate(mt1[:, -1]):
        print((module - elem) % module, end=f"x^{id} + ")
    print(f"x^{len(mt1[:-1])+1}")


# changeToBacThangModule(mt1, 2)


def createMatrixAndColumnfieldGF(lrp_u, degreeFunction, module):
    mtr = []
    # columnA = []
    lst_row = lrp_u[0:degreeFunction]
    mtr.append(lst_row.copy())
    for i in range(0, degreeFunction - 1):
        lst_row.pop(0)
        lst_row.append(lrp_u[degreeFunction + i])
        mtr.append(lst_row.copy())
    # print(lrp_u[len(lrp_u) - m :])
    # return mtr, lrp_u[len(lrp_u) - m :]
    # ------------------------------------------------------------------------------
    # step 2: solve the system
    # A = np.array(mtr)
    # B = np.array(lrp_u[len(lrp_u) - m :])
    # X = np.linalg.solve(A, B)
    # print(X)
    for id, elem in enumerate(lrp_u[len(lrp_u) - degreeFunction :]):
        mtr[id].append(elem)
    print("created matrix : ")
    for elem in mtr:
        print(elem)
    print("start bien doi : ", end="\n\n")
    changeToBacThangModule(np.array(mtr), module)


# createMatrixAndColumn([0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1], 6)

module = int(input("Nhập module của Pole: "))
arrMultiple2 = [[0] * module for i in range(module)]
arrInverseSubtraction2 = [0] * module
createArrayMultModule(module=module)


####################### bài 3$$################################################################
m = int(input("Nhập giá trị m(độ dài 1/2 của LRP u đề bài cho:"))
# lrp_u = [6, 2, 0, 5, 4, 5, 4, 0, 4, 5, 2, 5, 6, 6]
lrp_u = []
temp = 0
for i in range(m * 2):
    temp = int(input(f"U[{i}]"))
    lrp_u.append(temp)
print("Your LRP : ")
print(lrp_u)
# m = int(len(lrp_u) / 2)
createMatrixAndColumnfieldGF(lrp_u, degreeFunction=m, module=module)
