#include <stdio.h
#include <stdlib.h>

#define MAX 500
/* Definição das estruturas */
typedef struct {
    int r, g, b;
} pixel;
/* Definição das funções */
//ler a imagem quando tá no padrão ascii
void ler_ascii(pixel imagem[MAX][MAX], char *code, int *max, int *coluna, int *linha);
//salva a imagem em ascii
void salvar_ascii(pixel imagem[MAX][MAX], char *code, int max, int coluna, int linha);
//transformar a imagem em tons de cinzas
void gray_scale(pixel imagem[MAX][MAX], int coluna, int linha);
//filtro de auto relevo
void autorelevo(pixel imagem[MAX][MAX], int coluna, int linha);
//espelhamento
void espelhar(pixel imagem[MAX][MAX], int coluna, int linha);
/*
    A função main contém a criação das variáveis e da matriz imagens.
    A matriz imagem é composta pelo tipo pixel, que por sua vez abriga 
    em sua estrutura três inteiros, r, g, b, cada um contendo um tom,
    como foi anteriormente mencionado. Fora isso, ela tem apenas as
    chamadas de funções, que serão explicadas a seguir. 
*/
int main(int argc, char** argv) {
    pixel imagem[MAX][MAX]; //cria uma matriz de pixeis para armazenar a imagem
    char code[3]; //o código para saber se a imagem é ascii ou binária
    int max; //o valor máximo de tonalidade de cada pixel
    int larg, alt; // largura e altura da imagem em pixeis
   
    return 0;
}
/*
    A função ler_ascii faz a leitura do arquivo quando está no
    formato ascii. 
*/
void ler_ascii(pixel imagem[MAX][MAX], char *code, int *max, int *coluna, int *linha) {
    int i, j;
    FILE *arquivo;

    char nome_arq[50];
    printf("entre com o nome do arquivo\n");
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
/*
    O funcionamento dela é simples de entender, primeiro pega o
    código da imagem, depois as dimensões e por fim o valor máximo,
    após isso entra em um loop que percorre a matriz salvando 
    cada tom de cada pixel na estrutura imagem.
*/
/*
    A função salvar_ascii salva o arquivo no padrão ascii. 
*/
void salvar_ascii(pixel imagem[MAX][MAX], char *code, int max, int coluna, int linha) {
    int i, j;
    FILE *arquivo;

    char nome_arq[50];
    printf("entre com o nome que deseja salvar: \n");
    scanf("%s", nome_arq);

    arquivo = fopen(nome_arq, "w");

    fprintf (arquivo, "P3\n");
    fprintf (arquivo, "%d\n ", coluna);
    fprintf (arquivo, "%d\n", linha);
    fprintf (arquivo, "%d\n", max);

    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            fprintf(arquivo, "%d ", imagem[i][j].r);
            fprintf(arquivo, "%d ", imagem[i][j].g);
            fprintf(arquivo, "%d\n", imagem[i][j].b);
        }
    }

    fclose(arquivo);
}
/*
    Parecida com a anterior, as diferenças estão na passagem dos
    valores que é feita por parâmetro e não por referência já que 
    as mesmas não serão alteradas. Outra coisa diferente é que o
    "code" da imagem já é salvo como P3, e não pega o char code,
    pois isso evita o erro ao salvarmos uma imagem de um arquivo 
    aberto que estava em binário. 
*/
/* F I L T R O S *
/*
    Começaremos com um filtro que transforma uma imagem colorida
    em uma imagem com tons de cinza, famoso "B&W" ou em português, 
    branco e preto, que na verdade é chamado assim incorretamente.
    Para converter qualquer cor em seu nível aproximado de cinza, 
    deve-se primeiro obter suas primitivas vermelho, verde e azul
    (da escala RGB). Adiciona-se então 30% do vermelho mais 59% 
    do verde mais 11% do azul, independente da escala utilizada
    (0.0 a 1.0, 0 a 255, 0% a 100%.). No código serão valores 
    com melhor precisão, para não escaparem cores fracas.
*/
void gray_scale(pixel imagem[MAX][MAX], int coluna, int linha) {
    int i, j;
    for (i = 0; i < linha; i++){
        for (j = 0; j < coluna; j++){
            imagem[i][j].r = (int) ((0.299 * imagem[i][j].r) + (0.587 * imagem[i][j].g) + (0.144 * imagem[i][j].b)); //calcula o valor para conversÃ£o
            imagem[i][j].g = imagem[i][j].r; //copia o valor para
            imagem[i][j].b = imagem[i][j].r; //todas componentes

            //testa o valor para ver se o mesmo não passou de 255
            if (imagem[i][j].r > 255){
                imagem[i][j].r = 255;
                imagem[i][j].g = 255;
                imagem[i][j].b = 255;
            }
        }
    }
}
/*
    O código em si é bem simples, apenas calcula a regra mostrada 
    anteriormente e depois distribui para todos três componentes 
    dos pixeis. E também confere, caso no calculo, algum dos pixeis
    acabem passando de 255.
*/
/*
    O segundo filtro será o filtro de auto relevo, que é usado para
    fazer macas d'água em papéis e outros tipos de materiais 
    timbrados. Para o calculo dele, pegamos uma variável qualquer
    e subtraímos de sua variável de posição oposta, e este valor
    substitui a central, escolhi fazer isso com as variáveis das
    linhas anteriores e posteriores, mas poderia ser feito com 
    as da lateral, ou até mesmo diagonal. 
*/
void autorelevo(pixel imagem[MAX][MAX], int coluna, int linha) {
    pixel img[linha][coluna]; // cria uma imagem para salvar o resultado do emboss
    int i, j;
    for (i = 1; i < linha - 1; i++){
        for (j = 0; j < coluna; j++){
            img[i][j].r = imagem[i + 1][j].r - imagem[i -1][j].r; //faz a operação passando o 
            img[i][j].g = imagem[i + 1][j].b - imagem[i -1][j].b; //resultado para a matriz de
            img[i][j].b = imagem[i + 1][j].b - imagem[i -1][j].b; //backup

            if (img[i][j].r < 0) //testa os limites
                img[i][j].r = 0;

            if (img[i][j].g < 0)
                img[i][j].g = 0;

            if (img[i][j].b < 0)
                img[i][j].b = 0;
        }
    }

    for (i = 1; i < linha - 1; i++){
        for(j = 0; j < coluna; j++){

                imagem[i][j].r = img[i][j].r + 128; //adiciona 128 para clarear a imagem
                imagem[i][j].g = img[i][j].g + 128;
                imagem[i][j].b = img[i][j].b + 128;

                if (img[i][j].r > 255) //testa os limites
                img[i][j].r = 255;

                if (img[i][j].g > 255)
                img[i][j].g = 255;

                if (img[i][j].b > 255)
                img[i][j].b = 255;                          
        }
    }
}
/*
    O cálculo é de forma simples de se explicar feito sobre esta 
    matriz:

    0      -1       0
    0       C       0
    0       1       0

    Onde o pixel central é substituído pela soma do negativo 
    imediatamente acima, e o valor positivo imediatamente abaixo, 
    depois testamos os limites. Lembrando que usamos uma matriz 
    para guardar os resultados, já que se alterarmos o valor
    imediatamente após realizarmos a conta, haveria interferência, 
    pois usamos os pixeis para calcular os da próxima linha. Depois 
    que tudo é calculado a matriz resposta é passada para a matriz 
    original.
*/
/*
    E por último aplicaremos o espelhamento, que é nada mais que 
    inverter a imagem. 
*/
void espelhar(pixel imagem[MAX][MAX], int coluna, int linha) {
    pixel img[linha][coluna];
    int i, j;

    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            img[i][j].r = imagem[i][coluna - j].r; //salva em uma matriz do tipo pixel a imagem com suas 
            img[i][j].g = imagem[i][coluna - j].g; //linhas salvas em complementos, isso faz com que a imagem
            img[i][j].b = imagem[i][coluna - j].b; //pegue o pixel complementar no seu extremo oposto horizontal 
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
/* 
    Esse efeito é bem simples, ele apenas substitui o pixel atual 
    pelo pixel de complemento, ou seja, pega a dimensão da imagem, 
    e subtrai dela o pixel corrente, para encontrar seu 
    correspondente no outro lado da imagem. Neste caso o 
    espelhamento foi feito na horizontal, mas nada impede de 
    faze-lo na vertical, ou alterar a fórmula para girar a imagem.
*/