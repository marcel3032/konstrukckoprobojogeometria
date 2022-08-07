const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <style>
  .card {
     border-style: solid;
  }
  </style>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
</head>
<body>
  <div class="content" id="content"></div>
  <div>
    <table id="debug_log" border>
    <tr><th>Time</th><th>Level</th><th>Message</th></tr>
    </table>
  </div>
<script>
  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  window.addEventListener('load', (e) => {
    initWebSocket();
  });
  
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen = (ev => { console.log('Connection opened'); });
    websocket.onclose = (ev => {
    console.log('Connection closed');
      setTimeout(initWebSocket, 2000);
  });
    websocket.onmessage = onMessage;
  }
  
  function onMessage(event) {
    let recieved_data = JSON.parse(event.data);
    if(recieved_data.type=="message"){
    buttons.forEach( b => b.update(recieved_data));
    }
  if(recieved_data.type=="input_changed"){
    port_inputs.forEach( p => p.update(recieved_data));
    }
  if(recieved_data.type=="debug"){
      document.getElementById('debug_log').innerHTML += "<tr><td>"+recieved_data.date+"</td><td>"+recieved_data.level+"</td><td>"+recieved_data.data+"</td></tr>";
    }
  }
  
  const $e = (elName, cl, parEl) => {
    let e = document.createElement(elName);
    cl.forEach( val => e.setAttribute(val[0], val[1]));

    if (parEl) parEl.appendChild (e);
    return e;
  }
  
  class PortOutput{
  constructor(port) {
    this.port = port;
    this.value = 0;
    this.el = $e("div", [["class", "card"]], document.getElementById("content"));
    this.el.innerHTML = "Port: "+port;
    this.description = $e("div", [], this.el);
    this.description.innerHTML = "current state: "+this.value;
  }
  }
  
  class OutputButton extends PortOutput{
  constructor(port) {
    super(port);
    this.button = $e("button", [], this.el);
    this.button.innerHTML = "port: "+port;
    this.button.addEventListener('click', ev => {
      let send_value = 1 - this.value;
      websocket.send('{"port1":'+this.port+', "method":"digital", "value":'+send_value+'}');
    });
  }
  
    update(recieved_data){
    if(recieved_data.port==this.port){
      this.description.innerHTML = "current state: "+recieved_data.data;
      this.value = recieved_data.data;
    }
  }
  }
  
  class Slider extends PortOutput {
  constructor(port) {
    super(port);
    this.slider = $e("input", [["type", "range"], ["min", "0"], ["max", "255"]], this.el);
    this.slider.value = 0;
    this.slider.addEventListener('input', ev => {
      let send_value = this.slider.value;
      websocket.send('{"port1":'+this.port+', "method":"analog", "value":'+send_value+'}');
    });
  }
  
    update(recieved_data){
    if(recieved_data.port==this.port){
      this.description.innerHTML = "current state: "+recieved_data.data;
      this.value = recieved_data.data;
    }
  }
  }
  
  class MotorSlider {
  constructor(port1, port2) {
    this.el = $e("div", [["class", "card"]], document.getElementById("content"));
    this.el.innerHTML = `Ports: ${port1} and ${port2}`;
    
    this.description1 = $e("div", [], this.el);
    this.description1.innerHTML = `port ${port1}: N/A`;
    
    this.description2 = $e("div", [], this.el);
    this.description2.innerHTML = `port ${port2}: N/A`;
    
    this.port1 = port1;
    this.port2 = port2;
    
    this.slider = $e("input", [["type", "range"], ["min", "-255"], ["max", "255"]], this.el);
    this.slider.value = 0;
    this.slider.addEventListener('input', ev => {
      let send_value = this.slider.value;
    console.log('{"port1":'+this.port1+', "port2":'+this.port2+', "method":"motor", "value":'+send_value+'}');
      websocket.send('{"port1":'+this.port1+', "port2":'+this.port2+', "method":"motor", "value":'+send_value+'}');
    });
  }
  
    update(recieved_data){
    if(recieved_data.port==this.port1)
      this.description1.innerHTML = `port ${this.port1}: ${recieved_data.data}`;
    if(recieved_data.port==this.port2)
      this.description2.innerHTML = `port ${this.port2}: ${recieved_data.data}`;
  }
  }
  
  class SliderFunctionButton {
  constructor(function_index){
    this.function_index = function_index;
    this.el = $e("div", [["class", "card"]], document.getElementById("content"));
    this.description = $e("div", [], this.el);
    
    this.slider = $e("input", [["type", "range"], ["min", "0"], ["max", "2000"]], this.el);
    
    this.button = $e("button", [], this.el);
    this.button.innerHTML = "function: "+function_index;
    this.button.addEventListener('click', ev => {
      console.log('{"method": "function", "index":'+this.function_index+', "args":\'{"time":'+this.slider.value+'}\'}')
      websocket.send('{"method": "function", "index":'+this.function_index+', "args":\'{"time":'+this.slider.value+'}\'}');
    });
  }
  
  update(recieved_data){ }
  }
  
  class PortInput{
  constructor(port) {
    this.port = port;
    this.value = 0;
    this.el = $e("div", [["class", "card"]], document.getElementById("content"));
    this.el.innerHTML = "Port: "+port;
    this.description = $e("div", [], this.el);
  }
  
  update(recieved_data){
    if(recieved_data.port==this.port){
      this.value = recieved_data.data;
      this.description.innerHTML = "current state: "+this.value;
    }
  }
  }
  
  var buttons = [];
  buttons.push(new OutputButton(22));
  buttons.push(new Slider(13));
  buttons.push(new Slider(22));
  buttons.push(new SliderFunctionButton(0));
  buttons.push(new MotorSlider(13,22));
  
  var port_inputs = [];
  port_inputs.push(new PortInput(32));
  port_inputs.push(new PortInput(33));
</script>
</body>
</html>
)rawliteral";
