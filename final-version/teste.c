#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  int tamanho_linha = 80;
  char text[20] = "Gustav";
  char texto[150];

  sprintf(texto, "| %s", text);
  printf("%s", texto);
  for (int i = 0; i < tamanho_linha - strlen(texto); i++) {
    if (i != tamanho_linha - strlen(texto) - 1)
      printf(" ");
    else 
      printf("|");

  }
  
  printf("\n|                                                                              |\n");
}