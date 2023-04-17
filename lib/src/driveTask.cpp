//
// Created by matt on 4/17/23.
//

#include "driveTask.h"
#include <Arduino.h>
#include <esp_now.h>
#define BACK_LEFT_PIN 13
#define BACK_LEFT_MOTOR1 12
#define BACK_LEFT_MOTOR2 14
#define BACK_RIGHT_PIN 15
#define BACK_RIGHT_MOTOR1 2
#define BACK_RIGHT_MOTOR2 4
#define FRONT_LEFT_PIN 25
#define FRONT_LEFT_MOTOR1 33
#define FRONT_LEFT_MOTOR2 32
#define FRONT_RIGHT_PIN 5
#define FRONT_RIGHT_MOTOR1 18
#define FRONT_RIGHT_MOTOR2 19

//Struct to format received controller data
typedef struct structMessage {
    char x[32];
    char y[32];
} structMessage;

//Initialize an instance of structMessage
structMessage savedValue;

//Constants for controlling PWM output
const int freq = 30000;
//Channel from 0-15
const int pwmChannel = 0;
//Duty cycle resolution from 1 to 16 bits... 8 bits mean you can use values from 0-255!
const int resolution = 8;
//Controls the speed of the DC motors
int dutyCycle = 255;

void driveTask(void *parameter) {
    //Back left wheel-related pin modes
    pinMode(BACK_LEFT_PIN, OUTPUT);
    pinMode(BACK_LEFT_MOTOR1, OUTPUT);
    pinMode(BACK_LEFT_MOTOR2, OUTPUT);
    //Back right wheel-related pin modes
    pinMode(BACK_RIGHT_PIN, OUTPUT);
    pinMode(BACK_RIGHT_MOTOR1, OUTPUT);
    pinMode(BACK_RIGHT_MOTOR2, OUTPUT);
    //Front left wheel-related pin modes
    pinMode(FRONT_LEFT_PIN, OUTPUT);
    pinMode(FRONT_LEFT_MOTOR1, OUTPUT);
    pinMode(FRONT_LEFT_MOTOR2, OUTPUT);
    //Front right wheel-related pin modes
    pinMode(FRONT_RIGHT_PIN, OUTPUT);
    pinMode(FRONT_RIGHT_MOTOR1, OUTPUT);
    pinMode(FRONT_RIGHT_MOTOR2, OUTPUT);

    //Callback function's signature
    void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int size);

    //Initialize ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
    }

    //Register the receiving device's callback function
    esp_now_register_recv_cb(onDataRecv);

    //Set up PWM for use with the DC motors
    ledcSetup(pwmChannel, freq, resolution);
    ledcAttachPin(BACK_LEFT_PIN, pwmChannel);
    ledcAttachPin(BACK_RIGHT_PIN, pwmChannel);
    ledcAttachPin(FRONT_LEFT_PIN, pwmChannel);
    ledcAttachPin(FRONT_RIGHT_PIN, pwmChannel);

    while (1) {
        //Loops and using PWM, actuates the DC motors based on the received controller values
        if (atoi(savedValue.x) <= 1850 && atoi(savedValue.y) <= 1800) {
            //Forward left... duty cycle is dependent on a "flipped" 10-bit y value (joystick up)
            dutyCycle = (atoi(savedValue.y) - 4095) / 16 * -1;
            ledcWrite(pwmChannel, dutyCycle);
            //Serial.println(dutyCycle);
            digitalWrite(BACK_LEFT_MOTOR1, HIGH);
            digitalWrite(BACK_LEFT_MOTOR2, LOW);
            digitalWrite(BACK_RIGHT_MOTOR1, HIGH);
            digitalWrite(BACK_RIGHT_MOTOR2, LOW);
            digitalWrite(FRONT_LEFT_MOTOR1, LOW);
            digitalWrite(FRONT_LEFT_MOTOR2, LOW); //Turn off front left (HIGH for forward)
            digitalWrite(FRONT_RIGHT_MOTOR1, LOW);
            digitalWrite(FRONT_RIGHT_MOTOR2, HIGH);
        } else if (atoi(savedValue.x) >= 1950 && atoi(savedValue.y) <= 1800) {
            //Forward right... duty cycle is dependent on a "flipped" 10-bit y value (joystick up)
            dutyCycle = (atoi(savedValue.y) - 4095) / 16 * -1;
            ledcWrite(pwmChannel, dutyCycle);
            //Serial.println(dutyCycle);
            digitalWrite(BACK_LEFT_MOTOR1, HIGH);
            digitalWrite(BACK_LEFT_MOTOR2, LOW);
            digitalWrite(BACK_RIGHT_MOTOR1, HIGH);
            digitalWrite(BACK_RIGHT_MOTOR2, LOW);
            digitalWrite(FRONT_LEFT_MOTOR1, LOW);
            digitalWrite(FRONT_LEFT_MOTOR2, HIGH);
            digitalWrite(FRONT_RIGHT_MOTOR1, LOW);
            digitalWrite(FRONT_RIGHT_MOTOR2, LOW); //Turn off front right (HIGH for forward)
        } else if (atoi(savedValue.y) <= 1800) {
            //Go forward... duty cycle is dependent on a "flipped" 10-bit y value (joystick up)
            dutyCycle = (atoi(savedValue.y) - 4095) / 16 * -1;
            ledcWrite(pwmChannel, dutyCycle);
            //Serial.println(dutyCycle);
            digitalWrite(BACK_LEFT_MOTOR1, HIGH);
            digitalWrite(BACK_LEFT_MOTOR2, LOW);
            digitalWrite(BACK_RIGHT_MOTOR1, HIGH);
            digitalWrite(BACK_RIGHT_MOTOR2, LOW);
            digitalWrite(FRONT_LEFT_MOTOR1, LOW);
            digitalWrite(FRONT_LEFT_MOTOR2, HIGH);
            digitalWrite(FRONT_RIGHT_MOTOR1, LOW);
            digitalWrite(FRONT_RIGHT_MOTOR2, HIGH);
        } else if (atoi(savedValue.x) <= 1850 && atoi(savedValue.y) >= 1900) {
            //Backward left... duty cycle is dependent on a 10-bit y value (joystick down)
            dutyCycle = atoi(savedValue.y) / 16;
            ledcWrite(pwmChannel, dutyCycle);
            //Serial.println(dutyCycle);
            digitalWrite(BACK_LEFT_MOTOR1, LOW);
            digitalWrite(BACK_LEFT_MOTOR2, LOW); //Turn off back left (originally HIGH)
            digitalWrite(BACK_RIGHT_MOTOR1, LOW);
            digitalWrite(BACK_RIGHT_MOTOR2, HIGH);
            digitalWrite(FRONT_LEFT_MOTOR1, HIGH);
            digitalWrite(FRONT_LEFT_MOTOR2, LOW);
            digitalWrite(FRONT_RIGHT_MOTOR1, HIGH);
            digitalWrite(FRONT_RIGHT_MOTOR2, LOW);
        } else if (atoi(savedValue.x) >= 1950 && atoi(savedValue.y) >= 1900) {
            //Backward right... duty cycle is dependent on a 10-bit y value (joystick down)
            dutyCycle = atoi(savedValue.y) / 16;
            ledcWrite(pwmChannel, dutyCycle);
            //Serial.println(dutyCycle);
            digitalWrite(BACK_LEFT_MOTOR1, LOW);
            digitalWrite(BACK_LEFT_MOTOR2, HIGH);
            digitalWrite(BACK_RIGHT_MOTOR1, LOW);
            digitalWrite(BACK_RIGHT_MOTOR2, LOW); //Turn off back right (originally HIGH)
            digitalWrite(FRONT_LEFT_MOTOR1, HIGH);
            digitalWrite(FRONT_LEFT_MOTOR2, LOW);
            digitalWrite(FRONT_RIGHT_MOTOR1, HIGH);
            digitalWrite(FRONT_RIGHT_MOTOR2, LOW);
        } else if (atoi(savedValue.y) >= 1900) {
            //Go backward... duty cycle is dependent on a 10-bit y value (joystick down)
            dutyCycle = atoi(savedValue.y) / 16;
            ledcWrite(pwmChannel, dutyCycle);
            //Serial.println(dutyCycle);
            digitalWrite(BACK_LEFT_MOTOR1, LOW);
            digitalWrite(BACK_LEFT_MOTOR2, HIGH);
            digitalWrite(BACK_RIGHT_MOTOR1, LOW);
            digitalWrite(BACK_RIGHT_MOTOR2, HIGH);
            digitalWrite(FRONT_LEFT_MOTOR1, HIGH);
            digitalWrite(FRONT_LEFT_MOTOR2, LOW);
            digitalWrite(FRONT_RIGHT_MOTOR1, HIGH);
            digitalWrite(FRONT_RIGHT_MOTOR2, LOW);
        } else {
            //No movement
            digitalWrite(BACK_LEFT_MOTOR1, LOW);
            digitalWrite(BACK_LEFT_MOTOR2, LOW);
            digitalWrite(BACK_RIGHT_MOTOR1, LOW);
            digitalWrite(BACK_RIGHT_MOTOR2, LOW);
            digitalWrite(FRONT_LEFT_MOTOR1, LOW);
            digitalWrite(FRONT_LEFT_MOTOR2, LOW);
            digitalWrite(FRONT_RIGHT_MOTOR1, LOW);
            digitalWrite(FRONT_RIGHT_MOTOR2, LOW);
        }
    }
}

//Callback function for when data is received from the controller
void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int size) {
    memcpy(&savedValue, incomingData, sizeof(savedValue));
    Serial.print("Saved value X: ");
    Serial.print(savedValue.x);
    Serial.print(" Saved value Y: ");
    Serial.println(savedValue.y);
}