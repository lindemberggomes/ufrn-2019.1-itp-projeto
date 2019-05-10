#include <stdio.h>
#include <stdlib.h>

//copia a imagem para outro arquivo
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