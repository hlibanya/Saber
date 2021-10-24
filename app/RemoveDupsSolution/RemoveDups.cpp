#include <cstring>

void removeDups(char* string)
{
    const size_t len = strlen(string);
    if (len == 0 || len == 1)
    {
        return;
    }
    size_t  writeIndex = 0;
    for (size_t i = 0; i < len; i++)
    {
        const char uniqueChar = string[i];
        //POSSIBLE OPTIMIZATION:
        //If it is known that strings are big and may have a long duplicate sequences
        //comparison 1 by 1 may be changed to n-width memcmp 
        //with block of n bytes set to value of char being compared.
        //When memory blocks is not equal we fall back to 1 by 1 cmp to find last non-unique char
        //This optimization may and will slow down strings with a few duplicate sequences
        while (uniqueChar == string[i + 1])
        {
            i++;
        }
        string[writeIndex++] = uniqueChar;
    }
    string[writeIndex] = '\0';
}
