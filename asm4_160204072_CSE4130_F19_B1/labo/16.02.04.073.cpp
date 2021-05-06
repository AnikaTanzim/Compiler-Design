#include <bits/stdc++.h>
#include<stdio.h>
#include <stdbool.h>
#include <string.h>

#include <iostream>
using namespace std;
FILE *f1,*f2;
int n =0;
struct symbol{
    int slNO;
    char name[40], idType[40],dataType[40],scope[40],value[40],lineNumber[40];
}symbolTable[40];

int keyword_rec(char v[])
{
    int i,flag=0;
    char key[][15] = {"char","int","float","double","return","if","else","else if","while","for","switch","case","goto"};
   /// char key[][15] = {"char","int","float","double"};
    for(i=0; i<13; i++)
        if(!strcmp(v,key[i]))
        {
            flag=1;
            break;
        }
    return flag;
}

int datatypes(char v[])
{
    int i,flag=0;
    char key[][15] = {"char","int","float","double"};
    for(i=0; i<4; i++)
        if(!strcmp(v,key[i]))
        {
            flag=1;
            break;
        }
    return flag;
}
bool Number(char lex[])
{
    int i;
    int in=1,coun=0;
    for (i = 0; i < strlen(lex); i++)
    {
        if (isdigit(lex[i]) || lex[i] == '.')
        {
            if (lex[i] == '.')
            {
                coun++;
            }
        }
        else
            return false;
    }

    if (coun > 1)
    {
        return false;
    }

    return true;
}
int number_rec(char v[20])
{
    int i, l, flag;
    i=0;
    if(isdigit(v[i]))
    {
        flag=1;
        i++;
    }
    else if(v[i]=='.')
    {
        flag=2;
        i++;
    }
    else flag=0;
    l=strlen(v);
    if(flag==1)
        for(; i<l; i++)
        {
            if(isdigit(v[i]))
                flag=1;
            else if(v[i]=='.')
            {
                flag=2;
                i++;
                break;
            }
            else
            {
                flag=0;
                break;
            }
        }
    if(flag==2)
        if(isdigit(v[i]))
        {
            flag=3;
            i++;
        }
        else flag=0;
    if(flag==3)
        for(; i<l; i++)
        {
            if(isdigit(v[i]))
                flag=3;
            else
            {
                flag=0;
                break;
            }
        }
    if(flag==3) flag=1;
    return flag;
}
int identifier_rec(char val[])
{
    int i,flag=0,l;
    l=strlen(val);
    if(isalpha(val[0])||val[0]=='_')
    {
         flag=1;
    }
    if(flag==1)
    {
        for(i=1; i<l; i++)
        {
            if(!isalnum(val[i]) && val[i]!='_' && !isalpha(val[i]))
            {
                flag=0;
                break;
            }
        }
    }
    return flag;
}
int operator_rec(char val[])
{
    int i, l,flag=0;
    l=strlen(val);
    if(l==1 && (val[0]=='>' || val[0]=='+' || val[0]=='-' || val[0]=='*' || val[0]=='/' || val[0]=='<' || val[0]=='='))
        return 1;
    else if(l==2 && (val[0]=='>' || val[0]=='<'|| val[0]=='=' || val[0]=='!') && val[1]=='=')
        flag=1;
    else flag=0;
    return flag;
}
int separator_rec(char val[])
{
    int i, l;
    l=strlen(val);
    if(l==1 && (val[0]==',' || val[0]==';' || val[0]=='"' || val[0]=='\'' ))
        return 1;
    else
        return 0;
}
int bracket_rec(char val[])
{
    int l = strlen(val);
    return (l==1 && (val[0]=='(' || val[0]==')' || val[0]=='{' || val[0]=='}' || val[0]=='[' || val[0]==']'));
}
void PrintLine()
{
    char c,a,b,d,e;
    int count=1;
    f1=fopen("input.c","r");
    f2=fopen("output.txt","w");
    if(!f1)
        printf("\n File cannot be opened");
    else
    {
        fprintf(f2,"%d ",count);
        while((c=fgetc(f1))!=EOF)
        {
            fputc(c,f2);
            if(c=='\n')
            {
                count++;
                fprintf(f2,"%d ",count);

            }

        }
    }
    fclose(f1);
    fclose(f2);
}
void RemoveSingleMultilineComment(){

    char c,a,b,d,e;
    f1= fopen("output.txt","r");
    f2= fopen("output2.txt","w");
   // printf("\n\nRemoving spaces and multiline: \n");
    if(!f1)
        printf("\n File cannot be opened");
    else
    {
        ///Single Line & multi line
        while ((c = fgetc(f1)) != EOF)
        {
           if(c==' ')
            {

                fputc(c,f2);
                //avoiding extra spaces.
                while ((c = fgetc(f1)) == ' '){continue;}
                if (c == '\n') {
                    fputc(c,f2);
                    continue;

                }



            }
             if (c == '/') {
                c = fgetc(f1);
                if (c == '/') {
                    //omitting single line comments.
                    while ((c = fgetc(f1)) != '\n') {}
                    fputc(c,f2);

                  // continue;
                } else if (c == '*') {
                    //omitting multi line comments.
                    while ((c = fgetc(f1)) != '/') {}
                   // continue;
                }
            }
            else if (c == '\t')
            {
                //avoiding tabs.
                while((c=fgetc(f1))=='\t');
                fputc(c,f2);
            }
            else if (c == '\n')
            {
                fputc(c,f2);

            }
            else
            {
                fputc(c,f2);
            }
        }


    }
    fclose(f1);
    fclose(f2);

}

