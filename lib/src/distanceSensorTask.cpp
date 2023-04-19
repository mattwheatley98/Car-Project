//
// Created by matt on 4/17/23.
//

#include <Arduino.h>
#include "distanceSensorTask.h"
#include </home/matt/CLionProjects/CarProject/.pio/libdeps/esp32dev/NewPing/src/NewPing.h>

#define FRONT_TRIGGER_PIN 21
#define FRONT_ECHO_PIN 35
#define BACK_TRIGGER_PIN 22
#define BACK_ECHO_PIN 34
#define BUZZ_PIN 27

//Detection range in centimeters
const int detectionRange = 15;

void objectDetectionTask(void *parameter) {
    //Initialize front sonar
    NewPing frontSonar(FRONT_TRIGGER_PIN, FRONT_ECHO_PIN, detectionRange);
    //Initialize back sonar
    NewPing backSonar(BACK_TRIGGER_PIN, BACK_ECHO_PIN, detectionRange);
    pinMode(BUZZ_PIN, OUTPUT);
    while (1) {
        //If the safety toggle is false (no safety override), the safety features work normally
        if (!toggleStatus) {
            //Deferred interrupt from shock detection ISR
            if (xSemaphoreTake(interruptObjectDetectionHandle, 0) == pdTRUE) {
                for (int i = 0; i < 4; ++i) {
                    digitalWrite(BUZZ_PIN, HIGH);
                    vTaskDelay(125 / portTICK_PERIOD_MS);
                    digitalWrite(BUZZ_PIN, LOW);
                    vTaskDelay(125);
                }
            } else vTaskDelay(10 / portTICK_PERIOD_MS); //Delay to avoid watchdog
            //Buzz and signal for when both sonars are triggered
            if ((frontSonar.ping_cm() <= 15 && frontSonar.ping_cm() != 0) && (backSonar.ping_cm() <= 15 && backSonar.ping_cm() != 0)) {
                //digitalWrite(BUZZ_PIN, HIGH);
                //Serial.println(digitalRead(BUZZ_PIN));
                xSemaphoreGive(frontBackObjectDetectionHandle);
                //Buzz and signal for when front sonar is triggered
            } else if (frontSonar.ping_cm() <= 15 && frontSonar.ping_cm() != 0) {
                //digitalWrite(BUZZ_PIN, HIGH);
                //Serial.println(frontSonar.ping_cm());
                xSemaphoreGive(frontObjectDetectionHandle);
                //Buzz and signal for when back sonar is triggered
            } else if (backSonar.ping_cm() <= 15 && backSonar.ping_cm() != 0) {
                //digitalWrite(BUZZ_PIN, HIGH);
                //Serial.println(backSonar.ping_cm());
                xSemaphoreGive(backObjectDetectionHandle);
            } else {
                digitalWrite(BUZZ_PIN, LOW);
            }
            //If the safety toggle is true (safety override enabled), safety features will not work
        } else {
            vTaskDelay(10 / portTICK_PERIOD_MS); //Delay to avoid watchdog
        }
    }
}