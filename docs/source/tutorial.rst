===================================
Ukážky kódov, tutoriál
===================================

Tento text predpokladá, že máte rozbehané Arduino IDE, a urobené všetky veci z :ref:`ide`.

V predchádzajúcom texte ste overili, že keď ťukáte na tlačítko, 
ktoré ovláda port 22, tak by sa mala ledka na ESPčku zapínať a vypínať.

Dokopy sa Vám zobrazuje:

* Tlačítko ovládajúce port 22
* Slider ovládajúci port 22
* Slider s tlačítkom, ovládajúci funkciu 0
* Tlačítko ovládajúce funkciu 0
* Slider ovládajúci 2 porty (19 a 22)
* Element ukazujúci aktuálny stav portu (13)

Opíšme si teraz postupne všetky tieto veci:

Tlačítko ovládajúce port 22
----------------------------------------------

V predchádzajúcom texte ste overili, že keď ťukáte na tlačítko, 
ktoré ovláda port 22, tak by sa mala ledka na ESPčku zapínať a vypínať.

Nové tlačítko najprv musí byť pridané do poľa :code:`input_elements`
v `index.ino` dole, okolo riadku 185.

.. code-block:: javascript

   input_elements.push(new OutputButton(22));
   
Trieda `OutputButton` urobí všetko za nás, jediná vec,
ktorú jej potrebujeme dať, je port, ktorý má ovládať.

Slider ovládajúci port 22
----------------------------------------------

Výstupnú hodnotu portu vieme ovládať aj plynule/analógovo, slidrom.

Ak posúvate slider, čo patrí k portu 22, tak by sa mala LEDka na ESPčku
pomaly zhasínať/zapínať.

Slider musí byť tiež pridaný do poľa:code:`input_elements`
v `index.ino` dole, okolo riadku 185.

.. code-block:: javascript

   input_elements.push(new Slider(22));

Trieda `Slider` tiež urobí všetko za nás,
jediná vec, ktorú jej potrebujeme dať, je port, ktorý má ovládať.

(Ak už LEDku raz ovládate slidrom, do reštartu espčka ju neviete ovládať tlačítkom,
pozri :ref:`knownIssues`)

Slider s tlačítkom, ovládajúci funkciu 0
----------------------------------------------

Okrem zapínania/vypínania portov napriamo
si vieme vyrobiť aj funkciu v ESPčku, ktorú budeme volať z mobilu.

Presuňte slider približne do ľavej tretiny a po stlačení tlačítka
by sa mala LEDka zasvietiť a zhasnúť.
Čím viac posuniete slider doprava, tým dlhšie bude svietiť.

Najprv si do poľa :code:`input_elements` v `index.ino` dole,
okolo riadku 185 pridáme triedu, ktorou budeme 
volať funkciu. Napríklad si môžeme pridať triedu 
`SliderFunctionButton`, ktorú ste dostali ako príklad.

.. code-block:: javascript

   input_elements.push(new SliderFunctionButton(0));

Rozoberme si, ako presne je urobená trieda `SliderFunctionButton`.
Jej definácia je okolo riadku 130.

Na jej začiatku si uložíme index do poľa funkcií, aby sme vedeli,
ktorú funkciu v ESPčku budeme volať.
Potom vyrobíme html blok, v ktorom bude tento ovládací prvok, jeho popis, slider a tlačítko.
Tlačítku tiež nastavíme text.

