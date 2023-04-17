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
        //Delay to avoid watchdog
        vTaskDelay(10 / portTICK_PERIOD_MS);
        //Buzz and signal for when both sonars are triggered
        if ((frontSonar.ping_cm() <= 15 && frontSonar.ping_cm() != 0) && (backSonar.ping_cm() <= 15 && backSonar.ping_cm() != 0)) {
            digitalWrite(BUZZ_PIN, HIGH);
            xSemaphoreGive(frontBackObjectDetectionHandle);
            //Buzz and signal for when front sonar is triggered
        } else if (frontSonar.ping_cm() <= 15 && frontSonar.ping_cm() != 0) {
            digitalWrite(BUZZ_PIN, HIGH);
            xSemaphoreGive(frontObjectDetectionHandle);
            //Buzz and signal for when back sonar is triggered
        } else if (backSonar.ping_cm() <= 15 && backSonar.ping_cm() != 0) {
            digitalWrite(BUZZ_PIN, HIGH);
            xSemaphoreGive(backObjectDetectionHandle);
        } else {
            digitalWrite(BUZZ_PIN, LOW);
        }
    }
}