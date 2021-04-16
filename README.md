# basic_C_implementation_of_among_us_game


TASK 1 - ROTATEMATRIX

La acest task am declarat o matrice de stringuri,
am umplut-o cu 11,12,13..., am transpuns matricea si
am oglindit-o fata de coloana din mijlocul acesteia.
( as fi putut sa umplu direct matricea cu 31,21,11,etc,
dar am vrut sa exersez rotirea matricei)

------------------------------------------------------

TASK 2 -DECODESTRING

La acest task am apelat la functia strtok cu separatorul
"_". Am stocat intr-un int suma numerelor (am folosit
atoi pentru a converti din char/string in int si sprintf 
pentru convertia din int in string)

------------------------------------------------------ 

TASK 3 - INVERTARRAY

Acest task are 2 cazuri, cand numarul elementelor este
impar trebuie doar sa inversam vectorul, iar daca 
numarul este par inversam elementele consecutive, 2 cate 2.
Am folosit, precum la taskul precedent, sprintf pentru
convert din int in char si strcat pentru concatenare.

-------------------------------------------------------

TASK 4 - ALLOCPLAYER & ALLOCGAME

Am alocat memorie structurii player, dar si variabilelor
de tip structura precum hat, name, color etc. . La fel si 
la functia AllocGame.

-------------------------------------------------------

TASK 5  - READPLAYER & READGAME

Am folosit functiile precedente pentru a aloca memorie 
jocului si jucatorului. Prin fscanf alocam din inputFile
valori variabilelor declarate. De asemenea, in ReadPlayer
am prelucrat si variabilele locations si ability.
In ReadGame am alocat memorie si prelucrat inputul- ul
pentru fiecare crewmate prin intermediul functiei
 ReadPlayer, cat si pentru impostor.

--------------------------------------------------------

TASK 6 - WRITEPLAYER & WRITEGAME

La acest task am stocat intr-un string abilitatea jucato-
rului si pe urma am scris in fisierul outputFile informatiile
dorite. La WriteGame am facut acelasi lucru ca WritePlayer, 
insa am apelat functia WritePlayer pentru a scrie mai usor
informatiile de la crewmates si impostor.

---------------------------------------------------------

TASK 7 - KillPlayer

In acest task am declarat mai multe variabile: 
LowestDinstance (pastrez cea mai mica distanta la care 
poate fi omorat un player) stock_crewamte(pastrez index-ul 
crewmate-ului ucis) stock_indexoflocation( pastrez index-ul 
locatiei pentru crewmate-ul ucis) str(un string unde voi 
pastra sirul de caractere care va fi scris in fisier), 
LowestDinstance_str( pastrez valoarea celei mai mici distante,
dar in format de string), crewmate_x, crewmate_y...(coordonatele
crewmate-ului si impostorului) modul_x si modul_y (aici pastram
modulul diferentei dintre coordonatele crewmate-ului si 
impostorului ( Dinstanta Manhattan)) Pentru fiecare crewmate
verificam daca acesta poate fi ucis si daca  distanta este 
cea mai mica. Daca se intampla ca dinstantele la care pot fi 
ucisi 2 crewmates sunt egale (implicit cele mai mici) verificam
care are indicele de locatie mai mare si astfel alegeam cine sa 
fie ucis.

------------------------------------------------------------

TASK 8 - CalculateNextCycleOfGame

Acest task mi se pare destul de asemenator cu WriteGame, doar
ca de data aceasta trebuie sa tinem cont de abilitatile juca-
torilor si sa verificam daca crewmate-ul mai traieste sau nu.
Daca nu mai traieste, afisam mesajul dorit, iar daca inca 
traieste, afisam mesajul dorit, ii schimbam locatia si folosim
abilitatea corespunzatoare. Acelasi lucru si pentru impostor.
P.S: De precizat ca locatiile sunt ciclice, iar daca 
indexoflocation devine egal cu numarul de locatii, acesta 
revine la valoarea 0.

---------------------------------------------------------

TASK 9 - FreePlayer & FreeGame

Desi pare cel mai scurt, acest task mi s-a parut cel mai
greu. Am dat de foarte multe erori, deoarece, inca de la
inceput, alocam memorie fara sa initializez, alocam
prea putina memorie s.a.m.d, insa dupa ceva debugging prin
toata tema am reusit sa finalizez acest task.
Majoritatea memoriei a fost eliberata la aceste functii prin
free.
Pe checker-ul temei iau 95 de puncte, dar pe vmchecker primesc
doar 93. Nu stiu cum sa identific problema.

------------------------------------------------------------
