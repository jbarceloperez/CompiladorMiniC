%{
#include <stdio.h>
#include "listaSimbolos.h"
#include "listaCodigo.h"

Lista tablaSimb;
int contCadenas=0;
Tipo tipo;
int perteneceTablaS(char *lexema);
void anadeEntrada(char *lexema, Tipo tipo);
int esConstante(char *lexema);
void imprimirTablaS();

int buscarReg();
ListaC crearLista(char* arg1, char* op);
ListaC crearLista2(ListaC lista, ListaC arg2, char* op);
ListaC crearLista3(ListaC lista, char* op);
ListaC listaIf(ListaC cond, ListaC st);
ListaC listaPrintItem(int cadena);
ListaC listaPrintExpresion(ListaC arg);
ListaC concatena(ListaC l1, ListaC l2);
ListaC listaRead(char* cadena);

int registros[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int tag_counter = 0;

void yyerror();
extern int yylex();
extern int yylineno;
%}

//Definimos los tipos que tendrán los tokens
%union{
char *cadena;
ListaC codigo;
}

%token VOID VAR CONST IF ELSE WHILE PRINT READ SEMICOLON COMA IGUAL APAR CPAR ACOR CCOR
//Indicamos el tipo de los tokens
%token <cadena> CADENA ID NUM
%type <codigo> expression statement statement_list print_item print_list read_list program declarations      // aunque no lo ponga en las diapositivas, hay que hacerlo así para poder asignarle al statement un valor de ListaC
//Establecemos la precedencia y la asociatividad (una línea tiene más precedencia que las líneas anteriores)
%left MAS MENOS
%left POR DIV
%left UMENOS

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

asig : ID			                  {if (!perteneceTablaS($1)) anadeEntrada($1,tipo); else printf("Error en línea %d: variable %s ya declarada\n",yylineno,$1);}
     | ID IGUAL expression	    {if (!perteneceTablaS($1)) anadeEntrada($1,tipo); else printf("Error en línea %d: variable %s ya declarada\n",yylineno,$1);}
     ;

statement_list : statement_list statement
               | /*empty*/
               ;

statement : ID IGUAL expression SEMICOLON			  {if (!perteneceTablaS($1)) printf("Error en línea %d: variable %s no declarada\n",yylineno,$1); else if (esConstante($1)) printf("Error en línea %d: asignación a constante %s\n",yylineno,$1); $$ = crearLista3($3, "sw");}
          | ACOR statement_list CCOR
          | IF APAR expression CPAR statement ELSE statement
          | IF APAR expression CPAR statement   {$$ = listaIf($3, $5);}
          | WHILE APAR expression CPAR statement
          | PRINT print_list SEMICOLON          {$$ = $2;}
          | READ read_list SEMICOLON            {$$ = $2;}
          ;

print_list : print_item                         {$$ = $1;}
           | print_list COMA print_item         {$$ = concatena($1, $3);}
           ;

print_item : expression              {$$ = listaPrintExpresion($1);}
           | CADENA		               {anadeEntrada($1,STRING); $$ = listaPrintItem(contCadenas); contCadenas++;}
           ;

read_list : ID				              {if (!perteneceTablaS($1)) printf("Error en línea %d: variable %s no declarada\n",yylineno,$1); else if (esConstante($1)) printf("Error en línea %d: asignación a constante %s\n",yylineno,$1); $$ = listaRead($1);}
          | read_list COMA ID		    {if (!perteneceTablaS($3)) printf("Error en línea %d: variable %s no declarada\n",yylineno,$3); else if (esConstante($3)) printf("Error en línea %d: asignación a constante %s\n",yylineno,$3);}
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
  printf("crearLista\n");
  ListaC lista = creaLC();
  int reg = buscarReg();
  printf("reg=%d\n",reg);                 //debug
  registros[reg] = 1;
  char registro[4];
  sprintf(registro, "$t%d", reg);
  printf("%s\n",registro);                 //debug
  PosicionListaC inicio = inicioLC(lista);
  //Creamos la operación
  Operacion operacion;
  operacion.op = op;
  operacion.res = registro;
  operacion.arg1 = arg1;
  printf("1\n");                 //debug
  //Insertamos la operación en la lista
  insertaLC(lista, inicio, operacion);
  guardaResLC(lista, registro);
  printf("0\n");                 //debug
  return lista;
}

