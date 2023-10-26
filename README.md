# Minishell

Minishell é um interpretador de comandos simples desenvolvido como parte de um projeto do curso. Ele oferece uma experiência de linha de comando básica e implementa recursos comuns encontrados em shells de sistemas operacionais modernos.

## Funcionalidades

- Exibe um prompt de comando.
- Oferece histórico de comandos.
- Localiza e executa comandos com base no PATH ou caminhos relativos/absolutos.
- Implementa redirecionamento de entrada e saída.
- Suporta pipes para encadear comandos.
- Manipula variáveis de ambiente e expande seus valores.
- Gerencia comandos incorporados, como `echo`, `cd`, `pwd`, `export`, `unset`, `env` e `exit`.
- Lida com sinais de interrupção, término e interrupção.

## Pré-requisitos

- GCC (GNU Compiler Collection)
- Biblioteca readline (instalada com `sudo apt-get install libreadline-dev` no Ubuntu)

## Como Usar

1. Clone este repositório:

   ```bash
   https://github.com/rsleslie/minishell-rv.git
   cd minishell
   
2. Compile o projeto com o Makefile:
     make
3. Execute o Minishell:
   ./minishell
