#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int MAX_STR = 50;

//função em fase de teste
//FILE *abrirImagem(char img[50], char modo[3]);

int main(){
	//declarações de variáveis
	char string[MAX_STR], modo[3];
	//declara, abre e copia a imagem
	FILE *imgEntrada, *imgSaida, *img;
	imgEntrada = fopen("rgb.ppm", "r");		//fazer uma função pra abrir
	imgSaida = fopen("rgb2.ppm", "w");		//fazer uma função pra abrir
	copiaImagem(imgEntrada, imgSaida);
	//fecha as imagens
	fclose(imgEntrada);
	fclose(imgSaida);
/*
	//abrir uma imagem
	printf("Digite o nome da imagem: ");
	fgets(string, MAX_STR, stdin);
	printf("Digite o modo: r ou w: ");
	fgets(modo, 3, stdin);
	imgSaida = abrirImagem(string, modo);
	//res = abrirImagem(string, modo);???
	//imprimir res????
	//fclose(img); ????

	//função: abre um arquivo de imagem -- em fase de testes
	FILE *abrirImagem(char img[50], char modo[3]){	
		FILE *retorno;
		//img = fopen("rgb2.ppm", "r");
		//printf("Digite o nome da imagem: ");
		//fgets(string, MAX_STR, stdin);
		//retorno = fopen(string, "r");
		retorno = fopen(img, modo);
		return retorno;
	}
*/
	printf("\n");
	return 0;
}