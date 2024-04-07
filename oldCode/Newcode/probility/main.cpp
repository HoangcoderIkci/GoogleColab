#include <iostream>
#include <cmath>
#include <bitset>
#define U32 unsigned int
#define U8 unsigned char
using namespace std;

void process(U32 n)
{
    U32 lim = pow(2, n);
    float sum = 0;
    U32 temp;
    int c = 0;
    for (U32 i = 0; i < lim; i++)
    {
        sum = 0;
        temp = i;
        for (U32 j = 1; j <= n; j++)
        {
            if (temp & 0x1)
                sum -= sqrt(j);
            else
                sum += sqrt(j);
            temp >>= 1;
        }
        if (sum >= n / 2)
        {
            c++;
            // cout << (bitset<16>)i << " " << sum << endl;
        }
    }
    printf("Luot thứ %d : %f , %f  c: %d \n", n, log2(c), n - log2(c), c);
    // cout << log2(c) << endl;
    printf("================================================================================================\n");
    // printf("================================================================================================\n");
}

int main()
{
    for (U32 i = 9; i < 16; i++)
    {
        // printf("Luot thứ %d : \n", i);
        printf("================================================================================================\n");
        printf("================================================================================================\n");
        process(i);
    }

    return 0;
}