# Introduction

<!-- TODO -->

O Projeto Sloc tem como opbjetivo a entregar ao usuário uma visualização tabelada da quantidade de Linhas código, linhas de comentários, linhas em branco, linhas totais e a porcetagem de cada tipo de linha em relação ao total de linhas para todos os arquivos de programação nas linguagens suportadas de um diretório especificado ou arquivo especificado.

# Author(s)

Victor Bold Ribeiro da Cunha - victorisbold@gmail.com

Luís Eduardo de Oliveira Sales - duduosales@hotmail.com

# Problems found or limitations

<!-- TODO -->

Lista aqui os problemas encontrados (se houve algum) e as possíveis limitações do programa.

Dificuldade na leitura de pastas, especialmente quando se fez necessário acessar todas as pastas recursivamente.

Dificuldade em formatar a apresentação do resultado.

# Grading

<!-- TODO -->

Preencha os itens que você implementou, indicando qual a nota esperada para cada item.

| Item                                                | Valor máximo | Valor esperado |
| --------------------------------------------------- | :----------: | :------------: |
| Read a single source file                           |      10      |        8       |
| Read a list of files from a directory               |      15      |        4       |
| Show help as requested `-h`                         |      4       |        4       |
| Treat error situations                              |      8       |        4       |
| Show correct number of blank lines                  |      5       |        5       |
| Show correct number of comment lines                |      10      |       10       |
| Show correct number of code lines                   |      10      |       10       |
| Show correct number of total lines                  |      5       |        5       |
| Show the type of source file                        |      5       |        5       |
| Show percentages as requested                       |      10      |       10       |
| Show consolidation at the bottom of a table         |      5       |        0       |
| Table is formatted as requested                     |      8       |        4       |
| The project contains at least one struct or classes |      5       |        5       |

# Compiling and Runnig

<!-- TODO -->
1º Entrar na pasta do projeto
2º Digitar a Seguinte Linha de Comando
"g++ -Wall -std=c++17 -o <nome do executável> src/main.cpp src/functions/sloc.cpp"