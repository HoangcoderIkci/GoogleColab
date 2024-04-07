from collections import Counter

def check_three_occurrences2(input_list,lst_keys):
    # Đếm số lần xuất hiện của mỗi phần tử trong danh sách
    count_dict = Counter(input_list)
    
    # Kiểm tra xem có phần tử nào xuất hiện 3 lần không
    c = 0
    for key, value in count_dict.items():
        if value == 3 and key in lst_keys:
            return True
    #return c==len(lst_k)
    
    return False

def check_three_occurrences(input_list):
    # Đếm số lần xuất hiện của mỗi phần tử trong danh sách
    count_dict = Counter(input_list)
    
    # Kiểm tra xem có phần tử nào xuất hiện 3 lần không
    c = 0
    for key, value in count_dict.items():
        if value == 3:
            return True
    #return c==len(lst_k)
    
    return False

def next_permutation(arr):
    # Tìm chỉ số lớn nhất i sao cho arr[i] < arr[i+1]
    i = len(arr) - 2
    while i >= 0 and arr[i] >= arr[i + 1]:
        i -= 1

    if i == -1:
        return False

    # Tìm chỉ số lớn nhất j sao cho arr[j] > arr[i]
    j = len(arr) - 1
    while arr[j] <= arr[i]:
        j -= 1

    # Hoán đổi arr[i] và arr[j]
    arr[i], arr[j] = arr[j], arr[i]

    # Đảo ngược phần còn lại của mảng từ i+1 đến cuối
    arr[i + 1:] = arr[i + 1:][::-1]

    return True

lst = list(range(1,8))
flag = 0
count = 0
set_temp = set()
lst_res = []
for turn in range(1,4):
    lst = list(range(1,8))
    #set_temp = set()
    flag = 0
    count = 0
    for i in range(7*6*5*4*3*2):
        lst2 =lst[turn:] + lst[:turn] 
        # for id2 in range(turn):
        #     lst2.append(lst[id2])
        c_temp = 0
        # for id in range(7):
        #     if lst[id] ^ lst2[id] == 3:
        #         c_temp += 1
        lst_temp = [lst[x] ^ lst2[x] for x in range(7)]
        flag = check_three_occurrences(lst_temp)
        if flag:
            count+=1
            set_temp.add(tuple(lst))
        next_permutation(lst)
    print(count)   
    #lst_res.append(set_temp)
print(len(set_temp))
    

# lst = list(range(1,8))
# flag = 0
# count = 0
# set_temp1 = set()
# #lst_res2 = []
# for turn in range(1,4):
#     lst = list(range(1,8))
#     #set_temp = set()
#     flag = 0
#     count = 0
#     for i in range(7*6*5*4*3*2):
#         lst2 =lst[turn:] + lst[:turn] 
#         # for id2 in range(turn):
#         #     lst2.append(lst[id2])
#         c_temp = 0
#         for id in range(7):
#             if lst[id] ^ lst2[id] == 1:
#                 c_temp += 1
#         if c_temp==3:
#             count+=1
#             set_temp1.add(tuple(lst))
#         flag = next_permutation(lst)
#     #print(count)   
#     #lst_res2.append(set_temp)
# print(len(set_temp1))


lst_set_temps =[]
for val in range(1,2):
    lst = list(range(1,8))
    flag = 0
    count = 0
    set_temp2 = set()
    #lst_res2 = []
    for turn in range(1,4):
        lst = list(range(1,8))
        #set_temp = set()
        flag = 0
        count = 0
        for i in range(7*6*5*4*3*2):
            lst2 =lst[turn:] + lst[:turn] 
            # for id2 in range(turn):
            #     lst2.append(lst[id2])
            c_temp = 0
            for id in range(7):
                if lst[id] ^ lst2[id] == val:
                    c_temp += 1
            if c_temp==3:
                count+=1
                set_temp2.add(tuple(lst))
            flag = next_permutation(lst)
        #print(count)   
        #lst_res2.append(set_temp)
    lst_set_temps.append(set_temp2)
    print(len(set_temp2))

