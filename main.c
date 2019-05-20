#include <stdio.h>
#include <stdlib.h>
//#include "func.h"
//#include "rotacao.h"
#define MAX 500

typedef struct {
    int r, g, b;
} Pixel;

void menu();
void ler_imagem(Pixel **imagem, char *code, int *max, int *coluna, int *linha);
void filtro_cinza(Pixel **imagem, int coluna, int linha);
void salvar_imagem(Pixel **imagem, char *code, int max, int coluna, int linha);

void alocar_memoria(Pixel **imagem, int coluna, int linha);
void liberar_memoria(Pixel **imagem, int linha);

//função principal
int main() {
    menu();     //chama a função menu

    printf("\nSistema encerrado com suvesso!!!\n");
	printf("\n");
	return 0;
}

/*O programa fica rodando até escolher a opção 0 (sair: opção zero)*/
void menu(){
    Pixel **imagem; //cria uma matriz de pixeis para armazenar a imagem
    char code[3]; //o código para saber se a imagem é ascii ou binária
    int max; //o valor máximo de tonalidade de cada pixel
    int larg, alt; // largura e altura da imagem em pixeis
    int op;
    do{
        system("clear");    //limpa a tela do terminal
        //Escolher a opção desejada
        printf("\nDigite a opção desejada:\n");
        printf("1 - Para aplicar escala de cinza na imagem.\n");
        printf("0 - Para sair.\n");
        scanf("%i", &op);    /*Escolher as opções de filtros*/
        getchar();     //limpa o buffer
        switch (op){
            case 1:
                ler_imagem(imagem, code, &max, &larg, &alt);
         
                //aloca espaço de memória dinamicamente
                alocar_memoria(imagem, larg, alt);               
             
                /* aplicar o filtro de tom de cinzas */
                filtro_cinza(imagem, larg, alt);
                salvar_imagem(imagem, code, max, larg, alt);
               
                //libera o espaço de memória alocado dinamicamente
                liberar_memoria(imagem, alt);
                printf("\nFiltro de cinza aplicado na imagem com sucesso!!!");
                break;
            case 0:
                break;
            default:
                printf("\nOpção inválida!!!");
                getchar();  //mantém a tela aberta até apertar ENTER
                break;
        }
    }while (op != 0);

}

void ler_imagem(Pixel **imagem, char *code, int *max, int *coluna, int *linha) {
    int i, j;

    FILE *arquivo;

    char nome_arq[50];
    printf("entre com o nome do arquivo: \n");
    scanf("%s", nome_arq);

    if ((arquivo = fopen(nome_arq, "r")) == NULL) {
        printf("Erro ao abrir o arquivo %s!!!\n", nome_arq);
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

void filtro_cinza(Pixel **imagem, int coluna, int linha) {
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

void salvar_imagem(Pixel **imagem, char *code, int max, int coluna, int linha) {
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

/* faz a alocação dinâmica de memória da imagem */
void alocar_memoria(Pixel **imagem, int coluna, int linha){
    imagem = calloc(linha, sizeof(int));
    for (int i = 0; i < linha; i++){
        imagem[i] = calloc(coluna, sizeof(int));
    }
}

/* faz a liberação de memória alocada da imagem */
void liberar_memoria(Pixel **imagem, int linha){
    for (int i = 0; i < linha; i++){
        free(imagem[i]);
    }
    free(imagem);
}