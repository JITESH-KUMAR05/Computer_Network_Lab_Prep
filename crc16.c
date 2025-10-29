#include <stdio.h>
#include <string.h>

#define MAX 100

void divide(char data[], char divisor[], char remainder[]) {
    int dl = strlen(data), divl = strlen(divisor);
    char temp[MAX];
    strcpy(temp, data);

    for (int i = 0; i <= dl - divl; i++) {
        if (temp[i] == '1') {
            for (int j = 0; j < divl; j++)
                temp[i+j] = (temp[i+j] == divisor[j]) ? '0' : '1';
        }
    }
    strncpy(remainder, temp + dl - divl + 1, divl - 1);
    remainder[divl - 1] = '\0';
}

int main() {
    char data[MAX], divisor[MAX], appended[MAX], crc[MAX], transmitted[MAX], rem[MAX];
    printf("Enter data: ");
    scanf("%s", data);
    printf("Enter divisor: ");
    scanf("%s", divisor);

    strcpy(appended, data);
    for (int i = 0; i < strlen(divisor) - 1; i++)
        strcat(appended, "0");

    divide(appended, divisor, crc);

    printf("\nCRC = %s\n", crc);

    strcpy(transmitted, data);
    strcat(transmitted, crc);
    printf("Transmitted data = %s\n", transmitted);

    divide(transmitted, divisor, rem);
    if (strspn(rem, "0") == strlen(rem))
        printf("No error detected.\n");
    else
        printf("Error detected!\n");
    return 0;
}