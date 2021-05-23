%{
#include "listaSimbolos.h"
#include "listaCodigo.h"
#include "minic.tab.h"

void error_lexico();
void error_comentario();
int error_cadena();
int comprobacion_id();
int comprobacion_numero();
int numero_linea;
int numero_errores = 0;
%}

digito              [0-9]
letra               [a-zA-Z]
entero              {digito}+
%x COMENT
%x CAD
%option yylineno

%%

[ \n\t\r]+                           ;
"//"(.*)[\n]                         ;
"/*"				    {BEGIN COMENT;yymore();numero_linea=yylineno;}
<COMENT>[^*]*			    yymore();
<COMENT>[*]+[^*/]*		    yymore();			
<COMENT>[*]+[/]			    {BEGIN 0;}
<COMENT><<EOF>>		  	    {error_comentario();BEGIN 0;yyterminate();}
\"				    {BEGIN CAD;yymore();numero_linea=yylineno;}
<CAD>([^\"\n]|\\+\")*		    yymore();
<CAD>\"				    {yymore();BEGIN 0;yylval.cadena=strdup(yytext);return CADENA;}
<CAD>"\n"			    {error_cadena();BEGIN 0;yylval.cadena=strdup(yytext);return CADENA;}
void				    return VOID;
var				    return VAR;
const				    return CONST;
if				    return IF;
else				    return ELSE;
do				    return DO;
while				    return WHILE;
print                                return PRINT;
read                                 return READ;
({letra}|_)({letra}|{digito}|_)*     {comprobacion_id();yylval.cadena=strdup(yytext);return ID;}
{entero}                             {comprobacion_numero();yylval.cadena=strdup(yytext);return NUM;}
";"                                  return SEMICOLON;
","                                  return COMA;
"+"                                  return MAS;
"-"                                  return MENOS;
"*"				    return POR;
"/"				    return DIV;
"="				    return IGUAL;
"("                                  return APAR;		
")"                                  return CPAR;
"{"				    return ACOR;
"}"				    return CCOR;
[^a-zA-Z0-9_ \n\t\r;,+\-*/=(){}"]+   error_lexico();
%%

void error_lexico()
{
  printf("ERROR: caracteres no validos en linea %d: %s\n",yylineno,yytext);
  numero_errores++;
}

void error_comentario()
{
  printf("ERROR: comentario no cerrado iniciado en linea %d\n",numero_linea);
  numero_errores++;
}

int error_cadena()
{
  printf("ERROR: cadena sin cerrar en línea %d: %s",numero_linea,yytext);
  numero_errores++;
}

int comprobacion_id()
{
  if (yyleng > 16) {
	printf("ERROR: identificador demasiado largo en linea %d: %s\n",yylineno,yytext);
	numero_errores++;
  }
}

int comprobacion_numero()
{
  if (atoll(yytext) > 2147483648) {
	printf("ERROR: entero demasiado grande en linea %d: %s\n",yylineno,yytext);
	numero_errores++;
  }
}
