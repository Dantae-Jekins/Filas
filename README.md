# Filas

A cidade Belzonte é cortada por um lago formado a partir de uma represa, esse lago separa duas regiões importantes da cidade, assim, a prefeitura precisou desenvolver um meio de transporte para pedestres, a decisão foi colocar lanchas com 50 lugares.
O tempo de travessia de entre as duas regiões entre 6 horas e 18 horas segue uma distribuição normal de média 15 minutos e desvio padrão 3 minutos e no período entre 18 horas e 6 horas segue uma distribuição normal de média 20 minutos e desvio padrão 5 minutos.
O horário de funcionamento da lancha é de 24 horas, mas há blocos de horários com demandas diferentes, as demandas estão na tabela.

### Horário
Taxa de chegada de pessoas a cada 5 minutos 

6h – 10h -> Distribuição normal com média 25 e desvio padrão 2 

10h – 12h -> Distribuição normal com média 10 e desvio padrão 3 

12h – 15h -> Distribuição normal com média 15 e desvio padrão 2

15h – 18h -> Distribuição normal com média 10 e desvio padrão 2

18h – 21h -> Distribuição normal com média 20 e desvio padrão 4

21h – 6h -> Distribuição normal com média 4 e desvio padrão 3

---

Em `problema.h` temos as estruturas relacionadas ao problema, tais estruturas que definem o comportamento da simulação:

Dentro de há a classe `class Simulação`, que define as propriedades de uma simulação, como a função de distribuição, como a distribuição para a travessia do barco e a distribuição para a chegada de pessoas no porto.

No codigo a seguir é definido a simulação. Ela recebe o dia inicial na primeira posição. A segunda posição é a distribuição probabilidades para uma viagem que ocorre das 18 às 6, e por fim a distribuição da chegada das 21 às 6. 
```c++
Simulação simul(0, &viagem18_06, &chegada21_06);
```

O arquivo `problema.h` conta com `class Viagem` para a definição de viagme em nosso cenário. Uma viagem pode ser definida como um serie de eventos que ocorrem de sequencialmente em relação ao horário. Tais eventos que ocorrem com base na probabilidade daquilo ocorrer naquele horário. A viagem possui seus estados que vão variar conforme o tempo.

A função deve receber seu contexto de atuação, no caso a simulação vigente. Na segunda posição, a simulação deve receber o tempo, 0 (definido anteriormente no tempo da simulação acima) mais 20. Na próxima posição, é recebido o estado atual do barco, 0 que dizer que ele se encontra no porto 0, o estado 1 indica que obarco está na rota ao porto 1, o estado 2 indica que o barco está no porto 1 e o estado 3 indica que o barco se encontra na rota ao porto 0. E por fim, o tanto de embarcados no momento inicial da definição do parco, 0 embarcados.

A função defini um barco (o barco viaja).

```c++
Barcos[0] = new Viagem(&simul, simul.time+20, 0, 0);
```

Por fim a classe `class Chegada` de `problema.h`. Essa classe define o evento de chagadas.

```c++
Chegadas[1] = new Chegada(&simul, simul.time+5, 1);
```

