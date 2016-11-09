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
#include <SoftwareSerial.h>

//Librerias para lector de humedad/temperatura
#include <dht.h>

LiquidCrystal_I2C lcd(0x27,20,4);

// Connect HM10      Arduino Uno
int bluetoothTx = 8;
int bluetoothRx = 9;

SoftwareSerial BluetoothSerial(bluetoothTx, bluetoothRx);

dht DHT;
#define DHT11_PIN 7

void setup()
{
  //Iniciamos el fondo retroiluminado
  lcd.backlight();
  //Iniciamos la pantalla
  lcd.init();

  //Iniciamos el serial
  Serial.begin(9600);
  BluetoothSerial.begin(9600);
  
  while(!Serial){}
  
  // Should respond with OK
  BluetoothSerial.print("AT");
  waitForResponse();

  BluetoothSerial.print("AT+UUID?");
  waitForResponse();   
  
  BluetoothSerial.print("AT+CHAR?");
  waitForResponse();

  BluetoothSerial.print("AT+ADDR?");
  waitForResponse();  

  BluetoothSerial.print("AT+VERS?");
  waitForResponse();  

  BluetoothSerial.print("AT+HELP?");
  waitForResponse();            
}

// Function to pass BlueTooth output through to serial port output
void waitForResponse() {
  delay(1000);
  while (BluetoothSerial.available()) {
    Serial.write(BluetoothSerial.read());
  }
  Serial.write("\n");
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
