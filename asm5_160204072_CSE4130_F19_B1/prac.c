/*
S → b | AB
A →a | aA
B →b
*/


#include<stdio.h>

char str[10];
int i=0;
int l=0;
int f=1;


void B(){

    if(str[i]=='b') f=1;
    else f=0;
}
void A(){

    if(str[i]=='a'){
        i++;
        A();
        f=1;
    }else { f=0; return;}

    if(i<l-1) A();
}


void S(){

    if(l==1 && str[i]=='b'){
        f=1;
        return;
    }
    else{

        A();
        if(f) B();
        else {f=0; return;}

    }
}



int main(){

    printf("CFG: \n");
    printf("\tS-> b | AB\n\tA-> a | aA\n\tB->b\n");


    printf("\nEnter a string to parse: ");
    scanf("%s",&str);


    l=strlen(str);
    //printf("%d",l);

    if(l>=1){
        S();
    }
    else{
        printf("Invalid String");
    }

    if(f==0){
        printf("Invalid String");
    }
    else if(f==1 && i==l-1){
        printf("Valid String");
    }



}
