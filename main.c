#include <stdio.h>
#include <stdlib.h>
//#include "func.h"
//#include "rotacao.h"
#define MAX 500

typedef struct {
    int r, g, b;
} Pixel;

typedef struct {
    int col, lin;
    Pixel **matriz;
} Imagem;

void menu();
void ler_imagem(Imagem imagem, char *code, int *max, int *coluna, int *linha);
void filtro_cinza(Imagem imagem, int coluna, int linha);
void salvar_imagem(Imagem imagem, char *code, int max, int coluna, int linha);

void alocar_memoria(Imagem imagem);
void liberar_memoria(Imagem imagem);

//função principal
int main() {
    menu();     //chama a função menu
    printf("\nSistema encerrado com suvesso!!!\n");
	printf("\n");
	return 0;
}

/*O programa fica rodando até escolher a opção 0 (sair: opção zero)*/
void menu(){
    Imagem imagem; //declara matriz de pixeis que armazena a imagem
    char code[3]; //o código para saber se a imagem é ascii ou binária
    int max; //valor máximo de cada pixel
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
          
                /* aplicar o filtro de tom de cinzas */
                filtro_cinza(imagem, larg, alt);
                salvar_imagem(imagem, code, max, larg, alt);
               
                //libera o espaço de memória alocado dinamicamente
                liberar_memoria(imagem);
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

void ler_imagem(Imagem imagem, char *code, int *max, int *coluna, int *linha) {
    int i, j;

    FILE *arquivo;

    char nome_arq[50];
    printf("Digite o nome do arquivo de imagem: \n");
    scanf("%s", nome_arq);

    if ((arquivo = fopen(nome_arq, "r")) == NULL) {
        printf("Erro ao abrir o arquivo %s!!!\n", nome_arq);
        exit(1);
    }

    fscanf(arquivo, "%s", code);
    fscanf(arquivo, "%d", coluna);
    fscanf(arquivo, "%d", linha);
    fscanf(arquivo, "%d", max);

    //aloca espaço de memória dinamicamente
    imagem.col = *coluna;
    imagem.lin = *linha;

/* -----------TESTE: ok------------*/
    printf("---Teste: imagem.col = %i\n", imagem.col);
    printf("---Teste: imagem.lin = %i\n", imagem.lin);
//------------FIM TESTE------------

    alocar_memoria(imagem);               

/* -----------TESTE: ok------------*/
    printf("---teste: ATEH AQUI OK---\n");
//------------FIM TESTE------------

    for (i = 0; i < *linha; i++) {
        for (j = 0; j < *coluna; j++) {
            fscanf(arquivo, "%d", &imagem.matriz[i][j].r);
            fscanf(arquivo, "%d", &imagem.matriz[i][j].g);
            fscanf(arquivo, "%d", &imagem.matriz[i][j].b);
        }
    }


/* -----------TESTE: bug------------*/
    printf("---Teste: imagem.matriz[0][0] = %i\n", imagem.matriz[0][0]);
    printf("---Teste: imagem.matriz[0][1] = %i\n", imagem.matriz[0][1]);
    printf("---Teste: imagem.matriz[0][2] = %i\n", imagem.matriz[0][2]);
//------------FIM TESTE------------



    fclose(arquivo);
}

void filtro_cinza(Imagem imagem, int coluna, int linha) {
    int i, j;
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            imagem.matriz[i][j].r = (int) ((0.299 * imagem.matriz[i][j].r) + (0.587 * imagem.matriz[i][j].g) + (0.144 * imagem.matriz[i][j].b)); //calcula o valor para conversão
            imagem.matriz[i][j].g = imagem.matriz[i][j].r; //copia o valor para
            imagem.matriz[i][j].b = imagem.matriz[i][j].r; //todas componentes
            //testa o valor para ver se o mesmo não passou de 255
            if (imagem.matriz[i][j].r > 255) {
                imagem.matriz[i][j].r = 255;
                imagem.matriz[i][j].g = 255;
                imagem.matriz[i][j].b = 255;
            }
        }
    }
}

void salvar_imagem(Imagem imagem, char *code, int max, int coluna, int linha) {
    int i, j;
    FILE *arquivo;

    char nome_arq[50];
    printf("Digite o nome da imagem que deseja salvar: \n");
    scanf("%s", nome_arq);

    arquivo = fopen(nome_arq, "w");

    fprintf(arquivo, "P3\n");
    fprintf(arquivo, "%d\n ", coluna);
    fprintf(arquivo, "%d\n", linha);
    fprintf(arquivo, "%d\n", max);

    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            fprintf(arquivo, "%d ", imagem.matriz[i][j].r);
            fprintf(arquivo, "%d ", imagem.matriz[i][j].g);
            fprintf(arquivo, "%d\n", imagem.matriz[i][j].b);
        }
    }
    fclose(arquivo);
}

/* faz a alocação dinâmica de memória da imagem */
void alocar_memoria(Imagem imagem){
    imagem.matriz = (Pixel**)calloc(imagem.lin, sizeof(Pixel*));
    for (int i = 0; i < imagem.lin; i++){
        imagem.matriz[i] = (Pixel*)calloc(imagem.col, sizeof(Pixel));
    }
}

/* faz a liberação de memória alocada da imagem */
void liberar_memoria(Imagem imagem){
    for (int i = 0; i < imagem.lin; i++){
        free(imagem.matriz[i]);
    }
    free(imagem.matriz);
}