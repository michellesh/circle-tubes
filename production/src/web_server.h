/*
 * The webserver will attempt to connect to the primary ssid 5 times, with a delay
 * of 1 second between each attempt. If it fails to connect, it will retry
 * using the secondary ssid. The reasoning behind this: If I am at home, I want
 * it to connect to my home network. If I'm elsewhere, I want it to connect
 * to the hotspot on my phone. If it fails to connect to either, it will default
 * to its previously saved settings.
 *
 * Libraries:
 * ESPAsyncWebServer    https://github.com/me-no-dev/ESPAsyncWebServer
 * AsyncTCP             https://github.com/me-no-dev/AsyncTCP
 *
 * Include in platformio.ini:
 * lib_deps =
 *     ...
 *     ESP Async WebServer
 *     ESP Async TCP
 *     FS
 */

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "secrets.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Web server html
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Infinitube</title>
  <style>
    html { font-family: Arial; display: inline-block; }
    body { max-width: 500px; margin:0px auto; padding: 0px 7px; }
    button { width: 32%%; height: 50px; font-size: 0.9rem; }
    table { width: 100%%; }
    h2 { font-size: 2.3rem; text-align: center }
    p { font-size: 1.9rem; }
    .buttons { display: flex; flex-wrap: wrap; align-items: center; gap: 0.3em; }
    .break { flex-basis: 100%%; height: 10px; }
    .labelCol { width: 80px; }
    .valCol { width: 40px; padding-left: 14px; }
    .slider { -webkit-appearance: none; margin: 14px 0; width: 100%%;
      height: 15px; background: #FFD65C; outline: none; -webkit-transition: .2s;
      transition: opacity .2s; }
    .slider::-webkit-slider-thumb { -webkit-appearance: none; appearance: none;
      width: 25px; height: 25px; background: #003249; cursor: pointer; }
    .slider::-moz-range-thumb { width: 25px; height: 25px; background: #003249;
      cursor: pointer; }
  </style>
</head>
<body>
  <h2>Circle Tubes</h2>

  <h3>Sliders</h3>
  <table border="0">
  <tr>
    <td class="labelCol"><label for="speedSlider">Speed</label></td>
    <td><input type="range" id="speedSlider" onchange="sendData('s',this.value)" min="1" max="10" value="%SPEEDVALUE%" step="1" class="slider"></td>
    <td class="valCol"><span id="speedValue">%SPEEDVALUE%</span></td>
  </tr>
  <tr>
    <td class="labelCol"><label for="offsetSlider">Offset</label></td>
    <td><input type="range" id="offsetSlider" onchange="sendData('d',this.value)" min="1" max="10" value="%OFFSETVALUE%" step="1" class="slider"></td>
    <td class="valCol"><span id="offsetValue">%OFFSETVALUE%</span></td>
  </tr>
  <tr>
    <td class="labelCol"><label for="widthSlider">Width</label></td>
    <td><input type="range" id="widthSlider" onchange="sendData('w',this.value)" min="1" max="10" value="%WIDTHVALUE%" step="1" class="slider"></td>
    <td class="valCol"><span id="widthValue">%WIDTHVALUE%</span></td>
  </tr>
  <tr>
    <td class="labelCol"><label for="brightnessSlider">Brightness</label></td>
    <td><input type="range" id="brightnessSlider" onchange="sendData('b',this.value)" min="0" max="255" value="%BRIGHTNESSVALUE%" step="1" class="slider"></td>
    <td class="valCol"><span id="brightnessValue">%BRIGHTNESSVALUE%</span></td>
  </tr>
  <tr>
    <td class="labelCol"><label for="fadeSlider">Fade</label></td>
    <td><input type="range" id="fadeSlider" onchange="sendData('f',this.value)" min="0" max="100" value="%FADEVALUE%" step="1" class="slider"></td>
    <td class="valCol"><span id="fadeValue">%FADEVALUE%</span></td>
  </tr>
  </table>

  <div>
    <input type="checkbox" id="reverse" name="reverse" onclick="sendData('r',this.value)" />
    <label for="reverse">Reverse</label>
  </div>

  <h3>Patterns</h3>
  <div class="buttons">
    <button type="button" onclick="sendData('p',0)">Noise</button>
    <div class="break"></div>
  </div>

  <h3>Color Palettes</h3>
  <div class="buttons">
    <button type="button" onclick="sendData('c',0)">OrangePurpleBlue</button>
    <button type="button" onclick="sendData('c',1)">BluesAndPurples</button>
    <button type="button" onclick="sendData('c',2)">PinkCloudUpdate</button>
    <button type="button" onclick="sendData('c',3)">RedRoseLavendar</button>
    <button type="button" onclick="sendData('c',4)">TealYellow</button>
    <div class="break"></div>
  </div>


<script>
  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  window.addEventListener('load', onLoad);

  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage; // <-- add this line
  }

  function onOpen(event) {
    console.log('Connection opened');
    document.getElementById('autoBtn').style.backgroundColor = '#baffb3';
  }

  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }

  function onMessage(event) {
    var dataType = event.data.charAt(0);
    var dataValue = event.data.substring(1);
    switch (dataType){
    case 's':
      document.getElementById('speedValue').innerHTML = dataValue;
      document.getElementById('speedSlider').value = dataValue;
      break;
    case 'd':
      document.getElementById('offsetValue').innerHTML = dataValue;
      document.getElementById('offsetSlider').value = dataValue;
      break;
    case 'w':
      document.getElementById('widthValue').innerHTML = dataValue;
      document.getElementById('widthSlider').value = dataValue;
      break;
    case 'b':
      document.getElementById('brightnessValue').innerHTML = dataValue;
      document.getElementById('brightnessSlider').value = dataValue;
      break;
    case 'f':
      document.getElementById('fadeValue').innerHTML = dataValue;
      document.getElementById('fadeSlider').value = dataValue;
      break;
    }
  }

  function onLoad(event) {
    initWebSocket();
  }

  function sendData(type, val) {
    console.log(type+val);
    websocket.send(type+val);
  }
