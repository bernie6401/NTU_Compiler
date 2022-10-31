#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
int comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}
int main(int argc, char* argv[]) 
{
    char str1[] = "abcd", str2[] = "zabCd", str3[] = "Abcde";
    int result;

    // comparing strings str1 and str2
    // result = strcmp(str1, str2);
    if(strcmp(str1, str2))
    printf("strcmp(str1, str2) = %d\n", result);

    // comparing strings str1 and str3
    // result = strcmp(str1, str3);
    if(strcmp(str1, str3))
    printf("strcmp(str1, str3) = %d\n", result);

    return 0;
}