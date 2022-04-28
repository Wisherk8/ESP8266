



#include "ESP8266WiFi.h"                                // Подключаем библиотеку ESP8266WiFi

#include "WiFiUDP.h"                                // Подключает библиотеку UDP
#include "MAX6675_Thermocouple.h"

const char* ssid = "test";               // Название Вашей WiFi сети
const char* password = "123456789";          // Пароль от Вашей WiFi сети

#define SCK_PIN 15 //D8
#define CS_PIN 13 //D7
#define SO_PIN 12 //D6

WiFiUDP Udp;
int counter = 1;                                        // Счетчик
MAX6675_Thermocouple* thermocouple = NULL;

void setup() 
{
  WiFiUDP Udp;
  Serial.begin(115200);                                 // Скорость передачи 115200 
  delay(10);                                            // Пауза 10 мкс
  
                             
  Serial.println("");                                   // Печать пустой строки 
  Serial.print("Connecting to ");                       // Печать "Подключение к:"
  Serial.println(ssid);                                 // Печать "Название Вашей WiFi сети"
  
  WiFi.begin(ssid, password);                           // Подключение к WiFi Сети
  
  while (WiFi.status() != WL_CONNECTED)                 // Проверка подключения к WiFi сети
  {
   delay(500);                                          // Пауза 500 мкс
   Serial.print(".");                                   // Печать "."
  }
   Serial.println("");                                  // Печать пустой строки                                          
   Serial.println("WiFi connected");                    // Печать "Подключение к WiFi сети осуществлено"
  
  
   delay(10000);                                        // Пауза 10 000 мкс
   Serial.println(WiFi.localIP());                      // Печатаем полученный IP-адрес ESP

   thermocouple = new MAX6675_Thermocouple(SCK_PIN, CS_PIN, SO_PIN);

}
void loop() 
{
 while(true){
 MAX6675_Thermocouple thermocouple(SCK_PIN, CS_PIN, SO_PIN);

    // Read a temperature in Celsius.
    double celsius = thermocouple.readCelsius();
    // Read a temperature in Kelvin.
    double Kelvin = thermocouple.readKelvin();
    // Read a temperature in Fahrenheit.
    double fahrenheit = thermocouple.readFahrenheit();
  Serial.print("Temperature: ");
  Serial.print(String(celsius) + " C, ");
  Serial.print(String(Kelvin) + " K, ");
  Serial.println(String(fahrenheit) + " F");
  String out = String(counter) + "_" + String(celsius);
  char outu[64];
  out.toCharArray(outu,64);
  Udp.beginPacket("192.168.1.255", 43210); 
  Udp.write(outu);
  Udp.endPacket();
  

  
  
  //Udp.beginPacket("192.168.1.255", 43210); 
  //Udp.write(counter);
  //Udp.endPacket();
  //Udp.beginPacket("192.168.1.255", 43210); 
  //Udp.write(celsius);
  //Udp.endPacket();
  counter++;
  delay(1000);  
  }                // Получаем данные, посылаемые клиентом 
  
 

}
