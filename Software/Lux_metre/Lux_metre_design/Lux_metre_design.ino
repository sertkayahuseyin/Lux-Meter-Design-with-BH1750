#include <BH1750.h>
#include <Wire.h>
#include<LiquidCrystal.h>

BH1750 lightMeter(0x23);
LiquidCrystal lcd (2, 3, 4, 5, 6, 7);
int R = 9;
int G = 10;
int B = 11;
int buzzer = 12;

void setup() {
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Wire.begin();
  lcd.begin(16, 2);
  lcd.print("EEM418 LUX Metre");
  lcd.setCursor(0, 1);
  lcd.print("    Tasarimi     ");
  delay(2000);

  lcd.clear();
  Serial.begin(9600);
  Wire.begin();

  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println(F("BH1750 Advanced begin"));
  } else {
    Serial.println(F("Error initialising BH1750"));
  }
}

void loop() {
  if (lightMeter.measurementReady()) {
    float lux = lightMeter.readLightLevel();
    lcd.print(" Isik Yogunlugu   ");
    lcd.setCursor(6, 1);
    lcd.print(lux);
    lcd.print("   ");
    if (lux < 300) {
      //Sarı LED
      analogWrite(R, 255);
      analogWrite(G, 255);
      analogWrite(B, 0);
    }
    if (lux > 300 && lux < 600) {
      //Kırmızı LED
      analogWrite(R, 255);
      analogWrite(G, 0);
      analogWrite(B, 255);
    }
    if (lux > 600) {
      //Yeşil LED
      analogWrite(R, 0);
      analogWrite(G, 255);
      analogWrite(B, 255);
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      delay(1000);
    }

  }
}
