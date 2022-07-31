===================================
Ostatné a iné
===================================

.. _ideas:

Nápady, čo môžete programovať
------------------------------

* funkcia, po ktorej spustení bude robot chodiť po čiare
* ovládanie pre 2 ľudí
* rozumné ovládanie motorom niečím ako joystick
* funkcie na otočenie o 90 stupňov
* chodenie po bludisku podľa dotykov

.. _knownIssues:

Known issues
--------------

Nasleduje zoznam vecí, o ktorých vieme, že nefungujú, resp. nefungujú tak, ako by ste očakávali:

* V prípade, že výstupný pin ESPčka ovládate ako :code:`analogWrite`, tak už ho neviete ovládať ako :code:`digitalWrite` (treba resetnúť ESPčko).
* 