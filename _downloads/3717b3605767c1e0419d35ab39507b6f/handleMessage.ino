void doBlink(String args){
  // kvoli posielaniu argumentov na DEBUG log
  // nahradime uvodzovky apostrofmi
  args.replace("\"", "\'");
  sendDebugMessage(DEBUG, "zavolana funkcia doBlink s argumentami: "+args);
  
  // rozparsujeme argumenty
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, args);
  
  digitalWrite(LED_PIN, LOW);
  delay(doc["time"]);
  digitalWrite(LED_PIN, HIGH);
  delay(doc["time"]);
}

// definitions of functions, which you can call from ESP
void (*functions[])(String) = {doBlink};


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
    (*functions[index])(args);
  }
}
