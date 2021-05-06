/*<stat> -> <asgn_stat> | <dscn_stat> | <loop_stat>
<asgn_stat> ->id = <expn>
<expn>  -><smpl_expn> <extn>
<extn>  -><relop> <smpl_expn> | epsilon
<dcsn_stat>  -> if (<expn> ) <stat> <extn1>
<extn1>  -> else <stat> | epsilon
<loop_stat>→while (<expn>) <stat>for (<asgn_stat> ; <expn> ; <asgn_stat> ) <stat>
<relop>  -> == | != | <= | >= | > | <
*/

/*
a=a+b  a=a+b<=a*b
if(a)a  if(a)aelseb  if(a<=b)a   if(a=a+b<=a*b)a=a+belsea=a*b
for(a=1;a;a=2)a=1
*/


#include<stdio.h>
#include<string.h>
#include <stdbool.h>
int f=0;
int i=0;
int l;
char str[10];
int s=0;

void stat(void);
void asgn_stat(void);
void dscn_stat(void);
void loop_stat(void);
bool relop(void);
void expn(void);
void extn(void);

void E(void);
void T(void);
void F(void);

void stat()
{
    asgn_stat();
    if(s==0)
        dscn_stat();
    else if(s==0)
        loop_stat();
}



void asgn_stat()
{
    if(i<l && (str[i]=='a' || str[i]=='b'|| str[i]=='c' || str[i]=='d' || str[i]=='e'))
    {
        i++;
        if(str[i]=='=')
        {
            i++;
            expn();
        }
        s=1;
    }
}

void expn()
{
    E();
    if(f)
    {
        extn();
    }
}

bool relop()
{
    if(f && i<l && (str[i]=='=' || str[i]=='!'))
    {
        i++;
        if(i<l && str[i]=='=')
        {
            i++;
            return true;
        }


        else return false;
    }
    else if(f && i<l && (str[i]=='<' || str[i]=='>'))
    {
        i++;
        if(i<l && str[i]=='=')
        {
            i++;
        }

        return true;
    }
    return false;
}



void extn()
{
    if(f && i<l && relop())
    {
        E();
    }
}







void extn1()
{
    if(f && i+3<l && str[i]=='e' && str[i+1]=='l' && str[i+2]=='s' && str[i+3]=='e') //f already 1
    {
        i=i+4;
        stat();
    }
}
void dscn_stat()
{
    if(i<l && str[i]=='i' && str[i+1]=='f')
    {
        i=i+2;
        if(str[i]=='(')
        {
            i++;
            expn();
            if(f && i<l && str[i]==')')
            {
                i++;
                stat();
                if(f)
                {
                    extn1();
                }
            }
            else f=0;
        }
        else f=0;
    }
    s=1;
}

void loop_stat()
{

    if(i<l && str[i]=='w' && str[i+1]=='h' && str[i+2]=='i' && str[i+3]=='l' && str[i+4]=='e')
    {
        i=i+5;
        if(i<l && str[i]=='(')
        {
            i++;
            expn();
            if(f && i<l && str[i]==')')
            {
                i++;
                stat();
            }
            else f=0;
        }
        else f=0;
    }
    else if(i<l && str[i]=='f' && str[i+1]=='o' && str[i+2]=='r')
    {

        i=i+3;
        if(str[i]=='(')
        {
            i++;
            asgn_stat();
            if(f && i<l && str[i]==';')
            {
                i++;
                expn();
                if(f && i<l && str[i]==';')
                {
                    i++;
                    asgn_stat();
                    if(f && i<l && str[i]==')')
                    {
                        i++;
                        stat();
                    }
                    else f=0;


                }
                else f=0;

            }
            else f=0;
        }
        else f=0;
    }



    }






void E()
{
    T();
    if(f && i<l &&(str[i]=='+' || str[i]=='-'))
    {
        i++;
        T();
    }

}
void T()
{
    F();
    if(f && i<l && (str[i]=='*' || str[i]=='/'))
    {
        i++;
        F();
    }

}

void F()
{
    if(i<l && str[i]=='(')
    {
        i++;
        f=1;
        E();
        if(f && str[i]==')')
        {
            i++;
        }
        else
        {
            f=0;
        }

    }
    else if(i<l && (str[i]=='a' || str[i]=='b'|| str[i]=='c' || str[i]=='d' || str[i]=='e'))
    {
        i++;
        f=1;
    }
    else if(i<l && isdigit(str[i])==1)
    {
        i++;
        f=1;
    }
    else f=0;
}


int main()
{


    printf("\n\t<stat> -> <asgn_stat> | <dscn_stat> | <loop_stat>\n\t<asgn_stat> ->id = <expn>\n\t<expn>  -><smpl_expn> <extn>\n\t<extn>  -><relop> <smpl_expn> | epsilon\n\t<dcsn_stat>  -> if (<expn> ) <stat> <extn1>\n\t<extn1>  -> else <stat> | epsilon\n\t<loop_stat> -> while (<expn>) <stat>for (<asgn_stat> ; <expn> ; <asgn_stat> ) <stat>\n\t<relop>  -> == | != | <= | >= | > | <");

    printf("\nEnter a string: ");
    scanf("%s", str);
	l = strlen(str);
    if (l>=1)
    {
        stat();
    }
    else
        printf("\nInvalid String\n");
    if (l == i && f )
        printf("\nValid String\n");
    else
        printf("\nInvalid String\n");
    return 0;
}




