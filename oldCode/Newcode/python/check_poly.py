from math import comb,gcd
DEGREE = 4
CHARACTER = 2
SIZEPOLE = 16
hsPole = 19
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
def elem_power_in_field(x,n):
    res = 1
    for i in range(n):
        res = arrMultiple[res][x]
    return res
def rootOfPolynomial(coeff_poly):
    res = []
    for i in range(SIZEPOLE):
        temp = 0
        x = 1
        for hs in (coeff_poly):
            temp ^= arrMultiple[hs][x]
            x = arrMultiple[x][i]
        if temp == 0:
            res.append(temp)
    return res

def convert_to_bin(decimal_number):
    binary_string = bin(decimal_number)[2:]  # Bỏ qua ký tự '0b' ở đầu

# Chuyển chuỗi nhị phân thành danh sách
    binary_list = [int(bit) for bit in binary_string]
    return binary_list
def multiplyTwoPolynomials(ls_poly_1,poly_2):
    # chuẩn hóa poly_1
    for i in range(SIZEPOLE,len(ls_poly_1)):
        if ls_poly_1[i]:
            ls_poly_1[i] = 0
            ls_poly_1[i-SIZEPOLE+1]^=0b1
    poly_1 = int("".join(map(str, ls_poly_1[::-1] )), 2)
    mod = SIZEPOLE 
    temp_so_sanh = 0b1 << SIZEPOLE
    res = 0
    for i,elem in enumerate(poly_2):
        if elem:
            k=i
            temp = poly_1
            while k:
                temp <<=1
                if temp & temp_so_sanh:
                    temp^=temp_so_sanh^0b10
                k-=1
            res ^= temp
    res = convert_to_bin(res)
    return res[::-1]
def powerPolynomial(ls_poly,expr):
    if expr == 0:
        return [1]
    temp = ls_poly.copy()
    for i in range(expr-1):
        temp = multiplyTwoPolynomials(temp,ls_poly)
    return temp
    
def is_permutation_polynomial(ls_poly_1):
    if len(ls_poly_1)==1:
        if ls_poly_1[0] != 0:
            return True
        return False
    # kiểm tra có nghiệm không
    #so_nghiem = 0
    lst_roots = rootOfPolynomial(ls_poly_1)
    if len(lst_roots)!= 1:
        return False
    for t in range(1,SIZEPOLE-1):
        if t % CHARACTER != 0:
            remainder = powerPolynomial(ls_poly_1,t)
            if len(remainder)== SIZEPOLE:
                return False
    return True

def is_permutation_p_polynomial(ls_poly_1):
    if len(ls_poly_1)==1:
        if ls_poly_1[0] != 0:
            return True
        return False
    for i,hs in enumerate(ls_poly_1):
        if hs :
            if i == 0:
                return False
            while i % CHARACTER == 0:
                i /= CHARACTER
            if i!= 1:
                return False
    if len(rootOfPolynomial(ls_poly_1))!=1:
        return False
    return True
def bien_doi_poly_x_power_s(ls_poly,s):
    """_summary_
        dạng g(x^s)).
    Args:
        ls_poly (_type_):
        
    """
    res = [0] * (SIZEPOLE+1)
    for i,hs in enumerate(ls_poly):
        if hs :
            temp = i*s
            while temp>=SIZEPOLE:
                temp-=(SIZEPOLE-1)
            res[temp]^=0b1
    return res
def find_permutation_of_poly(coeff_poly):
    res = []
    for i in range(SIZEPOLE):
        temp = 0
        x = 1
        for hs in (coeff_poly):
            temp ^= arrMultiple[hs][x]
            x = arrMultiple[x][i]
        res.append(temp)
    return res
def createDixonPoly(k,a):
    res = [0] * (k+1)
    for j in range(k//2+1):
       
       # hs = (k* comb(k-j,j)//(k-j) *(-a)**j) 
        hs = (k* comb(k-j,j)//(k-j) *(-1)**j)  % CHARACTER
        hs = arrMultiple[hs][elem_power_in_field(a,j)]
        res[k-2*j] = hs
    return res
def check_S_BOX(S_BOX,f):
    
    f.write("begin\n")
    res = [[0 for _ in range(SIZEPOLE)] for _ in range(SIZEPOLE)]
    mx = 0
    b = 0
    mx = 0
    for i in range(SIZEPOLE):
        for j in range(SIZEPOLE):
            res[i][j] = 0
    for i in range(2, SIZEPOLE):
        for j in range(SIZEPOLE):
            #print(f"{i},{j} : ", end="")
            b = S_BOX[arrMultiple[j][i]] ^ S_BOX[j]
            #print(b, "   ", end="")
            res[i][b] += 1
        #print()
    for i in range(2, SIZEPOLE):
        for j in range(SIZEPOLE):
            f.write(f"{res[i][j]}  ")
            if res[i][j] > mx:
                mx = res[i][j]
            res[i][j] = 0
        f.write("\n")
    f.write(f"max : {mx}\n")
#################################################### Main function #########################################################
createArrayMult()
# lst = [0,0,1]
with open("input.txt", "a") as f:
    for a in range(1,SIZEPOLE):
        f.write(f" a = {a} : \n")
        for k in range(1,SIZEPOLE):
            if gcd(k,SIZEPOLE**2-1):
                f.write("============================================================\n")
                lst = createDixonPoly(k,a)
                f.write(str(lst))
                lst_poly=find_permutation_of_poly(lst)
                check_S_BOX(lst_poly,f)
                f.write("============================================================\n")