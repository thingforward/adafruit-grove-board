#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Seeed_BME280.h>
// For OLED you need these libs:
// Adafruit_SSD1306, Adafruit_GFX

// OLED
#define BUTTON_A 4
#define BUTTON_B 3
#define BUTTON_C 8
#define LED 13
// BME
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_SSD1306 display = Adafruit_SSD1306();
BME280 bme;

#define LED1 A1
#define MOT 0

void setup(){
    delay(3000);
    Serial.println("test");
    Serial.begin(9600);
    //BME280 init
    if(!bme.init()){
      Serial.println("Error BME280 Initialization!");
    } else {
      Serial.println("BME280 Initialized!");
    }

    //OLED init
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    Serial.println("OLED begun");
    display.display();
    delay(1000);

    pinMode(LED1, OUTPUT);
    pinMode(MOT, INPUT);
    pinMode(BUTTON_A, INPUT_PULLUP);
    pinMode(BUTTON_B, INPUT_PULLUP);
    pinMode(BUTTON_C, INPUT_PULLUP);
    display.clearDisplay();
    display.display();

    // text display tests
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("ThingForward.io");
    display.println("Adafruit OLED Ready!");
    display.println("IP: 10.0.1.23");
    display.print("Today is: ");
    display.print(bme.getTemperature());
    display.println("C");

    display.setCursor(0,0);
    display.display();
}

void loop (){
    Serial.print("Today is: ");
    Serial.println(bme.getTemperature());
    if (! digitalRead(BUTTON_A)) display.print("A");
    if (! digitalRead(BUTTON_B)) display.print("B");
    if (! digitalRead(BUTTON_C)) display.print("C");
    delay(10);
    yield();
    display.display();

    if(digitalRead(MOT)){
	digitalWrite(LED1,HIGH);
    } else {
	digitalWrite(LED1, LOW);
    }
    delay(1500);
}
