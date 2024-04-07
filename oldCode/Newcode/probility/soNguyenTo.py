# Generating a list of prime numbers from 3 to 100
# from traceback import print_tb
from traceback import print_tb


# MAX_SIZE = 150


def beautify_condition(p,q):
    temp = p+q 
    return (is_prime(temp-1) or is_prime(temp+1))
def is_prime(n):
    """Check if a number is prime."""
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
    return True

def check_thieu_sot_prime(lst_prime,gioi_han_tren):
    for elem in range(3,gioi_han_tren):
        if elem not in lst_prime and is_prime(elem):
            print(f"thieu sot prime = {elem}")
def find_element_position(lst, target):
    for index, element in enumerate(lst):
        if element == target:
            return index
def process(MAX_SIZE): # hàm này để tính phần trăm trong đoạn từ 3 đến MAX_SIZE 
    prime_numbers = [n for n in range(3, MAX_SIZE) if is_prime(n)]
    sz = len(prime_numbers)
    sum = sz * (sz - 1)
    count = 0
    column_width = 5  # Set the desired column width
    for i in range(sz):
        for j in range(sz - i):
            if beautify_condition(prime_numbers[j], prime_numbers[j+i]) == False:
                #print(f'{prime_numbers[j]:<{column_width}}{prime_numbers[j+i]:<{column_width}}', end=" | ")
                count += 1
        #print()
    print(f"\n % = {(1 - count/sum) * 100}")

def intruction(a,b):  # hàm này tạo số nguyên tố từ 2 số ban đầu, có vẻ là vô tận ...............
    lst_temp =[a,b]
    idx = 0
    sum = 0
    flag = 0
    current_idx = 0
    while idx < len(lst_temp)-1 and len(lst_temp) <= 3000:
        flag = 0
        a = lst_temp[idx]
        for elem in lst_temp[current_idx:]:
            sum = a+elem
            if is_prime(sum+1) and (sum+1) not in lst_temp[idx:]:
                flag = 1
                lst_temp.append(sum+1)
                current_idx = len(lst_temp)-1
            if is_prime(sum-1) and (sum-1) not in lst_temp[idx:]:
                flag = 1
                lst_temp.append(sum-1)
                current_idx = len(lst_temp)-1
        if flag == 0:
            idx+=1
            current_idx = idx   
    print(f"độ dài mảng = {len(lst_temp)}")
    lst_temp.sort()
    print(lst_temp) 
    check_thieu_sot_prime(lst_temp,23172)
    
    
process(20000)
    
    
#intruction(3,5)