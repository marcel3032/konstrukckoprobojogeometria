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

.. cpp:function:: void websocket_server::notifyClientsMessage(int port, int value)

   Táto funkcia je zavolaná pri zapísaní výstupnej hodnoty na port.
   Pošle do prehliadača informáciu o tom, čo zapísal.

   :param port: port, ktorého hodnota sa zmenila
   :param value: hodnota, na ktorú sa zmenil výstup
   :return: void
   

.. cpp:function:: void websocket_server::notifyClientsInput(int port, int value)

   Táto funkcia je zavolaná pri zmene vstupnej hodnoty.
   Pošle do prehliadača informáciu o hodnote na vstupe.

   :param port: port, ktorého hodnota sa zmenila
   :param value: hodnota, na ktorú sa zmenil vstup
   :return: void


.. cpp:function:: void websocket_server::sendDebugMessage(String level, String message)

   Funkcia pošle do prehliadača debug log.

   :param level: úroveň dôležitosti tejto správy. Odporúčané deti sú "DEBUG", "INFO", "WARNING", "ERROR" (tieto sú aj v premenných hore)
   :param value: text správy, ktorá sa má poslať
   :return: void


.. cpp:function:: void websocket_server::motorWrite(int port1, int port2, int value)

   Funkcia, ktorá ovláda motor. 

   :param port1: prvý port, na ktorý je pripojený motor
   :param port2: druhý port, na ktorý je pripojený motor
   :param value: hodnota, ktorou sa má hýbať motor. Očakávaný rozsah je -255 až +255. 
   :return: void


.. cpp:function:: void websocket_server::handleWebSocketMessage(void *arg, uint8_t *data, size_t len)

   Funkcia, ktorá rieši prijatie správy z websocketu.
   V zásade jediné, čo Vás z nej musí zaujímať je, že zavolá funkciu :func:`handleMessage::handleMessage()`.

   :param port1: prvý port, na ktorý je pripojený motor
   :param port2: druhý port, na ktorý je pripojený motor
   :param value: hodnota, ktorou sa má hýbať motor. Očakávaný rozsah je -255 až +255. 
   :return: void


.. cpp:function:: void websocket_server::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)

   Opäť funkcia, ktorá Vás nemusí až tak zaujímať, obhospodaruje websocket.
   
   :return: void


.. cpp:function:: void websocket_server::initWebSocket()

   Opäť funkcia, ktorá Vás nemusí až tak zaujímať, obhospodaruje websocket.
   
   :return: void


.. cpp:function:: void websocket_server::setup()

   Defaultná Arduino funkcia, ktorá sa zavolá jediný krát pri spustení programu.
   V našom prípade inicializuje sériovú komunikáciu, nastavuje vstupné porty ako vstupné,
   nastavuje webserver a wifi.
   
   :return: void


.. cpp:function:: void websocket_server::loop()

   Defaultná Arduino funkcia, ktorá sa volá dookola, počas celého behu programu.
   V našom prípade okrem websocket sránd robí to, že skontroluje vstupné hodnoty,
   a spustí funkciu :cpp:func:`performLoop::performLoop()`, v ktorej môžete mať naprogramované všetko,
   čo sa má vykonávať celý čas počas behu programu (napríklad sledovanie čiary).
   
   :return: void


.. cpp:function:: void performLoop::performLoop()

   Táto funkcia je určená na napísanie vecí, ktoré sa majú diať celý čas počas behu programu.
   Odporúčaný postup, v prípade, že chcete mať funkciu (nazvime ju F),
   ktorú budete zapínať/vypínať počas behu programu je urobiť si funkciu,
   ktorá sa bude volať z prehliadača a zmení nejakú boolean premennú,
   že či sa bude funkcia F vykonávať.
   
   :return: void


.. cpp:function:: void handleMessage::handleMessage(DynamicJsonDocument doc)

   Toto je funkcia, ktorá sa volá vždy po prijatí websocketovej správy.
   Podľa toho, aký je :code:`method` v prijate websocket správe
   (:code:`analog`/:code:`digital`/:code:`function`/:code:`motor`)
   sa vykoná tá-ktorá vec.
   
   Asi jediné nepriamočiare je to, ako to funguje s funkciami.
   V poli :code:`functions` máme všetky funkcie, ktoré môžeme volať.
   Všetky funkcie berú ako parameter string - json,
   v ktorom funkcii môžete poslať vstupné parametre.
   To, ktorá funkcia sa má spustiť, sa ESP posiela ako index do poľa funkcií.
   
   :param doc: json dokument, ktorý obsahuje prijatú správu.
   :return: void


.. cpp:function:: void checkInputs::checkInputs()

   Táto funkcia kontroluje hodnoty na vstupných portoch.
   Porty sú uložené v poli :code:`ports`.
   Aby zbytočne nezahlcovala websocket komunikáciu,
   tak pošle hodnotu na vstupa iba raz za čas
   (koľko presne, viete nastaviť v premennej :code:`min_dif`,
   ale máme pocit, že prednastavených 500ms je +- fajn)
   
   Funkcia aktuálne číta všetky vstupné hodnoty digitálne (0/1).
   
   :return: void


.. cpp:function:: void checkInputs::setInputsAsInput()

   Funkcia nastaví všetky vstupné porty ako vstupné.
   
   :return: void


