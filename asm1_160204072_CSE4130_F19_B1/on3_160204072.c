//prints total executable lines

#include <stdio.h>

FILE *p1,*p2;
int main(void)
{
    char c,d,e,f,g;
    p1 = fopen("input1.c", "r");
    p2 = fopen("output.txt","w");
    int cnt=0;
printf("header files: ");
    while((c = fgetc(p1)) != EOF)
    {

        if(c=='#')
            {
                while((c = fgetc(p1))!= '<');
                while((c = fgetc(p1))!= '>')
                    printf("%c", c);
                printf("\n");
            }


        if(c=='\n'){

            cnt++;
        }
        if (c=='/')
        {
            d=fgetc(p1);
            if(d=='/')
            {
                cnt--;
                while((e=fgetc(p1))!=EOF)
                {
                    if(e=='\n'){
                        break;
                    }
                }
            }
            else if( d == '*')
            {
                cnt--;

                while((f=fgetc(p1))!=EOF)
                {
                    if(f=='\n'){
                        cnt--;
                    }
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
                 //fputc(c,p2);
                 //fputc(d,p2);
            }

        }
        else{
            fputc(c,p2);
        }
    }

    fclose(p1);
    fclose(p2);


    printf("total executable lines %d",cnt);
   return 0;
}

