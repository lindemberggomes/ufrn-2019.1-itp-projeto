#include "console.h"
#include "func.h"   //local do arq.h???
#include <stdio.h>
#include <stdlib.h>

void main(){
  print("ITP - Linguagem C");
  int a = 10;
  int b = 2; 
  printInt(a/b);
  //testa a modularização
  printInt(soma(a,b));
}