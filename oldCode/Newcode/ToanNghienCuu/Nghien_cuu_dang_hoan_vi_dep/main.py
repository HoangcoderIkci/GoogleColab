import itertools
import numpy as np
from math import gcd,comb
from collections import defaultdict

CHAR = 2
DEGREE = 4
SIZEPOLE = 1 << DEGREE
limit = (1 << DEGREE) - 1
hsPole = 19  # x^3 + x + 1
#hsPole =(1<<8) + (1 << 4) + 8 + 4 + 1#x^8+x^4+x^3+x^2+1
def myRegister(x):
    return ((x << 1) ^ (x >> (DEGREE - 1))) & limit

def multipleTwoElement(a, b):
    if a == 0 or b == 0:
        return 0
    result = 0
    temp = 1 << DEGREE
    a_cp = 0
    k = 0
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
    arrMultiple = np.zeros((SIZEPOLE, SIZEPOLE), dtype=np.uint32)
    arrInverseSubtraction = np.zeros(SIZEPOLE, dtype=np.uint32)
    for i in range(SIZEPOLE):
        for j in range(i, SIZEPOLE):
            temp = multipleTwoElement(i, j)
            arrMultiple[i][j] = temp
            arrMultiple[j][i] = temp
            if temp == 1:
                arrInverseSubtraction[i] = j
                arrInverseSubtraction[j] = i
    return arrMultiple, arrInverseSubtraction

def Tim_he_so_hoan_vi(MyS_BOX, luot, vec_he_so_hoan_vi):
    #res = np.zeros((SIZEPOLE, SIZEPOLE), dtype=np.uint32)
    A = 0
    #check = True
    v_temp = []
    for i in range(1, SIZEPOLE - 1):
        A = 0
        for j in range(1, SIZEPOLE):
            c = 1
            nghich_j = arrInverseSubtraction[j]
            for k in range(i):
                c = arrMultiple[c][nghich_j]
            A ^= arrMultiple[c][MyS_BOX[j]]
        if A:
            v_temp.append(i)
    vec_he_so_hoan_vi[tuple(v_temp)] += 1

    template_elem = v_temp[0]
    for i in range(1, len(v_temp)):
        elem = v_temp[i]
        flag = False
        elem2 = myRegister(elem)
        while elem2 != elem:
            if elem2 == template_elem:
                flag = True
                break
            elem2 = myRegister(elem2)
        if not flag:
            print("Hoan vi xau!!!", luot)
            return False
    #print("Hoan vi dep !!!", luot)
    return True

def Dixon(k,a):
    int_part_k = k//2
    coefficients = [1]
    a_temp = 1
    for j in range(1,int_part_k+1):
        c = k * comb(k-j,j)*(-1)**(j)//(k-j) 
        #print(f"c = {c}")
        if c&0b1:
            a_temp = arrMultiple[a][a_temp]
            #print(f"a_temp = {a_temp}")
            coefficients.append(a_temp)
        else:
            coefficients.append(0)
    #for j in range(int_part_k+1):
        #print(f"x^{k-2*j}",end="+")
    #print()
    return coefficients

arrMultiple, arrInverseSubtraction = createArrayMult()
ArrayPowerSupport = [0] * SIZEPOLE  # tại vị trí i là giá trị của x^i
ArrayPower = []   # tại vị trí[x][i]  là x^i
def createArrayPower():
    ArrayPowerSupport[0] = 1
    temp = 2
    for idx1 in range(1,SIZEPOLE):
        ArrayPowerSupport[idx1] = temp
        temp = arrMultiple[2][temp]                
    lst_temp = []
    ArrayPower.append([0] * SIZEPOLE)
    ArrayPower.append([1] * SIZEPOLE)
    ArrayPower.append(ArrayPowerSupport)
    for idx1 in range(3,SIZEPOLE):
        temp = idx1
        lst_temp = [1,temp]
        # tìm vị trí của temp trong arrSp
        index_temp = ArrayPowerSupport.index(temp)
        for idx2 in range(2,SIZEPOLE):
            temp = (idx2 * index_temp) % (SIZEPOLE - 1)
            lst_temp.append(ArrayPowerSupport[temp])
        ArrayPower.append(lst_temp.copy())  
createArrayPower()
def valueOfDixon(k,coeff):
    #k = coeff[0]
    val = 0
    int_part_k = k//2
    arrVal = [0]
    for elem in range(1,SIZEPOLE):
        val = 0
        for j in range(0,int_part_k+1):
            val ^= arrMultiple[coeff[j]][ArrayPower[elem][k-2*j]]
        arrVal.append(val)
    return arrVal
