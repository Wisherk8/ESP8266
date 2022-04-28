

/*
Тестировалось на Arduino IDE 1.8.5
Дата тестирования 25.10.2017г.
*/ 

#include "ESP8266WiFi.h"                                // Подключаем библиотеку ESP8266WiFi
#include "Adafruit_Sensor.h"                            // Adafruit_Sensor
#include "DHT.h"                                        // Подключаем библиотеку DHT
#include "WiFiUDP.h"                                // Подключает библиотеку UDP

const char* ssid = "test";               // Название Вашей WiFi сети
const char* password = "123456789";          // Пароль от Вашей WiFi сети

#define DHTPIN 2                                        // Пин к которому подключен датчик
#define DHTTYPE DHT11                                   // Используемый датчик DHT 11
  // #define DHTTYPE DHT21
  // #define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);                               // Инициализируем датчик
WiFiServer server(80);                                  // Указываем порт Web-сервера
WiFiUDP Udp;
int counter = 1;                                         // Счетчик
String name = "dht02";                                     // Имя контроллера
void setup() 
{
  WiFiUDP Udp;
  Serial.begin(115200);                                 // Скорость передачи 115200 
  delay(10);                                            // Пауза 10 мкс
  dht.begin();                                          // Инициализация DHT
                             
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
   server.begin();                                      // Запуск Web сервера
   Serial.println("Web server running.");               // Печать "Веб-сервер запущен"
   delay(10000);                                        // Пауза 10 000 мкс
   Serial.println(WiFi.localIP());                      // Печатаем полученный IP-адрес ESP

}
void loop() 
{
 while(true){
  float t = dht.readTemperature();                  // Запрос на считывание температуры
  float h = dht.readHumidity();
  //String ts = String(counter) + " Temperature = " + String(t);
  //String hs = String(counter) + " Humidity = " + String(h);
  String out = name + " C" + String(counter) + " Temperature = " + String(t) + " Humidity = " + String(h);
  //char tc[32];
  //char hc[32];
  char outu[64];
  
  //Serial.print("Temperature = ");
  //Serial.println(ts); 
  //Serial.print("Humidity = ");                                                                          
  //Serial.println(hs);
  Serial.println(out);
  //ts.toCharArray(tc,32);
  //hs.toCharArray(hc,32);
  out.toCharArray(outu,64);
  Udp.beginPacket("192.168.47.1", 43210);
  //Udp.write("Temperature = ");
  Udp.write(outu);
  //Udp.write("|");
  //Udp.write("Humidity = ");
  //Udp.write(hc);
  Udp.endPacket();
  counter++;
  delay(5000);  
  }                // Получаем данные, посылаемые клиентом 
  
 

}
