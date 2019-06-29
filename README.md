# Serpentine Snake Robot
A biomorphic hyper-redundant snake robot capable of taversing different terrains using serpentine motion. It is also designed to autonomously detect pests such as dummy rodents and scare them away using sound. It is based on the ATmega328 microcontroller, which uses 10 servo motors(GS-5515MG) for the serpentine motion and rodent detection circuit to detect rodents and scare them using sound. The rodent detection circuit uses color sensor(TCS230) to detect the rodent, two LEDs (eyes of the snake) to display the color of the rodent and a buzzer to make sound. A self-designed wireless joystick controller is used for navigation of the robot using nRF24L01 tranceiver.

## Video Demonstration
[Serpentine Snake Robot Video Demonstration](../blob/master/LICENSE)

Team ID: eYRC-BB#440 | eYRC-2017 conducted by e-Yantra, CSE Department, IIT Bombay, sponsored by MHRD, Government of India.
Team members: Paul Sebastian, Adarsh V.S, Akshay S.N, Adhish G.V

## Repository Contents
* Code - The entire firmware of the robot and the wireless joystick controller.
* Datasheets - Contains all the datasheets and references.
* Images - Images of the robot and the joystick controller.
* Report - Documentation on the theme analysis and initial implementation strategy.
* Schematics - Hardware schematic of the robot and the joystick controller.

## Serpentine Snake Robot
![alt tag](https://github.com/paulsebastian97/Serpentine-Snake-Robot/blob/master/Images/Serpentine%20Snake%20Robot.png)

## Wireless Joystick Controller
![alt tag](https://github.com/paulsebastian97/Serpentine-Snake-Robot/blob/master/Images/Wireless%20Joystick%20Controller.PNG)

## Serpentine Snake Robot Schematics
![alt tag](https://github.com/paulsebastian97/Serpentine-Snake-Robot/blob/master/Schematics/Serpentine%20Snake%20Robot%20Schematics.png)

## Wireless Joystick Controller Schematics
![alt tag](https://github.com/paulsebastian97/Serpentine-Snake-Robot/blob/master/Schematics/Wireless%20Joystick%20Controller%20Schematics.PNG)

## Challenges Involved in Building the Robot
* Electronic circuit designing.
* Microcontroller programming (Using Arduino Nano), especially coming up with the Serpentine Motion Algorithm.
* 3D designing(Fusion 360) and 3D printing.
* Simulation (V-rep software).
* Joystick designing for wireless communication.
