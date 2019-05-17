#include <stdio.h>
#include <stdlib.h>
#include "func.h"
/*
	Esta função copia a imagem para outro arquivo.
	A cópia é feita caracter por caracter da imagem de entrada
	para a imagem de saída.
*/
void copiaImagem(FILE *imgEntrada, FILE *imgSaida){
	if (imgEntrada == NULL){
		printf("Não foi possível abrir o arquivo!!!\n");
	}else{
		char c;
		while((c = getc(imgEntrada)) != EOF){
			putc(c, imgSaida);
		}
		printf("\nArquivo copiado com sucesso!!!\n");
	}
}