// client programme
#include <ESP8266WiFi.h>

byte ledPin = 2;
char ssid[] = "walkieAP";           // SSID of your Access Point
char pass[] = "Wemos_comm";         // password of your AP

IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;  // create wifi client

void setup() {
  Serial.begin(9600);  // start serial monitor for debug and view data transmisiton 
  WiFi.mode(WIFI_STA);  // act as wifi client
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {  // wait for connect AP
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.println("station_bare_01.ino");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
  pinMode(ledPin, OUTPUT); // for indicator bulb
  pinMode(16, OUTPUT);  // for speaker out
  client.connect(server, 80);  // server and port
}

void loop() {
 
  int micVal = analogRead(A0); // get ,ic input
  client.connect(server, 80);  // connect server

 String valString = String(micVal);  
  Serial.println("Sending Mic val as client: " + valString);
  client.print(valString+"\r"); // micVal+"\r"  // send mic data
  
  String answer = client.readStringUntil('\r');  // get received audio data 
  Serial.println("From the server: " + answer);
  int speekerVal = answer.toInt();            // convert to integer
  //Serial.println("Int val : " + speekerVal);
  client.flush();  // clear connection
  
 analogWrite(2, 1024-speekerVal);  // indicator show
 analogWrite(16, 1024-speekerVal);  //Speaker out
 //delay(1);
}