void insertFunct()
{
    /// step 2 symbol table

    FILE *f1;
    char str[10],s[50];
    char temp[40],iddt[40],c;
    char lineNo[40],name[40],scope[40],idType[40];
    int i;
    strcpy(temp,"global");
    f1= fopen("output6.txt","r");


    while((c=fgetc(f1))!=EOF)
    {
        if(c=='[')
        {
            memset(iddt,'\0',sizeof(iddt));
            i =0;
            while((c=fgetc(f1))!=']' && c!=' ')
            {
                iddt[i++]=c;

            }
            iddt[i]='\0';
            if(keyword_rec(iddt)==1)
            {
                if(datatypes(iddt)==1)
                {

                    strcpy(symbolTable[n].dataType, iddt);///found out the dataType of the var/func
                    fscanf(f1,"%s",&s);

                    i=0;
                    while((c=fgetc(f1))!=']'){ ///found out the name of variable/func
                        iddt[i++]=c;
                    }

                    iddt[i]='\0';

                    strcpy(symbolTable[n].name,iddt);

                    strcpy(name,iddt);

                    strcpy(symbolTable[n].lineNumber,lineNo);
                    c=fgetc(f1);//[
                    c=fgetc(f1);//next value
                    strcpy(symbolTable[n].scope, temp);
                    strcpy(scope, temp);


                    if(c==';'||c=='='||c==')'||c==',')
                    {
                        i=0;
                        if(c=='='){

                            c=fgetc(f1);//]
                            c=fgetc(f1);//[
                            while((c=fgetc(f1))!=']')
                            { ///found out the value
                                iddt[i++]=c;
                            }
                            iddt[i]='\0';
                            strcpy(symbolTable[n].value,iddt);
                        }

                        else{
                            strcpy(symbolTable[n].value," ");
                        }

                        strcpy(symbolTable[n].idType,"var");
                        strcpy(idType,"var");
                        strcpy(symbolTable[n].lineNumber,lineNo);
                    }
                    else if(c=='('){
                       strcpy(symbolTable[n].idType,"func");
                        strcpy(idType,"func");
                       strcpy(temp,symbolTable[n].name);
                        strcpy(temp,name);
                        strcpy(symbolTable[n].lineNumber,lineNo);
                    }
                    int sizeOfSt=n;
                    int f=0;
                    for(int j=0; j<sizeOfSt; j++)
                    {


                        if ( (!strcmp(symbolTable[j].scope, scope)) &&(!strcmp(symbolTable[j].name, name))&&(!strcmp(symbolTable[j].idType, idType))  ) /// if not a global function
                        {
                            f=1;
                            n--;
                            printf("Duplicate Id at line %s\n",symbolTable[j].lineNumber);///duplicate line no
                            continue;
                        }
                    }

                    symbolTable[n].slNO=n+1;
                    n++;
                }
                else{
                    fscanf(f1,"%s",&s);//taking'id'
                    i=0;
                    while((c=fgetc(f1))!=']'){ ///found out the name of variable/func
                        iddt[i++]=c;
                    }

                    iddt[i]='\0';

                    strcpy(name,iddt);

                    c=fgetc(f1);//[
                    c=fgetc(f1);//next value
                    strcpy(scope, temp);


                    if(c==';'||c=='='||c==')'||c==',')
                    {
                        strcpy(idType,"var");

                    }
                    else if(c=='('){

                        strcpy(idType,"func");
                        strcpy(temp,name);
                    }
                    int sizeOfSt=n;
                    int f=0;
                    for(int j=0; j<sizeOfSt; j++)
                    {
                        if  ((strcmp(symbolTable[j].scope, scope))&&(!strcmp(symbolTable[j].name, name)) &&(!strcmp(symbolTable[j].idType, idType)))
                        {
                            printf("Undeclared identifier at line %s\n",symbolTable[n].lineNumber);///undeclare identifier line no
                            break;
                        }
                    }

                }


            }
            if (strstr(iddt,"ln"))
            {
                i=0;
                while((c=fgetc(f1))!=']'){ ///found out the name of variable/func
                    iddt[i++]=c;
                }
                iddt[i]='\0';
                strcpy(lineNo,iddt);
                strcpy(symbolTable[n].lineNumber,lineNo);




            }

            else if(!strcmp("}", iddt))
            {

                strcpy(temp, "global");
            }

            if(!strcmp("=", iddt))
            {///found out the value if no keyword before
                c = fgetc(f1);//[
                c = fgetc(f1);//next text
                int i=0;
                if(isdigit(c)|| c=='.')
                {
                    symbolTable[n-1].value[i++]=c;
                    while((c=fgetc(f1))!=']')
                    {
                        symbolTable[n-1].value[i++]=c;

                    }
                }
            }
        }
    }
    fclose(f1);
}

