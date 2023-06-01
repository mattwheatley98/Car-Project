# Car Project

This project is a fully-functioning remote control car that allows for precise joystick controller input. In addition to driving, the car also features toggleable anti-collision mechanisms that prevent and minimize damage caused by collisions and sporadic accelerating. Two separate ESP32s use the ESP-NOW protocol to communicate with each other: the receiving ESP32 is used for the car, while the transmitting ESP32 is for the joystick controller.

**Please note that this project uses two different codebases: one for the car itself (this GitHub page) and the [controller](https://github.com/mattwheatley98/Car-Project-Controller)!**

The main features of this project include:

1. **Precise Wheel Actuation.** When both the car and the controller are powered, moving the joystick "up" makes the car go forward (and vice versa). Left, right, and diagonal inputs make the car turn in the corresponding direction. The joystick can be lightly pushed to allow for slower wheel actuation. Each front and rear pair of wheels has its own motor driver powered by a 9-volt battery.
2. **Toggleable Anti-Collision and Shock Detection.** The car is equipped with ultrasonic distance sensors mounted in the front and rear of the frame. These sensors detect objects within 15 centimeters, prompting the car to move in the opposite direction to avoid collisions. In the event of a collision or sporadic acceleration, a shock detector triggers an ISR that flashes a warning LED while temporarily disabling driving. This prevents damage to the car's components. The anti-collision and shock detection features can be toggled by pressing the switch on the joystick.
3. **Custom Wiring.** All wiring for the car was crimped and measured between the ESP32 and whichever component it was attached to. The custom-measured wires were woven through the internal frame of the car to minimize wire exposure. This helps prevent wire snags and disconnections while also promoting a more streamlined appearance. A rechargable power supply and breadboard were mounted on top of the frame, which also houses the ESP32.

Please refer below for demonstrations of each feature:

## Precise Wheel Actuation
Gradual Acceleration  | Rapid Acceleration
------------- | -------------
<video src="https://github.com/mattwheatley98/Car-Project/assets/113391095/412e3f2c-fd11-494c-8bd1-ee98df446c77" width = 500 height = 1000>  |  <video src="https://github.com/mattwheatley98/Car-Project/assets/113391095/5131a8e2-df90-455d-9609-fc625f7b0def" width = 500 height = 1000>

Turning | Rapid Turning
------------- | -------------
<video src="https://github.com/mattwheatley98/Car-Project/assets/113391095/eaa399f8-37fb-4dbf-924d-70e8fc7e6105" width = 500 height = 1000>  |  <video src="https://github.com/mattwheatley98/Car-Project/assets/113391095/6d7fe69d-bb7d-48af-8d46-070eab59cfed" width = 500 height = 1000>

## Toggleable Anti-Collision and Shock Detection
Front Collision Avoidance  | Rear Collision Avoidance
------------- | -------------
<video src="https://github.com/mattwheatley98/Car-Project/assets/113391095/790a98f4-f288-4737-a5af-08cba7c5be11" width = 350 height = 700>  |  <video src="https://github.com/mattwheatley98/Car-Project/assets/113391095/07333ee0-b89f-46a2-966f-dfc5820a7226" width = 350 height = 700>

Shock Detection  | Anti-Collision Toggle
------------- | -------------
<video src="https://github.com/mattwheatley98/Car-Project/assets/113391095/df81e19a-32d2-416e-8c43-0757553b419a" width = 350 height = 700>  |  <video src="https://github.com/mattwheatley98/Car-Project/assets/113391095/8b3fbcd8-a59c-4047-bfb8-a3a5bc6435be" width = 350 height = 700>

## Custom Wiring
Front View | Rear View
------------- | -------------
<img src="https://github.com/mattwheatley98/Car-Project/assets/113391095/1bfea074-2e67-4c0c-b2c0-162f9c4cc7bc" width = 350 height = 700>  |  <img src="https://github.com/mattwheatley98/Car-Project/assets/113391095/bfc848d2-51e6-4e05-bbab-b63c70cc84c7" width = 350 height = 700>

Right Side View | Left Side View
------------- | -------------
<img src="https://github.com/mattwheatley98/Car-Project/assets/113391095/a5b8b5ba-9dd5-4807-9047-da36cee31520" width = 350 height = 700>  |  <img src="https://github.com/mattwheatley98/Car-Project/assets/113391095/cf1cbfb9-f56d-401b-9540-f51ac49f578e" width = 350 height = 700>

Top View | Bottom View
------------- | -------------
<img src="https://github.com/mattwheatley98/Car-Project/assets/113391095/e6737250-8c62-4701-9baa-0e6201a2fc05" width = 350 height = 700>  |  <img src="https://github.com/mattwheatley98/Car-Project/assets/113391095/7d3075e9-7ab5-43db-bbc1-b09fcc92afe9" width = 350 height = 700>
