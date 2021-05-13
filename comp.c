#include <stdio.h>

int main(void)
{
    int reg = 9;
    char* registro;
    sprintf(registro, "$t%d", reg);
    printf("%s\n", registro);
    char r = registro[2];
    printf("%c\n", r);
    int rr = r - '0';
    printf("%d",rr);
    return 0;
}
