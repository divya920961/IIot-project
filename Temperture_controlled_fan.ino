#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

// Hardware Pins
#define DHTPIN 1     
#define DHTTYPE DHT11
#define Fan 2


// Initialize LCD and Sensor
// If 0x27 doesn't work, try 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2); 
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  dht.begin();
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("System Starting");
  delay(1500);
  lcd.clear();
  pinMode(Fan,OUTPUT);
}

void loop() {
  // 1. Read the actual temperature
  float Temp = dht.readTemperature();
  float Hum = dht.readHumidity();
  

  // Check if sensor is working
  if (isnan(Temp)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!   ");
    return;
  }

  // Row 1: Actual Temp
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(Temp, 1);
  lcd.print((char)223); // Degree symbol
  lcd.print("C   ");

  lcd.setCursor(0, 1);
  lcd.print("Humidity");
  lcd.print(Hum);
  lcd.print(" % ");


  
  lcd.setCursor(10, 1);
  if (Temp > 40 ) {
    lcd.print("FAN:ON ");
    digitalWrite(Fan,HIGH);
  } else {
    lcd.print("FAN:OFF");
     digitalWrite(Fan,LOW);
  }

  delay(1000); // Update every second
}