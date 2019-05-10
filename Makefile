secao_1: FUNC
	gcc main.c func.o -o a.out
	./a.out
FUNC:
	gcc -c func.c