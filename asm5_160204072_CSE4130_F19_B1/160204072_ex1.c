/*A → aXd
X → bbX
X → bcX
X →  */

#include<stdio.h>

char str[10];
int i=0;
int l=0;
int f=1;

void A(void);
void X(void);


void A(){
    if(str[i]=='a'){

        i++;
        X();

        if(f==1){
            if(str[i]=='d'){
                    f=2;
                    return;
            }
            else{
                f=0;
                return;
            }

        }


    }else
    {
        f=0;
        return;
    }

}

void X(){
    if(i==l-1){ // checking epsilon
        f=1;
        return;
    }
    else if(str[i]== 'b'){
        i++;
        if(str[i]=='b' || str[i]== 'c'){
            i++;
            X();
        }
        else f=0;
    }

}

int main()
{

    printf("CFG: \n");
    printf("\tA -> aXd\n\tX -> bbX\n\tX -> bcX\n\tX -> epsilon \n");


    printf("\nEnter a string to parse: ");
    scanf("%s",&str);

    l=strlen(str);
    //printf("%d",l);

    if(l>=2){
        A();
    }
    else{
        printf("Invalid String");
    }

    if(f==0){
        printf("Invalid String");
    }
    else if(f==2 && i==l-1){
        printf("Valid String");
    }


    return 0;
}
