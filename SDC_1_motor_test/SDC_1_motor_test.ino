/**
 * Motorshield test for the Self-driving Toy Car – Hack Night
 * 
 * You need to install the Adafruit motor shield library to run this sketch.
 * Install it through the Library managers under Sketch > Import Library > Manage Libraries... 
 * Search for "Adafruit Motor shield V1 firmware". There are two versions, make sure you have the right one!
 * Or download and install it manually: https://github.com/adafruit/Adafruit-Motor-Shield-library
 * 
 * IMPORTANT! 
 * Disconnect the (green) jumper marked PWR right next to the screw terminal marked EXT_PWR
 * 
 * Connect the cars battery plus and minus wires to the EXT_PWR screw header
 * Connect the steering motor to the M1 screw header
 * Connect the drive motor to the M4 screw header
 * Upload this code
 * Open the serial monitor and follow instructions
 * 
 * If your car drives backwards when it should be going forward, reverse the wires in the screw terminal.
 * Same for the steering. 
 * 
 * created 23 Feb 2017
 * by Heerko van der Kooij
 * 
 * Serial code modified from https://www.bananarobotics.com/shop/How-to-use-the-HG7881-(L9110)-Dual-Channel-Motor-Driver-Module
 */


#include <AFMotor.h>

#define LEFT FORWARD
#define RIGHT BACKWARD

AF_DCMotor steer( 1 ); // connect the steering motor to the M1 header.
AF_DCMotor motor( 4 ); // connect the driving motor to the M4 header.

void setup() {
  Serial.begin( 9600 ); // set up Serial library at 9600 bps
  
  steer.setSpeed( 128 ); // half speed
  steer.run( RELEASE ); // but off. Or your car might drive off right away.

  motor.setSpeed( 255 ); // steering always full speed.
  motor.run( RELEASE ); // and in the neutral position
}

void loop() {
boolean isValidInput;
  // draw a menu on the serial port
  Serial.println( "-----------------------------" );
  Serial.println( "MENU:" );
  Serial.println( "1) Fast forward" );
  Serial.println( "2) Forward" );
  Serial.println( "3) Stop" );
  Serial.println( "4) Reverse" );
  Serial.println( "5) Fast reverse" );
  Serial.println( "6) Steer left" );
  Serial.println( "7) Steer neutral" );
  Serial.println( "8) Steer right" );
  Serial.println( "-----------------------------" );
  do {
    byte c;
    // get the next character from the serial port
    Serial.print( "?" );
    while( !Serial.available() )
      ; // LOOP...
    c = Serial.read();
    // execute the menu option based on the character recieved
    switch( c ) {
      case '1':
        Serial.println( "Fast forward..." );
        motor.setSpeed( 255 );
        motor.run( FORWARD );
        isValidInput = true;
        break;      
         
      case '2':
        Serial.println( "Forward..." );
        motor.setSpeed( 150 );
        motor.run( FORWARD );
        isValidInput = true;
        break;      
         
      case '3':
        Serial.println( "Stop..." );
        motor.run( RELEASE );
        isValidInput = true;
        break;      
 
      case '4':
        Serial.println( "Reverse..." );
        motor.setSpeed( 150 );
        motor.run( BACKWARD );
        isValidInput = true;
        break;      
         
      case '5':
        Serial.println( "Fast reverse..." );
        motor.setSpeed( 255 );
        motor.run( BACKWARD );
        isValidInput = true;
        break;
        
      case '6':
        Serial.println( "Steer left..." );
        steer.run( LEFT );
        isValidInput = true;
        break; 

      case '7':
        Serial.println( "Steer neutral..." );
        steer.run( RELEASE );
        isValidInput = true;
        break; 

      case '8':
        Serial.println( "Steer right..." );
        steer.run( RIGHT );
        isValidInput = true;
        break; 
      default:
        // wrong character! display the menu again!
        isValidInput = false;
        break;
    }
  } while( isValidInput == true );
 
  // repeat the main loop and redraw the menu...
}
