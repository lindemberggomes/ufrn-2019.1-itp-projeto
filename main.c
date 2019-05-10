#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int main(){
	//declara, abre e copia a imagem
	FILE *imgEntrada, *imgSaida;
	imgEntrada = fopen("teste.txt", "r");
	imgSaida = fopen("teste2.txt", "w");
	copiaImagem(imgEntrada, imgSaida);
	//fecha as imagens
	fclose(imgEntrada);
	fclose(imgSaida);

	printf("\n");
	return 0;
}