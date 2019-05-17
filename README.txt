# ufrn-2019.1-itp-projeto
Projeto final de ITP

Prof. Orientador: Dr. André Maurício Cunha Campos
Descrição do Projeto: Processamento de Imagem
Autores: Elildes Fortaleza Santos e Lindemberg Gomes da Silva

*** TAREFAS ***
1) Cria pastas para salvar tipos de arquivos iguais

2) Cria arquivos .c e .h: para separar arquivos com funcionalidades parecidas:
> funções parecidas, leitura/escrita, iteração com o usuário

3) Arquivos .h:
> Fazer as definições de: struct e enum
> Definir as constantes (#define)
. Criar filtro em escala de cinzas:
	imagem[i][j].r = (int) ((0.299 * imagem[i][j].r) + (0.587 * imagem[i][j].g) + (0.144 * imagem[i][j].b));
   
    imagem[i][j].g = imagem[i][j].r;
    imagem[i][j].b = imagem[i][j].r;

4) Outros Filtros:
. Auto relevo:
0      -1       0
0       C       0
0       1       0
Obs.: c = 1 - 1, depois c = 1-1+128

. Espelhamento:
//copia os pixels da coluna aposta
imgAux[i][j].r = imagem[i][coluna - j].r;
imgAux[i][j].g = imagem[i][coluna - j].g;
imgAux[i][j].b = imagem[i][coluna - j].b;

//passa os pixels para a imagem original
imagem[i][j].r = img[i][j].r;
imagem[i][j].g = img[i][j].g;
imagem[i][j].b = img[i][j].b;

*** EXTRA ***
. Criação de bibliotecas
. Fazer a parte gráfica no programa
. Filtros:
>  blur motion, sépia, detecção de bordas, negativo...

*** FONTES DE CONSULTAS ***
--Introdução ao formato ppm e seus usos--
https://www.vivaolinux.com.br/artigo/Manipulacao-de-imagens-no-formato-PPM

https://www.vivaolinux.com.br/artigo/Manipulacao-de-imagens-no-formato-PPM?pagina=2

https://pt.stackoverflow.com/questions/136858/girar-imagem-ppm-em-90-graus-em-c (Girando a imagen 90º)


1) O que foi feito:
. <listar aqui o básico>
. <listar aqui as funcionalidades extras implementadas>

2) O que não foi feito:
. <listar aqui, caso não tenha sido possível implementar alguma funcionalidade>

3) O que seria feito diferentemente:
. <listar aqui: quando aprendemos à medida que vamos
implementando, por vezes vemos que podíamos ter implementado algo de forma diferente. Assim, esse tópico é para vocês refletirem sobre o que vocês aprenderamdurante o processo que, se fossem fazer o mesmo projeto novamente, fariam diferente>

4) Como compilar o projeto, deixando explícito se foi utilizada alguma biblioteca externa que precise ser instalada, que versão e quais parâmetros extras são necessários para o
compilador.

*** PADRONIZAÇÕES ***
. variavel: int nome (simples). int nomeMaiuscula (composta). Ex.: int vetorNome.
. nome da função: tipo 




