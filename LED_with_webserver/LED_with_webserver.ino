/*
 * Project name: LED Web Server
 * Description: Control a LED with a browser
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 1.0
 * Last Uptate: 15.03.24
 * Dependences: ESP8266WiFi
 * Current: Yes
 * Maintainer: leandroteodoro.rj@gmail.com
 * Architecture: ModeMCU Ver3.0 - ESP8266
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes:
 *  To the NodeMCU on-board LED the logic is inverted.
 *
 */

#include <ESP8266WiFi.h>

const char* ssid = "LAN SSID name";
const char* password = "LAN password";

WiFiServer server(80);

#define led 2

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected!");

  //Start server
  server.begin();
  Serial.println("Server Started!");

  //Server IP Address
  Serial.print("Server IP: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {
  // Initialize client object
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  String req = client.readStringUntil('\r');
  client.flush();

  String txt = "";
  
  txt += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  txt += "<h3>Led WebServer</h3>";
  txt += "<p><a href=\"ledon\"><button>TURN ON</button></a></p>";
  txt += "<p><a href=\"ledoff\"><button>TURN OFF</button></a></p>";
  txt += "</html>\n";
  client.print(txt);
  client.flush();

  if (req.indexOf("ledon") != -1)
  {
    digitalWrite(led, HIGH);
  }
  else if (req.indexOf("ledoff") != -1)
  {
    digitalWrite(led, LOW);
  }
client.stop();
}

