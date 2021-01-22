#include <DHTesp.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include "rgb_lcd.h"
#include "DHT.h"

#define DHTPIN 12
#define DHTTYPE DHT11 

rgb_lcd lcd;

int colorR = 255;
int colorG = 020;
int colorB = 147;
const int BUTTON_PIN = 7;
int currentState;
int lastTemp;
unsigned long long t = millis();
int count = 0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  dht.begin();  
  Serial.print("Here we go !");

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
    
  lcd.setRGB(colorR, colorG, colorB);
}

void loop() {
  t = millis();
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  lcd.setCursor(0, 1);

  lcd.print("Temp : ");
  lcd.print(lastTemp);

  //BUTTON PART
  // read the state of the switch/button:
  currentState = digitalRead(BUTTON_PIN);
  if(currentState == 0 && (millis() - t) < 10){
    lcd.setCursor(0,0);
    lcd.print("");
    lastTemp = temperature;
    count++;
  }
  lcd.setCursor(0,0);
  if(count % 3 == 0){
    lcd.println("Oeuf de paques");
  } else {
    lcd.print("Act Temp : ");
    lcd.println(temperature);
  }
  
  Serial.println(count);
  
  if(temperature < lastTemp){
    colorR = 0;
    colorB = 255;
    colorG = 0;
  } else if (temperature > lastTemp) {
    colorR = 255;
    colorB = 0;
    colorG = 0;
  } else {
    colorR = 255;
    colorG = 020;
    colorB = 147;
  }
  lcd.setRGB(colorR, colorG, colorB);
}
