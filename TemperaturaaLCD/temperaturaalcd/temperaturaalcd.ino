/*
Codigo realizado por Salvador Ruiz Sedeño el 27-9-2014 

Mas info en: http://www.frostcode.es/

Codigo para aprender a utilizar una pantarra lcd mediate i2c.
Puedes ver el Tutorial en vídeo en Youtube:http://youtu.be/4mTRnRwDnF8

*/

//Pantalla 20x4 

//Librerias necesarias
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Librerias para lector de humedad/temperatura
#include <dht.h>

LiquidCrystal_I2C lcd(0x27,20,4);

dht DHT;
#define DHT11_PIN 7

void setup()
{
  //Iniciamos el serial
  //Serial.begin(9600);
  //Iniciamos el fondo retroiluminado
  lcd.backlight();
  //Iniciamos la pantalla
  lcd.init();
}


void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  //Serial.print("Temperature = ");
  //Serial.println(DHT.temperature);
  //Serial.print("Humidity = ");
  //Serial.println(DHT.humidity);
  
  lcd.clear();//Limpiamos la LCD
    lcd.print("Temperatura: ");
    lcd.print(DHT.temperature );
  lcd.setCursor(0,1);//Saltamos a la segunda linea
    lcd.print("Humedad: ");
    lcd.print(DHT.humidity );  
  lcd.setCursor(0,2);
    lcd.print("Magtel.es");
  
  //Tiempo de espera para que reinicie el ciclo
  delay(10000);
  
}
