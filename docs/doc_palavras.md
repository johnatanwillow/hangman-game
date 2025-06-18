# Documentação: `palavras.c`

Este arquivo é responsável pelo gerenciamento das palavras utilizadas nas partidas do jogo da forca. Ele provê funcionalidades como sorteio aleatório, adição e validação das palavras e dicas.

## Funções

### `void palavraAleatoria(char **palavra, char **dica)`

Sorteia uma linha aleatória do arquivo `data/palavras.txt` e extrai os campos `palavra` e `dica`. A palavra e a dica são retornadas por ponteiros.

### `int contaLinhasPalavras()`

Conta e retorna o número total de linhas (palavras) presentes no arquivo `palavras.txt`.

### `void adicionarPalavra()`

Adiciona uma nova palavra ao arquivo `palavras.txt`, após verificar se ela já existe. Caso seja nova:

- Valida se está em letras e sem acentos
- Solicita uma dica
- Valida a dica
- Confirma com o usuário antes de gravar no arquivo

## Formato do Arquivo

O arquivo `data/palavras.txt` possui linhas no seguinte formato:

```
ID|PALAVRA|DICA|
```

- `ID` é sequencial
- `PALAVRA` deve estar em maiúsculas, sem espaços ou acentos
- `DICA` é capitalizada e sem acentos

## Validações

- A palavra não pode conter espaços ou acentos e precisa ser composta apenas por letras.
- A dica também é validada para não conter acentos ou começar com espaços.

## Observações

- A função `temArquivo()` (de `interface.c`) garante a existência do arquivo antes de acessá-lo.
- `gets()` é usado para ler a dica, o que pode ser inseguro em contextos reais — substituí-lo por `fgets()` é recomendável.
- Usa `toupper()` e `tolower()` para formatar a entrada do usuário.

---

**Dependências:**

- `palavras.h`
- `interface.h`

**Autor:** Projeto colaborativo - Jogo da Forca

**Localização do arquivo:** `src/palavras.c`

