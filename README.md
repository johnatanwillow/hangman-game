# Jogo da Forca - Documentação Técnica (Hangman Game)

Este repositório implementa um jogo da forca completo com modos Singleplayer e Multiplayer, gerenciamento de palavras, ranking e histórico de partidas. Abaixo está o índice com links para a documentação de cada módulo fonte do projeto.

| ----------------- | ----------------- | ----------------- | ----------------- | ----------------- | ----------------- |
| [Interface](https://github.com/ghustcc/hangman-game/blob/main/docs/doc_interface.md)     | [Histórico](https://github.com/ghustcc/hangman-game/blob/main/docs/doc_historico.md)        | [SinglePlayer](https://github.com/ghustcc/hangman-game/blob/main/docs/doc_single_player.md)     | [Palavras](https://github.com/ghustcc/hangman-game/blob/main/docs/doc_palavras.md)         | [Ranking](https://github.com/ghustcc/hangman-game/blob/main/docs/doc_ranking.md)          | [Multiplayer](https://github.com/ghustcc/hangman-game/blob/main/docs/doc_multiplayer.md)      |
| ----------------- | ----------------- | ----------------- | ----------------- | ----------------- | ----------------- |

## Introdução

Lorem

## Objetivos

O objetivo era desenvolver um jogo (Jogo da Velha) em linguagem C que utilizasse arquivos externos para armazer as informações de forma persistente:
    - Ser possível armazer e carregar palavras para serem utilizadas no jogo
    - O jogo permite que um jogador tente adivinhar uma palavra oculta que é sorteada (aleatoriamente) da nossa base de dados palavras.txt
    - Deve registrar as tentativas e verificar acertos e erros do jogador
    - Verificação de acertos e erros, sem repetição de palavras ou insercão de caracteres indevidos 
    - O sistema deve permitir a adição de novas palavras à base de dados, garantindo expansão
    - Exibis pontuação em ranking em forma de ranking e em histórico, para armazezar as informações do jogo
    - Implementação de modo multiplyer (de dois jogadores local)
    - Jogo dever ser construído em C
    - Deve-se usar matrizes, arquivos .txt, vetores e ponteiros 
    - Código modularizado com funções bem definidas
    - Jogo deve fornecer interface de interação com input e output (console)
    ![image](https://github.com/user-attachments/assets/2b26110a-bd47-47bb-a633-aa10e0ec3502)

![image](https://github.com/user-attachments/assets/b5d6ecf9-6c48-4e3e-a137-63df83883717)

## Fluxograma

A forma como pensamos e estruturamos o nosso projeto a fim de satisfazer os objetivos propostos (foi definido no início do projeto e se manteve até o fim): 

![image](https://github.com/user-attachments/assets/242501e6-dd4a-4f7f-a887-0b92ec29b3f9)

 - Organização das tarefas e planejamento (foram utilizadas as ferramentas Milanote, Google Wordspace e Notion): 
    ![image](https://github.com/user-attachments/assets/efdd4330-575e-43aa-b65a-adea5383000c)

## Módulos do Projeto

| Módulo            | Descrição                                                                | Link para documentação                       |
| ----------------- | ------------------------------------------------------------------------ | -------------------------------------------- |
| `interface.c`     | Responsável por todas as telas e mensagens exibidas ao jogador.          | [Interface](https://github.com/ghustcc/hangman-game/blob/main/docs/doc_interface.md)       |
| `historico.c`     | Manipula o arquivo de histórico de partidas, incluindo busca e listagem. | [Histórico](https://github.com/ghustcc/hangman-game/blob/main/docs/doc_historico.md)                 |
| `single-player.c` | Implementa a lógica do modo solo, controle de fluxo e pontuação.         | [SinglePlayer](https://github.com/ghustcc/hangman-game/blob/main/docs/doc_single_player.md)           |
| `multiplayer.c`   | Controla o modo multiplayer e alternação entre jogadores.                | [Multiplayer](https://github.com/ghustcc/hangman-game/blob/main/docs/doc_multiplayer.md)             |
| `palavras.c`      | Gerencia a lista de palavras e dicas, incluindo sorteio e adição.        | [Palavras](https://github.com/ghustcc/hangman-game/blob/main/docs/doc_palavras.md)                   |
| `ranking.c`       | Mantém o sistema de ranking atualizado com base nas pontuações.          | [Ranking](https://github.com/ghustcc/hangman-game/blob/main/docs/doc_ranking.md)                     |

## Compilação

Este projeto foi desenvolvido em C e depende da biblioteca `windows.h`. Recomendado compilar no ambiente Windows:

```bash
gcc src/*.c -o forca.exe
OU
gcc main.c ./src/single-player.c ./src/interface.c ./src/palavras.c ./src/ranking.c ./src/historico.c ./src/multiplayer.c -o forca.exe
```

## Diretórios

* `src/` - Arquivos fonte do jogo
* `include/` - Cabeçalhos utilizados pelos módulos
* `data/` - Arquivos persistentes como `palavras.txt`, `historico.txt` e `ranking.txt`
* `docs/` - Arquivo com toda a documentação do prjeto

## Autoria

Projeto colaborativo de alunos/desenvolvedores. Licenciado para fins educacionais e prática de programação estruturada.


## Cronograma

Inicio: Projeto iniciado em 03/2025.
Término: 06/2025.
Disponível em: https://docs.google.com/document/d/1ihc3gZmNoJa847M0WD065ILuE_dpgfzT43TwQkcy86E/edit?usp=sharing
---

> Para ver os detalhes de cada módulo, clique nos links acima ou navegue pelas documentações associadas.
