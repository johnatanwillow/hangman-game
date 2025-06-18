# Documentação: `single-player.c`

Este arquivo contém a implementação da lógica do jogo no modo Singleplayer. Ele gerencia desde o fluxo principal da partida até o cálculo da pontuação, letras testadas, e interações com ranking e histórico.

## Funções

### `void singlePlayerJogo()`
Executa o ciclo principal da partida no modo solo:
- Solicita nome do jogador
- Sorteia uma palavra e dica
- Exibe a tela do jogo a cada rodada
- Avalia se a letra ou palavra digitada é correta
- Atualiza acertos, erros e boneco
- Calcula e exibe a pontuação
- Salva resultado no ranking e histórico

### `void adicionaLetraTestada(char *letras_testadas, char letra[])`
Adiciona uma letra ao vetor de letras já testadas, se ainda não estiver presente.

### `int letraTestada(char *letra, char *letras_testadas)`
Verifica se uma letra já foi testada pelo jogador. Retorna `1` se sim, `0` caso contrário.

### `void dificuldadeDaPalavra(int tamanho, char **dificuldade)`
Define a dificuldade da palavra com base em seu comprimento:
- ≤4 letras: Fácil
- 5 a 7 letras: Médio
- >7 letras: Difícil

## Fluxo de Jogo

1. Chamada inicial: `telaSingleplayer()` para obter o nome
2. Sorteio: `palavraAleatoria()` e `dificuldadeDaPalavra()`
3. Início do laço `while`:
   - Tela: `telaSingleplayerJogo()`
   - Entrada: uma letra ou palavra
   - Avaliação:
     - Se letra correta e nova → revela na palavra e soma acertos
     - Se letra errada → soma erro e atualiza boneco
     - Se palavra correta → fim do jogo com vitória
     - Se palavra incorreta → erro e boneco atualizado
4. Fim da partida:
   - Exibe tela final com `telaResultadoJogo()`
   - Registra resultado com `ranqueamento()` e `escreveHistorico()`

## Observações

- O boneco é representado por `char partes_do_corpo[6]`, que é atualizado a cada erro.
- Pontuação = `(tamanho da palavra) * (tentativas restantes) * 100 - penalidade por letras repetidas`
- A lógica de validação de letras e palavras considera acentuação, tamanho e letras repetidas.

---

**Dependências:**
- `palavras.h`
- `interface.h`
- `ranking.h`
- `historico.h`
- `single-player.h`

**Autor:** Projeto colaborativo - Jogo da Forca

**Localização do arquivo:** `src/single-player.c`

