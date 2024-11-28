#include <Arduino.h>
#include <iostream>
#include <ArduinoJson.h>


#define LED21 21
#define LED22 22

  int led_brightness = 0;
  bool increasing = true;
  JsonDocument doc;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED21, OUTPUT);
  pinMode(LED22, OUTPUT);




  
}

void loop() {
  // put your main code here, to run repeatedly:
    // Serial.println("Hello ESP32");

    if(increasing == true){
    // increase brightness value
    led_brightness = led_brightness + 1;
  }
  else{
    // decrease brightness value
    led_brightness = led_brightness - 1;
  }
  

  // if maximum brightness reached, start reducing brightness
  if(led_brightness >= 255){
    increasing = false;
  }
  // if minimum brightness reached, start increasing brightness
  else if(led_brightness <= 0){
    increasing = true;
  }

    String message = Serial.readStringUntil('\n');
    Serial.println(message);
    Serial.println(led_brightness);

    deserializeJson(doc, message);

    String name = doc["name"];
    String action = doc["action"];
    int intensity = doc["intensity"];

    if (name == "Led 21" and doc["action" == "on"]) {
        analogWrite(LED21, doc["intensity"]);
    }
      else if (doc["name"] == "Led 21" and doc["action"] == "off") {
        analogWrite(LED21, doc["intensity"]);
    }

        if (message == "Led On 22") {
        analogWrite(LED22, 150);
    } else if (message == "Led Off 22") {
        analogWrite(LED22, 10);
    }
}

