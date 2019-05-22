#include <stdio.h>
#include <stdlib.h>
//#include "menu.h"
//#include "rotacao.h"

typedef struct {
    int r, g, b;
} Pixel;

typedef struct {
    char code[3];
    int col, lin, ton;
    Pixel **matriz;
} Imagem;

void menu();
void ler_imagem(Imagem *imagem);
void filtro_cinza(Imagem *imagem);
void salvar_imagem(Imagem *imagem);

void alocar_memoria(Imagem *imagem);
void liberar_memoria(Imagem *imagem);

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
                ler_imagem(&imagem);
                /* aplicar o filtro de tom de cinzas */
                filtro_cinza(&imagem);
                salvar_imagem(&imagem);
                //libera o espaço de memória alocado dinamicamente
                liberar_memoria(&imagem);
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

void ler_imagem(Imagem *imagem) {
    int i, j;

    FILE *arquivo;

    char nome_arq[50];
    printf("Digite o nome do arquivo de imagem: \n");
    scanf("%s", nome_arq);

    if ((arquivo = fopen(nome_arq, "r")) == NULL) {
        printf("Erro ao abrir o arquivo %s!!!\n", nome_arq);
        exit(1);
    }

    fscanf(arquivo, "%s", imagem->code);
    fscanf(arquivo, "%d", &imagem->col);
    fscanf(arquivo, "%d", &imagem->lin);
    fscanf(arquivo, "%d", &imagem->ton);

    alocar_memoria(imagem);               

    //ler o conteúdo da imagem (pixel r,g,b)
    for (i = 0; i < imagem->lin; i++) {
        for (j = 0; j < imagem->col; j++) {
            fscanf(arquivo, "%d", &imagem->matriz[i][j].r);
            fscanf(arquivo, "%d", &imagem->matriz[i][j].g);
            fscanf(arquivo, "%d", &imagem->matriz[i][j].b);
        } 
    }
    fclose(arquivo);
}

void filtro_cinza(Imagem *imagem) {
    int i, j;
    for (i = 0; i < imagem->lin; i++) {
        for (j = 0; j < imagem->col; j++) {
            imagem->matriz[i][j].r = (int) (((imagem->matriz[i][j].r) + (imagem->matriz[i][j].g) + (imagem->matriz[i][j].b))/3); //calcula o valor para conversão
            imagem->matriz[i][j].g = imagem->matriz[i][j].r; //copia o valor para
            imagem->matriz[i][j].b = imagem->matriz[i][j].r; //todos membros r, g, b
        }
    }
}

void salvar_imagem(Imagem *imagem) {
    int i, j;
    FILE *arquivo;

    char nome_arq[50];
    printf("Digite o nome da imagem que deseja salvar: \n");
    scanf("%s", nome_arq);

    arquivo = fopen(nome_arq, "w");

    fprintf(arquivo, "P3\n");
    fprintf(arquivo, "%d\n ", imagem->col);
    fprintf(arquivo, "%d\n", imagem->lin);
    fprintf(arquivo, "%d\n", imagem->ton);

    for (i = 0; i < imagem->lin; i++) {
        for (j = 0; j < imagem->col; j++) {
            fprintf(arquivo, "%d ", imagem->matriz[i][j].r);
            fprintf(arquivo, "%d ", imagem->matriz[i][j].g);
            fprintf(arquivo, "%d\n", imagem->matriz[i][j].b);
        }
    }
    fclose(arquivo);
}

/* faz a alocação dinâmica de memória da imagem */
void alocar_memoria(Imagem *imagem){
    imagem->matriz = (Pixel**)calloc(imagem->lin, sizeof(Pixel*));
    for (int i = 0; i < imagem->lin; i++){
        imagem->matriz[i] = (Pixel*)calloc(imagem->col, sizeof(Pixel));
    }
}

/* faz a liberação de memória alocada da imagem */
void liberar_memoria(Imagem *imagem){
    for (int i = 0; i < imagem->lin; i++){
        free(imagem->matriz[i]);
    }
    free(imagem->matriz);
}