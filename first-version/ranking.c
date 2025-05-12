#include <stdio.h>
#include<string.h>
#include <stdlib.h>

#include"ranking.h"

#define MAX_N_CHAR 255
#define MAX_PLAYERS 1000

char buffer[MAX_N_CHAR];
char memoria[MAX_PLAYERS][2][MAX_N_CHAR];



void ajustarPontuacao(char *nome , int pontuacao_player){
    
    int tamanho =contaLinhas(); 
    int pontuacao_players[tamanho];
    int i = 0, iN;//i é o indice,
    int s =-1;
    //iN é o lugar onde esteja a última pontuação do jogador.Se for -1 é pq esse nome é inédito
    int n=1;//Se for inédito n irá aumentar o tamanho na hora de demsontrar o highscore.Se n for inédito ele será zero.
    char pontuacao[2];
    char aux1[2][MAX_N_CHAR],aux2[2][MAX_N_CHAR];
    
    rankingEmVetor(nome,&pontuacao_player,pontuacao_players,&s);
    iN = s;
    while(pontuacao_player < pontuacao_players[i] && i < tamanho)
            i++;//Se for maior agente ignora        
    //Quando acabar ou seja pela pontuação anterior ser menor que a atual ou o indice

    //Esse blocão aqui é um porblema e agente precisa arrumar um jeito de diminuílo
    for(int j =0;j<2;j++)
            strncpy(aux1[j],memoria[i][j],MAX_N_CHAR-1);
        strncpy(memoria[i][0],nome,MAX_N_CHAR-1);
        sprintf(pontuacao,"%d",pontuacao_player);
        
        strncpy(memoria[i][1],pontuacao,MAX_N_CHAR-1);

        while(i <= tamanho){
        i++;
        for(int j=0;j<2;j++){
                strncpy(aux2[j],memoria[i][j],MAX_N_CHAR-1);
                strncpy(memoria[i][j],aux1[j],MAX_N_CHAR-1);
                strncpy(aux1[j],aux2[j],MAX_N_CHAR-1);
            }
        
        }
        
       if(iN != -1){
            iN++;
             strncpy(memoria[iN][0],memoria[iN+1][0],MAX_N_CHAR-1);
             strncpy(memoria[iN][1],memoria[iN+1][1],MAX_N_CHAR-1);
             n = 0;
        
        for(int i = iN;i <=tamanho;i++)
            for(int j =0;j < 2;j++){
                 strncpy(memoria[i][j],memoria[i+1][j],MAX_N_CHAR-1);
            }
        }
    tamanho += n;
    escreveArquivo(tamanho);
    
    printf("=============Highscores===============");
    for(int j = 0; j<tamanho;j++)
        printf("\n%d %s %s",j+1,memoria[j][0],memoria[j][1]);
   
}   
void rankingEmVetor(char *nome, int *pSomaDasPontuacoes , int pontuacao_ante[], int *pIn){
    FILE *ranking;
    ranking = fopen("ranking.txt","r");

    int i =0;
    char *recebeBuffer;//O meio que eu encontrei para colocar os valores na memoria sem sobrescrever o outro
    
    while(fgets(buffer,MAX_N_CHAR,ranking)){
        recebeBuffer= strtok(buffer,"|") ;
        strncpy(memoria[i][0],recebeBuffer,MAX_N_CHAR-1);//Copia do recebe buffer e passa para memoria
        memoria[i][0][MAX_N_CHAR - 1] = '\0';//Para terminar a string nome;
        
        recebeBuffer= strtok(NULL,"\n");
        strncpy(memoria[i][1],recebeBuffer,MAX_N_CHAR-1);//Copia do recebe buffer e passa para memoria;
        memoria[i][1][MAX_N_CHAR - 1] = '\0';//Para terminar a string  porntuacção;
        sscanf(memoria[i][1],"%d",&pontuacao_ante[i]);

        if(strcmp(nome,memoria[i][0]) == 0){//Verificar se o há outras jogadas deste jogador e somar a pontuação dele
        
            *pSomaDasPontuacoes+= pontuacao_ante[i];
            *pIn = i;

        }
        
        i++;
    }

    fclose(ranking);
}

void escreveArquivo(int tamanho){
 FILE *ranking;
         ranking = fopen("ranking.txt","w");
        for(int i = 0;i < tamanho ; i++){
            fputs(("%s",memoria[i][0]),ranking);
            fputs("|",ranking);
            fputs(("%s",memoria[i][1]),ranking);
            fputs("\n",ranking);
        }
    fclose(ranking);    
 }
int contaLinhas()
{
    FILE *arquivo;
    arquivo = fopen("ranking.txt", "r");

    int qLinhas = 0;

    // O fgets é o que faz o buffer receber cada linha do arquivo,Enqunto a linha não possuir o fim de texto o contador aumentará
    while (fgets(buffer, MAX_N_CHAR, arquivo))
    {
        qLinhas++;
    }

    fclose(arquivo);
    return qLinhas;
}

