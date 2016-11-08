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

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

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
  bluetooth.begin(9600);
  
  while(!Serial){}
  
    Serial.write("AT sent");
  delay(500);
  bluetooth.write("AT+NAME?");
  delay(500);
  while (bluetooth.available()) {
     Serial.write(bluetooth.read());
   }
  delay(100);
  Serial.println("");

  bluetooth.write("AT+POWE3");
  delay(500);
  while(bluetooth.available()) 
  {
    Serial.write(bluetooth.read());
  }
  delay(100);
  Serial.println("");

  delay(500);
  bluetooth.write("AT+CHAR?");
  delay(500);
  while (bluetooth.available()) {
     Serial.write(bluetooth.read());
   }
  delay(100);
  Serial.println("");

  delay(500);
  bluetooth.write("AT+NAMEFlightline"); //Check Status
  delay(500);
  while (bluetooth.available()) {
      Serial.write((char)bluetooth.read());

    }

  Serial.println("");
  bluetooth.write("AT+CHAR0x2901"); //add charicteristic
  delay(500);
  while (bluetooth.available()) {
      Serial.write(bluetooth.read());

    }

  Serial.println("");
  bluetooth.write("AT+RELI0"); 
  delay(500);
  while (bluetooth.available()) {
      Serial.write(bluetooth.read());
    }
    
  Serial.println("");
  bluetooth.write("AT+SHOW1");
  delay(100);
  while (bluetooth.available()) {
      Serial.write(bluetooth.read());

    }
  Serial.println("");

    Serial.println("");
  bluetooth.write("AT+VERR?");
  delay(100);
  while (bluetooth.available()) {
      Serial.write(bluetooth.read());

    }
  Serial.println("");
 

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

  //Escribimos una característica
  //bluetooth.write("AT+CHAR0x2901"); //add charicteristic
  delay(100);
  while (bluetooth.available()) {
      Serial.write(bluetooth.read());
    }  
  
}
