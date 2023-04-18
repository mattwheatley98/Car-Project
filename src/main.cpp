#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "../lib/src/driveTask.h"
#include "../lib/src/distanceSensorTask.h"

SemaphoreHandle_t frontBackObjectDetectionHandle;
SemaphoreHandle_t frontObjectDetectionHandle;
SemaphoreHandle_t backObjectDetectionHandle;

//ISR-related handles and constants
hw_timer_t *interruptTimer;
SemaphoreHandle_t interruptDriveHandle;
SemaphoreHandle_t interruptObjectDetectionHandle;
BaseType_t taskWoken = pdTRUE;
const uint16_t divider = 80;
const uint64_t timerMaxCount = 1000000;

//ISR callback function (stored on RAM) that defers work to the display and LED tasks
void IRAM_ATTR onTimer() {
    xSemaphoreGiveFromISR(interruptDriveHandle, &taskWoken);
    xSemaphoreGiveFromISR(interruptObjectDetectionHandle, &taskWoken);
}

void setup() {
    Serial.begin(9600);
    WiFi.mode(WIFI_STA);

    pinMode(26, INPUT);

    //Turn the object detection semaphores into one queue?
    frontBackObjectDetectionHandle = xSemaphoreCreateBinary();
    frontObjectDetectionHandle = xSemaphoreCreateBinary();
    backObjectDetectionHandle = xSemaphoreCreateBinary();

    //Interrupt semaphores
    interruptDriveHandle = xSemaphoreCreateBinary();
    interruptObjectDetectionHandle = xSemaphoreCreateBinary();
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
    //ISR-related functions
    interruptTimer = timerBegin(0, divider, true);
    timerAttachInterrupt(interruptTimer, &onTimer, true);
    timerAlarmWrite(interruptTimer, timerMaxCount, false);
}

void loop() {
    if (digitalRead(26) == LOW) {
        timerAlarmEnable(interruptTimer);
    }
}