.. code-block:: javascript

   class SliderFunctionButton {
      constructor(function_index){
        this.function_index = function_index;
        this.el = $e("div", [["class", "card"]], document.getElementById("content"));
        this.description = $e("div", [], this.el);

        this.slider = $e("input", [["type", "range"], ["min", "0"], ["max", "2000"]], this.el);

        this.button = $e("button", [], this.el);
        this.button.innerHTML = "function: "+function_index;

Následne potrebujeme nastaviť, čo sa má stať po kliknutí na tlačítko:

.. code-block:: javascript

   this.button.addEventListener('click', ev => {
     console.log('{"method": "function", "index":'+this.function_index+', "args":\'{"time":'+this.slider.value+'}\'}')
     websocket.send('{"method": "function", "index":'+this.function_index+', "args":\'{"time":'+this.slider.value+'}\'}');
   });

Po stlačení tlačítka zalogujeme do javascript konzoly,
čo presne odosielame (:code:`console.log(...)`).
Potom toto aj odošleme do ESPčka (:code:`websocket.send(...)`).

Posielame index do poľa funkcií v ESPčku, a hodnotu slidra,
ktorú získavame ako :code:`this.slider.value`.

Pozrime sa teraz do :code:`handleMessage.ino`:

Na začiatku súboru je definícia funkcie :code:`doBlink`, ktorú voláme.

To čo robí je okomentované už aj v kóde:

.. code-block:: cpp
   
   void doBlink(String args){
     // kvoli posielaniu argumentov na DEBUG log
     // nahradime uvodzovky apostrofmi
     args.replace("\"", "\'");
     sendDebugMessage(DEBUG, "zavolana funkcia doBlink s argumentami: "+args);
     
     // rozparsujeme argumenty
     DynamicJsonDocument doc(1024);
     deserializeJson(doc, args);
     
     // ziskame zo spravy cas, ako dlho ma LEDka svietit
     int time = doc["time"]
     
     digitalWrite(LED_PIN, LOW);
     delay(time);
     digitalWrite(LED_PIN, HIGH);
     delay(time);
   }
   
Tiež musíme túto funkciu vložiť do poľa funkcií ESPčka, ktoré chceme volať z mobilu (okolo riadku 30):

.. code-block:: cpp

   // definitions of functions, which you can call from ESP
   void (*functions[])(String) = {doBlink, blinkOnTouch};
   
Keďže sme do klienta napísali, že bude na indexe 0, tak ju sem do poľa musíme dať na tento index.

Zvyšok už za nás urobí funkcia :code:`handleMessage` (na konci súboru). 
Na jej konci je, že v prípade, že správa z ESPčka hovorí o tom, že treba zavolať funkciu,
tak to urobí (zaindexuje do poľa, a zavolá ju).


Tlačítko ovládajúce funkciu 1
----------------------------------------------

Táto funkcia ukazuje, ako môžete z mobilu zapínať niečo,
čo bude na ESP bežať, kým to nevypnete (napríklad sledovanie čiary).

Najprv si do poľa :code:`input_elements` v `index.ino` dole,
okolo riadku 185 pridáme triedu, ktorou budeme 
volať funkciu. V našom prípade to bude trieda
`BlinkFunctionButton`.

.. code-block:: javascript

   input_elements.push(new BlinkFunctionButton(0));
   
Definícia tejto triedy je okolo riadku 150, rozoberme si ju.
Podobne ako pri prechádzajúcej funkcii si najprv vytvoríme html elementy,
ktorými ju budeme ovládať. (Ukladáme si index funkcie, vytvárame celý element, popis, tlačítko.)

.. code-block:: javascript

   this.function_index = function_index;
   this.el = $e("div", [["class", "card"]], document.getElementById("content"));
   this.description = $e("div", [], this.el);
   
   this.button = $e("button", [], this.el);
   this.button.innerHTML = "function: "+function_index;
   
Následne naprogramujeme, čo sa stane po stlačení tlačítka.
V tomto prípade je to pomerne priamočiare, keďže funkcia neočakáva žiadne argumenty.
To znamená, že iba zalogujeme do konzoly a odošleme do ESP.

.. code-block:: javascript

   this.button.addEventListener('click', ev => {
     console.log('{"method": "function", "index":'+this.function_index+', "args":\'{}\'}')
     websocket.send('{"method": "function", "index":'+this.function_index+', "args":\'{}\'}');
   });

Aby sme od funkcie mali spätnú väzbu, tak naprogramujeme aj niečo do metódy :code:`update`.
Keďže funkcia neovláda priamo žiaden port, tak v správach chodí nejaký vymyslený,
aby sme ich vedeli správne identifikovať.
Po prijatí správy nastavíme popis podľa prijatého stavu.

.. code-block:: javascript

   update(recieved_data){
     if(recieved_data.port==101)
       this.description1.innerHTML = `state: ${recieved_data.data}`;
   }

Pozrime sa teraz, ako vyzerá tento kód v ESPčku.
V súbore :code:`handleMessage` je okolo riadku 20 funkcia, ktorú voláme.

Táto funkcia najprv zaloguje prijaté argumenty:

.. code-block:: cpp

   args.replace("\"", "\'");
   sendDebugMessage(DEBUG, "zavolana funkcia doBlink s argumentami: "+args);
   
A nastaví globálnu premennú, na jej opačnú hodnotu
(ak bola pred tým `true`, teraz bude `false` a opačne).
Nakoniec zalogujeme nastavenú hodnotu s vymysleným portom (rovnakým, ako je v metóde :code:`update`).

.. code-block:: cpp

  extern bool blinking;
  blinking = !blinking;
  notifyClientsMessage(101, blinking);

Premenná :code:`blinking`, je v definovaná v súbore :code:`performLoop.ino`,
a vždy, keď sa spustí funkcia :code:`performLoop`, tak si program overí,
či je premenná nastavená na `true`, a ak áno, tak na výstup 22 (vstavaná LEDka) zapíše hodnotu,
ktorá bola prečítaná na porte 13.

.. code-block:: cpp

   if(blinking){
     digitalWrite(LED_PIN, digitalRead(13));
   }

To znamená, že prípade, že zapnete túto funkciu, tak v prípade,
že káblom prepojíte zem (port :code:`G`) a port 13, tak sa vstavaná LEDka rozsvieti,
inak ostane zhasnutá.

Slider ovládajúci 2 porty (19 a 22)
----------------------------------------------

Ako sme už písali v :ref:`suciastky`, motor je ovládaný dvomi pinmi.
Najjednoduchší spôsob, ako ho ovládať, je použíť hotovú triedu :code:`MotorSlider`.

Klasicky slider pridáte do poľa:code:`input_elements`
v `index.ino` dole, okolo riadku 185.

.. code-block:: javascript

   input_elements.push(new MotorSlider(22));

Trieda `MotorSlider` tiež urobí všetko za nás,
jediná vec, ktorú jej potrebujeme dať, sú dva porty, kde sú zapojené motory.

Element ukazujúci aktuálny stav portu (13)
----------------------------------------------

Slider treba pridať do poľa :code:`port_inputs`
v `index.ino` dole, okolo riadku 190.

.. code-block:: javascript

   port_inputs.push(new PortInput(13));

Trieda `PortInput` opäť urobí všetko za nás,
jediná vec, ktorú jej potrebujeme dať, je port, ktorý chceme sledovať.

Okrem úprav v javascripte treba tento port pridať aj do kódu k ESPčku.
V súbore :code:`checkInputs` je úplne na vrchu pole, v ktorom sú napísané všetky porty,
ktoré ESPčko sleduje a posiela do mobilu:

.. code-block:: cpp

   int ports[] = {13};

Do tohoto poľa treba napísať všetky porty, ktoré má ESPčko sledovať.