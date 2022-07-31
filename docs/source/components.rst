============================================
Technické info, ovládanie a popis robota
============================================

Robot nemusí byť plne autonómny, rátame s tým, že ho budete ovládať na diaľku.
Čo sa týka autonómnosti, môžete si ale naprogramovať čo len chcete.

.. _suciastky:

Súčiastky
----------

Riadiaca jednotka
~~~~~~~~~~~~~~~~~~~~~~~
Ako "počítač" pre robota bude slúžiť jedno esp32 (je to v zásade nejaký klon arduina).
Oproti bežnému arduinu je táto doska vybavená wifi a bluetooth.
Táto doska sa programuje v rovankom jazyku ako arduino

Motory a ich ovládanie
~~~~~~~~~~~~~~~~~~~~~~~
K dispozícii máte 2 motory aj s ich riadiacou jednotkou, ktorá vie ovládať 2 motory, obomi smermi.

Vstupné senzory
~~~~~~~~~~~~~~~~~~~~~~~
K dispozícii máte 4 senzory čiary, ktoré vracajú digitálnu hodnotu,
či je odrazené svetlo väčšie ako nejaká prahová hodnota.
Táto hodnota je nastavovaná trimrom, ktorý je na senzore.
Tiež máte k dispozícii 4 mikrospínače, pomocou ktorých viete zisťovať dotyk s prekážkou.

Šasí a stavebné prvky
~~~~~~~~~~~~~~~~~~~~~~~
Tiež dostanete niekoľko dosiek s M3 dierami.
Na pripájjanie súčiastok kolmo na tieto dosky dosta také. Lká, tiež s M3 dierami.
Väčšina súčastok má M3 alebo M2.5 dieru, takže to je odporúčaný spôsob ich spájania.
Máte k dispozícii dlhé a krátke M3 šrouby, veľkoplošné podložky, matky a zopár samoistných matiek.

Napájanie
~~~~~~~~~~~~~~~~~~~~~~~
Celý robot bude napájaný jednou jednočlánkovou Li-Ion baterkou.
Túto baterku zvláda dobíjať samotné espčko v prípade,
že je zároveň pripojené usb káblom k zdroju napätia.

.. _ovladanie:

Ovládanie robota
-----------------
Na espčku, ktoré je na robotovi je spustený webserver.
Po pripojení sa na tento server cez (napr.) mobil sa načíta stránka,
pomocou ktoreje je možné ovládať robota.
Od robota do pripojeného zariadenia (mobilu) sú posielané jednak nejaké informácie o tom,
ako robot nastavil nejaký výstup, rôzne pomocné výpisy,
pomocou ktorých môžete robota ladiť a tiež aj informácie zo vstupných senzorov (čiary alebo dotyku).