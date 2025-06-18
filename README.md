# Jogo da Forca - Documentação Técnica (Hangman Game)

Este repositório implementa um jogo da forca completo com modos Singleplayer e Multiplayer, gerenciamento de palavras, ranking e histórico de partidas. Abaixo está o índice com links para a documentação de cada módulo fonte do projeto.

## Introdução

Lorem

## Objetivos

- Lorem:
    - Lorem

## Fluxograma
![image](https://github.com/user-attachments/assets/efdd4330-575e-43aa-b65a-adea5383000c)

Lorem

## Módulos do Projeto

| Módulo            | Descrição                                                                | Link para documentação                       |
| ----------------- | ------------------------------------------------------------------------ | -------------------------------------------- |
| `interface.c`     | Responsável por todas as telas e mensagens exibidas ao jogador.          | [Interface]("https://github.com/ghustcc/hangman-game/blob/main/docs/doc_interface.md")       |
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