ListaC crearLista2(ListaC lista, ListaC arg2, char* op) {
  printf("crearLista2\n");                 //debug
  //recuperamos los registros de las expresiones para la operacion
  char* regArg1 = recuperaResLC(lista);
  char* regArg2 = recuperaResLC(arg2);
  //concatena listas
  concatenaLC(lista, arg2);
  liberaLC(arg2);
  //buscamos registros libres
  int reg = buscarReg();
  registros[reg] = 1;
  char registro[4];
  sprintf(registro, "$t%d", reg);
  printf("%s\n",registro);                 //debug
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
  printf("crearLista3\n");                 //debug
  //recuperamos los registros de las expresiones para la operacion
  char* regArg = recuperaResLC(lista);
  //buscamos registros libres
  int reg = buscarReg();
  registros[reg] = 1;
  char registro[4];
  sprintf(registro, "$t%d", reg);
  printf("%s\n",registro);                 //debug
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

ListaC listaIf(ListaC cond, ListaC st) {
  printf("listaIf\n");                                //debug
      //recuperamos los registros de las expresiones
  char* regCond = recuperaResLC(cond);
  char* regSt = recuperaResLC(st);
      //creamos la etiqueta del salto
  char* tag;
  sprintf(tag, "ET%d", tag_counter);
  tag_counter++;
      //añade beqz
  PosicionListaC final = finalLC(cond);
  Operacion operacion;
  operacion.op = "beqz";
  operacion.res = regCond;
  operacion.arg1 = tag;
      //liberamos registros ¿se libera el regCond que decide el salto? ¿qué hacemos con el registro res de la lista cond? ¿con cual nos quedamos?
  char r = regCond[2];
  int r1 = r - '0';
  registros[r1] = 0;
      // insertar la op
  insertaLC(cond, final, operacion);
      //concatena listas
  concatenaLC(cond, st);
  liberaLC(st); 
  guardaResLC(cond, regSt);
      //insertar etiqueta
  final = finalLC(cond);
  Operacion etiqueta;
  char* etq;
  sprintf(etq, "%s:", tag);
  etiqueta.op = etq;
  insertaLC(cond, final, etiqueta);
  return cond;
}

ListaC listaPrintItem(int cadena) {
  printf("listaPrintItem\n");           //debug
  ListaC lista = creaLC();
  char str[10];
  sprintf(str, "$str%d", cadena);
  printf("[%s]\n",str);                 //debug
  // la $a0, $strX
  Operacion op_la;
  op_la.op = "la";
  op_la.res = "$a0";
  op_la.arg1 = str;
  PosicionListaC final = finalLC(lista);
  insertaLC(lista, final, op_la);
  // li $v0, 4
  Operacion op_li;
  op_li.op = "li";
  op_li.res = "$v0";
  op_li.arg1 = "4";
  final = finalLC(lista);
  insertaLC(lista, final, op_li);
  Operacion syscall;
  syscall.op = "syscall";
  final = finalLC(lista);
  insertaLC(lista, final, syscall);
  return lista; 
}

ListaC listaPrintExpresion(ListaC lista) {
  char* regLista = recuperaResLC(lista);
  //move $a0, $tX
  Operacion op_move;
  op_move.op = "move";
  op_move.res = "$a0";
  op_move.arg1 = regLista;
  // se libera el registro
  char r = regLista[2];
  int r1 = r - '0';
  registros[r1] = 0;
  PosicionListaC final = finalLC(lista);
  insertaLC(lista, final, op_move);
  // li $v0, 1
  Operacion op_li;
  op_li.op = "li";
  op_li.res = "$v0";
  op_li.arg1 = "1";
  final = finalLC(lista);
  insertaLC(lista, final, op_li);
  Operacion syscall;
  syscall.op = "syscall";
  final = finalLC(lista);
  insertaLC(lista, final, syscall);
  return lista;
}

ListaC concatena(ListaC l1, ListaC l2){
  concatenaLC(l1, l2);
  liberaLC(l2);
  return l1;
}

ListaC listaRead(char* cadena){
  ListaC lista = creaLC();
  // li $v0, 5
  Operacion op_li;
  op_li.op = "li";
  op_li.res = "$v0";
  op_li.arg1 = "5";
  PosicionListaC final = finalLC(lista);
  insertaLC(lista, final, op_li);
  Operacion syscall;
  syscall.op = "syscall";
  final = finalLC(lista);
  insertaLC(lista, final, syscall);
  // sw $v0, _X
  Operacion op_sw;
  op_sw.op = "sw";
  op_sw.res = "$v0";
  char arg[16];
  sprintf(arg, "_%s", cadena);
  printf("%s", arg);                      //debug
  op_sw.arg1 = arg;
  final = finalLC(lista);
  insertaLC(lista, final, op_sw); 
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
