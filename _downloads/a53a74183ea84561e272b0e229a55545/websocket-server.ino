/*
  Web server is running at http://192.168.4.1/
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "ESP1";
const char* password = "12345678";

const int ledPin = 22;
extern const char index_html[];

//debug levels
String DEBUG = "DEBUG";
String INFO = "INFO";
String WARNING = "WARNING";
String ERROR = "ERROR";

const int MAX_VALUE = 255;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void notifyClientsMessage(long port, long value) {
  ws.textAll("{ \"type\": \"message\", \"data\": "+String(value)+", \"port\": "+String(port)+"}");
  sendDebugMessage(DEBUG, "na vystup portu "+String(port)+" som dal: "+String(value));
}

void notifyClientsInput(long port, int value) {
  ws.textAll("{ \"type\": \"input_changed\", \"data\": "+String(value)+", \"port\": "+String(port)+"}");
  sendDebugMessage(DEBUG, "na vstupe portu "+String(port)+" som precital: "+String(value));
}

void sendDebugMessage(String level, String message){
  ws.textAll("{ \"type\": \"debug\", \"level\": \""+level+"\", \"date\": "+String(millis())+", \"data\": \""+message+"\"}");
}

void motorWrite(int port1, int port2, int value){
  if(value < -MAX_VALUE){
    sendDebugMessage(WARNING, "Value for motor write was lower than -255, setting output to -255");
    value = -MAX_VALUE;
  }
  if(value > MAX_VALUE){
    sendDebugMessage(WARNING, "Value for motor write was greater than +255, setting output to 255");
    value = MAX_VALUE;
  }
  
  int value1 = MAX_VALUE-(int)max(0, value);
  analogWrite(port1, value1);
  notifyClientsMessage(port1, MAX_VALUE-value1);

  int value2 = MAX_VALUE+(int)min(0, value);
  analogWrite(port2, value2);
  notifyClientsMessage(port2, MAX_VALUE-value2);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, data);
    handleMessage(doc);
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      sendDebugMessage(DEBUG, "Client successfully connected");
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

void setup(){
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  setInputsAsInput();

  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  
  Serial.println("Server started");

  initWebSocket();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.begin();
}

void loop() {
  ws.cleanupClients();
  checkInputs();
}
