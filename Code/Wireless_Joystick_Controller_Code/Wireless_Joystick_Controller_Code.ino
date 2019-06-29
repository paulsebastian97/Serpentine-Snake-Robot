/* Transmitter/Joystick
 * Team Id: SS440
 * Author List: Paul Sebastian, Akshay, Adarsh, Adhish
 * Filename: Transmitter
 * Theme: Spotter Snake
 * Functions: void setup(), void loop().
 * Global Variables: address[6],X_pin,Y_pin,xPosition,yPosition,pushButton.
 */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8);
const byte address[6] = "00001"; //address: address variable for NRF module
const int X_pin = A1; // X_pin: joystick analog pin connected to X output
const int Y_pin = A2; // Y_pin: joystick analog pin connected to Y output
int xPosition = 0;    // xPosition: stores the x position,range 0 to 1024 
int yPosition = 0;    // yPosition: stores the y position, range 0 to 1024
int pushButton= 3;    // pushButton: push button for buzzer
/*
 * Function Name: void setup()
 * Input: none
 * Output: none
 * Logic: assigning initial values to the variables and pins
*/
void setup() 
{
  // setting up NRF module
  Serial.begin(9600); 
  pinMode(pushButton,INPUT);
  pinMode(X_pin, INPUT);
  pinMode(Y_pin, INPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  digitalWrite(pushButton,HIGH); // push button is initially set to high
}
/*
 * Function Name: void loop()
 * Input: none
 * Output: transmits the value of 'text' variable
 * Logic: mapping the position of joystick to 'text' varaiable that stores a number/character. 
 */
void loop() 
{
  // ***********reading the joystick 'x' and 'y' values.***********
  xPosition=analogRead(X_pin);
  yPosition=analogRead(Y_pin);
  
  // ********reading joystick position for left turn***************
  if(xPosition<=450)
  {
    int text = 3;  // text: stores a value that defines the state of the joystick, range 1 to 6
    // transmitting the text value
    radio.write(&text, sizeof(int)); 
  }
  
  // ********reading joystick position for right turn*************
  if(xPosition>=650)
  {
  Serial.println("ads");
  int text = 4; // text: stores a value that defines the state of the joystick, range 1 to 6
  // transmitting the text value
  radio.write(&text, sizeof(int));// transmitting the text value
  }
  
  // *********reading joystick position for reverse motion***********
  if(yPosition<=400)
  {
    int text = 2;// text: stores a value that defines the state of the joystick, range 1 to 6
    // transmitting the text value
    radio.write(&text, sizeof(int));// transmitting the text value
  }
  
  // *********reading joystick position for forward motion************
  if(yPosition>=600)
  {
    int text = 1;// text: stores a value that defines the state of the joystick, range 1 to 6
    // transmitting the text value
    radio.write(&text, sizeof(int));// transmitting the text value
  }
  
  //***********************PUSH BUTTON************************
  if((digitalRead(pushButton))==LOW)
  { 
    int text =6;// text: stores a value that defines the state of the joystick, range 1 to 6
    // transmitting the text value
    radio.write(&text, sizeof(text));// transmitting the text value
  }
  
  // ***********reading joystick position when its in center position************
  if((xPosition>480)&&(xPosition<580)&&(yPosition>480)&&(yPosition<580))
  {
    int text = 5;
    // transmitting the text value
    radio.write(&text, sizeof(int));// transmitting the text value
  }
}
// End
