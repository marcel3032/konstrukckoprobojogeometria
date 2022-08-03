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
    long index = doc["index"];
    String args = doc["args"];
    (*functions[index])(args);
  } else {
    long port = doc["port"];
    bool analog = doc["analog"];
    long value = doc["value"];
    if(analog)
      analogWrite(port, value);
    else
      digitalWrite(port, value);  
    notifyClientsMessage(port, value);
  }
}