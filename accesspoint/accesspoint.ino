#include <ESP8266WiFi.h>

WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);

byte ledPin = 2;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("walkieAP", "Wemos_comm");
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();
  pinMode(ledPin, OUTPUT);
  Serial.println();
  Serial.println("Server started.");
  Serial.print("IP: ");     Serial.println(WiFi.softAPIP());
  Serial.print("MAC:");     Serial.println(WiFi.softAPmacAddress());
}


void loop() {
  WiFiClient client = server.available();
  if (!client) {return;}  // exit when server not available 
  //digitalWrite(ledPin, LOW);
  String request = client.readStringUntil('\r');  // get received audio data
  Serial.println("From the client val: " + request);
  int speekerVal = request.toInt();
 // Serial.println("Int val: " + speekerVal);
  client.flush();  // clear connection
  
  int micVal = analogRead(A0);  // get mic data from A0 pin
  String valString = String(micVal);  // convert value to string
  
  client.println(valString+"\r"); //micVal+"\r" // send mic data
  Serial.println("Sending Mic val: " +valString);
 // digitalWrite(ledPin, HIGH);
 
 analogWrite(2, 1024-speekerVal);  // inditace received audio strenth 
 analogWrite(16, 1024-speekerVal);  //Speaker out
 
}