lst_check = [2,3,4,5,6,7]
lst_k = []
for elem in lst_set_temps[0]:
    elem = list(elem)
    flag = False
    count = 0
    for turn in range(1,4):
        lst = list(range(1,8))
        lst2 =elem[turn:] + elem[:turn] 
        lst_k = [elem[id] ^ lst2[id] for id in range(7)]
        flag = check_three_occurrences2(lst_k,lst_check)
        if flag:
            break
        #print(count)   
        #lst_res2.append(set_temp)
    #lst_set_temps.append(set_temp2)
    #print(len(set_temp2))
    if flag == False:
        print("khong thoa man")
    
for i in range(7):
    for j in range(i+1,7):
        for k in range(j+1,7):
            x = lst_set_temps[i] & lst_set_temps[j] & lst_set_temps[k]
            if len(x) == 0:
                print(f"{i+1} {j+1} {k+1}")




# x = set_temp1 & set_temp2 
# print(len(x))

# lst = list(range(1,8))
# flag = 0
# count = 0
# set_temp = set()
# lst_res3 = []
# for turn in range(1,4):
#     lst = list(range(1,8))
#     set_temp = set()
#     flag = 0
#     count = 0
#     for i in range(7*6*5*4*3*2):
#         lst2 =lst[turn:] + lst[:turn] 
#         # for id2 in range(turn):
#         #     lst2.append(lst[id2])
#         c_temp = 0
#         for id in range(7):
#             if lst[id] ^ lst2[id] == 7:
#                 c_temp += 1
#         if c_temp==3:
#             count+=1
#             set_temp.add(tuple(lst))
#         flag = next_permutation(lst)
#         if flag == 0:
#             print(flag)
#     print(count)   
#     lst_res3.append(set_temp)
# print("\n================================")

# lst = list(range(1,8))
# flag = 0
# count = 0
# set_temp = set()
# lst_res4 = []
# for turn in range(1,4):
#     lst = list(range(1,8))
#     set_temp = set()
#     flag = 0
#     count = 0
#     for i in range(7*6*5*4*3*2):
#         lst2 =lst[turn:] + lst[:turn] 
#         # for id2 in range(turn):
#         #     lst2.append(lst[id2])
#         c_temp = 0
#         for id in range(7):
#             if lst[id] ^ lst2[id] == 5:
#                 c_temp += 1
#         if c_temp==3:
#             count+=1
#             set_temp.add(tuple(lst))
#         flag = next_permutation(lst)
#         if flag == 0:
#             print(flag)
#     print(count)   
#     lst_res4.append(set_temp)

# lst = list(range(1,8))
# flag = 0
# count = 0
# set_temp = set()
# lst_res5 = []
# for turn in range(1,4):
#     lst = list(range(1,8))
#     set_temp = set()
#     flag = 0
#     count = 0
#     for i in range(7*6*5*4*3*2):
#         lst2 =lst[turn:] + lst[:turn] 
#         # for id2 in range(turn):
#         #     lst2.append(lst[id2])
#         c_temp = 0
#         for id in range(7):
#             if lst[id] ^ lst2[id] == 4:
#                 c_temp += 1
#         if c_temp==3:
#             count+=1
#             set_temp.add(tuple(lst))
#         flag = next_permutation(lst)
#         if flag == 0:
#             print(flag)
#     #print(count)   
#     lst_res5.append(set_temp)

# for i in range(3):
#     for j in range(3):
#         xx = (lst_res3[i] & lst_res2[j])    
#         if len(xx) >0:
#             print(f"trung tai {i} {j}")
#             print(len(xx))
#             # for k in range(3):
#             #     xxx = xx & lst_res4[k]
#             #     if len(xxx) > 0 :
#             #         for h in range(3):
#             #             xxxx = xxx & lst_res5[h]
#             #             if len(xxxx) > 0 :
#             #                 print(f"trung tai {i} {j} {k} {h}")
#             #                 print(xxxx)
# print(18816/336)