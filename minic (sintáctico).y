
%{
#include <stdio.h>
void yyerror();
extern int yylex();
int cont=1;
%}

//Definimos los tipos que tendrán los tokens
%union{
char *cadena;
}

%token VOID VAR CONST IF ELSE WHILE PRINT READ SEMICOLON COMA IGUAL APAR CPAR ACOR CCOR
//Indicamos el tipo de los tokens (ya que por defecto son de tipo CHAR ¿?)
%token <cadena> CADENA ID NUM
//Establecemos la precedencia y la asociatividad (una línea tiene más precedencia que las líneas anteriores)
%left MAS MENOS
%left POR DIV
%left UMENOS
//Declaramos el tipo de los no terminales
//%type <entero> expresion
%%

program : VOID ID APAR CPAR ACOR declarations statement_list CCOR	{printf("Aplica program -> void id ( ) { declarations } \n");}
        ;

declarations : declarations VAR identifier_list SEMICOLON		{printf("Aplica declarations -> declarations VAR identifier_list ; \n");}
             | declarations CONST identifier_list SEMICOLON	{printf("Aplica declarations -> declarations CONST identifier_list ; \n");}
             | /*empty*/					{printf("Aplica declarations -> lambda \n");}
             ;

identifier_list : asig						{printf("Aplica identifier_list -> asig \n");}
                | identifier_list COMA asig			{printf("Aplica identifier_list -> identifier_list , asig \n");}
                ;

asig : ID							{printf("Aplica asig -> ID \n");}
     | ID IGUAL expression					{printf("Aplica asig -> ID = expression \n");}
     ;

statement_list : statement_list statement			{printf("Aplica statement_list -> statement_list statement \n");}
               | /*empty*/					{printf("Aplica statement_list -> lambda \n");}
               ;

statement : ID IGUAL expression SEMICOLON			{printf("Aplica statement -> ID = expression ; \n");}
          | ACOR statement_list CCOR				{printf("Aplica statement -> ( statement_list ) \n");}
          | IF APAR expression CPAR statement ELSE statement	{printf("Aplica statement -> IF ( expression ) statement ELSE statement \n");}
          | IF APAR expression CPAR statement			{printf("Aplica statement -> IF ( expression ) statement \n");}
          | WHILE APAR expression CPAR statement			{printf("Aplica statement -> WHILE ( expression ) statement \n");}
          | PRINT print_list SEMICOLON				{printf("Aplica statement -> PRINT print_list ; \n");}
          | READ read_list SEMICOLON				{printf("Aplica statement -> READ read_list ; \n");}
          ;

print_list : print_item						{printf("Aplica print_list -> print_item \n");}
           | print_list COMA print_item				{printf("Aplica print_list -> print_list , print_item \n");}
           ;

print_item : expression						{printf("Aplica print_item -> expression \n");}
           | CADENA						{printf("Aplica print_item -> CADENA \n");}
           ;

read_list : ID							{printf("Aplica read_list -> ID  \n");}
          | read_list COMA ID					{printf("Aplica read_list -> , ID  \n");}
          ;

expression : expression MAS expression				{printf("Aplica expression -> expression + expression \n");}
           | expression MENOS expression				{printf("Aplica expression -> expression - expression \n");}
           | expression POR expression				{printf("Aplica expression -> expression * expression \n");}
           | expression DIV expression				{printf("Aplica expression -> expression / expression \n");}
           | MENOS expression %prec UMENOS			{printf("Aplica expression -> - expression \n");}
           | APAR expression CPAR				{printf("Aplica expression -> ( expression ) \n");}
           | ID							{printf("Aplica expression -> ID \n");}
           | NUM						{printf("Aplica expression -> NUM \n");}
           ;

%%

void yyerror()
{
printf("Se ha producido un error en esta expresion\n");
}

