#include<stdio.h>
#include<string.h>//PARA A SEPARAÇÃO DOS COMPONENTES DA LINHA
#include<stdlib.h>
#include<time.h>
#include<conio.h>//PARA RECEBER AS PALVRAS DO USUÁRIO
#define MAX_N_CHAR 255//MAXIMO NUMERO DE CARACTERES POR LINHA
void linhaAleatoria();
void novasPalavras();
int contaLinhas();
int main(){
    int escolha =0;
    printf("Por favor escolha [1]-Para ter uma listagem aleatoria [2]-Para adicionar uma palavra a lista\n");
    scanf("%d",&escolha);
    switch(escolha){
        case 1:
        linhaAleatoria();
        break;
        case 2:
        novasPalavras();
        break;
        default:
        printf("Por favor realize uma escolha valida");
        break;
    }   
    return 0;
}
void linhaAleatoria(){
    char buffer [MAX_N_CHAR];//Cada linha irá ser passada para esse buffer.
    char *id;
    char *nome;
    char *dica;
    srand(time(NULL));
    int linhaAleatoria = rand() % contaLinhas() + 1;//Aleatoriza qual linha será lida,o +1 é pq 0 até (qLinha-1) ir pra 1 até qLinhas
    FILE *arquivo;
    arquivo = fopen("arquivo.txt","r");//Abertura do arquivo em modo de apenas leitura 'r'
    int i =0;//Um contador para chegar até a linha aleatorizada
    while (i < linhaAleatoria && fgets(buffer,MAX_N_CHAR,arquivo) != NULL)//Um contador para chegar até a linha aleatorizada
          i++;
    id = strtok(buffer,",");//Passa o ID,pois é o primeiro item no arquio
    nome = strtok(NULL,",");//O USO DO NULL É PARA LIMPAR O ENDEREÇO ANTERIOR (O ID)E IR PARA O PROXIMO ITEM DA LISTA QUE É O NOME
    dica = strtok(NULL,",");//O USO DO NULL É PARA LIMPAR O ENDEREÇO ANTERIOR (O NOME) E VAI PARA O PROXIMO ITEM DA LISTA QUE É A DICA
    printf("id:%s\n",id);
    printf("nome:%s\n",nome);
    printf("dica:%s",dica);
    fclose(arquivo); //Fecha o arquivo 
}
int contaLinhas(){
    FILE *arquivo;
    arquivo = fopen("arquivo.txt","r");
    if(arquivo == NULL){//SE CASO ARQUIVO NÃO FOR LIDO,DÁ MENSAGEM DE ERRO
        fprintf(stderr,"ERRO NA TENTATIVA DE LER O ARQUIVO.\n");
        return 1;
    }
    char buffer [MAX_N_CHAR];//Cada linha irá ser passada para esse buffer.
    int qLinhas=0;
    while (fgets(buffer,MAX_N_CHAR,arquivo)){//O fgets é o que faz o buffer receber cada linha do arquivo,Enqunto a linha não possuir o fim de texto o contador aumentará
        qLinhas++;
    }
    fclose(arquivo);
    return qLinhas;
}
void novasPalavras(){
    int linhas = contaLinhas()+1;//Para o próximo id
    char id[2];//Para guardar o numero no i = 0,e o fim deles em i =1 
    sprintf(id,"%d",linhas);//Transformar de int para str; 
    char palavra[25];
    char dica[25];
    char *formato[3];
    FILE *arquivo;
    arquivo = fopen("arquivo.txt","a");//Abertura do arquivo em mode de adicão recente sem apagar os dados anteirores 'a'
    printf("Por favor escreva uma palavra:");
    fflush(stdin);//Para limpar o 'buffer do teclado' que armazenava dados perdidos,impedindo que o proximo gets fosse lido
    gets(palavra);
    fflush(stdin);//Para limpar o 'buffer do teclado' que armazenava dados perdidos,impedindo que o proximo gets fosse lido
    printf("Por favor escreva uma dica:");
    gets(dica);
    formato[0] = id;
    formato[1] = palavra;
    formato[2] = dica;
    fputs("\n",arquivo);//Para pular a linha dentro do arquivo
    for(int i = 0;i<3;i++){    
    fputs(("%s ",formato[i]),arquivo);//Colocar o id , a palavar e a dica
    fputs(",",arquivo);//Para colocar a vírgula,se juntar os dois a virgula não a aparece
}
    fclose(arquivo);
}
