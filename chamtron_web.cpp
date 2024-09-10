#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "Sam";
const char* password = "sam_2907";
bool present[10] = { 1, 0, 1, 0, 0, 0, 1, 0, 1, 0 };
String alunos[10] = {"aquilis","delwin","juliana","geciara","beija-flor","salmuel","anna","andre","gusthavo","abrao"};

AsyncWebServer server(80);

String getHTML() {
  String html = "<!DOCTYPE html>";
  html += "<html lang=\"pt-BR\">";
  html += "<head>";
  html += "<meta charset=\"UTF-8\">";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  html += "<title>Chamatron</title>";
  html += "<style>";
  html += "body { background-color: rgb(203, 219, 223); }";
  html += "div { display: flex; align-items: center; justify-content: center; }";
  html += ".button { border: none; color: white; padding: 16px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; font-weight: bold; margin: 4px 2px; transition-duration: 0.4s; cursor: pointer; border-radius: 10px; }";
  html += ".button1 { background-color: #04AA6D; color: black; }";
  html += ".button1:hover { background-color: #018152; color: white; }";
  html += ".button2 { background-color: red; color: black; }";
  html += ".button2:hover { background-color: #860202; color: white; }";
  html += "h1 { text-align: center; font-family: sans-serif; background-color: #005774; margin-top: 0px; padding: 10px; font-size: 50px; }";
  html += "table { font-family: arial, sans-serif; border-collapse: collapse; width: 70%; margin-top: 30px; }";
  html += "td { border: 2px solid #272727; text-align: left; padding: 8px; }";
  html += "th { border: 2px solid #272727; text-align: center; padding: 8px; }";
  html += "tr:nth-child(even) { background-color: #9c9c9c; }";
  html += "</style>";
  html += "</head>";
  html += "<body>";
  html += "<h1>CHAMATRON</h1>";
  html += "<div>";
  html += "<button class=\"button button1\" type=\"button\"><a href='/on'>LIGAR</a></button>";
  html += "<button class=\"button button2\" type=\"button\"><a href='/off'>DESLIGAR</a></button>";
  html += "</div>";
  html += "<div>";
  html += "<table>";
  html += "<tr><th colspan=\"2\">ALUNOS</th></tr>";
  // for (bool i : alunos)
  for (int i = 0; i < 10; i ++) {
    html += "</tr><td>" + alunos[i]+"</td>";
    if (present[i]) {
      html += "<td>presente</td></tr>";
    } else {
      html += "<td>nao presente</td></tr>";
    }
  }
  html += "";
  html += "</table>";
  html += "</div>";
  html += "</body>";
  html += "</html>";

  return html;
}

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print the ESP8266's IP address
  Serial.print("ESP8266 Web Server's IP address: ");
  Serial.println(WiFi.localIP());

  // Home page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    Serial.println("ESP8266 Web Server: New request received:");
    Serial.println("GET /");
    request->send(200, "text/html", getHTML());
  });

  // Start the server
  server.begin();
}

void loop() {
  // Add your repeating code here, if any
}
