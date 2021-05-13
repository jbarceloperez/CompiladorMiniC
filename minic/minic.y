%{
#include <stdio.h>
#include "listaSimbolos.h"
//#include "listaCodigo.h"

Lista tablaSimb;
int contCadenas=0;
Tipo tipo;
int perteneceTablaS(char *lexema);
void anadeEntrada(char *lexema, Tipo tipo);
int esConstante(char *lexema);
void imprimirTablaS();

int registros[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void yyerror();
extern int yylex();
extern int yylineno;
%}

%token VOID VAR CONST IF ELSE WHILE PRINT READ SEMICOLON COMA IGUAL APAR CPAR ACOR CCOR
//Indicamos el tipo de los tokens
%token <cadena> CADENA ID NUM
%type <codigo> expression statement statement_list print_item print_list read_list program declarations      // aunque no lo ponga en las diapositivas, hay que hacerlo así para poder asignarle al statement un valor de ListaC
//Establecemos la precedencia y la asociatividad (una línea tiene más precedencia que las líneas anteriores)
%left MAS MENOS
%left POR DIV
%left UMENOS

//Definimos los tipos que tendrán los tokens
%union{
char *cadena;
ListaC codigo;
}

%code requires{

	#include "listaCodigo.h"
}

%%

program : {tablaSimb=creaLS();} VOID ID APAR CPAR ACOR declarations statement_list CCOR	{imprimirTablaS(); liberaLS(tablaSimb);}
        ;

declarations : declarations VAR {tipo=VARIABLE;} identifier_list SEMICOLON
             | declarations CONST {tipo=CONSTANTE;} identifier_list SEMICOLON
             | /*empty*/
             ;

identifier_list : asig
                | identifier_list COMA asig
                ;

asig : ID			{if (!perteneceTablaS($1)) anadeEntrada($1,tipo); else printf("Error en línea %d: variable %s ya declarada\n",yylineno,$1);}
     | ID IGUAL expression	{if (!perteneceTablaS($1)) anadeEntrada($1,tipo); else printf("Error en línea %d: variable %s ya declarada\n",yylineno,$1);}
     ;

statement_list : statement_list statement
               | /*empty*/
               ;

statement : ID IGUAL expression SEMICOLON			{if (!perteneceTablaS($1)) printf("Error en línea %d: variable %s no declarada\n",yylineno,$1); else if (esConstante($1)) printf("Error en línea %d: asignación a constante %s\n",yylineno,$1); $$ = crearLista3($3, "sw");}
          | ACOR statement_list CCOR
          | IF APAR expression CPAR statement ELSE statement
          | IF APAR expression CPAR statement
          | WHILE APAR expression CPAR statement
          | PRINT print_list SEMICOLON
          | READ read_list SEMICOLON
          ;

print_list : print_item
           | print_list COMA print_item
           ;

print_item : expression
           | CADENA		{anadeEntrada($1,STRING);contCadenas++;}
           ;

read_list : ID				{if (!perteneceTablaS($1)) printf("Error en línea %d: variable %s no declarada\n",yylineno,$1); else if (esConstante($1)) printf("Error en línea %d: asignación a constante %s\n",yylineno,$1);}
          | read_list COMA ID		{if (!perteneceTablaS($3)) printf("Error en línea %d: variable %s no declarada\n",yylineno,$3); else if (esConstante($3)) printf("Error en línea %d: asignación a constante %s\n",yylineno,$3);}
          ;

expression : expression MAS expression	  	{$$ = crearLista2($1, $3, "add");}
           | expression MENOS expression	  {$$ = crearLista2($1, $3, "sub");}
           | expression POR expression		  {$$ = crearLista2($1, $3, "mul");}
           | expression DIV expression		  {$$ = crearLista2($1, $3, "div");}
           | MENOS expression %prec UMENOS	{$$ = crearLista3($2, "neg");}
           | APAR expression CPAR		  	    {$$ = $2;}	// como la expresion ya es una listaC, no hace falta crear otra listaC
           | ID								              {if (!perteneceTablaS($1)) printf("Error en línea %d: variable %s no declarada\n",yylineno,$1);$$ = crearLista($1, "lw");}
           | NUM							              {$$ = crearLista($1, "li");}
           ;

%%

void yyerror()
{
  printf("Se ha producido un error en esta expresion\n");
}

ListaC crearLista(char* arg1, char* op)		// esto vale para id y num, solo cambia el tipo de op (li o lw)
{
  ListaC lista = creaLC();
  int reg = buscarReg();
  registros[reg] = 1;
  char* registro;
  sprintf(registro, "$t%d", reg);
  PosicionListaC inicio = inicioLC(lista);
  //Creamos la operación
  Operacion operacion;
  operacion.op = op;
  operacion.res = registro;
  operacion.arg1 = arg1;
  //Insertamos la operación en la lista
  insertaLC(lista, inicio, operacion);
  guardaResLC(lista, registro);
  return lista;
}

ListaC crearLista2(ListaC lista, ListaC arg2, char* op) {
  //recuperamos los registros de las expresiones para la operacion
  char* regArg1 = recuperaResLC(lista);
  char* regArg2 = recuperaResLC(arg2);
  //concatena listas
  concatenaLC(lista, arg2);
  //buscamos registros libres
  int reg = buscarReg();
  registros[reg] = 1;
  char* registro;
  sprintf(registro, "$t%d", reg);
  PosicionListaC final = finalLC(lista);
  //crea la operacion
  Operacion operacion;
  operacion.op = op;
  operacion.res = registro;
  operacion.arg1 = regArg1;
  operacion.arg2 = regArg2;
  //liberamos registros
  char r = regArg1[2];
  char rr = regArg2[2];
  int r1 = r - '0';
  int r2 = rr - '0';
  registros[r1] = 0;
  registros[r2] = 0;
  //insertar la op al final de la lista
  insertaLC(lista, final, operacion);
  guardaResLC(lista, registro);
  return lista;
}

ListaC crearLista3(ListaC lista, char* op){
  //recuperamos los registros de las expresiones para la operacion
  char* regArg = recuperaResLC(lista);
  //buscamos registros libres
  int reg = buscarReg();
  registros[reg] = 1;
  char* registro;
  sprintf(registro, "$t%d", reg);
  PosicionListaC final = finalLC(lista);
  //crear op
  Operacion operacion;
  operacion.op = op;
  operacion.res = registro;
  operacion.arg1 = regArg;  
  //liberamos registros
  char r = regArg[2];
  int r1 = r - '0';
  registros[r1] = 0;
  // insertar op
  insertaLC(lista, final, operacion);
  guardaResLC(lista, registro);
  return lista;    
}

int buscarReg()
{
  int i = 0;
  while (registros[i] != 0) i++;
  return i;
}

int perteneceTablaS(char *lexema)
{
  PosicionLista posicion = buscaLS(tablaSimb, lexema);
  return posicion != finalLS(tablaSimb);
}

void anadeEntrada(char *lexema, Tipo tipo)
{
  PosicionLista final = finalLS(tablaSimb);
  Simbolo simbolo;
  simbolo.nombre = lexema;
  simbolo.tipo = tipo;
  if (tipo == STRING) simbolo.valor = contCadenas;
  else simbolo.valor = 0;
  insertaLS(tablaSimb, final, simbolo);
}

int esConstante(char *lexema)
{
  PosicionLista posicion = buscaLS(tablaSimb, lexema);
  Simbolo simbolo = recuperaLS(tablaSimb, posicion);
  return simbolo.tipo == CONSTANTE;
}

void imprimirTablaS()
{
  PosicionLista posicion = inicioLS(tablaSimb);
  printf("############################\n");
  printf(".data\n\n");
  printf("# STRINGS ##################\n");
  while (posicion != finalLS(tablaSimb))
  {
    Simbolo simbolo = recuperaLS(tablaSimb, posicion);
    if (simbolo.tipo == STRING) printf("$str%d:\t.asciiz %s\n",simbolo.valor,simbolo.nombre);
    posicion = siguienteLS(tablaSimb, posicion);
  }
  printf("\n# IDENTIFIERS ##############\n");
  posicion = inicioLS(tablaSimb);
  while (posicion != finalLS(tablaSimb))
  {
    Simbolo simbolo = recuperaLS(tablaSimb, posicion);
    if (simbolo.tipo != STRING) printf("_%s:\t.word %d\n",simbolo.nombre,simbolo.valor);
    posicion = siguienteLS(tablaSimb, posicion);
  }
}
