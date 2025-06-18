# Documentação: `ranking.c`

Este arquivo é responsável por gerenciar o sistema de ranking do jogo da forca. Ele lê, organiza, atualiza e grava os dados dos jogadores com base na pontuação.

## Funções

### `void ranqueamento(char *nome, int pontuacao_player)`
Principal função de interface com o ranking. Faz:
- Leitura dos dados existentes do ranking
- Soma de pontuação acumulada se o jogador já existir
- Inserção do novo valor na posição correta
- Escrita do ranking atualizado no arquivo

### `void rankingEmVetor(...)`
Converte os dados do arquivo `data/ranking.txt` para um vetor de estruturas `Memoria`. Também:
- Soma pontuação acumulada do jogador (caso já exista)
- Atualiza a posição onde o nome do jogador foi encontrado (`iNome`)
- Define o comprimento do nome mais longo para alinhamento

### `void organizaRanking(...)`
Reorganiza o vetor com a nova pontuação:
- Ordena o jogador atual por pontuação (decrescente)
- Remove duplicata anterior se já existia

### `void escreveArquivo(...)`
Reescreve o arquivo `ranking.txt` com os dados atualizados e metadados:
```
<quantidade_de_linhas> <tamanho_maior_nome>
NOME|PONTOS
...
```

### `void lerArquivoRanking()`
Lê e exibe os dados de ranking formatados para o usuário, utilizando o tamanho do maior nome para alinhar colunas.

### `int contaLinhasRanking()`
Conta a quantidade de entradas no arquivo de ranking.

## Formato do Arquivo

O arquivo `data/ranking.txt` segue o formato:
```
LINHAS MAX_TAM_NOME
NOME|PONTOS
NOME|PONTOS
...
```

## Observações

- A estrutura `Memoria` armazena temporariamente os dados em RAM para processamento.
- A ordenação não usa algoritmos sofisticados, mas é eficiente dado o pequeno tamanho do ranking.
- Permite que um jogador acumule pontos em partidas diferentes.

---

**Dependências:**
- `ranking.h` (estrutura `Memoria` e protótipos)

**Autor:** Projeto colaborativo - Jogo da Forca

**Localização do arquivo:** `src/ranking.c`