void displayFunc(){
   // symbol *a= symbolTable;
    printf("\n\nID\tName\tType\tData Type\tScope\tValue\tlines\n");
    printf("-----------------------------------------------------------\n");
    for(int i=0; i<n; i++)
    {
        printf("%d\t%s\t%s\t%s\t\t%s\t%s\t%s\n", symbolTable[i].slNO, symbolTable[i].name, symbolTable[i].idType, symbolTable[i].dataType, symbolTable[i].scope,symbolTable[i].value,symbolTable[i].lineNumber);
    }
}

bool is_parenthesis_or_separator(char c)
{
    if (c == ';'||c == ','||c == '\''||c == '\"'||c == '('||c == ')'||c == '{'||c == '}'||c == '['||c == ']')
    {
        return true;
    }
    return false;
}
bool is_operator(char c)
{
    if (c == '+'||c == '-'||c == '*'||c == '/'||c == '<'||c == '>'||c == '%'||c == '='||c == '&'||c == '|'||c == '!'||c == '^'||c == '~')
    {
        return true;
    }
    return false;
}
void Lexemes()
{
    char c;
    f1= fopen("output2.txt","r");
    f2 = fopen("output3.txt","w");

    //separator , parenthesis
    while((c = fgetc(f1))!= EOF)
    {
        if(is_parenthesis_or_separator(c))
        {
            fputc(' ',f2);
            fputc(c,f2);
            fputc(' ',f2);
        }
        else
        {
            fputc(c,f2);
        }
    }

    fclose(f2);
    fclose(f1);

    f1 = fopen("output3.txt", "r");
    f2 = fopen("output4.txt", "w");

    //separator , parenthesis
    while((c = fgetc(f1))!= EOF)
    {
        if (is_operator(c))
        {
            fputc(' ',f2);
            fputc(c,f2);
            while((c = fgetc(f1)) != EOF && is_operator(c))
            {
                fputc(c,f2);
            }
            fputc(' ',f2);
            fputc(c,f2);
        }
        else
        {
            fputc(c,f2);
        }

    }

    fclose(f2);
    fclose(f1);

}
void final_lexeme(){
    char c;

    f1 = fopen("output4.txt", "r");
    f2 = fopen("output3.txt", "w");
    while((c = fgetc(f1)) != EOF)
    {
        if (c == ' ')
        {
            fputc(c,f2);
            while((c = fgetc(f1)) != EOF && c == ' '){}
            fputc(c,f2);
        }
        else
        {
            fputc(c,f2);
        }
    }

    fclose(f1);
    fclose(f2);
}

