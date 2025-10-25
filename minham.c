#include <stdio.h>
#include<string.h>

int minham(char *s,char *t){
    int c=0;
    int n=strlen(s);
    int m=strlen(t);
    if(n!=m) return -1;
    int i=0;
    while(i<n){
        if(s[i]!=t[i]){
            c++;
        }
        i++;
    }
    return c;
}

int main()
{
    char data[100], stuffed[200];
    printf("enter first string : \n");
    scanf("%s",data);
    printf("enter the second string : \n");
    scanf("%s",stuffed);
    int m = minham(data,stuffed);
    printf("%d\n",m);

    return 0;
}