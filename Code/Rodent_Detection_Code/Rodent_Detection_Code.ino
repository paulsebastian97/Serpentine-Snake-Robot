/* Rodent detection using color sensor
 * Team Id: SS440
 * Author List: Paul Sebastian, Akshay, Adarsh, Adhish
 * Filename: rodentDectection
 * Theme: Spotter Snake
 * Functions: void setup(), void loop().
 * Global Variables: S0,S1,S2,S3,r,b,g,LED1,LED2,LED3,LED4,BuzzerSingal,Buzzer.
 */
#include <Servo.h>
#include <SPI.h>
#define S0 4  //Color sensors LEDS
#define S1 5  //Color sensors LEDS
#define S2 6  //Color sensors LEDS
#define S3 7  //Color sensors LEDS
#define sensorOut 8 
Servo s; // servo for snake tongue 
int red = 0; // Red color frequency
int green = 0; // Green color frequency, used during calibration
int blue = 0; // Blue color frequency
int BuzzerSignal=9; //receives a pulse from arduino,..to activate the buzzer
int LED1=A3;// Red LED
int LED2=A4;// Blue LED
int counter1=0; // counter1: Counter variable for switching red LED ON, range 0 to 1
int counter2=0; // counter2: Counter variable for switching blue LED ON, range 0 to 1
int counter3=0; // counter3: Counter variable for activating the buzzer for starting and ending the run, range 0 to 1
int Buzzer=3;   //Buzzer: digital pin connecting the buzzer
/*
 * Function Name: void setup()
 * Input: none
 * Output: none
 * Logic: assigning initial values to the variables and pins
*/
void setup()
{
 s.attach(2);
 pinMode(S0, OUTPUT);
 pinMode(S1, OUTPUT);
 pinMode(S2, OUTPUT);
 pinMode(S3, OUTPUT);
 pinMode(sensorOut, INPUT);
 pinMode(BuzzerSignal, INPUT);
 pinMode(LED1, OUTPUT);
 pinMode(LED2, OUTPUT);
 analogWrite(LED1,0);
 analogWrite(LED2,0);
 // Setting frequency-scaling to 20%
 digitalWrite(S0,HIGH);
 digitalWrite(S1,LOW);
 pinMode(Buzzer,OUTPUT);
 digitalWrite(Buzzer,LOW);
 Serial.begin(9600);
 delay(1000);
}
/*
 * Function Name: void loop()
 * Input: none
 * Output: 1. prints the output of color sensor...used during the calibration of color sensor.
           2. Activates corresponding LED when a rodent is detected and activates the buzzer.
 * Logic: By using the output of the color sensor, after calibration, conditioning the range to detect the rodent and its color and activating the LEDs 
*/
void loop() 
{
  // ************  * Buzzer...For starting the run*****************
  // true when push button is pressed
  if(digitalRead(BuzzerSignal)==HIGH) 
  {
    if(counter3==0)
    {
      // buzzer beeps for 2 seconds...for starting the run
      counter3=1;
      digitalWrite(Buzzer,HIGH);
      delay(2000);
      digitalWrite(Buzzer,LOW);
    }
    // Buzzer..for ending the run
    else if(counter3==1) 
    {
      int counter4=0; // counter4: counter variable used for activating the buzzer to end the run
      // buzzer beeps 5 times...for ending the run
      while(counter4<5)
      {
        //buzzer is set to high for 1 second
        digitalWrite(Buzzer,HIGH);
        delay(1000);
        digitalWrite(Buzzer,LOW);
        delay(1000);
        counter4++;
      }
      // counter3 is set to zero.
      counter3=0; 
    }
  }
  
  // *************Setting red filtered photodiodes to be read***************
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  red = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(red);//printing RED color frequency
  Serial.print(" ");
  delay(100);
  
  // **********Setting Green filtered photodiodes to be read***************
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  green = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor 
  Serial.print("G= ");//printing name
  Serial.print(green);//printing RED color frequency
  Serial.print(" ");
  delay(100);
  
  // **********Setting Blue filtered photodiodes to be read***************
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  blue = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(blue);//printing RED color frequency
  Serial.println(" ");
  
  // Detecting the color/Rodents
  
  //*************************Detecting red color********************
  if((red<160)&&(blue>200))
  { 
    // rodent detection 
    if(counter1==0)
    { 
      // activates the tongue servo...tongue moves forward
      s.attach(2);
      s.write(180);
      //Switching on Red LED
      analogWrite(LED1,255);
      //switching OFF blue LED
      analogWrite(LED2,0);
      int counter5=0;// counter5: counter used to activate the buzzer beeping
      //Buzzer beeps when the rodent is detected
      while(counter5<2)
      { 
        // buzzer beeps twice interval of 1 second   
        digitalWrite(Buzzer,HIGH);
        delay(1000);
        digitalWrite(Buzzer,LOW);
        delay(1000);
        counter5++;
      }
      // servo is reset to inital position and the tongue retracts
      s.write(0);
      delay(300);
      s.detach();
      counter1++;
    }
  }
  
  //*********************Detecting blue color****************************
  if((blue<110)&&(red>210 ))
  {
    if(counter2==0)
    {  
      // activates the tongue servo...tongue moves forward
      s.attach(2);
      s.write(180);
      // switching red LED OFF
      analogWrite(LED1,0);
      // switching blue LED ON
      analogWrite(LED2,255);
      int counter5=0;
      //Buzzer beeps when the rodent is detected
      while(counter5<2)
      {
         // buzzer beeps twice interval of 1 second
         digitalWrite(Buzzer,HIGH);
         delay(1000);
         digitalWrite(Buzzer,LOW);
         delay(1000);
         counter5++;
      }
      // servo is reset to inital position and the tongue retracts
      s.write(0);
      delay(300);
      s.detach();
      counter2++;
    }
  }
  
  // ***********if the sensor detects color other than red, blue.**************
  else
  {
    // counter variables are reset to zero...so that rodent detection process continues
    counter1=0;
    counter2=0;
    //switching OFF LEDs
    analogWrite(LED1,0);
    analogWrite(LED2,0);
  }
  delay(100);
}
// End.
