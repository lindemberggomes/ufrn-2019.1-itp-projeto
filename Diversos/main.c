#include <stdlib.h>
#include <stdio.h>
#define MAX 500

typedef struct {
    int r, g, b;
} pixel;

void ler_ascii(pixel imagem[MAX][MAX], char *code, int *max, int *coluna, int *linha);
void salvar_ascii(pixel imagem[MAX][MAX], char *code, int max, int coluna, int linha);
void gray_scale(pixel imagem[MAX][MAX], int coluna, int linha);
void autorelevo(pixel imagem[MAX][MAX], int coluna, int linha);
void espelhar(pixel imagem[MAX][MAX], int coluna, int linha);

int main(int argc, char** argv) {
    pixel imagem[MAX][MAX]; //cria uma matriz de pixeis para armazenar a imagem
    char code[3]; //o código para saber se a imagem é ascii ou binária
    int max; //o valor máximo de tonalidade de cada pixel
    int larg, alt; // largura e altura da imagem em pixeis

    ler_ascii(imagem, code, &max, &larg, &alt);
    gray_scale(imagem, larg, alt);
    //autorelevo(imagem, larg, alt);
    //espelhar(imagem, larg, alt);
    salvar_ascii(imagem, code, max, larg, alt);

    return 0;
}

void ler_ascii(pixel imagem[MAX][MAX], char *code, int *max, int *coluna, int *linha) {
    int i, j;
    FILE *arquivo;

    char nome_arq[50];
    printf("entre com o nome do arquivo: \n");
    scanf("%s", nome_arq);

    if ((arquivo = fopen(nome_arq, "r")) == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arq);
        exit(1);
    }

    fscanf(arquivo, "%s", code);
    fscanf(arquivo, "%d", coluna);
    fscanf(arquivo, "%d", linha);
    fscanf(arquivo, "%d", max);

    for (i = 0; i < *linha; i++) {
        for (j = 0; j < *coluna; j++) {
            fscanf(arquivo, "%d", &imagem[i][j].r);
            fscanf(arquivo, "%d", &imagem[i][j].g);
            fscanf(arquivo, "%d", &imagem[i][j].b);
        }
    }

    fclose(arquivo);
}

void salvar_ascii(pixel imagem[MAX][MAX], char *code, int max, int coluna, int linha) {
    int i, j;
    FILE *arquivo;

    char nome_arq[50];
    printf("entre com o nome que deseja salvar: \n");
    scanf("%s", nome_arq);

    arquivo = fopen(nome_arq, "w");

    fprintf(arquivo, "P3\n");
    fprintf(arquivo, "%d\n ", coluna);
    fprintf(arquivo, "%d\n", linha);
    fprintf(arquivo, "%d\n", max);

    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            fprintf(arquivo, "%d ", imagem[i][j].r);
            fprintf(arquivo, "%d ", imagem[i][j].g);
            fprintf(arquivo, "%d\n", imagem[i][j].b);
        }
    }

    fclose(arquivo);
}

void gray_scale(pixel imagem[MAX][MAX], int coluna, int linha) {
    int i, j;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            imagem[i][j].r = (int) ((0.299 * imagem[i][j].r) + (0.587 * imagem[i][j].g) + (0.144 * imagem[i][j].b)); //calcula o valor para conversão
            imagem[i][j].g = imagem[i][j].r; //copia o valor para
            imagem[i][j].b = imagem[i][j].r; //todas componentes

            //testa o valor para ver se o mesmo não passou de 255
            if (imagem[i][j].r > 255) {
                imagem[i][j].r = 255;
                imagem[i][j].g = 255;
                imagem[i][j].b = 255;

            }

        }
    }
}

void autorelevo(pixel imagem[MAX][MAX], int coluna, int linha) {
    pixel img[linha][coluna];
    int i, j;
    for (i = 1; i < linha - 1; i++) {
        for (j = 0; j < coluna; j++) {
            img[i][j].r = imagem[i + 1][j].r - imagem[i - 1][j].r;
            img[i][j].g = imagem[i + 1][j].b - imagem[i - 1][j].b;
            img[i][j].b = imagem[i + 1][j].b - imagem[i - 1][j].b;

            if (img[i][j].r < 0)
                img[i][j].r *= -1;

            if (img[i][j].g < 0)
                img[i][j].g *= -1;

            if (img[i][j].b < 0)
                img[i][j].b *= -1;


        }
    }

    for (i = 1; i < linha - 1; i++) {
        for (j = 0; j < coluna; j++) {

            imagem[i][j].r = img[i][j].r + 128;
            imagem[i][j].g = img[i][j].g + 128;
            imagem[i][j].b = img[i][j].b + 128;

            if (img[i][j].r > 255)
                img[i][j].r = 255;

            if (img[i][j].g > 255)
                img[i][j].g = 255;

            if (img[i][j].b > 255)
                img[i][j].b = 255;




        }
    }
}

void espelhar(pixel imagem[MAX][MAX], int coluna, int linha) {
    pixel img[linha][coluna];
    int i, j;

    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            img[i][j].r = imagem[i][coluna - j].r; //salva em uma matriz do tipo pixel a imagem com suas 
            img[i][j].g = imagem[i][coluna - j].g; //linhas salvas em complementos, isso faz com que a imagem
            img[i][j].b = imagem[i][coluna - j].b; //pegue o pixel complementar no seu extremo oposto horizonal 
        }
    }

    //passa a imagem para a matriz original
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            imagem[i][j].r = img[i][j].r;
            imagem[i][j].g = img[i][j].g;
            imagem[i][j].b = img[i][j].b;   
        }
    }
}