def findNumberOfSpecialDifferenceCharacteristics2(intput_S_BOX):
    intput_S_BOX_temp = []
    for elem in ArrayPowerSupport[1:]:
        intput_S_BOX_temp.append(intput_S_BOX[elem])
    print(intput_S_BOX_temp)
    #intput_S_BOX_temp.append(intput_S_BOX[1])
    for turn in range(1,SIZEPOLE-1):
        arr_temp = intput_S_BOX_temp[turn:] + intput_S_BOX_temp[:turn]
        row_A = [arr_temp[id]^intput_S_BOX_temp[id] for id in range(SIZEPOLE-1)]
        print(row_A,len(set(row_A)))
        
def findNumberOfSpecialDifferenceCharacteristics(intput_S_BOX):
    mx = 0
    res = np.zeros((SIZEPOLE, SIZEPOLE), dtype=np.uint32)

        # Tính toán bảng số lần xuất hiện của các giá trị sau khi áp dụng S-Box và XOR
    for i in range(2, SIZEPOLE):
        for j in range(SIZEPOLE):
            b = intput_S_BOX[arrMultiple[j][i]] ^ intput_S_BOX[j]
            res[i][b] += 1

        # Tìm giá trị lớn nhất trong bảng res và reset bảng cho lần tính toán tiếp theo
    for i in range(2, SIZEPOLE):
        for j in range(SIZEPOLE):
            if res[i][j] > mx:
                mx = res[i][j]
            res[i][j] = 0
        #if mx == 1:
    print(f"mx = {mx}")
    return mx
            #count_per_beautiful+=1
            # if Tim_he_so_hoan_vi(S_BOX_permuted, luot, vec_he_so_hoan_vi):
            #     count_per_beautiful += 1
            # luot += 1

#2x^1 + 5x^2 + 6x^4
def F():
    values = []
    for elem in range(SIZEPOLE):
        c = 0
        c^= arrMultiple[5][ArrayPower[elem][2]] ^ arrMultiple[6][ArrayPower[elem][4]] ^ arrMultiple[2][elem] #^ ArrayPower[elem][6]
        values.append(c)
    print(f"values = {values}")
#-----------------------------------------------------  Main Functions ----------------------------------------------------

arr_temp_sbox = [0, 10, 2, 15, 13, 6, 4, 8, 1, 7, 12, 5, 3, 14, 9, 11]
print(findNumberOfSpecialDifferenceCharacteristics(arr_temp_sbox))
# glo_k = 7
# coeff = Dixon(glo_k,1)
# arrV = valueOfDixon(glo_k,coeff)
# print(coeff)
#         #print(len(set(arrV)) == SIZEPOLE)
# mx = findNumberOfSpecialDifferenceCharacteristics2(arrV)
# lst = [0]
# for id in range(1,128):
#     lst.append(id)
#     lst.append(255-id)
# lst.append(255)
# print(lst)
# lst2 = [0] * SIZEPOLE
# for id in range(len(lst)):
#     lst2[ArrayPowerSupport[id]] = lst[id]
# mx = findNumberOfSpecialDifferenceCharacteristics(lst2)
# print(mx)

for k in range(2,SIZEPOLE):
    d = gcd(k,SIZEPOLE**2 - 1)
    glo_a = 2
    if d == 1:
        glo_k = k
        coeff = Dixon(glo_k,glo_a)
        arrV = valueOfDixon(glo_k,coeff)
        #print(arrV)
        #print(len(set(arrV)) == SIZEPOLE)
        print(f"k={k}")
        print(f"coeff = {coeff}")
        mx = findNumberOfSpecialDifferenceCharacteristics(arrV)
        #if mx == 1:
        print(f"mx={mx}") 
# if __name__ == "__main__":
#     S_BOX = list(range(SIZEPOLE))
#     vec_he_so_hoan_vi = defaultdict(int)
#     luot = 1
#     count_per_beautiful = 0
#     for permutation in itertools.permutations(S_BOX):
#         S_BOX_permuted = list(permutation)
#         # Giả sử arrMultiple và S_BOX đã được khởi tạo và tính toán trước đó
#         mx = 0
#         res = np.zeros((SIZEPOLE, SIZEPOLE), dtype=np.uint32)

#         # Tính toán bảng số lần xuất hiện của các giá trị sau khi áp dụng S-Box và XOR
#         for i in range(2, SIZEPOLE):
#             for j in range(SIZEPOLE):
#                 b = S_BOX_permuted[arrMultiple[j][i]] ^ S_BOX_permuted[j]
#                 res[i][b] += 1

#         # Tìm giá trị lớn nhất trong bảng res và reset bảng cho lần tính toán tiếp theo
#         for i in range(2, SIZEPOLE):
#             for j in range(SIZEPOLE):
#                 if res[i][j] > mx:
#                     mx = res[i][j]
#                 res[i][j] = 0
#         if mx == 1:
#             #count_per_beautiful+=1
#             if Tim_he_so_hoan_vi(S_BOX_permuted, luot, vec_he_so_hoan_vi):
#                 count_per_beautiful += 1
#             luot += 1

#     print("dem_so_luong_hv_dep:", count_per_beautiful)





