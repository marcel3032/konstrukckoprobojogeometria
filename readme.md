## Úvod
Vašou úlohou v tejto hre bnude postaviť robota, ktorý bude súťažiť v 4 disciplínach.
Popíšme teraz presnejšie tieto disciplíny:

## Disciplíny

### Prekážková dráha
V tejto disiplíne má robot za úlohu prejsť cez prekážkovú dráhu od začiatku po koniec.
Dráha sa skladá z 2 častí, prvá je označená čiernou páskou na svetlom podklade
a druhá je "bludisko", ktorého steny sú tvorené kartónom.
Na trase vyznačenej čiernou páskou sa môžu vyskytnúť prekážky, ktoré znamenajú,
že robot musí prekáku obísť a nemôže cez ňu pokračovať ďalej po čiare.

### Robotické sumo
V tejto disciplíne budú roboty proti sebe súťažiť v tzv. robotickom sume,
kde je úlohou vytlačiť ostatných súperov (zvyšných robotov) mimo vyznačeného kruhu.
Robot je vytlačený z kruhu v prípade, že je celý mimo kruhu.
Prosím, snažte sa Vášho robota konštruovať tak, aby vytláčaním ostatných robotov nepoškodil.

### Súťaž krásy
V tejto disciplíne sa bude hodnotiť estetická stránka robota.
Vašou úlohou bude odprezentovať robota, aby vynikla jeho krása
(príklad: chodenie po móle ako modelka).
Celé "vystúpenie" by malo trvať maximálne 60s.

### Naloženie a presunutie objektu
TODO

# Technické info, ovládanie a popis robota

Robot nemusí byť plne autonómny, rátame s tým, že ho budete ovládať na diaľku.
Čo sa týka autonómnosti, môžete si ale naprogramovať čo len chcete.

## Súčiastky

### Riadiaca jednotka
Ako "počítač" pre robota bude slúžiť jedno esp32 (je to v zásade nejaký klon arduina).
Oproti bežnému arduinu je táto doska vybavená wifi a bluetooth.
Táto doska sa programuje v rovankom jazyku ako arduino

### Motory a ich ovládanie
K dispozícii máte 2 motory aj s ich riadiacou jednotkou, ktorá vie ovládať 2 motory, obomi smermi.

### Vstupné senzory
K dispozícii máte 4 senzory čiary, ktoré vracajú digitálnu hodnotu,
či je odrazené svetlo väčšie ako nejaká prahová hodnota.
Táto hodnota je nastavovaná trimrom, ktorý je na senzore.
Tiež máte k dispozícii 4 mikrospínače, pomocou ktorých viete zisťovať dotyk s prekážkou.

### Šasí a stavebné prvky
Tiež dostanete niekoľko dosiek s M3 dierami.
Na pripájjanie súčiastok kolmo na tieto dosky dosta také. Lká, tiež s M3 dierami.
Väčšina súčastok má M3 alebo M2.5 dieru, takže to je odporúčaný spôsob ich spájania.
Máte k dispozícii dlhé a krátke M3 šrouby, veľkoplošné podložky, matky a zopár samoistných matiek.

### Napájanie
Celý robot bude napájaný jednou jednočlánkovou Li-Ion baterkou.
Túto baterku zvláda dobíjať samotné espčko v prípade,
že je zároveň pripojené usb káblom k zdroju napätia.

## Ovládanie robota
Na espčku, ktoré je na robotovi je spustený webserver.
Po pripojení sa na tento server cez (napr.) mobil sa načíta stránka,
pomocou ktoreje je možné ovládať robota.
Od robota do pripojeného zariadenia (mobilu) sú posielané jednak nejaké informácie o tom,
ako robot nastavil nejaký výstup, rôzne pomocné výpisy,
pomocou ktorých môžete robota ladiť a tiež aj informácie zo vstupných senzorov (čiary alebo dotyku).

# Podrobnejší popis kódu

## ESP32
Na espčku je urobený wifi hotspot.
Po pripojení na wifi na 192.168.4.1 (čo je adresa espčka) beží webserver,
ktorý hostuje jedinú stránku. Táto stránka slúži na diaľkové ovládanie robota.
Viac o stránke je nasledujúcom odstavci

## Klient (stránka na ovládanie robota)
Stránka a robot spolu komunikujú cez websocket.
Komunikácia prebieha obojsmerne, od klienta chodia robotovi príkazy
na zmenu výstupnej hodnoty pinov a od robota informácie o úspešne zmenenej výstupnej hodnote,
zmenenej vstupnej hodnote a pomocné debugovacie výpisy.

# Schémy zapojenia
Ukážková schéma zapojenia je tu:
...
Máme pocit, že tu sa veľmi nedá vynájsť amerika, takže sa o tom nebudeme viac rozpisovať. Ak by vám niečo chýbalo, ozvite sa.

# Nápady, čo môžete programovať:
-funkcia, po ktorej spustení bude robot chodiť po čiare
-ovládanie pre 2 ľudí
-rozumné ovládanie motorom niečím ako joystick
-funkcie na otočenie o 90 stupňov
-chodenie po bludisku podľa dotykov