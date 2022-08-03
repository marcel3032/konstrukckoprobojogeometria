void doBlink(String args){
  args.replace("\"", "\'");
  sendDebugMessage(DEBUG, "zavolana funkcia doBlink s argumentami: "+args);
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, args);
  digitalWrite(ledPin, LOW);
  delay(doc["time"]);
  digitalWrite(ledPin, HIGH);
  delay(doc["time"]);
}

// definitions of functions, which you can call from ESP
void (*functions[4])(String) = {doBlink};


void handleMessage(DynamicJsonDocument doc){
  bool call_function = doc["call_function"];
  if(call_function){
    int index = doc["index"];
    String args = doc["args"];
    (*functions[index])(args);
  } else {
    int port = doc["port1"];
    String method = doc["method"];
    int value = doc["value"];
    if(method.compareTo("analog")==0){
      analogWrite(port, 255-value);
      notifyClientsMessage(port, value);
    }
    if(method.compareTo("digital")==0){
      digitalWrite(port, value);
      notifyClientsMessage(port, value);
    }
    if(method.compareTo("motor")==0){
      int port2 = doc["port2"];
      motorWrite(port, port2, value); 
    }
    
  }
}
