const delay_time = 600;
// js, ktorý inicializuje websocket

const char init_js[] PROGMEM = R"rawliteral(
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

const $e = (elName, cl, parEl) => {
  let e = document.createElement(elName);
  cl.forEach( val => e.setAttribute(val[0], val[1]));

  if (parEl) parEl.appendChild (e);
  return e;
}
)rawliteral";
