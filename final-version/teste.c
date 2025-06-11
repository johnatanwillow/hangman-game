#include <stdio.h>
#include <time.h>

int main()
{
  time_t tempo;
  struct tm *tempo_local;

  // Obter o tempo atual
  tempo = time(NULL);

  tempo_local = localtime(&tempo);

  //   Exibir a data e hora no formato DD/MM/YYYY HH:MM:SS
  printf("Data e hora atuais: %02d/%02d/%04d %02d:%02d:%02d\n",
        tempo_local->tm_mday, tempo_local->tm_mon + 1, tempo_local->tm_year + 1900,
        tempo_local->tm_hour, tempo_local->tm_min, tempo_local->tm_sec);
}