</script>
</body>
</html>
)rawliteral";

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    Serial.println((char*)data);
    String message = String((char*)data);
    char dataType = message.charAt(0);
    String dataValue = message.substring(1);

    switch (dataType) {
      case 's':
        globalSpeed = dataValue.toInt();
        ws.textAll(message);
        break;
      case 'd':
        globalOffset = dataValue.toInt();
        ws.textAll(message);
        break;
      case 'w':
        globalWidth = dataValue.toInt();
        ws.textAll(message);
        break;
      case 'r':
        globalReverse = !globalReverse;
        ws.textAll(message);
        break;
      case 'b':
        globalBrightness = dataValue.toInt();
        ws.textAll(message);
        break;
      case 'f':
        globalFade = dataValue.toInt();
        ws.textAll(message);
        break;
      case 'p':
        activePatternIndex = dataValue.toInt();
        ws.textAll(message);
        break;
      case 'c':
        palette.setPalette(dataValue.toInt());
        ws.textAll(message);
        break;
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
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

String processor(const String& var){
  if(var == "SPEEDVALUE"){
    return String(globalSpeed);
  }
  if(var == "OFFSETVALUE"){
    return String(globalOffset);
  }
  if(var == "WIDTHVALUE"){
    return String(globalWidth);
  }
  if(var == "BRIGHTNESSVALUE"){
    return String(globalBrightness);
  }
  if(var == "FADEVALUE"){
    return String(globalFade);
  }
  return "";
}

void setupWebServer(){

  uint8_t connectionAttempts = 0;

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay (1000);
    Serial.println("Connecting to primary WiFi ...");
    connectionAttempts++;
    if (connectionAttempts > 5) break;
  }

  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid2, password2);
    delay (1000);
    Serial.println("Connecting to secondary WiFi ...");
    connectionAttempts++;
    if (connectionAttempts > 10) break;
  }

  // Print ESP Local IP Address
  Serial.print("Local IP address: ");
  Serial.println(WiFi.localIP());

  initWebSocket();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  server.begin();
}