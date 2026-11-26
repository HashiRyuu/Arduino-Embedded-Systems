#include <LiquidCrystal.h>
#include <DHT.h>

// LCD: RS, E, D4, D5, D6, D7 (change if your LCD wiring differs)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// DHT settings
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("DHT11 + LCD1602");

  dht.begin();
  delay(1500);
  lcd.clear();
}

void loop() {
  // Read humidity and temperature (Celsius)
  float h = dht.readHumidity();
  float t = dht.readTemperature();      // Celsius
  float f = dht.readTemperature(true);  // Fahrenheit (optional)

  // If the sensor fails, reads return NaN (not a number)
  if (isnan(h) || isnan(t)) {
    lcd.setCursor(0, 0);
    lcd.print("DHT11 read FAIL ");
    lcd.setCursor(0, 1);
    lcd.print("Check wiring     ");
    delay(1000);
    return;
  }

  // Line 1: Temperature
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(t, 1);          // 1 decimal place
  lcd.print((char)223);     // degree symbol on most 1602s
  lcd.print("C  ");

  // (Optional) show Fahrenheit too, compact
  // lcd.print(f, 0);
  // lcd.print("F ");

  // Line 2: Humidity
  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(h, 0);          // no decimals (DHT11 is low-res anyway)
  lcd.print("%          "); // pad spaces to clear old text

  delay(1500); // DHT11 should not be read too fast; ~1s+ is safe
}
