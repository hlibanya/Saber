#include <cstdio>
#include <cstdint>
//NOTE: may be templated on integral type to support different bit widths
void integerToBinaryString(const int32_t value, char* stringBuffer)
{
    for(int i = 0; i < 32; i++)
    {
        //NOTE: left shift on 2`s compliment is illformed, so we do it RIGHT
        const int32_t shifted = (value >> (31 - i));
        const int32_t isRightMostBitSet = (shifted & 1);
        //NOTE: I assume strings are ASCII
        stringBuffer[i] = '0' + isRightMostBitSet; 
    }
}
void printIntInBinaryForm(int32_t value)
{
    char stringBuffer[33]{};
    stringBuffer[32] = '\0';
    integerToBinaryString(value, stringBuffer);
    printf("%s\n", stringBuffer);
}
