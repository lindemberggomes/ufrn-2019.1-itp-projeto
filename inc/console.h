/***************************************************************************
 * console.h
 * Biblioteca de funções de entrada e saída a partir do terminal (console).
 * @author André Maurício (andre@dimap.ufrn.br)
 ***************************************************************************/

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

/**
 * Lê uma sequência de caracteres de stdin até encontrar um "enter" ('\n').
 * A entrada pode ser um texto de tamanho qualquer. Uma string é alocada dinamicamente para comportá-lo.
 * A string é retornada e deve ser liberada (usando free()) quando não for mais necessário.
 */
char* readString();

/**
 * Lê uma string (até o "enter", '\n'), mas considera apenas o primeiro caractere.
 * Diferentemente do scanf(), os demais caracteres são removidos do buffer e desprezados.
 * Entradas em branco são consideradas inválidas.
 */
char readChar();

/**
 * Lê uma string (até o "enter", '\n') e tenta convertê-la para inteiro.
 * Strings que não são valores inteiros (ex: "asw", "17d" e "36.2") são consideradas inválidas e uma nova entrada é solicitada.
 * Entradas em branco também são consideradas inválidas.
 */
int readInt();

/**
 * Lê uma string (até o "enter", '\n') e tenta convertê-la para um float.
 * Strings que não são valores decimais (ex: "asw" e "17d") são consideradas inválidas e uma nova entrada é solicitada.
 * Entradas em branco também são consideradas inválidas.
 */
float readFloat();

/**
 * Imprime um caractere e faz um salto de linha ('\n').
 */
void printChar(char c);

/**
 * Imprime um valor inteiro e faz um salto de linha ('\n').
 */
void printInt(int i);

/**
 * Imprime um valor decimal, com o número de casas decimais especificado, e faz um salto de linha ('\n').
 */
void printFloat(float f, unsigned int n);

/**
 * Substitui o printf, inserindo um salto de linha ('\n') no final.
 */
void print(char *format, ...);

#endif