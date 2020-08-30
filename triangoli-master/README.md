# Classe Triangoli
Implementazione di una classe in C++ usata per studiare i triangoli. 

I metodi della classe permettono di trovare area, perimetro, le altezze relative ai lati, baricentro, circocentro ed incentro di ogni triangolo di cui siano noti o 3 lati o 2  lati ed un angolo o 1 lato e i 2 angoli adiacenti ad essi.

La classe prevede infine un'implementazione grafica tramite gnuplot. La parte grafica, oltre a disegnare il triangolo e i punti notevoli, disegna le circonferenze inscritta e circoscritta al triangolo.

### Prerequisiti
Programma pensato per un OS Debian-Based. Con alcune modifiche puù funzionare anche su altre piattaforme, purchè queste siano dotate di:
+ gcc versione 7.5
+ cmake versione 3.13
+ gnuplot 5.52 (Le modifiche per fare andare il programma su Winodws - ad esempio - è l'esecuzione di gnuplot che per Linux è semplicemete "gnuplot" mentre su Winodws è "start gnuplot")
+ git

### Istruzioni
Aprire il terminale e digitare:
+ git clone https://github.com/morganapederzoli/Triangoli_esame
+ cd Triangoli_esame/triangoli-master/Programma
+ cmake .
+ make
+ ./triangoli
