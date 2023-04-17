#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "../lib/src/driveTask.h"

void setup() {
    Serial.begin(9600);
    WiFi.mode(WIFI_STA);
    xTaskCreate(
            driveTask,
            "Drive Task",
            1024,
            nullptr,
            1,
            nullptr
    );
}

void loop() {

}