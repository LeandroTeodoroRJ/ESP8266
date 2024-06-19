/*
 * Project name: Sensor Webserver
 * Description: Show on browser humidity and temperature from DHT11 sensor
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 1.0
 * Last Uptate: 11.06.24
 * Dependences: genericWiFi
 * Current: Yes
 * Maintainer: leandroteodoro.engenharia@gmail.com
 * Architecture: ModeMCU Ver3.0 - ESP8266
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes: No
 *
 */

#include "genericWiFi.h"
#include "DHT.h"

#define DHTPIN 5        // Output pin from DHT11
#define DHTTYPE DHT11   // DHT 11
#define TIME_10_MS    10
#define RATE_115KBPS  115200
#define CLIENT_NOT_CONNECTED 0
#define HTTP_PORT 80
#define TIME_TO_REQUEST_MS 1
#define BOTH_MESURE_ERROR 1

const char* ssid = SSID_NAME;     //wifi ssid name --string
const char* password = PASSWORD;  //wifi password --string

String html_template = "";  
struct dataMesure{
  float humidity; 
  float temperature;
};
struct dataMesure mesure;

WiFiServer server(HTTP_PORT);
DHT dht(DHTPIN, DHTTYPE);

bool mesureIsNotValid(float humidity, float temperature);
void showReadErrorMessage();

void setup() {
  serialMonitorStart();
  WiFi.begin(ssid, password);
  WifiWatingConnect();
  startWebServer();
  showServerStatus();  
  makeHTMLTemplate();  
}

void serialMonitorStart(){ 
    Serial.begin(RATE_115KBPS);
    delay(TIME_10_MS);
}

void startWebServer(){
  server.begin();
  Serial.println("Start Web Server!");
}

void showServerStatus(){
  Serial.println("");
  Serial.println("Connected!");  
  Serial.print("Server IP:");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void makeHTMLTemplate(){
  html_template += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  html_template += "<h3>Webserver with DHT11 Sensor.</h3>";
  html_template += "<p>Humidity and Temperature</p>";
}

void loop() {
  WiFiClient client = server.available();
  if (client == CLIENT_NOT_CONNECTED) {
    return;
  }
  else{
    Serial.println("New Client");
  }  

  mesure.humidity = dht.readHumidity(); 
  mesure.temperature = dht.readTemperature(); 

  try{
    if (mesureIsNotValid(mesure)){
    throw(BOTH_MESURE_ERROR);
    return;
    }
  }
  catch(int code){
    showReadErrorMessage();
  }

  waitingGetResquest(client); 
  responseTemplate(client, mesure);
}

bool mesureIsNotValid(dataMesure data){
  return isnan(data.humidity) || isnan(data.temperature);
}

void showReadErrorMessage(){
  Serial.println("Falha na leitura!");
}

void waitingGetResquest(WiFiClient client_request){
  while (!client_request.available()) {
    delay(TIME_TO_REQUEST_MS);
  }
}

void responseTemplate(WiFiClient client_request, dataMesure data){
  client_request.print(html_template);  
  client_request.print(data.humidity);
  client_request.print(" %   ");
  client_request.print("<br>");
  client_request.print(data.temperature);
  client_request.print(" Celsius");
  client_request.print("</html>");
  delay(TIME_TO_REQUEST_MS);
  Serial.println("");
}