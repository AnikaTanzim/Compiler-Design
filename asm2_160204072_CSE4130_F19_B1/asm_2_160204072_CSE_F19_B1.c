#include <stdio.h>
#include <string.h>

void Lexemes();
int Keyword(char *str);
int Operator(char *str);
int Separator(char lexeme[]);
int Identifier(char lexeme[]);
int Parenthesis(char lexeme[]);
int Number(char lexeme[20]);

FILE *f1,*f2,*f3;

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

int Keyword(char *str) {
    int s=0;
    if( (!strcmp(str, "while")) || (!strcmp(str, "static")) || (!strcmp(str, "if")) ||
    (!strcmp(str, "volatile")) || (!strcmp(str, "do")) || (!strcmp(str, "goto")) ||
    (!strcmp(str, "sizeof")) || (!strcmp(str, "else")) || (!strcmp(str, "default")) ||
    (!strcmp(str, "void")) || (!strcmp(str, "for")) || (!strcmp(str, "signed")) ||
    (!strcmp(str, "continue")) || (!strcmp(str, "unsigned")) || (!strcmp(str, "short")) ||
    (!strcmp(str, "char")) || (!strcmp(str, "float")) || (!strcmp(str, "double")) ||
    (!strcmp(str, "int")) || (!strcmp(str, "char")) || (!strcmp(str, "const")) ||
    (!strcmp(str, "union")) || (!strcmp(str, "return")) || (!strcmp(str, "extern")) ||
    (!strcmp(str, "enum")) || (!strcmp(str, "register")) || (!strcmp(str, "typedef")) ||
    (!strcmp(str, "switch")) || (!strcmp(str, "long")) || (!strcmp(str, "break")) ||
    (!strcmp(str, "auto")) || (!strcmp(str, "struct")) )
    {
        s=1;
    }
    return s;
}


int Operator(char *str) {
    int s=0;
    if( (!strcmp(str, "+=")) || (!strcmp(str, "--")) || (!strcmp(str, "++")) ||
      (!strcmp(str, "<=")) || (!strcmp(str, "-=")) || (!strcmp(str, ">=")) ||
      (!strcmp(str, "&&")) || (!strcmp(str, "||")) || (!strcmp(str, "+")) ||
      (!strcmp(str, "-")) || (!strcmp(str, "=")) || (!strcmp(str, "==")) ||
      (!strcmp(str, "*")) || (!strcmp(str, "/")) || (!strcmp(str, "/=")) ||
      (!strcmp(str, "*=")) || (!strcmp(str, "%")) || (!strcmp(str, "%=")) ||
      (!strcmp(str, "!")) || (!strcmp(str, "^")) || (!strcmp(str, "<")) ||
      (!strcmp(str, ">"))){
          s=1;
      }
      return s;
}
int Separator(char *str)
{
    int i, l;
    l=strlen(str);
    if(l==1 && (str[0]==';' || str[0]=='"' || str[0]==',' || str[0]=='\''))
        return 1;
    else
        return 0;
}

int Parenthesis(char *str)
{
    int l = strlen(str);
    return (l==1 && (str[0]=='(' || str[0]==')' || str[0]=='{' || str[0]=='}' || str[0]=='[' || str[0]==']'));
}

int Identifier(char *str)
{
    int i, s=0, l;
    l=strlen(str);
    if((isalpha(str[0])) || (str[0]=='_'))
        s=1;
    if(s==1)
    {
        for(i=1; i<l; i++)
        {
            if(!isalnum(str[i]) && str[i]!='_'&& !isalpha(str[i]))
            {
                s=0;
                break;
            }
        }
    }
    return s;
}

int Number(char *str)
{
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

int main()
{
    char c;
    f1 = fopen("input.c", "r");
    f2 = fopen("lexemesOutput.txt", "w");

    Lexemes();

    fclose(f1);
    fclose(f2);

    f1 = fopen("lexemesOutput.txt", "r");

    while((c=fgetc(f1))!=EOF)
    {
        printf("%c",c);
    }
    printf("\n");
    f1 = fopen("lexemesOutput.txt", "r");
    f2 = fopen("tokensOutput.txt", "w");
    char str[50];
    while(fscanf(f1, "%s", &str)!=EOF)
    {
        if(Keyword(str)){
            fprintf(f2, "[kw %s] ", str);}
        else if(Operator(str)){
            fprintf(f2, "[op %s] ", str);}
        else if(Separator(str)){
            fprintf(f2, "[sep %s] ", str);}
        else if(Identifier(str)){
            fprintf(f2, "[id %s] ", str);}
        else if(Parenthesis(str)){
            fprintf(f2, "[par %s] ", str);}
        else if(Number(str)){
            fprintf(f2, "[num %s]", str);}
        else
        {
            fprintf(f2, "[unkn %s]", str);
            f3 =fopen("ErrorOutput.txt","w");
            fprintf(f3, "\nunknown %s", str);
            fclose(f3);
        }
    }
    fclose(f1);
    fclose(f2);

    f1 = fopen("tokensOutput.txt", "r");
    while((c=fgetc(f1))!=EOF)
    {
        printf("%c",c);
    }
    printf("\n");

    f2 =fopen("Error.txt","r");
    while((c=fgetc(f2))!=EOF)
    {
        printf("%c",c);
    }
    fclose(f2);
    return 0;
}

