%{
#include <stdio.h>
#include "listaSimbolos.h"
#include "listaCodigo.h"
#include <string.h>

Lista tablaSimb;
int contCadenas=0;
Tipo tipo;
int perteneceTablaS(char *lexema);
void anadeEntrada(char *lexema, Tipo tipo);
int esConstante(char *lexema);
void imprimirTablaS();
ListaC imprimirListaC(ListaC declarations, ListaC statements);

char* buscarReg();
ListaC crearLista(char* arg1, char* op);
ListaC crearLista2(ListaC lista, ListaC arg2, char* op);
ListaC crearLista3(ListaC lista, char* var, char* op);
ListaC crearListaNeg(ListaC lista, char* op);
ListaC listaIf(ListaC cond, ListaC st);
ListaC if_else(ListaC exp, ListaC stat1, ListaC stat2);
ListaC listaPrintItem(int cadena);
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

%token VOID VAR CONST IF ELSE WHILE PRINT READ SEMICOLON COMA IGUAL APAR CPAR ACOR CCOR
//Indicamos el tipo de los tokens
%token <cadena> CADENA ID NUM
%type <codigo> expression statement statement_list print_item print_list read_list program declarations asig identifier_list 
//Establecemos la precedencia y la asociatividad (una línea tiene más precedencia que las líneas anteriores)
%left MAS MENOS
%left POR DIV
%left UMENOS

%%

program : {tablaSimb=creaLS();} VOID ID APAR CPAR ACOR declarations statement_list CCOR	{imprimirTablaS(); liberaLS(tablaSimb); imprimirListaC($7, $8);}
        ;

declarations : declarations VAR {tipo=VARIABLE;} identifier_list SEMICOLON			{$$=concatena($1, $4);}
             | declarations CONST {tipo=CONSTANTE;} identifier_list SEMICOLON		{$$=concatena($1, $4);}
             | /*empty*/			{printf("Aplica declarations -> lambda \n");$$=creaLC();}
             ;

identifier_list : asig							{$$ = $1;}
                | identifier_list COMA asig		{$$ = concatena($1, $3);}
                ;

asig : ID			                  	{if (!perteneceTablaS($1)) anadeEntrada($1,tipo); else printf("Error en línea %d: variable %s ya declarada\n",yylineno,$1); $$ = creaLC();}
     | ID IGUAL expression	    		{if (!perteneceTablaS($1)) anadeEntrada($1,tipo); else printf("Error en línea %d: variable %s ya declarada\n",yylineno,$1); $$ = crearLista3($3, $1, "sw");}
     ;

statement_list : statement_list statement		{$$ = concatena($1, $2);}
               | /*empty*/						{$$ = creaLC();printf("Aplica statement_list -> lambda \n");}
               ;

statement : ID IGUAL expression SEMICOLON			  {if (!perteneceTablaS($1)) printf("Error en línea %d: variable %s no declarada\n",yylineno,$1); else if (esConstante($1)) printf("Error en línea %d: asignación a constante %s\n",yylineno,$1); $$ = crearLista3($3, $1, "sw");}
          | ACOR statement_list CCOR
          | IF APAR expression CPAR statement ELSE statement
          | IF APAR expression CPAR statement   {$$ = listaIf($3, $5);}
          | WHILE APAR expression CPAR statement{{printf("Aplica while \n");}}
          | PRINT print_list SEMICOLON          {$$ = $2;}
          | READ read_list SEMICOLON            {$$ = $2;}
          ;

print_list : print_item                         {$$ = $1;}
           | print_list COMA print_item         {$$ = concatena($1, $3);}
           ;

print_item : expression              		{$$ = listaPrintExpresion($1);}
           | CADENA		               		{anadeEntrada($1,STRING); $$ = listaPrintItem(contCadenas); contCadenas++;}
           ;

read_list : ID				             	{if (!perteneceTablaS($1)) printf("Error en línea %d: variable %s no declarada\n",yylineno,$1); else if (esConstante($1)) printf("Error en línea %d: asignación a constante %s\n",yylineno,$1); $$ = listaRead($1);}
          | read_list COMA ID		    	{if (!perteneceTablaS($3)) printf("Error en línea %d: variable %s no declarada\n",yylineno,$3); else if (esConstante($3)) printf("Error en línea %d: asignación a constante %s\n",yylineno,$3); $$ = concatena($1, listaRead($3));}
          ;

expression : expression MAS expression	  	  {$$ = crearLista2($1, $3, "add");}
           | expression MENOS expression	  {$$ = crearLista2($1, $3, "sub");}
           | expression POR expression		  {$$ = crearLista2($1, $3, "mul");}
           | expression DIV expression		  {$$ = crearLista2($1, $3, "div");}
           | MENOS expression %prec UMENOS	  {$$ = crearListaNeg($2, "neg");}
           | APAR expression CPAR		  	    {$$ = $2;}	// como la expresion ya es una listaC, no hace falta crear otra listaC
           | ID								    {if (!perteneceTablaS($1)) printf("Error en línea %d: variable %s no declarada\n",yylineno,$1);$$ = crearLista($1, "lw");}
           | NUM							    {$$ = crearLista($1, "li");}          	
		   										
           ;

%%

void yyerror()
{
  	printf("Se ha producido un error en esta expresion\n");
}

ListaC crearLista(char* arg1, char* op)		// esto vale para id y num, solo cambia el tipo de op (li o lw)
{
  	printf("crearLista %s\n", op);            //debug

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
		operacion.arg1 = arg;
	}
	else {operacion.arg1 = arg1;}
	operacion.arg2 = NULL;
	//Insertamos la operación en la lista
	insertaLC(lista, inicio, operacion);
	guardaResLC(lista, registro);
	printf("%s\t%s,%s\n",operacion.op, operacion.res, operacion.arg1);   //debug
	int i;for (i=0;i<10;i++) printf("[%d]", registros[i]); printf(" %s\n\n", recuperaResLC(lista));    //debug
	return lista;
}