void tokenize()
{
    char c;int error=0,j=0;

    f1 = fopen("output3.txt", "r");
    f2 = fopen("output5.txt", "w");
    fputc('\n',f2);
    //separator , parenthesis
    while((c = fgetc(f1))!= EOF)
    {
        char val[50];
        int i=0;
        while(c!=' ' && c!=EOF)
        {
            val[i]=c;
            i++;
            c = fgetc(f1);
        }
        val[i]='\0';
        if (strlen(val) != 0)
        {
            if(keyword_rec(val))
            {
                fprintf(f2, "[kw %s] ", val);
            }
            else if (Number(val))
            {
                fprintf(f2, "[num %s]", val);
            }
            else if (bracket_rec(val))
            {
               fprintf(f2, "[par %s] ", val);
            }
            else if (operator_rec(val))
            {
                fprintf(f2, "[op %s] ", val);
            }
            else if (identifier_rec(val))
            {
                fprintf(f2, "[id %s] ", val);
            }
            else if (separator_rec(val))
            {
                fprintf(f2, "[sep %s] ", val);
            }
            else
            {
                if (val[0] == '\n'){
                    int z = 1;
                    while(val[z] != '\0'){
                       val[z-1] = val[z];
                        z++;
                    }
                    val[z-1] =  val[z];
                    fputc('\n',f2);
                    fprintf(f2, "[ln %s] ", val);
                }
                else
                {
                    fprintf(f2, "[unkn %s]", val);
                    error=1;
                }
            }
        }
    }
    fclose(f1);
    fclose(f2);
    char str[10],s[50];
    f1 = fopen("output5.txt", "r");
    f2 = fopen("output6.txt", "w");
    while((c=fgetc(f1))!=EOF)
        {

            if(c=='[') // if it is not an id
            {

                int i=0;
                fputc(c,f2);
                while((c=fgetc(f1))!=EOF)
                {
                    if(c==' ')
                    {
                        str[i++]=' ';
                        break;
                    }
                    else
                    {
                        str[i++]=c;
                    }
                }
                str[i]='\0';
                if(!strcmp(str,"id ")|| !strcmp(str,"ln "))
                {
                    fputs(str,f2);
                }


            }
            else
                {
                    if(c!=' ')
                    {
                        fputc(c,f2);
                    }

                }

        }

    fclose(f1);
    fclose(f2);
}

void parenthesisError(){

    f1= fopen("output2.txt","r");
    int parBalance=0;
    int count;
    char c;
    count=1;
    if(!f1)
        printf("\n File cannot be opened");
    else
    {
        while((c=fgetc(f1))!=EOF)
        {
            if(c=='\n')
            {
                count++;
            }
            else if(c=='{')
            {

                parBalance++;

            }
            else if(c=='}')
            {
                parBalance--;

            }


            if((parBalance <0))
            {
                printf("Misplaced '}' at %d\n",count);
                parBalance=0;

            }

        }

            if((parBalance >0))
            {
                printf("Misplaced '{' at %d\n",count);
                parBalance=0;

            }
    }
    fclose(f1);

}


void duplicateTokenError()
{
    char c;
    int cnt=0,dup=0,ln=1;
    f1 = fopen("output3.txt","r");
    while((c=fgetc(f1))!=EOF)
    {
        if(c=='f' && (c=fgetc(f1))=='o' && (c=fgetc(f1))=='r')
        {
            while((c=fgetc(f1))!=')')
            {
                if(c==';')
                {
                    dup++;
                }
            }
            if(dup>2)
            {
                printf("Duplicate token ';' at line %d",ln);
            }
        }
        if(c==';')
        {
            c=fgetc(f1);
            if((c=fgetc(f1)) == ';')
            {
                printf("Duplicate token ';' at line %d\n",ln);
            }
        }
        if(c=='\n')
        {
            ln++;
        }
        if(c=='i')
        {
            if((c=fgetc(f1))=='f')
            {
                cnt++;
            }
        }
        if(c=='e' && (c=fgetc(f1))=='l' && (c=fgetc(f1))=='s' && (c=fgetc(f1))=='e')
        {
            cnt--;
            if(cnt<0)
            {
                printf("Mismatched 'else' at line %d\n",ln);

            }

        }


    }
}
void idPrint()
{
    char c;
    f1 = fopen("output3.txt","r");
    f2= fopen("output7.txt","w");


    while((c = fgetc(f1))!= EOF)
    {
        char val[50];
        int i=0;
        while(c!=EOF &&c!=' ')
        {
            val[i]=c;
            i++;
            c = fgetc(f1);
        }
        val[i]='\0';
        if (strlen(val) != 0)
        {

            if ((identifier_rec(val)) && (!keyword_rec(val)))
            {
                fprintf(f2, "id %s ", val);
            }
            else{
                fprintf(f2, "%s ", val);
            }
        }
    }
    printf("\n\n");
    fclose(f1);
    fclose(f2);
    f1= fopen("output7.txt","r");
    while((c=fgetc(f1))!=EOF)
    {
        printf("%c",c);
    }
    printf("\n\n");
    fclose(f1);
}
int main()
{
    PrintLine();
    RemoveSingleMultilineComment();

    char c;

    f1= fopen("output.txt","r");
    while((c=fgetc(f1))!=EOF)
    {
        printf("%c",c);
    }
    fclose(f1);
    printf("\n\n");
    ///finding unmatched parenthesis error

    Lexemes();
    final_lexeme();

    idPrint();

    parenthesisError();
    duplicateTokenError();

    tokenize();
    insertFunct();

    //displayFunc();

    return 0;
}
