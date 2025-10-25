#include <stdio.h>
#include<string.h>

int main()
{
    char data[100], stuffed[200];
    char flag = 'F';
    char esc = 'E';
   
    int i,j=0;
   
    printf("Enter the data : ");
    scanf("%s",data);
    stuffed[j++]=flag;
    for(int i=0;i<strlen(data);i++){
        if(data[i]==flag || data[i]==esc){
            stuffed[j++]=esc;
        }
        stuffed[j++]=data[i];
    }
   
    stuffed[j++]=flag;
    stuffed[j]='\0';
    printf("Stuffed data : %s \n",stuffed);

    return 0;
}