ListaC crearLista2(ListaC lista, ListaC arg2, char* op) {
	printf("crearLista2 %s\n", op);                 //debug

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
	printf("%s\t%s,%s,%s\n",operacion.op, operacion.res, operacion.arg1, operacion.arg2);   //debug
	//liberamos registros
	liberarReg(regArg1);
	liberarReg(regArg2);
	//insertar la op al final de la lista
	insertaLC(lista, final, operacion);
	guardaResLC(lista, registro);
	int i;  for (i=0;i<10;i++) printf("[%d]", registros[i]); printf("\n");    //debug
	return lista;
}

ListaC crearLista3(ListaC lista, char* var, char* op) {
	printf("crearLista3\n");                 //debug

	//recuperamos los registros de las expresiones para la operacion
	char* regArg = recuperaResLC(lista);
	PosicionListaC final = finalLC(lista);
	char arg[16];
	sprintf(arg, "_%s", var);
	//crear op
	Operacion operacion;
	operacion.op = op;
	operacion.res = regArg;
	operacion.arg1 = arg;
	operacion.arg2 = NULL;  
	//liberamos registros
	liberarReg(regArg);
	printf("%s\t%s,%s\n",operacion.op, operacion.res, operacion.arg1);   //debug
	// insertar op
	insertaLC(lista, final, operacion);
	int i;for (i=0;i<10;i++) printf("[%d]", registros[i]); printf("\n");    //debug
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
	printf("%s\t%s,%s\n",operacion.op, operacion.res, operacion.arg1);   //debug
	insertaLC(lista, final, operacion);
	guardaResLC(lista, regArg);
	int i;for (i=0;i<10;i++) printf("[%d]", registros[i]); printf("\n");    //debug
	return lista;
}

ListaC listaIf(ListaC cond, ListaC st) {
	printf("listaIf\n");                                //debug
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
	//liberamos registros ¿se libera el regCond que decide el salto? ¿qué hacemos con el registro res de la lista cond? ¿con cual nos quedamos?
	liberarReg(regCond);
		// insertar la op
	insertaLC(cond, final, operacion);
		//concatena listas
	concatenaLC(cond, st);
	liberaLC(st); 
	// guardaResLC(cond, regSt);
		//insertar etiqueta
	final = finalLC(cond);
	Operacion etiqueta;
	char* etq;
	sprintf(etq, "%s:", tag);
	etiqueta.op = etq;
	etiqueta.res = NULL;
	etiqueta.arg1 = NULL;
	etiqueta.arg2 = NULL;
	insertaLC(cond, final, etiqueta);
	int i;for (i=0;i<10;i++) printf("[%d]", registros[i]); printf("\n");    //debug
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
	b.res = NULL;
	b.arg1 = et2;
	b.arg2 = NULL;
	insertaLC(exp, finalLC(exp), b);
	//Insertamos et1
	Operacion etiq1;
	etiq1.op = et1;
	etiq1.res = NULL;
	etiq1.arg1 = NULL;
	etiq1.arg2 = NULL;
	insertaLC(exp, finalLC(exp), etiq1);
	//Concatenamos exp y stat2 (y la liberamos)
	concatenaLC(exp, stat2);
	liberaLC(stat2);
	//Insertamos et2
	Operacion etiq2;
	etiq2.op = et2;
	etiq2.res = NULL;
	etiq2.arg1 = NULL;
	etiq2.arg2 = NULL;
	insertaLC(exp, finalLC(exp), etiq2);
	//Liberamos registros
	liberarReg(reg1);
	//Devolvemos la lista
	return exp;
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
	op_la.arg2 = NULL;

	PosicionListaC final = finalLC(lista);
	insertaLC(lista, final, op_la);
	// li $v0, 4
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
	int i;for (i=0;i<10;i++) printf("[%d]", registros[i]); printf("\n");    //debug
	return lista; 
}

