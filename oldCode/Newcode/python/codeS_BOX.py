SIZEPOLE = 16
CHAR = 2
DEGREE = 4

hsPole = 19
S_BOX = [0, 1, 5, 4, 2, 3, 7, 6, 10, 11, 15, 14, 8, 9, 13, 12]

arrMultiple = [[0 for _ in range(SIZEPOLE)] for _ in range(SIZEPOLE)]
arrAddition = [[0 for _ in range(SIZEPOLE)] for _ in range(SIZEPOLE)]
arrInverseSubtraction = [0] * SIZEPOLE
arrOppositeArray = list(range(SIZEPOLE))


def createArrayMult():
    for i in range(SIZEPOLE):
        for j in range(SIZEPOLE):
            temp = multipleTwoElement(i, j)
            arrMultiple[i][j] = temp
            arrMultiple[j][i] = temp
            if temp == 1:
                arrInverseSubtraction[i] = j
                arrInverseSubtraction[j] = i

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

def __startCreateMatrices():
    createArrayMult()


def main():
    __startCreateMatrices()
    print("begin")
    res = [[0 for _ in range(SIZEPOLE)] for _ in range(SIZEPOLE)]
    mx = 0
    b = 0
    mx = 0
    for i in range(SIZEPOLE):
        for j in range(SIZEPOLE):
            res[i][j] = 0
    for i in range(2, SIZEPOLE):
        for j in range(SIZEPOLE):
            print(f"{i},{j} : ", end="")
            b = S_BOX[arrMultiple[j][i]] ^ S_BOX[j]
            print(b, "   ", end="")
            res[i][b] += 1
        print()
    for i in range(2, SIZEPOLE):
        for j in range(SIZEPOLE):
            print(res[i][j], "  ", end="")
            if res[i][j] > mx:
                mx = res[i][j]
            res[i][j] = 0
        print()
    print("max : ", mx)

if __name__ == "__main__":
    main()
