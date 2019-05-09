# Introdução a Técnicas de Programação

Esta é uma estrutura de pastas e arquivos a ser usada como modelo inicial nas atividades da disciplina de Introdução a Técnicas de Programação (UFRN).

A princípio, os arquivos que você deve alterar/criar encontram-se unicamente na pasta `./src` (no final da 2ª unidade, outras pastas serão modificadas). Para cada atividade, crie uma cópia do arquivo `main.c` que se encontra na pasta e edite-a.

Para criar uma cópia do arquivo, utilize o comando `cp` abaixo, onde `<nome>` é o nome de arquivo qualquer, por exemplo `itp1`.
```
cp src/main.c src/<nome>.c
```

Depois de editar o código, você pode gerar (compilar) o programa através do comando:
```
make code=<nome>
```

Por exemplo, se você está editando o arquivo `itp1.c`, você pode compilá-lo através do comando:
```
make code=itp1
```

Este comando seguirá as especificações de compilação que se encontram no arquivo `./Makefile` e irá criar o programa `itp1` na pasta `./bin`. Para executá-lo, escreva no terminal:
```
./bin/itp1
```

Resumindo:
1) Crie uma cópia do arquivo `.src/main.c`;
1) Edite a cópia em função do que for solicitado como tarefa;
1) Gere o programa dele através do comando `make code=<nome>`, onde `<nome>` é o nome da cópia criada sem a extensão `.c`;
1) Execute o programa chmando-o a partir do terminal através de `./bin/<nome>`.

Mais informações sobre o processo de compilação e o arquivo Makefile serão fornecidas ao longo do curso.

**Obs**: Para simplificar a entrada e saída de dados a partir do terminal, foi criada uma biblioteca de rotinas (funções), nomeada de `console`. Esta biblioteca será incorporada no seu programa durante a compilação. Ao longo do curso, veremos mais detalhes sobre o uso da bliblioteca e como funciona.
