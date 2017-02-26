/**
 * HC-SR04 Ultrasonic sensor test for the Self-driving Toy Car – Hack Night
 * 
 * The motorshield we are using has two headers called SERVO_1 and SERVO 2. 
 * Internally these are connected to pin 9 and 10 on the Arduino.
 * Conveniently these headers also bring out two extra GND and 5V pins
 * Connect the sensor like this:
 * 
 * Sensor -> Arduino
 * GND  -> - (servo pin marked -(minus))
 * VCC  -> + (servo pin marked +(plus))
 * TRIG -> SERVO_2 S (connected to pin 9)
 * ECHO -> SERVO_1 S (connected to pin 10)
 * 
 * created 23 Feb 2017
 * by Heerko van der Kooij
 * 
 * This example is in the public domain
 */

#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 200
 
void setup() {
   Serial.begin( 9600 );
}
 
void loop() {
   delay( 50 );
   int m2 = getDistance();
   Serial.println( pulseToCm( m2  ));
}

/**
 * If the sensor gets a HIGH pulse on the trigger pin for 10uS or more
 * it will send out the ultrasonic pulse. It will then pull the echo pin
 * HIGH for the amount of time it take for the echo to return. 
 * We can measure that pulse with the Arduino pulseIn method. 
 */
int getDistance(){
  pinMode( TRIGGER_PIN, OUTPUT );
  digitalWrite( TRIGGER_PIN, LOW );
  delayMicroseconds( 2 ); // short time low so we can send the trigger pulse
  digitalWrite( TRIGGER_PIN, HIGH );
  delayMicroseconds( 10 ); // high for at least 10 uS
  digitalWrite( TRIGGER_PIN, LOW );

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode( ECHO_PIN, INPUT );
  int duration = pulseIn( ECHO_PIN, HIGH );
  return duration;
}

/** 
 *  Sound travels at 340.29 meters per second. This corresponds to about 29,4µs (microseconds) per centimeter. 
 *  To measure the distance the sound has travelled we use the formula: Distance = ( Time x SpeedOfSound ) / 2. 
 *  The "2" is in the formula because the sound has to travel back and forth. 
 *  First the sound travels away from the sensor, and then it bounces off of a surface and returns back. 
 *  The easy way to read the distance as centimeters is to use the formula: 
 *  
 *  Centimeters = ( ( Microseconds / 2 ) / 29.4 ). 
 *  
 *  For example, if it takes 100µs (microseconds) for the ultrasonic sound to bounce back, 
 *  then the distance is ( ( 100 / 2 ) / 29.4 ) centimeters or about 1.7 centimeters.
 */
int pulseToCm( int uS ){
  return ( uS / 2 ) / 29.4;
}

