import numpy as np
from math import gcd,comb
from collections import defaultdict

CHAR = 2
DEGREE = 5
SIZEPOLE = 1 << DEGREE
limit = (1 << DEGREE) - 1
hsPole = 37  # x^5 + x^2 + 1
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

def SolvSystem():
    flag = 1
    for a1 in range(1,SIZEPOLE):
        for a2 in range(1,SIZEPOLE):
            flag = 1
            for a in range(2,SIZEPOLE):
                for x in range(1,SIZEPOLE):
                    #res = arrMultiple[a1][ArrayPower[a][2]^1] ^ arrMultiple[ArrayPower[x][3]][arrMultiple[a2][ArrayPower[a][5]]^1]
                    res = a1 ^ arrMultiple[a2][x]
                    if res == 0:
                        flag = 0
                        break
                if flag == 0:
                    break
            if flag:
                print(f"a1 = {a1},a2 = {a2}")
    
myPermutation = [0,1,16,17,13,12,29,28,14,15,30,31,3,2,19,18,27,26,11,10,22,23,6,7,21,20,5,4,24,25,8,9]
S_BOX = []
for i in range(1,SIZEPOLE):
    S_BOX.append(myPermutation[ArrayPowerSupport[i]])
S_BOX.insert(0,0)
S_BOX2 = S_BOX[9:] + S_BOX[:9]
print(S_BOX)
print(S_BOX2)
#5, 26, 28, 19, 24, 25, 9, 4, 10, 17, 29, 3, 21, 23, 18, 8, 20, 7, 31, 6, 15, 11, 1, 0, 16, 13, 14, 27, 12, 30, 22, 2