.. _client:

Klient (stránka na ovládanie robota)
-------------------------------------
Stránka a robot spolu komunikujú cez websocket.
Komunikácia prebieha obojsmerne. Od klienta chodia robotovi príkazy
na zmenu výstupnej hodnoty pinov a od robota informácie o úspešne zmenenej výstupnej hodnote,
zmenenej vstupnej hodnote a pomocné debugovacie výpisy. 


.. js:function:: init_js.initWebSocket()
   
   Funkcia inicializuje websocket komunikáciu, v zásade Vás nemusí zaujímať.


.. js:function:: init_js.$e(elName, cl, parEl)
   
   Funkcia vytvorí nový html element.
   
   :param elName: Meno elementu, ktorý sa má vyrobiť (:code:`h1`, :code:`p`, :code:`input`, ...)
   :param cl: Pole, ktoré na každom indexe obsahuje dvojprvkové pole, kde nultý index je kľúč a druhý je hodnota parametrov (napríklad :code:`[["id", "nieco"], ["class", "content"]]`)
   :param parEl: Element, do ktorého sa má nový element, vložiť.
   :returns: Odkaz na vytvorený element.


.. js:function:: index.onMessage(event)

   Funkcia, ktorá je spustená po prijatí správy cez websocket.
   
   :param event: Objekt s dátami, ktoré boli prijaté.


.. js:class:: index.PortOutput(port)

   Trieda, z ktorej dedí väčšina ovládacích prvkov. Má iba konštruktor a ten vyrobí potrebné html elementy.
   
   :param port: Port, ktorý má tento ovládací prvok ovládať.


.. js:class:: index.OutputButton(port)

   Trieda, ktorá vyrába tlačítko, ktoré digitálne (0/1) ovláda jeden výstupný port na ESP.
   
   :param port: Port, ktorý má tento ovládací prvok ovládať.
   
   .. js:function:: update(recieved_data)
       
       Metóda, ktorá je zavolaná funkciou :js:func:`index.onMessage()`, ktorá o tom dostane info od ESPčka potom, čo ESPčko nastaví výstupný port na danú hodnotu.
       
       :param event: Objekt s dátami, ktoré boli prijaté.


.. js:class:: index.Slider(port)

   Trieda, ktorá vyrába slider (posúvatko), ktoré analógovo ovláda jeden výstupný port na ESP.
   
   :param port: Port, ktorý má tento ovládací prvok ovládať.
   
   .. js:function:: update(recieved_data)
       
       Metóda, ktorá je zavolaná funkciou :js:func:`index.onMessage()`, ktorá o tom dostane info od ESPčka potom, čo ESPčko nastaví výstupný port na danú hodnotu.
       
       :param event: Objekt s dátami, ktoré boli prijaté.


.. js:class:: index.MotorSlider(port1, port2)

   Trieda, ktorá vyrába slider (posúvatko), ktoré ovláda motor, ktorý je do ESP pripojený na 2 porty.
   
   :param port1: Prvý port, na ktorý je pripojený motor.
   
   :param port2: Druhý port, na ktorý je pripojený motor.
   
   .. js:function:: update(recieved_data)
       
       Metóda, ktorá je zavolaná funkciou :js:func:`index.onMessage()`, ktorá o tom dostane info od ESPčka potom, čo ESPčko nastaví výstupný port na danú hodnotu.
       
       :param event: Objekt s dátami, ktoré boli prijaté.


.. js:class:: index.PortInput(port)

   Trieda, ktorá vyrába element, ktorý prijíma informácie o zmene vstupnej hodnoty na porte na ESP.
   
   :param port: Port, ktorý zobrazuje tento element.
   
   .. js:function:: update(recieved_data)
       
       Metóda, ktorá je zavolaná funkciou :js:func:`index.onMessage()`, ktorá o tom dostane info od ESPčka potom, čo ESPčko zistí hodnotu na vstupnom porte.
       
       :param event: Objekt s dátami, ktoré boli prijaté.


.. js:class:: index.SliderFunctionButton(function_index)

   Ukážka triedy, ktorá ovláda funkciu na ESPčku.
   
   Po stlačení tlačítka (:code:`addEventListener`)   zistí hodnotu, na ktorej je slider nastavený (:code:`this.slider.value`), a pošle to ESPčku, ako argument funkcie.
   
   :param function_index: Index do poľa funkcií v ESPčku, ktorý označuje funkciu, ktorá sa má zavolať.
   
   .. js:function:: update(recieved_data)
       
       Metóda, ktorá je zavolaná funkciou :js:func:`index.onMessage()`, ktorá o tom dostane info od ESPčka potom, čo ESPčko zistí hodnotu na vstupnom porte.
	   
	   V tomto prípade nič neurobí.
       
       :param event: Objekt s dátami, ktoré boli prijaté.


.. js:data:: input_elements

   Pole, ktoré obsahuje ovládacie prvky, ktoré používate.
   V prípade, že chcete pridať nový ovládací prvok, tak potrebujete vložiť nový prvok do tohoto poľa.


.. js:data:: port_inputs

   Pole, ktoré obsahuje elementy, ktoré prijímajú informácie o zmenách vstupných hodnôt v ESPčku.
   V prípade, že chcete pridať nový takýto element, tak potrebujete vložiť nový prvok do tohoto poľa.