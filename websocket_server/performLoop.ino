bool blinking = false;

void performLoop(){
  if(blinking){
    digitalWrite(LED_PIN, digitalRead(12));
  }
}
