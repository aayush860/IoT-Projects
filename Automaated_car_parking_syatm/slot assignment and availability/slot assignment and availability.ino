#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "Aayush";
const char* password = "axxxxxx";

ESP8266WebServer server(80);
int analogPin = 4;     // potentiometer wiper (middle terminal) connected to analog pin 3
int sen2=5;
int sen3=0;

int val = 0;           // variable to store the value read

const int led = 16;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, 0);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_POST)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void){
pinMode(led, OUTPUT);
pinMode(analogPin,INPUT);
pinMode(sen2,INPUT);
pinMode(sen3,INPUT);

digitalWrite(led, 0);
Serial.begin(115200);
WiFi.begin(ssid, password);
Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(){
  WiFi.mode(WIFI_STA);

  delay(3000);
  const char* host="iotdirection.000webhostapp.com";
  WiFiClient client;
  const int httpport1=80;
  if(!client.connect(host,httpport1))
  {
    Serial.println("failed");
  }

    
   val = digitalRead(analogPin);     // read the input pin
     int val2 = digitalRead(sen2);     // read the input pin
        int val3 = digitalRead(sen3);     // read the input pin
  //Serial.println(val);   
String vals1;
String vals2;
String vals3;

String id1;
String id2;
String id3;

if(val==1)
{
 vals1="available"; 
 id1=1;
}
else
{
  vals1="unavailable";
  id1=1;
}

if(val2==1)
{
 vals2="available"; 
 id2=2;
}
else
{
  vals2="unavailable";
  id2=2;
}

if(val3==1)
{
  id3=3;
 vals3="available"; 
}
else
{
  id3=3;
  vals3="unavailable";
}

    
    String url="/index22%20.php?avail1="+vals1+"&id1="+id1+"&avail2="+vals2+"&id2="+id2+"&avail3="+vals3+"&id3="+id3;    
  client.print(String("POST ") + url + " HTTP/1.0\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(1000);




//https://stackoverflow.com/questions/11068450/arduino-c-language-parsing-string-with-delimiter-input-through-serial-interfa


  Serial.println();
  Serial.println("closing connection");

  server.handleClient();
}
