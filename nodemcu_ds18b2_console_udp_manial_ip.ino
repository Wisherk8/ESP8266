
// Including the ESP8266 WiFi library s1
#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFiUdp.h>

// Replace with your network details
const char* ssid = "test";
const char* password = "123456789";

// Data wire is plugged into pin D1 on the ESP8266 12-E - GPIO 5
#define ONE_WIRE_BUS 2 // Соотвествует D4

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

WiFiUDP udp;

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature DS18B20(&oneWire);
char temperatureCString[6];
char temperatureFString[6];
IPAddress ip(192, 168, 47, 101);
IPAddress gateway(192,168,47,1);
IPAddress subnet(255,255,255,0);
// only runs once on boot
void setup() {
  // Initializing serial port for debugging purposes
  Serial.begin(9600);
  delay(10);

  DS18B20.begin(); // IC Default 9 bit. If you have troubles consider upping it 12. Ups the delay giving the IC more time to process the temperature measurement
  
  // Connecting to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  
  //!Serial.println("Web server running. Waiting for the ESP IP...");
  //!delay(10000);
  
  // Printing the ESP IP address
  Serial.println(WiFi.localIP());
}

void getTemperature() {
  float tempC;
  float tempF; 
  do {
    DS18B20.requestTemperatures(); 
    tempC = DS18B20.getTempCByIndex(0);
    dtostrf(tempC, 2, 2, temperatureCString);
    tempF = DS18B20.getTempFByIndex(0);
    dtostrf(tempF, 3, 2, temperatureFString);
    udp.beginPacket("192.168.47.1",43210);
    udp.write("T:");
    udp.write(dtostrf(tempC, 2, 2, temperatureCString));
    udp.write("\n");
    udp.endPacket();
    delay(100);
    Serial.print("T:");
    Serial.println(tempC);
    int bytesSent = Serial.println("hello from Arduino");
  } while (tempC == 85.0 || tempC == (-127.0));
}

// runs over and over again
void loop() {
  getTemperature();
  delay(5000);
}   
