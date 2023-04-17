#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "../lib/src/driveTask.h"
#include "../lib/src/distanceSensorTask.h"

SemaphoreHandle_t frontBackObjectDetectionHandle;
SemaphoreHandle_t frontObjectDetectionHandle;
SemaphoreHandle_t backObjectDetectionHandle;

void setup() {
    Serial.begin(9600);
    WiFi.mode(WIFI_STA);

    frontBackObjectDetectionHandle = xSemaphoreCreateBinary();
    frontObjectDetectionHandle = xSemaphoreCreateBinary();
    backObjectDetectionHandle = xSemaphoreCreateBinary();
    //Task that handles DC motor actuation
    xTaskCreate(
            driveTask,
            "Drive Task",
            1024,
            nullptr,
            1,
            nullptr
    );
    //Task that handles object detection
    xTaskCreate(
            objectDetectionTask,
            "Object Detection Task",
            1024,
            nullptr,
            1,
            nullptr
    );
}

void loop() {

}