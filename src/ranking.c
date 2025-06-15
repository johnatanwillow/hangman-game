#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/ranking.h" //Ta dentro o struct memoria e as funções

char buffer[MAX_N_CHAR];//Char global para ler os arquivos

//A função principal no ranking ela chama as outras funções 

void ranqueamento(char *nome, int pontuacao_player)
{
    int tamanho = contaLinhasRanking();
    int iNome= -1;     // iN é o lugar onde esteja a última pontuação do jogador.Se for -1 é pq esse nome é inédito
    int charMax = strlen(nome);//Saber qual é o nome com maior chares;
    Memoria memoria[tamanho + 1];

    rankingEmVetor(nome, &pontuacao_player,&iNome,&charMax,memoria);
    
    organizaRanking(nome,pontuacao_player,iNome,&tamanho,memoria);

    escreveArquivo(tamanho,charMax,memoria);
}

/*Pega todos os nomes e pontuações no arquivo e colocam na memoria.Além de verificar se há outro nome igual ao nome jogador e se tiver adicionar a pontuação anterior e a sua posição do vetor.
* Além de pegar o maior tamanho do nome;
*/
void rankingEmVetor(char *nome, int *pSomaDasPontuacoes, int *piNome ,int *charMax, Memoria memoria[])
{
    FILE *ranking;
    ranking = fopen("data/ranking.txt", "r");

    int i = 0;
    char *recebeBuffer; // O meio que eu encontrei para colocar os valores na memoria sem sobrescrever o outro
    fgets(buffer,MAX_N_CHAR,ranking);//Pula a primeira linha
    while (fgets(buffer, MAX_N_CHAR, ranking))
    {
        recebeBuffer = strtok(buffer, "|");
        strncpy(memoria[i].nome, recebeBuffer, MAX_N_CHAR - 1); // Copia do recebe buffer e passa para memoria
        memoria[i].nome[MAX_N_CHAR-1]= '\0';//Acaba a nome na matriz

        recebeBuffer = strtok(NULL, "\n");                   
        strncpy(memoria[i].pontuacao,recebeBuffer,MAX_N_CHAR-1);  // Copia do recebe buffer e passa para memoria; 
        memoria[i].pontuacao[MAX_N_CHAR-1] = '\0';  // Para terminar a string  porntuacção;

        memoria[i].pontos=atoi(memoria[i].pontuacao);
        
        if (strcmp(nome, memoria[i].nome) == 0) // Verificar se o há outras jogadas deste jogador e somar a pontuação dele
        {
            *pSomaDasPontuacoes += memoria[i].pontos;
            *piNome = i;

        }
        if(*charMax < strlen(memoria[i].nome)){
            *charMax = strlen(memoria[i].nome);
        }
        i++;
    }
    fclose(ranking);
}
//Organiza o Rakning adicionando o nome player na posição além de ,se tiver , apagar o nome da antiga posição que estava;
void organizaRanking(char *nome,int pontuacao_player, int iNome, int *tamanho, Memoria memoria[]){
    int i = 0;
    int tam = *tamanho;//Para fazer mudar ou não o tamanho dela para escrever no arquivo
    Memoria aux1,aux2;
    
    //Não queremos sobrepassar a pontuação superiores a nossa e quando acabar ou seja pela pontuação anterior ser menor que a atual ou o indice
    while (pontuacao_player < memoria[i].pontos && i < *tamanho)
        i++; 

    aux1 = memoria[i];
    strncpy(memoria[i].nome, nome, MAX_N_CHAR - 1);
    sprintf(memoria[i].pontuacao, "%d", pontuacao_player);
    
    while (i < *tamanho)
    {
        i++;
        aux2 = memoria[i];
        memoria[i] = aux1;
        aux1 = aux2;
        
    }
    
    if (iNome == -1)
    {
         *tamanho = tam + 1;
    }else{ 

        iNome++;
        memoria[iNome] = memoria[iNome+1];
        for (int j = iNome; j <= *tamanho; j++)
            memoria[j] = memoria[j+1];
    }

}

//Escreve dentro de ./data/ranking.txt os metadados , o  nome e a pontuação
void escreveArquivo(int tamanho,int charMax, Memoria memoria[])
{
    FILE *ranking;
    ranking = fopen("data/ranking.txt", "w");

    fprintf(ranking,"%d %d\n",tamanho,charMax);
    
    for (int i = 0; i < tamanho; i++){
        fprintf(ranking,"%s|%s\n",memoria[i].nome,memoria[i].pontuacao);
    }
    fclose(ranking);
}

void lerArquivoRanking()
{
    FILE *ranking;
    ranking = fopen("data/ranking.txt", "r");
    char *nome_extraido;
    char *pontuacao_extraida;

    int i = 0;
    int palvramaior;
    int aux;
    fscanf(ranking,"%d %d",&aux,&palvramaior);
    fgets(buffer,MAX_N_CHAR,ranking);
    do{ 
    
        if(i == 0){
            nome_extraido = "NOME";
            pontuacao_extraida = "PONTOS";
            printf("| POS | %s ", nome_extraido);
        }else{
        nome_extraido = strtok(buffer, "|");
        pontuacao_extraida = strtok(NULL, "\n"); 
        printf("| %3d | %s ", i, nome_extraido);
        }
        i++;
        
        for(int j = 0 ; j < palvramaior-strlen(nome_extraido);j++)//Comparo os tamnhos e coloco os espaços devidos
        printf(" ");
        printf("| %s", pontuacao_extraida);
        for(int j = 0 ; j < 67-palvramaior -strlen(pontuacao_extraida);j++)
            printf(" ");//É so para n ter um textão de 51 espaços
        printf(" |\n");
        printf("+");
        for(int j = 0 ; j < palvramaior+8;j++)//Como o + vai na seta ent é necessário ver isso
        printf("-");
        printf("+");
        for(int j = 0;j < 69-palvramaior;j++)
            printf("-");
        printf("+\n");

    }while(fgets(buffer, MAX_N_CHAR, ranking));
    fclose(ranking);
}

int contaLinhasRanking()
{
    FILE *arquivo;
    arquivo = fopen("data/ranking.txt", "r");

    int qLinha = 0;
    if(arquivo != NULL)
        fscanf(arquivo,"%d",&qLinha);

    fclose(arquivo);
    return qLinha;
}
