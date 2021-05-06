#include <stdio.h>
FILE *p1,*p2;
int main(void)
{
    char c,d,e,f,g;
    p1 = fopen("input.c", "r");
    p2 = fopen("output.txt","w");

    while((c = fgetc(p1)) != EOF)
    {
        //removing new line
        if(c=='\n'){
            continue;
        }
        if( c == ' ')
        {
            //one space
            fputc(c, p2);
            while((c = fgetc(p1))==' ')
            {
                continue;
            }
            fputc(c, p2);


        }
        else if (c=='/') // removing comment
        {
            d=fgetc(p1);
            if(d=='/')
            {
                //single line comment
                while((e=fgetc(p1))!=EOF)
                {
                    if(e=='\n'){
                        break;
                    }
                }
            }
            else if( d == '*')
            {
                //multiple line comment
                while((f=fgetc(p1))!=EOF)
                {
                    if(f=='*')
                    {
                        g=fgetc(p1);
                        if(g=='/'){
                            break;
                        }
                    }
                }
            }
            else
            {
                 fputc(c,p2);
                 fputc(d,p2);
            }

        }
        else{
            fputc(c,p2);
        }
    }

    fclose(p1);
    fclose(p2);

    p2 = fopen("output.txt","r");

    while((c=fgetc(p2))!=EOF){
        printf("%c",c);
    }
    fclose(p2);
   return 0;
}


