print(2**30)
for i in [3,5,6,9,10,12,17,18,20,24,33,34,36,40,48]:
    print(bin(i))
def count_ones_in_string(input_string):
    count = 0
    for char in input_string:
        if char == '1':
            count += 1
    return count
def check(n,lst):
    for elem in lst:
        if count_ones_in_string(bin(elem)[2:]) != n:
            print(False)
            
n = 4
lst = [15,23,27,29,30,39,43,45,46,51,53,54,57,58,60,71,75,77,78,83,85,86,89,90,92,99,101,102,105,106,108,113,114,116,120,135,139,141,142,147,149,150,153,154,156,163,165,166,169,170,172,177,178,180,184,195,197,198,201,202,204,209,210,212,216,225,226,228,232,240,263,267,269,270,275,277,278,281,282,284,291,293,294,297,298,300,305,306,308,312,323,325,326,329,330,332,337,338,340,344,353,354,356,360,368,387,389,390,393,394,396,401,402,404,408,417,418,420,424,432,449,450,452,456,464,480,519,523,525,526,531,533,534,537,538,540,547,549,550,553,554,556,561,562,564,568,579,581,582,585,586,588,593,594,596,600,609,610,612,616,624,643,645,646,649,650,652,657,658,660,664,673,674,676,680,688,705,706,708,712,720,736,771,773,774,777,778,780,785,786,788,792,801,802,804,808,816,833,834,836,840,848,864,897,898,900,904,912,928,960]

check(n,lst)