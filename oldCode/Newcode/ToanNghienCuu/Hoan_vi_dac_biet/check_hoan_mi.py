import numpy as np
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
def checkHoanMi(S_BOX):
    size_temp = SIZEPOLE-1
    for t in range(1,(SIZEPOLE-2) // 2):
        res = []
        for idx1 in range(SIZEPOLE-1):
            res.append(S_BOX[idx1] ^ S_BOX[(idx1 + t) % size_temp])    
        if len(set(res)) != size_temp:
            return False
            print("failed with t = ",t,len(set(res)))
            print(res)
            for id1 in range(SIZEPOLE-1):
                for idx2 in range(id1+1,SIZEPOLE-1):
                    if res[id1] == res[idx2]:
                        print(res[id1])
    return True
    print(" Beautiful !!!!")
    
def resetA(val,idx=8):
    idx2 = 4
    val2 = 5
    A_temp = [x for x in A]
    A_temp[idx2] = val2
    A_temp[31-idx2] = 31 ^ val2
    for i in range(1,4):
        A_temp[i+idx2] = A_temp[idx2] ^ A_temp[i] 
        A_temp[31-i-idx2] = 31 ^ A_temp[i+idx2]
    print()
    A_temp[idx] = val
    A_temp[31-idx] = 31 ^ val
    for i in range(1,8):
        A_temp[i+8] = A_temp[8] ^ A_temp[i] 
        A_temp[31-i-8] = 31 ^ A_temp[i+8]
    return A_temp
def createA(vals : list[int]) :
    newA = [0] * 32
    so_doan = len(vals)
    
    for i in range(so_doan):
        newA[1 << i] = vals[i]
        newA[31-(1 << i)] = vals[i] ^ 31
    # co tat ca 2 doan
    for dis in range(1,so_doan):
        limit = (1 << dis)
        for i in range(1,limit):
            newA[i+limit] = newA[limit] ^ newA[i] 
            newA[31-i-limit] = 31 ^ newA[i+limit]
    newA[-1] = 31
    return newA
def createSBOX(S_BOX,aNew):
    S_BOX2 = [aNew[x] for x in S_BOX]
    return S_BOX2
def xem_Chi_so_tuong_ung(S_BOX,aNew):
    dt = dict(zip(aNew, list(range(32))))
    #checkHoanMi(S_BOX2)
    for e in S_BOX:
        ind = dt[e]
        if ind <16:
            print(ind,end=",")
        else:
            print("--",31-ind,end=",")

def xep_lai_SBOX_theo_bac(S_BOX):
    newSBOX = [0]
    for i in range(1,SIZEPOLE):
        newSBOX.append(S_BOX[ArrayPowerSupport[i]])
    return newSBOX

def createSboxBeautiful(num_class):
    newSBOX = [0]
    #num_class = 2
    for deg in range(1,SIZEPOLE):
        newSBOX.append(ArrayPower[ArrayPowerSupport[deg]][num_class])
    if len(set(newSBOX)) == SIZEPOLE:
        print("create susscess!!!")
    return newSBOX
def registerSbox(S_BOX):
    id = 0
    for i in range(1,SIZEPOLE-1):
        if S_BOX[i] ^ S_BOX[i+1] == 31:
            id = i
            break
    if id == 0:
        id = SIZEPOLE-1
    newSBOX = S_BOX[id:] + S_BOX[1:id]
    return newSBOX 
def createClassPower():  
    ''' 
    [[1, 2, 4, 8, 16],  18
    [3, 6, 12, 24, 17],  20
    [5, 10, 20, 9, 18],   19
    [7, 14, 28, 25, 19],   12
    [11, 22, 13, 26, 21],   13
    [15, 30, 29, 27, 23]]   14
    '''
    lst_class = []
    num_elems = 0
    while(num_elems < SIZEPOLE-2):
        for id1 in range(1,SIZEPOLE-1):
            flag = 1
            for cls in lst_class:
                if id1 in cls:
                    flag = 0
                    break
            if flag == 1:
                temp1 = id1
                newClass = [id1]
                for id2 in range(1,DEGREE):
                    temp1 =(temp1 << 1) % (SIZEPOLE-1)
                    newClass.append(temp1)
                lst_class.append(newClass)
                num_elems += DEGREE
    return lst_class


def myReverse(arr, begin, end):
    end -= 1
    while begin < end:
        #mySwap(arr, begin, end)
        temp = arr[begin]
        arr[begin] = arr[end]
        arr[end] = temp
        begin += 1
        end -= 1

def nextPermutation(arr):
    size = len(arr)
    # Bước 1: Tìm phần tử a[i-1] không tuân thủ thứ tự giảm dần từ phải sang trái
    i = size - 1
    while i > 0 and arr[i - 1] >= arr[i]:
        i -= 1
    # Nếu không tìm thấy, đây là hoán vị cuối cùng. Sắp xếp lại và trả về false.
    if i <= 0:
        myReverse(arr, 0, size)
        return False

    # Bước 2: Tìm phần tử a[j] lớn hơn a[i-1]
    j = size - 1
    while arr[j] <= arr[i - 1]:
        j -= 1

    # Bước 3: Đổi chỗ a[i-1] và a[j]
    #mySwap(arr, i - 1, j)
    temp = arr[i-1]
    arr[i-1] = arr[j]
    arr[j] = temp
    # Bước 4: Đảo ngược phần còn lại sau i-1
    myReverse(arr, i, size)
    return True
    
def check_nghiem(b,c,a):
    for elem in range(1,SIZEPOLE):
        val = arrMultiple[b][ArrayPower[elem][3]] ^ arrMultiple[c][elem] ^ a
        if val == 0:
            #print(elem)
            return False
    return True
def valOfSbox(b,c,a):
    newBox = []
    for elem in range(0,SIZEPOLE):
        val = arrMultiple[b][ArrayPower[elem][4]] ^ arrMultiple[c][ArrayPower[elem][2]] ^ arrMultiple[elem][a]
        print(val,end=",")
        newBox.append(val)
    print()
    return newBox
# Main function

s_temp = [1, 30, 6, 2, 15, 7, 28, 9, 5, 19, 14, 25, 26, 11, 10, 20, 18, 16, 31, 24, 4, 13, 8, 27, 21, 12, 22, 29, 23, 3, 17]
print(checkHoanMi(s_temp))

b = 1
c = 0
count = 0
for b in range(1,2):
    count = 0
    print("#########################")
    print("#########################")
    print(f"b = {b}")
    for c in range(0,SIZEPOLE):
        print("#########################")
        print(f"c={c}")
        for a in range(SIZEPOLE):
            flag = check_nghiem(b,c,a)
            if flag:
                count+=1
                print(f"a thỏa mãn là {a}")
                Box1 = valOfSbox(b,c,a)
                newBox = xep_lai_SBOX_theo_bac(Box1)
                print(newBox)
                #flag = checkHoanMi(newBox[1:])
                #print(flag)
    print(f"count = {count}")
    print("============= end ==============")
            
            

S_BOX = [5, 26, 28, 19, 24, 25, 9, 4, 10, 17, 29, 3, 21, 23, 18, 8, 20, 7, 31, 6, 15, 11, 1, 16, 13, 14, 27, 12, 30, 22, 2]
# S_b_temp = createSboxBeautiful(15)
# S2 = registerSbox(S_b_temp)
# print(S2)
# print(S2.index(31))

aNew = createA([5,2,4,8])
print("New")
print(aNew)
S_BOX2 = createSBOX(S_BOX,aNew)
print(S_BOX2)

lst1 = [31-15,6,11,15,31-11,9,14,31-4,12,31-5,31-13]
lst2 = [16,19,20,21,23,24,25,26,27,28,29]
lst1.sort()
print(lst1)
flag = 1
while(flag):
    #print(lst1)
    #S_BOX_cp = S_BOX2.copy()
    flag = nextPermutation(lst1)
    for id1 in range(len(lst2)):
        S_BOX2[lst2[id1]] = lst1[id1]
    flag2 = checkHoanMi(S_BOX2)
    if flag2:
        print(S_BOX2)
# for elem in range(8,24):
#     A_temp = resetA(elem)
#     # print(list(range(32)))
#     # print(A_temp)
#     S_BOX = [5, 26, 28, 19, 24, 25, 9, 4, 10, 17, 29, 3, 21, 23, 18, 8, 20, 7, 31, 6, 15, 11, 1, 16, 13, 14, 27, 12, 30, 22, 2]
#     S_BOX2 = [A_temp[x] for x in S_BOX]
#     #print(S_BOX2)

#     checkHoanMi(S_BOX2)