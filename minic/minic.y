%{
#include <stdio.h>
#include "listaSimbolos.h"
#include "listaCodigo.h"
#include <string.h>
#include <assert.h>

extern int numero_errores;
int error_sem = 0;
int error_sin = 0;

Lista tablaSimb;
int contCadenas=0;
Tipo tipo;
int perteneceTablaS(char *lexema);
void anadeEntrada(char *lexema, Tipo tipo);
int esConstante(char *lexema);
void imprimirTablaS();
void imprimirListaC(ListaC declarations, ListaC statements);

char* buscarReg();
ListaC crearLista(char* arg1, char* op);
ListaC crearLista2(ListaC lista, ListaC arg2, char* op);
ListaC crearLista3(ListaC lista, char* var, char* op);
ListaC crearListaNeg(ListaC lista, char* op);
ListaC listaIf(ListaC cond, ListaC st);
ListaC if_else(ListaC exp, ListaC stat1, ListaC stat2);
ListaC while_(ListaC exp, ListaC stat);
ListaC do_while(ListaC stat, ListaC exp);
ListaC listaPrintItem(char* cadena);
ListaC listaPrintExpresion(ListaC arg);
ListaC concatena(ListaC l1, ListaC l2);
ListaC listaRead(char* cadena);
void debugLista(ListaC lista);
void liberarReg(char* registro);
char *obtenerEtiqueta();

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

%token VOID VAR CONST IF ELSE WHILE PRINT READ SEMICOLON COMA IGUAL APAR CPAR ACOR CCOR DO
//Indicamos el tipo de los tokens
%token <cadena> CADENA ID NUM
%type <codigo> expression statement statement_list print_item print_list read_list program declarations asig identifier_list 
//Establecemos la precedencia y la asociatividad (una línea tiene más precedencia que las líneas anteriores)
%left MAS MENOS
%left POR DIV
%left UMENOS

%%

program : {tablaSimb=creaLS();} VOID ID APAR CPAR ACOR declarations statement_list CCOR	{if (numero_errores==0 && error_sem==0 && error_sin ==0) {imprimirTablaS();imprimirListaC($7, $8);} else printf("Errores léxicos: %d\nErrores semánticos: %d\nErrores sintácticos: %d\n",numero_errores,error_sem,error_sin); liberaLS(tablaSimb);}
        ;

declarations : declarations VAR {tipo=VARIABLE;} identifier_list SEMICOLON			{$$=concatena($1, $4);}
             | declarations CONST {tipo=CONSTANTE;} identifier_list SEMICOLON		{$$=concatena($1, $4);}
             | /*empty*/			{$$=creaLC();}
             ;

identifier_list : asig							{$$ = $1;}
                | identifier_list COMA asig		{$$ = concatena($1, $3);}
                ;

asig : ID			                  	{if (!perteneceTablaS($1)) anadeEntrada($1,tipo); else {printf("Error en línea %d: variable %s ya declarada\n",yylineno,$1);error_sin++;}; $$ = creaLC();}
     | ID IGUAL expression	    		{if (!perteneceTablaS($1)) anadeEntrada($1,tipo); else {printf("Error en línea %d: variable %s ya declarada\n",yylineno,$1);error_sin++;} $$ = crearLista3($3, $1, "sw");}
     ;

statement_list : statement_list statement		{$$ = concatena($1, $2);}
               | /*empty*/						{$$ = creaLC();}
               ;

statement : ID IGUAL expression SEMICOLON				{if (!perteneceTablaS($1)) {printf("Error en línea %d: variable %s no declarada\n",yylineno,$1);error_sin++;} else if (esConstante($1)) {printf("Error en línea %d: asignación a constante %s\n",yylineno,$1);error_sin++;} $$ = crearLista3($3, $1, "sw");}
          | ACOR statement_list CCOR					{$$ = $2;}
          | IF APAR expression CPAR statement ELSE statement	{$$ = if_else($3, $5, $7);}
          | IF APAR expression CPAR statement   		{$$ = listaIf($3, $5);}
          | WHILE APAR expression CPAR statement		{$$ = while_($3,$5);}
          | DO statement WHILE APAR expression CPAR		{$$ = do_while($2,$5);}
          | PRINT print_list SEMICOLON          		{$$ = $2;}
          | READ read_list SEMICOLON            		{$$ = $2;}
          ;

print_list : print_item                         {$$ = $1;}
           | print_list COMA print_item         {$$ = concatena($1, $3);}
           ;

print_item : expression              		{$$ = listaPrintExpresion($1);}
           | CADENA		               		{if (!perteneceTablaS($1)) anadeEntrada($1,STRING); $$ = listaPrintItem($1);}
           ;

read_list : ID				             	{if (!perteneceTablaS($1)) {printf("Error en línea %d: variable %s no declarada\n",yylineno,$1);error_sin++;} else if (esConstante($1)) {printf("Error en línea %d: asignación a constante %s\n",yylineno,$1);error_sin++;} $$ = listaRead($1);}
          | read_list COMA ID		    	{if (!perteneceTablaS($3)) {printf("Error en línea %d: variable %s no declarada\n",yylineno,$3);error_sin++;} else if (esConstante($3)) {printf("Error en línea %d: asignación a constante %s\n",yylineno,$3);error_sin++;} $$ = concatena($1, listaRead($3));}
          ;

expression : expression MAS expression	  	  {$$ = crearLista2($1, $3, "add");}
           | expression MENOS expression	  	  {$$ = crearLista2($1, $3, "sub");}
           | expression POR expression		  {$$ = crearLista2($1, $3, "mul");}
           | expression DIV expression		  {$$ = crearLista2($1, $3, "div");}
           | MENOS expression %prec UMENOS	  {$$ = crearListaNeg($2, "neg");}
           | APAR expression CPAR		  {$$ = $2;}	// como la expresion ya es una listaC, no hace falta crear otra listaC
           | ID					  {if (!perteneceTablaS($1)) {printf("Error en línea %d: variable %s no declarada\n",yylineno,$1);error_sin++;} $$ = crearLista($1, "lw");}
           | NUM				  {$$ = crearLista($1, "li");}          	
		   										
           ;

%%

void yyerror()
{
  	printf("Se ha producido un error en esta expresion\n");
  	error_sem++;
}

ListaC crearLista(char* arg1, char* op){	// esto vale para id y num, solo cambia el tipo de op (li o lw)
	ListaC lista = creaLC();
	char* registro = buscarReg();
	PosicionListaC inicio = inicioLC(lista);
	//Creamos la operación
	Operacion operacion;
	operacion.op = op;
	operacion.res = registro;
	if (op=="lw"){    // si es un id, se le coloca el '_' delante del nombre
		char arg[16];
		sprintf(arg, "_%s", arg1);
		operacion.arg1 = strdup(arg);
	}
	else {operacion.arg1 = arg1;}
	operacion.arg2 = NULL;
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
	liberaLC(arg2);
	//buscamos registros libres
	char* registro = buscarReg();
	PosicionListaC final = finalLC(lista);
	//crea la operacion
	Operacion operacion;
	operacion.op = op;
	operacion.res = registro;
	operacion.arg1 = regArg1;
	operacion.arg2 = regArg2;
	//liberamos registros
	liberarReg(regArg1);
	liberarReg(regArg2);
	//insertar la op al final de la lista
	insertaLC(lista, final, operacion);
	guardaResLC(lista, registro);
	return lista;
}

ListaC crearLista3(ListaC lista, char* var, char* op) {
	//recuperamos los registros de las expresiones para la operacion
	char* regArg = recuperaResLC(lista);
	PosicionListaC final = finalLC(lista);
	char arg[16];
	sprintf(arg, "_%s", var);
	//crear op
	Operacion operacion;
	operacion.op = op;
	operacion.res = regArg;
	operacion.arg1 = strdup(arg);
	operacion.arg2 = NULL;  
	//liberamos registros
	liberarReg(regArg);
	// insertar op
	insertaLC(lista, final, operacion);
	return lista;    
}

ListaC crearListaNeg(ListaC lista, char* op){
	char* regArg = recuperaResLC(lista);
	PosicionListaC final = finalLC(lista);
	Operacion operacion;
	operacion.op = op;
	operacion.res = buscarReg();
	operacion.arg1 = regArg;
	operacion.arg2 = NULL;  
	//liberamos registros
	liberarReg(regArg);
	insertaLC(lista, final, operacion);
	guardaResLC(lista, regArg);
	return lista;
}

ListaC listaIf(ListaC cond, ListaC st) {
		//recuperamos los registros de las expresiones
	char* regCond = recuperaResLC(cond);
	char* regSt = recuperaResLC(st);
		//creamos la etiqueta del salto
	char* tag = obtenerEtiqueta();
		//añade beqz
	PosicionListaC final = finalLC(cond);
	Operacion operacion;
	operacion.op = "beqz";
	operacion.res = regCond;
	operacion.arg1 = tag;
	operacion.arg2 = NULL;
	//liberamos registros *¿qué hacemos con el registro res de la lista cond?
	liberarReg(regCond);
		// insertar la op
	insertaLC(cond, final, operacion);
		//concatena listas
	concatenaLC(cond, st);
	liberaLC(st);
	guardaResLC(cond, regSt);
		//insertar etiqueta
	final = finalLC(cond);
	char etq[10];
	sprintf(etq, "%s:", tag);
	Operacion etiqueta;
	etiqueta.op = strdup(etq);
	etiqueta.res = NULL;
	etiqueta.arg1 = NULL;
	etiqueta.arg2 = NULL;
	insertaLC(cond, final, etiqueta);
	return cond;
}

ListaC if_else(ListaC exp, ListaC stat1, ListaC stat2) {	
	//Obtenemos el registro reg de exp para utilizarlo en el beqz
	char* reg1 = recuperaResLC(exp);
	//Creamos la operación beqz y la insertamos en la posición final
	char* et1 = obtenerEtiqueta();
	Operacion beqz;
	beqz.op = "beqz";
	beqz.res = reg1;
	beqz.arg1 = et1;
	beqz.arg2 = NULL;
	insertaLC(exp, finalLC(exp), beqz);
	//Concatenamos exp y stat1 (y la liberamos)
	concatenaLC(exp, stat1);
	liberaLC(stat1);
	//Creamos la operación b y la insertamos en la posición final
	char* et2 = obtenerEtiqueta();
	Operacion b;
	b.op = "b";
	b.res = et2;
	b.arg1 = NULL;
	b.arg2 = NULL;
	insertaLC(exp, finalLC(exp), b);
	//Insertamos et1
	char etq1[10];
	sprintf(etq1, "%s:", et1);
	Operacion etiq1;
	etiq1.op = strdup(etq1);
	etiq1.res = NULL;
	etiq1.arg1 = NULL;
	etiq1.arg2 = NULL;
	insertaLC(exp, finalLC(exp), etiq1);
	//Concatenamos exp y stat2 (y la liberamos)
	concatenaLC(exp, stat2);
	liberaLC(stat2);
	//Insertamos et2
	char etq2[10];
	sprintf(etq2, "%s:", et2);
	Operacion etiq2;
	etiq2.op = strdup(etq2);
	etiq2.res = NULL;
	etiq2.arg1 = NULL;
	etiq2.arg2 = NULL;
	insertaLC(exp, finalLC(exp), etiq2);
	//Liberamos registros
	liberarReg(reg1);
	//Devolvemos la lista
	return exp;
}

ListaC do_while(ListaC stat, ListaC exp){
	//Insertamos et1 al principio de stat
	char* et1 = obtenerEtiqueta();
	char etq1[10];
	sprintf(etq1, "%s:", et1);
	Operacion etiq1;
	etiq1.op = strdup(etq1);
	etiq1.res = NULL;
	etiq1.arg1 = NULL;
	etiq1.arg2 = NULL;
	insertaLC(stat, inicioLC(stat), etiq1);
	//Recuperamos reg de exp
	char* reg = recuperaResLC(exp);
	//Concatenamos exp y stat (y liberamos stat)
	concatenaLC(stat, exp);
	liberaLC(exp);
	//Insertamos bnez al final de la lista
	Operacion bnez;
	bnez.op = "bnez";
	bnez.res = reg;
	bnez.arg1 = et1;
	bnez.arg2 = NULL;
	insertaLC(exp, finalLC(stat), bnez);
	//Devolvemos la lista
	return stat;
}

ListaC while_(ListaC exp, ListaC stat){
	//Insertamos et1 al principio de exp
	char* et1 = obtenerEtiqueta();
	char etq1[10];
	sprintf(etq1, "%s:", et1);
	Operacion etiq1;
	etiq1.op = strdup(etq1);
	etiq1.res = NULL;
	etiq1.arg1 = NULL;
	etiq1.arg2 = NULL;
	insertaLC(exp, inicioLC(exp), etiq1);
	//Obtenemos el registro resultado de exp
	char* reg = recuperaResLC(exp);
	//Creamos la operación beqz y la insertamos en la posición final
	char* et2 = obtenerEtiqueta();
	char etq2[10];
	sprintf(etq2, "%s:", et2);
	Operacion beqz;
	beqz.op = "beqz";
	beqz.res = reg;
	beqz.arg1 = et2;
	beqz.arg2 = NULL;
	insertaLC(exp, finalLC(exp), beqz);
	//Liberamos el registro
	liberarReg(reg);
	//Concatenamos exp y stat (y liberamos stat)
	concatenaLC(exp, stat);
	liberaLC(stat);
	//Creamos la operación b y la insertamos en la posición final
	Operacion b;
	b.op = "b";
	b.res = et1;
	b.arg1 = NULL;
	b.arg2 = NULL;
	insertaLC(exp, finalLC(exp), b);
	//Insertamos et2 al final de exp
	Operacion etiq2;
	etiq2.op = strdup(etq2);
	etiq2.res = NULL;
	etiq2.arg1 = NULL;
	etiq2.arg2 = NULL;
	insertaLC(exp, finalLC(exp), etiq2);
	//Devolvemos la lista
	return exp;
}

ListaC listaPrintItem(char* cadena) {
	ListaC lista = creaLC();
	
	//Buscamos la cadena
	PosicionLista posicion = buscaLS(tablaSimb, cadena);
	Simbolo simbolo = recuperaLS(tablaSimb, posicion);
	
	char str[10];
	sprintf(str, "$str%d", simbolo.valor);
	// añadir el la $a0, $strX
	Operacion op_la;
	op_la.op = "la";
	op_la.res = "$a0";
	op_la.arg1 = strdup(str);
	op_la.arg2 = NULL;
	PosicionListaC final = finalLC(lista);
	insertaLC(lista, final, op_la);
	// añadir el li $v0, 4
	Operacion op_li;
	op_li.op = "li";
	op_li.res = "$v0";
	op_li.arg1 = "4";
	op_li.arg2 = NULL;
	final = finalLC(lista);
	insertaLC(lista, final, op_li);
	Operacion syscall;
	syscall.op = "syscall";
	syscall.res = NULL;
	syscall.arg1 = NULL;
	syscall.arg2 = NULL;
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
	op_move.arg2 = NULL;
	// se libera el registro
	liberarReg(regLista);
	PosicionListaC final = finalLC(lista);
	insertaLC(lista, final, op_move);
	// li $v0, 1
	Operacion op_li;
	op_li.op = "li";
	op_li.res = "$v0";
	op_li.arg1 = "1";
	op_li.arg2 = NULL;
	final = finalLC(lista);
	insertaLC(lista, final, op_li);
	Operacion syscall;
	syscall.op = "syscall";
	syscall.res = NULL;
	syscall.arg1 = NULL;
	syscall.arg2 = NULL;
	final = finalLC(lista);
	insertaLC(lista, final, syscall);
	return lista;
}

ListaC concatena(ListaC l1, ListaC l2){
	// debugLista(l1);
	// debugLista(l2);
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
	op_li.arg2 = NULL;
	PosicionListaC final = finalLC(lista);
	insertaLC(lista, final, op_li);
	Operacion syscall;
	syscall.op = "syscall";
	syscall.res = NULL;
	syscall.arg1 = NULL;
	syscall.arg2 = NULL;
	final = finalLC(lista);
	insertaLC(lista, final, syscall);
	// sw $v0, _X
	char arg[16];
	sprintf(arg, "_%s", cadena);
	Operacion op_sw;
	op_sw.op = "sw";
	op_sw.res = "$v0";
	op_sw.arg1 = strdup(arg);
	op_sw.arg2 = NULL;
	final = finalLC(lista);
	insertaLC(lista, final, op_sw);
	return lista;
}

void debugLista(ListaC lista){
	PosicionListaC aux = inicioLC(lista);
	int n = longitudLC(lista);
	printf("Info de lista:\n Longitud:%d\n",n);
	if (inicioLC(lista)==finalLC(lista)) printf("algo va mal...\n");
	int cont=0;
	while(aux!=finalLC(lista)){
		printf("[%d]\t%s", cont, recuperaLC(lista, aux).op);
		if (recuperaLC(lista, aux).res!=NULL) printf("\t%s",recuperaLC(lista, aux).res);
		if (recuperaLC(lista, aux).arg1!=NULL) printf(",%s",recuperaLC(lista, aux).arg1);
		if (recuperaLC(lista, aux).arg2!=NULL) printf(",%s\n",recuperaLC(lista, aux).arg2);
		else printf("\n");
		cont++; 
		aux = siguienteLC(lista, aux);
	}
	printf("Valor res de la lista: %s\n", recuperaResLC(lista));
}

char* buscarReg()
{
	int i = 0;
	while (registros[i] != 0) i++;
	assert(i < 10);		// si i llega a 10 o más, es porque nos hemos quedado sin registros, se aborta la ejecución.
	registros[i] = 1;
	char registro[4];
	sprintf(registro, "$t%d", i);
	return strdup(registro);
}

//Método para liberar registro
void liberarReg(char* registro) {
  char r = registro[2];
  int reg = r - '0';
  registros[reg] = 0;
}


//Métodos para traducir sentencias
char *obtenerEtiqueta() {
  char aux[32];
  sprintf(aux, "$l%d", tag_counter++);
  return strdup(aux);
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
	if (tipo == STRING) 
	{
		simbolo.valor = contCadenas;
		contCadenas++;
	}
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


void imprimirListaC(ListaC declarations, ListaC statements){
	printf("\n############################\n# Seccion de codigo\n.text\n.globl main\n\nmain:\n");
	//recorrer declarations
	PosicionListaC aux = inicioLC(declarations);
	int n = longitudLC(declarations);
	printf("##LongDeclarations=%d\n",n);
	// if (inicioLC(lista)==finalLC(lista)) printf("algo va mal...\n");
	int cont=0;
	while(aux!=finalLC(declarations)){
		// printf("[%d]\t", cont);		// DEBUG
		printf("%s\t%s, %s", recuperaLC(declarations, aux).op, recuperaLC(declarations, aux).res, recuperaLC(declarations, aux).arg1);
		if (recuperaLC(declarations, aux).arg2!=NULL) printf(", %s\n",recuperaLC(declarations, aux).arg2);
		else printf("\n");
		cont++; 
		aux = siguienteLC(declarations, aux);
	}
	//recorrer statements
	aux = inicioLC(statements);
	n = longitudLC(statements);
	printf("##LongStatements=%d\n",n);
	// if (inicioLC(lista)==finalLC(lista)) printf("algo va mal...\n");
	while(aux!=finalLC(statements)){
		// printf("[%d]\t", cont);		// DEBUG
		printf("%s", recuperaLC(statements, aux).op);
		if (recuperaLC(statements, aux).res!=NULL) printf("\t%s",recuperaLC(statements, aux).res);
		if (recuperaLC(statements, aux).arg1!=NULL) printf(", %s",recuperaLC(statements, aux).arg1);
		if (recuperaLC(statements, aux).arg2!=NULL) printf(", %s\n",recuperaLC(statements, aux).arg2);
		else printf("\n");
		cont++; 
		aux = siguienteLC(statements, aux);
	}
	printf("li\t$v0, 10\nsyscall\n############################\n# Fin de la ejecución ######\n############################\n\n##Regs:");
	int i;for (i=0;i<10;i++) printf("[%d]", registros[i]); printf("\n");	//debug
}
