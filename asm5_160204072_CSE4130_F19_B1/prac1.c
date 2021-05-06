
/*<Exp>→<Term> + <Term> | <Term> - <Term> | <Term>
<Term>→<Factor> * <Factor> | <Factor> / <Factor> | <Factor>
<Factor>→( <Exp> ) | ID | NUM
ID → a|b|c|d|e
NUM→ 0|1|2|…|9
*/

#include<stdio.h>

char str[10];
int i=0;
int l;
int f=0;

void E(void);
void T(void);
void F(void);


void E()
{



   T();
    if(f && i<l && (str[i]=='+' || str[i]=='-')){
        i++;
        T();
    }

}
void T()
{



  F();
    if(f && i<l && (str[i]=='*' || str[i]=='/')){
        i++;
        F();
    }
}

void F()
{




    if(i<l &&  str[i]=='('){
        i++;
        f=1;
        E();
        if(f){
            //i++;
            if(str[i]==')'){
                i++;
            }else f=0;
        } else f=0;
    }
    else if( (i<l && str[i]=='a' || str[i]=='b'|| str[i]=='c' || str[i]=='d' || str[i]=='e') || isdigit(str[i])==1){
        i++;
        f=1;
    }
    else f=0;

}
int main(void) {

	printf("CFG: \n");
    printf("\tE -> T+T | T-T | T \n\tT -> F*F | F/F | F \n\tID -> a|b|c|d|e \n\tNUM-> 0|1|2|...|9 \n");
    printf("\nEnter a string to parse: ");
	scanf("%s", str);

	l = strlen(str);

    if (l>=1)
        E();
    else
		printf("\nInvalid String\n");

    if (l == i && f )
		printf("\nValid String\n");
	else
		printf("\nInvalid String\n");

    return 0;
}




