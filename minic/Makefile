minic: minic_main.c minic.tab.c lex.yy.c minic.tab.h listaSimbolos.c listaSimbolos.h listaCodigo.c listaCodigo.h
	gcc lex.yy.c minic_main.c minic.tab.c listaSimbolos.c listaCodigo.c -lfl -o minic

minic.tab.c minic.tab.h: minic.y listaSimbolos.h listaCodigo.h
	bison -d minic.y

lex.yy.c: minic.l
	flex minic.l

limpiar:
	rm lex.yy.c minic.tab.c minic.tab.h minic

