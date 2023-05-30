# Car Project

This project is a fully-functioning remote control car that allows for precise joystick controller input. In addition to being able to drive, the car also has toggleable anti-collision features that prevents and minimizes damage caused from collisions. Two separate ESP32s use the ESP-NOW protocol to communicate with each other: the receiving ESP32 is used for the car, while the transmitting ESP32 is for the joystick controller. 

**Please note that this project uses two different codebases: one for the car itself (this GitHub page) and the [controller](https://github.com/mattwheatley98/Car-Project-Controller)!**

The main features of this project are as follows:
1. **Precise Wheel Actuation.** When both the car and controller are powered, moving "up" on the joystick makes the car go forward (and vice-versa), while left/right and diagonal inputs make the car turn in whichever direction the joystick points to. The joystick can be lightly pushed to allow for slower wheel actuation. Each front and rear pair of wheels have their own motor driver that is powered by a 9 volt battery.
2. **Toggleable Anti-Collision and Shock Detection.** The car has anti-collision features in the form of ultrasonic distance sensors that are mounted in the front and rear of the frame. When these sensors detect an object within 15 centimeters, the car will automatically move in the opposite direction to avoid a collision. In the event of a collision, a shock detector will trigger an ISR that flashes a warning LED while also temporarily disabling the ability to drive. The anti-collision and shock detection features can be toggled by pressing the switch on the joystick.
3. **Custom Wiring.** All wiring for the car was crimped and measured between the ESP32 and whichever component it was attached to. The custom-measured wires were woven through the internal frame of the car to minimize wire exposure. This helps prevent wire snags and disconnections while also promoting a more streamlined appearance. A rechargable power supply and breadboard were mounted on top of the frame, which also houses the ESP32.

Please refer below for demonstrations of each feature.

## Precise Wheel Actuation
Forward and Backward Gradual Acceleration  | Forward and Backward Rapid Acceleration
------------- | -------------
<img src="GIF HERE" width = 350 height = 700>  |  <img src="GIF HERE" width = 350 height = 700>

Turning | Rapid Turning
------------- | -------------
<img src="GIF HERE" width = 350 height = 700>  |  <img src="GIF HERE" width = 350 height = 700>

## Toggleable Anti-Collision and Shock Detection
Front Collision Avoidance  | Rear Collision Avoidance
------------- | -------------
<img src="GIF HERE" width = 350 height = 700>  |  <img src="GIF HERE" width = 350 height = 700>

Shock Detection  | Anti-Collision Toggle
------------- | -------------
<img src="GIF HERE" width = 350 height = 700>  |  <img src="GIF HERE" width = 350 height = 700>

## Custom Wiring
Top and Bottom View | "Walk Around" View
------------- | -------------
<img src="GIF HERE" width = 350 height = 700>  |  <img src="GIF HERE" width = 350 height = 700>
