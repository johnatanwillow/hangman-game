# Documentação: `historico.c`

Este arquivo é responsável pelo gerenciamento do histórico de partidas realizadas no jogo da forca. Ele provê funções para carregar, pesquisar e exibir registros de partidas.

## Funções

### `void carregarHistorico(Historico **historicos, int *total)`

Lê os dados do arquivo `data/historico.txt` e carrega em um vetor de estruturas `Historico`. Atualiza o ponteiro `total` com a quantidade de registros encontrados.

### `void liberarHistorico(Historico *historicos)`

Libera a memória alocada para o vetor de histórico.

### `void pesquisarPorData(char data[])`

Pesquisa e exibe registros de partidas que ocorreram em uma data específica. Aceita data no formato `DDMMAAAA` ou `DD/MM/AAAA`.

### `void pesquisarPorNome(char nome[])`

Pesquisa e exibe registros que contenham o nome informado, utilizando busca parcial (`strstr`).

### `void pesquisarPorID(int id)`

Exibe o registro correspondente ao ID informado, se encontrado.

### `void listarHistorico()`

Lista todos os registros contidos no arquivo `historico.txt`, com formatação visual e colunas alinhadas.

## Detalhes Adicionais

- Os dados são lidos a partir de `data/historico.txt`, onde cada linha possui o seguinte formato:

  ```
  ID|NOME|DATA|PONTUACAO
  ```

- A função `contaLinhasHistorico()` é utilizada para determinar o número de linhas existentes no histórico.

- A formatação da exibição utiliza um arquivo de metadados (`meta_historico.txt`) para saber o comprimento máximo do nome dos jogadores, melhorando a apresentação na tela.

- Em caso de erro ou nenhum dado encontrado, mensagens padronizadas são exibidas usando a função `semHistorico()` (presente em `interface.c`).

---

**Depências:**

- `interface.h` para interface de exibição.
- `historico.h` com a estrutura `Historico` e protótipos.

**Autor:** Projeto colaborativo - Jogo da Forca

**Localização do arquivo:** `src/historico.c`

