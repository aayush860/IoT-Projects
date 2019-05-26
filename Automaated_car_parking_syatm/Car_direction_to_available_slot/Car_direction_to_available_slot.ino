#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "Aayush";
const char* password = "aayush.860";
const int f1=5;
const int r1=4;
const int ri1=0;
const int l1=2;



ESP8266WebServer server(80);

const int led = 16;

void fwd()
{
  digitalWrite(f1, HIGH);   // Turn the LED on (Note that LOW is the voltage level
  digitalWrite(r1, LOW);   // Turn the LED on (Note that LOW is the voltage level
  digitalWrite(ri1, HIGH);   // Turn the LED on (Note that LOW is the voltage level
  digitalWrite(l1, LOW);   // Turn the LED on (Note that LOW is the voltage level
}

void right()
{
  digitalWrite(f1, LOW);   // Turn the LED on (Note that LOW is the voltage level
  digitalWrite(r1, LOW);   // Turn the LED on (Note that LOW is the voltage level
  digitalWrite(ri1, HIGH);   // Turn the LED on (Note that LOW is the voltage level
  digitalWrite(l1, LOW);   // Turn the LED on (Note that LOW is the voltage level
}

void left()
{
  digitalWrite(f1, LOW);   // Turn the LED on (Note that LOW is the voltage level
  digitalWrite(r1, LOW);   // Turn the LED on (Note that LOW is the voltage level
  digitalWrite(ri1, LOW);   // Turn the LED on (Note that LOW is the voltage level
  digitalWrite(l1, HIGH);   // Turn the LED on (Note that LOW is the voltage level
}

void stopp()
{
  digitalWrite(f1, LOW);   // Turn the LED on (Note that LOW is the voltage level
  digitalWrite(r1, LOW);   // Turn the LED on (Note that LOW is the voltage level
  digitalWrite(ri1, LOW);   // Turn the LED on (Note that LOW is the voltage level
  digitalWrite(l1, LOW);   // Turn the LED on (Note that LOW is the voltage level
}

void lr(String x)
{
  if(x=="R")
{
  right();
  delay(1500);
}
else if(x=="L")
{
  left();
  delay(1500);
}
else
{
  fwd();
}
}


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
  message += (server.method() == HTTP_GET)?"GET":"POST";
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
  digitalWrite(led, 0);
pinMode(f1, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
pinMode(r1, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
pinMode(l1, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
pinMode(ri1, OUTPUT);     // Initialize the BUILTIN_LED pin as an output

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
  const char* host="api.thingspeak.com";
  WiFiClient client;
  const int httpport1=80;
  if(!client.connect(host,httpport1))
  {
    Serial.println("failed");
  }
    String url="/apps/thinghttp/send_request?api_key=5JVMHQUO3465PHHD";
  //String url="/apps/thinghttp/send_request?api_key=58TNGC5RBMDIBFNP";
  client.print(String("GET ") + url + " HTTP/1.0\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(10000);
  
int yyy=0;



//Serial.print(yyy);
  
  while(client.available()){
    String line = client.readStringUntil('\r');
if(yyy>17)
{    
      int index1=line.indexOf("<p>");
      int index2=line.indexOf("</p>");

      String fival=line.substring(index1+26,index2-23);

     //     Serial.print("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    Serial.println(fival);

  int index3=fival.indexOf(",");
    int index4=fival.indexOf(",",index3+1);
      int index5=fival.indexOf(",",index4+1);
        int index6=fival.indexOf(",",index5+1);
          int index7=fival.indexOf(",",index6+1);
            int index8=fival.indexOf(",",index7+1);
              int index9=fival.indexOf(",",index8+1);
                int index10=fival.indexOf(",",index9+1);
                  int index11=fival.indexOf(",",index10+1);
                    int index12=fival.indexOf(",",index11+1);
                      int index13=fival.indexOf(",",index12+1);

//FIRST
String sec1=fival.substring(0,index3);
fwd();
delay(sec1.toInt());

String dir1=fival.substring(index3+1,index4);
lr(dir1);


//SECOND
String sec2=fival.substring(index4+1,index5);
fwd();
delay(sec2.toInt());

String dir2=fival.substring(index5+1,index6);
//lr(dir2);


/*
//THIRD
String sec3=fival.substring(index6+1,index7);
fwd();
delay(sec3.toInt());

String dir3=fival.substring(index7+1,index8);
lr(dir3);    


//FOURTH
String sec4=fival.substring(index8+1,index9);
fwd();
delay(sec4.toInt());

String dir4=fival.substring(index9+1,index10);
lr(dir4);    


//FIFTH
String sec5=fival.substring(index10+1,index11);
fwd();
delay(sec5.toInt());

String dir5=fival.substring(index11+1,index12);
lr(dir5);
*/    
    stopp();
    Serial.println(sec1);
    Serial.println(dir1);
    Serial.println(sec2);
    Serial.println(dir2);

    delay(30000);
}
yyy++;  

}
  Serial.println();
  Serial.println("closing connection");
  server.handleClient();
}
