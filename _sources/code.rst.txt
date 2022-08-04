==========================
Podrobnejší popis kódu
==========================

.. _esp32:

ESP32
------
Na espčku je urobený wifi hotspot.
Po pripojení na wifi na :code:`192.168.4.1` (čo je adresa espčka) beží webserver,
ktorý hostuje jedinú stránku. Táto stránka slúži na diaľkové ovládanie robota.
Viac o stránke je nasledujúcom odstavci :ref:`client`.

.. _client:

Klient (stránka na ovládanie robota)
-------------------------------------
Stránka a robot spolu komunikujú cez websocket.
Komunikácia prebieha obojsmerne. Od klienta chodia robotovi príkazy
na zmenu výstupnej hodnoty pinov a od robota informácie o úspešne zmenenej výstupnej hodnote,
zmenenej vstupnej hodnote a pomocné debugovacie výpisy. 