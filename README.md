# Problema de Comunicação entre Processos aplicado em RuPaul's Drag Race

# Programação Concorrente - UnB - Ítalo Frota (18/0019279)

![](https://img.buzzfeed.com/buzzfeed-static/static/2021-01/6/20/asset/4b24ac414e7e/anigif_sub-buzz-12644-1609964305-16.gif)

No primeiro episódio da nova temporada de *RuPaul's Drag Race*, temos 16 novas competidoras em busca do título de *"America's Next Drag Superstar"*. Nesta semana, as participantes foram desafiadas a confeccionar figurinos inspirados em professores do Departamento de Ciência da Computação da Universidade de Brasília.

A *workroom* possui um número x de espelhos, o que define a quantidade de *queens* que podem se preparar ao mesmo tempo, ninguém vai para a passarela enquanto todas as adversárias não estiverem prontas.

Uma vez que todas estão preparadas, elas seguem para o *backstage*. Aqui, elas esperam a permissão para desfilar, uma de cada vez.

Assim que todas mostraram o figurino na passarela, é hora do julgamento. A RuPaul consagra uma vencedora e coloca na berlinda as duas competidoras com o pior desempenho da semana.

As *queens* dublam e então uma é escolhida para dar adeus à competição.

O problema é solucionado com o uso de threads e semáforos, aplicando conceitos de programação concorrente e *multithreading*.

# Como executar?
 - Para compilar, basta executar o seguinte comando no terminal:
 `gcc -pthread -o dragrace main.c`
 - Para executar:
 `./dragrace [QTD_ESPELHOS]` , com QTD_ESPELHOS > 1.
