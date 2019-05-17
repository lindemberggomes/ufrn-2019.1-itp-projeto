#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "rotacao.h"

typedef struct {
    int r, g, b;
} pixel;

int MAX_STR = 50, MAX_VTR = 1000, MAX = 500;

int main(int argc, char** argv){
	//declara, abre e copia a imagem
	FILE *imgEntrada, *imgSaida, *img;
	imgEntrada = fopen("rgb.ppm", "r");		//fazer uma função pra abrir
	imgSaida = fopen("rgb2.ppm", "w");		//fazer uma função pra abrir
	copiaImagem(imgEntrada, imgSaida);
	//fecha as imagens
	fclose(imgEntrada);
	fclose(imgSaida);

	/* aplicar o filtro de tom de cinzas */
    pixel imagem[MAX][MAX]; //cria uma matriz de pixeis para armazenar a imagem
    char code[3]; //o código para saber se a imagem é ascii ou binária
    int max; //o valor máximo de tonalidade de cada pixel
    int larg, alt; // largura e altura da imagem em pixeis

    ler_ascii(imagem, code, &max, &larg, &alt);
    gray_scale(imagem, larg, alt);
    //autorelevo(imagem, larg, alt);
    //espelhar(imagem, larg, alt);
    salvar_ascii(imagem, code, max, larg, alt);

	printf("\n");
	return 0;
}