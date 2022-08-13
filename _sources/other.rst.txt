===================================
Ostatné a iné
===================================

.. _ideas:

Nápady, čo môžete programovať / ladiť
--------------------------------------

* funkcia, po ktorej spustení bude robot chodiť po čiare
* ovládanie pre 2 ľudí
* rozumné ovládanie motorov niečím ako joystick
* funkcie na otočenie o 90 stupňov
* chodenie po bludisku podľa dotykov
* do súťaže krásy môžete použiť aj  :ref:`pípače, alebo LEDky <led>` 

.. _knownIssues:

Known issues
--------------

Nasleduje zoznam vecí, o ktorých vieme, že nefungujú, resp. možno nefungujú tak, ako by ste očakávali:

* V prípade, že výstupný pin ESPčka ovládate ako :code:`analogWrite`, 
  tak už ho neviete ovládať ako :code:`digitalWrite` (treba resetnúť ESPčko).
* Piny, ktoré sú označené ako ADC2 nie je možné použiť na čítanie analógového vstupu
  (:code:`analogRead`) v prípade, že sa používa wifi. :code:`digitalRead` by na týchto pinoch malo fungovať vždy.
* ESPčko má prehodené 1 a 0, takže napríklad ak chcete zapnúť vstavanú ledku,
  tak musíte na port 22 zapísať `LOW` a nie `HIGH`. Toto sme sa snažili +- vyriešiť tak,
  aby sa to správalo rozumne, ale asi ak nebudete používať čisto naše funkcie,
  tak z toho môže byť kus zmätok, sorry :/
* Ak chcete z nejakého portu čítať vstup, napríklad si na neho napojiť tlačítko,
  tak aj ak nepotrebujete z neho mať výstup v mobile, tak si ho tam pridajte (najmä do :code:`checkInputs.ino`), keďže tam sa pri inicializácii rieši, aby bol port správne vstupný.
* V javascripte, ktorý ovláda motory, digitálne a analógové vstupy
  sú schválne umiestnené časti kódu, ktoré spôsobujú latenciu (oneskorenie).
* V prípade, že v serial monitore dostanete takýto error:

  .. code-block:: none
     
     rst:0x10 (RTCWDT_RTC_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
     configsip: 0, SPIWP:0xee
     clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
     mode:DIO, clock div:1
     load:0x3fff0030,len:1324
     ho 0 tail 12 room 4
     load:0x40078000,len:13508
     load:0x40080400,len:3604
     entry 0x400805f0
     ets Jun  8 2016 00:22:57
   
  Tak je to zrejme spôsobené pošahaným napájaním, skúste ESPčko natvrdo odpojiť od akéhokoľvek zdroja energie a opäť pripojiť.
  
.. _tips:

Tipy
--------------

Do tejto časti budú pribúdať tipy a triky, na ktoré prídeme počas hry,
tak si to skúste raz za čas refreshnúť.

* Môžete premýšľať rýchlejšie
* Ak sa Vám povoľujú matky, tak matky M3 máme aj samoistné (také vyššie s gumičkou),
  alebo ich môžete zakvapkať lakom na nechty.
* V spoločenskej vľavo sú pájkovačky, kliešte, lepidlá, laky na nechty, špajdle, gumičky, vrchnáčiky od fliaš, lepiace pásky, 3D pero a také.

Updates
-----------

V prípade, že počas hry budeme niečo podstatné pridávať/meniť v dokumentácii, tak to tu poznačíme, aj s časom, kedy sa to stalo.

+-------+-----------------------------------------------+
| Čas   | Čo                                            |
+=======+===============================================+
| 10:30 | Ok, nie som retardovaný, ten bug je asi ok    |
| 10:52 | Updaty tipov o tom, čo je v spoločenskej      |
| 11:14 | Update inštalačného návodu                    |
| 11:30 | Eh, som retard, už som fixol ten syntax error | 
|       |                                               |
|       |                                               |
|       |                                               |
|       |                                               |
|       |                                               |
|       |                                               |
|       |                                               |
+-------+-----------------------------------------------+

