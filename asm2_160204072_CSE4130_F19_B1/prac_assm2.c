#include<stdio.h>
#include <string.h>
void Lexemes();

FILE *f1, *f2, *f3,*f4;

void Lexemes()
{
    char c;
    while((c=fgetc(f1))!=EOF)
    {
        if(!isalnum(c) && c!='.' && c!=' ' && c!='_' ){
            fputc(' ', f2);
        }

        fputc(c, f2);
        if(c=='=' || c=='!' || c=='>' || c=='<' )
        {
            char d;
            if((d=fgetc(f1))=='=')
            {
                fputc(d, f2);
                fputc(' ', f2);
            }
            else
            {
                fputc(' ', f2);
                fputc(d, f2);
                if(!isalnum(d) && d!='.' && d!=' ' && d!='_')
                    fputc(' ', f2);
            }
        }
        else if(!isalnum(c) && c!='.' && c!=' ' && c!='_')
            fputc(' ', f2);
    }

}

int number(char *str){
   int i, l, s;
    i=0;
    if(isdigit(str[i]))

    {
        s=1;
        i++;
    }
    else if(str[i]=='.')
    {
        s=2;
        i++;
    }
    else s=0;
    l=strlen(str);
    if(s==1)
        for(; i<l; i++)
        {
            if(isdigit(str[i]))
                s=1;
            else if(str[i]=='.')
            {
                s=2;
                i++;
                break;
            }
            else
            {
                s=0;
                break;
            }
        }
    if(s==2)
        if(isdigit(str[i]))
        {
            s=3;
            i++;
        }
        else s=0;
    if(s==3)
        for(; i<l; i++)
        {
            if(isdigit(str[i]))
                s=3;
            else
            {
                s=0;
                break;
            }
        }
    if(s==3) s=1;
    return s;
}

int main(){



    f1= fopen("input.c","r");
    f2= fopen("prac_output.txt","w");
    Lexemes();
    fclose(f1);
    fclose(f2);

    f1= fopen("prac_output.txt","r");
    f2= fopen("prac_output1.txt","w");

    char str[50];
    while(fscanf(f1, "%s" , &str) != EOF){
            if(number(str)){

                fprintf(f2,"%s",str);
                printf("%s\t",str);
            }


    }

    return 0;

}
