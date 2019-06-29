/* Receiver
 * Team Id: SS440
 * Author List: Paul Sebastian, Akshay, Adarsh, Adhish, 
 * Filename: Receiver
 * Theme: Spotter Snake
 * Functions: void setup(), void loop().
 * Global Variables: s1,s2,s3,s4,s5,s6,s7,s8,s9,counter,lag,frequency,amplitude,rightOffset,leftOffset,offset,delayTime,startPause,test
 */
#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
// initializing the servo variables
Servo s1; 
Servo s2;
Servo s3;
Servo s4; 
Servo s5;
Servo s6;
Servo s7;
Servo s8;
Servo s9; 
Servo s10;
int counter = 0;// counter: Loop counter variable, range 0 to 
float lag = .5712; // lag: Phase lag between segments
int frequency = 1.5; // frequency: Oscillation frequency of segments.
int amplitude = 40; // amplitude: Amplitude of the serpentine motion of the snake
int rightOffset = 10; // rightOffset: Right turn offset
int leftOffset = -10; // leftOffset: Left turn offset
int offset = 0; // offset: Variable to correct servos that are not exactly centered
int delayTime = 7; // delayTime: Delay between limb movements
int startPause = 5000;  //sartPause: Delay time to position robot
int test = -3; // test: test varialble takes values from -6 to +6
RF24 radio(7, 8); // NRF module
const byte address[6] = "00001";// address: address variable for NRF module
int BuzzerSignal=10;
/*
 * Function Name: void setup()
 * Input: none
 * Output: none 
 * Logic: assigning initial values to the variables and pins
 * 
*/
void setup()
{ 
  // seting up the NRF module
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  // receiving the 'text' value
  radio.startListening();
  pinMode(BuzzerSignal,OUTPUT);
  digitalWrite(BuzzerSignal,LOW);
  
  // Attachs the servos to pins  
  s1.attach(2);
  s2.attach(3);
  s3.attach(4); 
  s4.attach(17);
  s5.attach(6);
  s6.attach(14);
  s7.attach(15);
  s8.attach(9);
  s9.attach(16);
  s10.attach(5);
  
  //Put snake in starting position
  s1.write(90+offset+amplitude*cos(5*lag));
  s2.write(90+offset+amplitude*cos(4*lag)); 
  s3.write(90+offset+amplitude*cos(3*lag));
  s4.write(90+amplitude*cos(2*lag));
  s5.write(90+amplitude*cos(1*lag));
  s6.write(90+amplitude*cos(0*lag));
  s7.write(90+amplitude*cos(-1*lag));
  s8.write(90+amplitude*cos(-2*lag));
  s9.write(90+amplitude*cos(-3*lag));
  s10.write(90+amplitude*cos(-4*lag));
  delay(startPause);  
  delay(15);
}
/*
 * Function Name: void loop()
 * Input: none
 * Output: movement signals to the servos and sends pulse to the rodent detection arduino
 * Logic: serpentine motion: sinusoidally increasing the angular displacement of the servos to generate the serpentine motion
*/
void loop() 
{
  // receiving the text values
  if (radio.available()) 
  {
    int text ; // text: text variable takes values from 1 to +6.
    //receiving the transmission from the joystick
    radio.read(&text, sizeof(int));
    
    // sending a pulse to arduino to activate the buzzer
    if(text==6)
    { 
      // sending a pulse to arduino(rodentDectection) to activate the buzzer for starting and ending the run
      digitalWrite(BuzzerSignal,HIGH);
      delay(500);
      digitalWrite(BuzzerSignal,LOW);
    }
    
    // ***********************serpentine forward motion*********************
    else if(text==1)
    {
      // attaches the servos to the pins
      s1.attach(2);
      s2.attach(3);
      s3.attach(4); 
      s4.attach(17);
      s5.attach(6);
      s6.attach(14);
      s7.attach(15);
      s8.attach(9);
      s9.attach(16);
      s10.attach(5);
      while(counter>=0) 
      { 
         //reading the text value 
         //receiving the transmission from the joystick 
         radio.read(&text, sizeof(int));
         if (text==5)
         {  
           break;  // loop breaks if the joystick is in center position.. snake does'nt move
         }
         // forward motion
         else 
         {
           // serpentine forward motion, the angular displacement of the servos varies sinusoidally
           delay(delayTime);
           s1.write(90+amplitude*cos(frequency*counter*3.14159/180+5*lag));
           s2.write(90+amplitude*cos(frequency*counter*3.14159/180+4*lag));
           s3.write(90+amplitude*cos(frequency*counter*3.14159/180+3*lag));
           s4.write(90+amplitude*cos(frequency*counter*3.14159/180+2*lag));
           s5.write(90+amplitude*cos(frequency*counter*3.14159/180+1*lag));
           s6.write(90+amplitude*cos(frequency*counter*3.14159/180+0*lag));    
           s7.write(90+amplitude*cos(frequency*counter*3.14159/180-1*lag));
           s8.write(90+amplitude*cos(frequency*counter*3.14159/180-2*lag));    
           s9.write(90+amplitude*cos(frequency*counter*3.14159/180-3*lag));
           s10.write(90+amplitude*cos(frequency*counter*3.14159/180-4*lag));
           counter++;
         } 
      }
      // detaching the servos from the pins 
      s1.detach();
      s2.detach();
      s3.detach();
      s4.detach();
      s5.detach();
      s6.detach();
      s7.detach();
      s8.detach();
      s9.detach();
      s10.detach();
    }  
    
    // ***********************serpentine reverse motion*********************
    else  if(text==2)
    {
      s1.attach(2);
      s2.attach(3);
      s3.attach(4); 
      s4.attach(17);
      s5.attach(6);
      s6.attach(14);
      s7.attach(15);
      s8.attach(9);
      s9.attach(16);
      s10.attach(5);
      while(counter>=0)
      {
        //reading the text value 
        //receiving the transmission from the joystick
        radio.read(&text, sizeof(int));
        if (text==5)
        {  
          break; // loop breaks if the joystick is in center position.. snake does not move
        }
        else 
        {
          // serpentine reverse motion, the angular displacement of the servos varies sinusoidally
          delay(delayTime);
          s10.write(90+amplitude*cos(frequency*counter*3.14159/180+5*lag));
          s9.write(90+amplitude*cos(frequency*counter*3.14159/180+4*lag));
          s8.write(90+amplitude*cos(frequency*counter*3.14159/180+3*lag));
          s7.write(90+amplitude*cos(frequency*counter*3.14159/180+2*lag));
          s6.write(90+amplitude*cos(frequency*counter*3.14159/180+1*lag));
          s5.write(90+amplitude*cos(frequency*counter*3.14159/180+0*lag));    
          s4.write(90+amplitude*cos(frequency*counter*3.14159/180-1*lag));
          s3.write(90+amplitude*cos(frequency*counter*3.14159/180-2*lag));    
          s2.write(90+amplitude*cos(frequency*counter*3.14159/180-3*lag));
          s1.write(90+amplitude*cos(frequency*counter*3.14159/180-4*lag));
          counter++;
        } 
      } 
      //detaching the servos from the pins
      s1.detach();
      s2.detach();
      s3.detach();
      s4.detach();
      s5.detach();
      s6.detach();
      s7.detach();
      s8.detach();
      s9.detach();
      s10.detach();   
    }
    
    // ******************** serpentine left motion ************************
    else if(text==4)
    {
      s1.attach(2);
      s2.attach(3);
      s3.attach(4); 
      s4.attach(17);
      s5.attach(6);
      s6.attach(14);
      s7.attach(15);
      s8.attach(9);
      s9.attach(16);
      s10.attach(5);
      while(counter>=0)  
      { 
        //reading the text value 
        //receiving the transmission from the joystick
        radio.read(&text, sizeof(int));
        if (text==5)
        { 
          break; // loop breaks if the joystick is in center position.. snake does not move
        }
        else 
        {  
          // serpentine left motion
          delay(delayTime);
          s1.write(90+offset+rightOffset+amplitude*cos(frequency*counter*3.14159/180+5*lag));
          s2.write(90+offset+rightOffset+amplitude*cos(frequency*counter*3.14159/180+4*lag));
          s3.write(90+offset+rightOffset+amplitude*cos(frequency*counter*3.14159/180+3*lag));
          s4.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180+2*lag));
          s5.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180+1*lag));
          s6.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180+0*lag));    
          s7.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180-1*lag));
          s8.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180-2*lag));    
          s9.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180-3*lag));
          s10.write(90+rightOffset+amplitude*cos(frequency*counter*3.14159/180-4*lag));
          counter++;
        }
      }
      s1.detach();
      s2.detach();
      s3.detach();
      s4.detach();
      s5.detach();
      s6.detach();
      s7.detach();
      s8.detach();
      s9.detach();
      s10.detach();    
    }
    
    //******************** serpentine right motion **********************
    else if(text==3)
    {
      s1.attach(2);
      s2.attach(3);
      s3.attach(4); 
      s4.attach(17);
      s5.attach(6);
      s6.attach(14);
      s7.attach(15);
      s8.attach(9);
      s9.attach(16);
      s10.attach(5);
      while(counter>=0)  
      {
        //reading the text value 
        //receiving the transmission from the joystick
        radio.read(&text, sizeof(int));
        if (text==5)
        { 
          break; // loop breaks if the joystick is in center position.. snake does not move
        }
        else 
        {
          // serpentine right motion
          delay(delayTime);
          s1.write(90+offset+leftOffset+amplitude*cos(frequency*counter*3.14159/180+5*lag));
          s2.write(90+offset+leftOffset+amplitude*cos(frequency*counter*3.14159/180+4*lag));
          s3.write(90+offset+leftOffset+amplitude*cos(frequency*counter*3.14159/180+3*lag));
          s4.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180+2*lag));
          s5.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180+1*lag));
          s6.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180+0*lag));    
          s7.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180-1*lag));
          s8.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180-2*lag));    
          s9.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180-3*lag));
          s10.write(90+leftOffset+amplitude*cos(frequency*counter*3.14159/180-4*lag));
          counter++;
        }
      } 
      s1.detach();
      s2.detach();
      s3.detach();
      s4.detach();
      s5.detach();
      s6.detach();
      s7.detach();
      s8.detach();
      s9.detach();
      s10.detach();    
    }
    
    // detaching the servos if the joystick is in center position.Snake does not move.
    else
    {
      s1.detach();
      s2.detach();
      s3.detach();
      s4.detach();
      s5.detach();
      s6.detach();
      s7.detach();
      s8.detach();
      s9.detach();
      s10.detach();
    }
    if(counter>32700)
    {
      counter=0;
    }
  }
}
//End
