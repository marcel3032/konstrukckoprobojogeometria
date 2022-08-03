int ports[] = {32,33};
long last_sent = 0;
long min_dif = 500;

void checkInputs(){
  if(last_sent+min_dif<millis()){
    last_sent = millis();
    for(int i=0; i<(sizeof(ports)/sizeof(ports[0])); i++){
      notifyClientsInput(ports[i], analogRead(ports[i]));
    }
  }
}

void setInputsAsInput(){
  for(int i=0; i<(sizeof(ports)/sizeof(ports[0])); i++){
    pinMode(ports[i], INPUT_PULLUP);
  }
}
