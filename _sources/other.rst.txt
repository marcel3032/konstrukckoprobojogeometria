===================================
Ostatné a iné
===================================

.. _ideas:

Nápady, čo môžete programovať / ladiť
--------------------------------------

* funkcia, po ktorej spustení bude robot chodiť po čiare
* ovládanie pre 2 ľudí
* rozumné ovládanie motorom niečím ako joystick
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
* ESPčko má prehodené 1 a 0, takže napríklad ak chcete zapnúť vstavanú ledku, tak musíte na port 22 zapísať `LOW` a nie `HIGH`. Toto sme sa snažili +- vyriešiť tak, aby sa to správalo rozumne, ale ak nebudete používať čisto naše funkcie, tak sa s tým stretnete.
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