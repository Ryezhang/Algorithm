#include <stdio.h>
#include <string.h>

void swap(char &a, char &b)
{
    char tmp = a;
    a = b;
    b = tmp;
}

void reverse(char string[], int num)
{
    int i = 0;
    int j = num - 1;

    while (i < j) {
        swap(string[i++], string[j--]);
    }
}

int main() {
    char string[] = "abcdefgh";
    reverse(string, 3);
    reverse(string + 3, 5);
    reverse(string, 8);
    printf("%s\n", string);
}
