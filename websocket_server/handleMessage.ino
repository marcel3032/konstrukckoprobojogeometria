void doBlink(String args){
  // kvoli posielaniu argumentov na DEBUG log
  // nahradime uvodzovky apostrofmi
  args.replace("\"", "\'");
  sendDebugMessage(DEBUG, "zavolana funkcia doBlink s argumentami: "+args);
  
  // rozparsujeme argumenty
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, args);
  
  // ziskame zo spravy cas, ako dlho ma LEDka svietit
  int time = doc["time"];
  
  digitalWrite(LED_PIN, LOW);
  delay(time);
  digitalWrite(LED_PIN, HIGH);
  delay(time);
}

void blinkOnTouch(String args){
  // kvoli posielaniu argumentov na DEBUG log
  // nahradime uvodzovky apostrofmi
  args.replace("\"", "\'");
  sendDebugMessage(DEBUG, "zavolana funkcia doBlink s argumentami: "+args);
  
  extern bool blinking;
  blinking = !blinking;
  notifyClientsMessage(101, blinking);
}

// definitions of functions, which you can call from ESP
void (*functions[])(String) = {doBlink, blinkOnTouch};


void handleMessage(DynamicJsonDocument doc){
  int port = doc["port1"];
  String method = doc["method"];
  int value = doc["value"];
  
  if(method.compareTo("analog")==0){
    analogWrite(port, MAX_VALUE-value);
    notifyClientsMessage(port, value);
  }
  else if(method.compareTo("digital")==0){
    digitalWrite(port, 1-value);
    notifyClientsMessage(port, value);
  }
  else if(method.compareTo("motor")==0){
    int port2 = doc["port2"];
    motorWrite(port, port2, value); 
  }
  else if(method.compareTo("function")==0){
    int index = doc["index"];
    String args = doc["args"];
    if(0 <= index && index < sizeof(functions)/sizeof(functions[0]))
      (*functions[index])(args);
    else
      sendDebugMessage(WARNING, "Function index out of range");
  }
}
