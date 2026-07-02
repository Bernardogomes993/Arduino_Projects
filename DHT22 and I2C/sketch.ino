#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22

LiquidCrystal_I2C lcd(0x27 , 16 , 2);
DHT dht(DHTPIN , DHTTYPE);

unsigned long lastMeasureTime = 0;
unsigned long measureInterval = 2000;

void setup() {
  Serial.begin(9600);
  dht.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print(" Meteo Station");
  lcd.setCursor(0,1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();

}

void loop() {
  unsigned long currentTime = millis();
  if(currentTime - lastMeasureTime > measureInterval){
    lastMeasureTime = currentTime;

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if(isnan(humidity) || isnan(temperature)){
      Serial.println("{\"error\": \"Could not read  DHT22\"}");
      lcd.clear();
      lcd.setCursor(0 ,0);
      lcd.print("Sensor Fail!");
      return;
    }
    Serial.print("{\"temp\": ");
    Serial.print(temperature,1);
    Serial.print(", \"hum\": ");
    Serial.print(humidity, 1);
    Serial.println("}");

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(temperature,1);
    lcd.print((char)223);
    lcd.print("C");


    lcd.setCursor(0,1);
    lcd.print("Hum: ");
    lcd.print(humidity , 1);
    lcd.print("%");

  }

}