ListaC listaPrintExpresion(ListaC lista) {
	printf("listaPrintExpresion\n");           //debug
	char* regLista = recuperaResLC(lista);
	//move $a0, $tX
	Operacion op_move;
	op_move.op = "move";
	op_move.res = "$a0";
	op_move.arg1 = regLista;
	op_move.arg2 = NULL;
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
	op_li.arg2 = NULL;
	final = finalLC(lista);
	insertaLC(lista, final, op_li);
	Operacion syscall;
	syscall.op = "syscall";
	final = finalLC(lista);
	insertaLC(lista, final, syscall);
	int i;for (i=0;i<10;i++) printf("[%d]", registros[i]); printf("\n");    //debug
	return lista;
}

ListaC concatena(ListaC l1, ListaC l2){
	printf("concatena\n");           //debug
	concatenaLC(l1, l2);
	liberaLC(l2);
	return l1;
}

ListaC listaRead(char* cadena){
	printf("listaRead\n");           //debug
	printf("%s\n", cadena);          //debug
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
	syscall.res = NULL;
	syscall.arg1 = NULL;
	syscall.arg2 = NULL;
	final = finalLC(lista);
	insertaLC(lista, final, syscall);
	// sw $v0, _X
	Operacion op_sw;
	op_sw.op = "sw";
	op_sw.res = "$v0";
	char arg[16];
	sprintf(arg, "_%s", cadena);
	printf("%s\n", arg);                      //debug
	op_sw.arg1 = arg;
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
	while(siguienteLC(lista, aux)!=NULL){
		printf("[%d]\t%s\t%s,%s", cont, recuperaLC(lista, siguienteLC(lista, aux)).op, recuperaLC(lista, siguienteLC(lista, aux)).res, recuperaLC(lista, siguienteLC(lista, aux)).arg1);
		if (recuperaLC(lista, siguienteLC(lista, aux)).arg2!=NULL) printf(",%s\n",recuperaLC(lista, siguienteLC(lista, aux)).arg2);
		else printf("\n");
		cont++; 
		aux = siguienteLC(lista, aux);
	}
}

char* buscarReg()
{
	int i = 0;
	while (registros[i] != 0) i++;

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


ListaC imprimirListaC(ListaC declarations, ListaC statements){
	printf("\n############################\n# Seccion de codigo\n.text\n.globl main\n\nmain:\n");
	//recorrer declarations
	PosicionListaC aux = inicioLC(declarations);
	int n = longitudLC(declarations);
	printf("##LongDec=%d\n",n);
	// if (inicioLC(lista)==finalLC(lista)) printf("algo va mal...\n");
	int cont=0;
	while(aux!=finalLC(declarations)){
		printf("[%d]\t%s\t%s,%s", cont, recuperaLC(declarations, aux).op, recuperaLC(declarations, aux).res, recuperaLC(declarations, aux).arg1);
		if (recuperaLC(declarations, aux).arg2!=NULL) printf(",%s\n",recuperaLC(declarations, aux).arg2);
		else printf("\n");
		cont++; 
		aux = siguienteLC(declarations, aux);
	}
	//recorrer statements
	aux = inicioLC(statements);
	n = longitudLC(statements);
	printf("##LongDec=%d\n",n);
	// if (inicioLC(lista)==finalLC(lista)) printf("algo va mal...\n");
	while(aux!=finalLC(statements)){
		printf("[%d]\t%s\t%s,%s", cont, recuperaLC(statements, aux).op, recuperaLC(statements, aux).res, recuperaLC(statements, aux).arg1);
		if (recuperaLC(statements, aux).arg2!=NULL) printf(",%s\n",recuperaLC(statements, aux).arg2);
		else printf("\n");
		cont++; 
		aux = siguienteLC(statements, aux);
	}
}