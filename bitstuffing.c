#include<stdio.h>
#include<string.h>


void bitstuffing(const char *input, char * output){
    int j=0;
    int c=0;
    for(int i=0;input[i]!='\0';i++){
        output[j++]=input[i];
        if(input[i]=='1'){
            c++;
        }
        else{
            c=0;
        }

        if(c==5 && i>0 && input[i-5]=='0'){
            output[j++] = '0';
            c=0;
        }
    }
    output[j]='\0';
}

void destuffing(const char*stuffed, char *destuffed){
    int c=0;
    int j=0;
    for(int i=0;stuffed[i]!='\0';i++){
        destuffed[j++]=stuffed[i];
        if(stuffed[i]=='1'){
            c++;
        }else{
            c=0;
        }

        if(c==5){
            i++;
            c=0;
        }
    }
    destuffed[j]='\0';
}

int main(){

    char input[] = "011111101111110";
    char stuffed[100];
    char destuffed[100];

    bitstuffing(input,stuffed);
    printf("Original : %s \n",input);
    printf("Stuffed : %s \n",stuffed);
    destuffing(stuffed,destuffed);
    printf("Destuffed : %s \n", destuffed);

    return 1;
}