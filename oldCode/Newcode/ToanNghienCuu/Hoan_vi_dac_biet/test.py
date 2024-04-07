from random import randint
n_global = 5
SIZE = (1 << n_global) - 1

def setup(arr : list):
    for id in range(SIZE):
        arr[id] = 0
    arr[0] = 1
    arr[1] = SIZE-1
    arr[4] = SIZE
    print(arr)
def step1(arr_used):
    check = 1
    while check:
        check = 0
        for elem in arr_used:
            if elem == 0:
                check = 1
        a2 = randint(2,SIZE-1)
        if arr_used[a2]==0:
            return a2    
    return -1
    
    # for id in range(len(arr_used)):
    #     if arr_used[id] == 0:
    #         return id
    # return -1
def step2(a2,sBOX):
    for id in range(SIZE):
        if sBOX[id] == 0:
            sBOX[id] = a2
            break
def step3(arr : list,used : list):
    isChanged = 1
    while isChanged:
        isChanged = 0
        for t in range(1,SIZE):
            lst_index = []
            lst_key = []
            flag1 = 1  # phần tử chưa dùng 
            flag2 = 0  # phần tử đã dùng
            #print(f"t = {t}")
            for idx2 in range(SIZE):
                if arr[idx2] and arr[(idx2+t) % SIZE]:
            #      print(f"{(idx2+t) % SIZE} : {arr[idx2] ^ arr[(idx2+t) % SIZE]}",end="  ")
                    temp = arr[idx2] ^ arr[(idx2+t) % SIZE]
                    flag1&=used[temp]
                    flag2|=used[temp]
                    # if temp > 7 and temp!=SIZE:
                    #     temp -=SIZE
                    lst_index.append((idx2+t) % SIZE)
                    lst_key.append(temp)
                    #dt[(idx2+t) % SIZE] = temp
                    #count+=1
            if flag1 == 0 and flag2 == 1:
                # tìm vị trí phần tử trùng với cái trong S_BOX
                idx_arr = -1
                idx_lst2 = -1
                for idx,val in enumerate(lst_key):
                    if val in arr:
                        idx_arr = arr.index(val)
                        idx_lst2 = lst_index[idx]
                        break
                # tính khoảng cách giữa 2 index đó
                if idx_arr!= - 1:
                    isChanged = 1
                    distance = idx_arr - idx_lst2
                    for idx in range(len(lst_index)):
                        arr[(lst_index[idx] + distance)%SIZE] = lst_key[idx]
                        used[lst_key[idx]] = 1
def createSbox():
    used = [0] * (SIZE+1)
    lst_used = [0,1,SIZE-1,SIZE]
    for elem in lst_used:
        used[elem] = 1
    idx_15 = 18
    sbox = [0] * SIZE
    sbox[idx_15] = SIZE
    sbox[0] = 1
    sbox[1] = SIZE-1
    return sbox,used
    #return isChanged                
def mainFunction():
    sbox,used = createSbox()
    # step1:
    a2 = 0
    while a2!=-1:
        a2 = step1(used)
        if a2 != -1:
            step2(a2,sbox)
            used[a2] = 1
            step3(sbox,used)
            count = 0
            for elem in used[1:-1]:
                if elem :
                    count+=1
            print(count)
    print(sbox)

mainFunction()
arr = [0] * SIZE
    
# for idx1 in range(SIZE):
#     if idx1 == 0 or idx1 == 1 or idx1 == 4:
#         continue
#     print(f"idx1 = {idx1}")
#     setup(arr)
#     arr[idx1] = elem_test
#     for t in range(1,SIZE):
#         print(f"t = {t}")
#         for idx2 in range(SIZE):
#             if arr[idx2] and arr[(idx2+t) % SIZE]:
#                 print(f"{(idx2+t) % SIZE} : {arr[idx2] ^ arr[(idx2+t) % SIZE]}",end="  ")


# elem_test = 5
# arr = [1, 14, 0, elem_test, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4] 
# arr[7] = 15-5
# arr[9] = 15-4
# arr[2] = 8
# used = [0] * 16
# for elem in arr:
#     used[elem] = 1   
# for t in range(1,SIZE):
#         count = 0
#         dt = {}
#         flag = 1
#         #print(f"t = {t}")
#         for idx2 in range(SIZE):
#             if arr[idx2] and arr[(idx2+t) % SIZE]:
#           #      print(f"{(idx2+t) % SIZE} : {arr[idx2] ^ arr[(idx2+t) % SIZE]}",end="  ")
#                 temp = arr[idx2] ^ arr[(idx2+t) % SIZE]
#                 flag&=used[temp]
#                 if temp > 7 and temp!=SIZE:
#                     temp -=SIZE
            
#                 dt[(idx2+t) % SIZE] = temp
#                 count+=1
#         if count >=2 and flag==0:
#             print(f"t = {t}")
#             print(dt)