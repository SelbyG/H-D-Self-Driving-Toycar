// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 200
#define LEFT BACKWARD
#define RIGHT FORWARD
#define NEUTRAL RELEASE

AF_DCMotor steer(1);
AF_DCMotor motor(4);

int LINE_SENSOR = A0;

// First run the SDC_TCRT500 sketch and set the min and max values for the sensor below.
int sMin = 300; // set this to the minimal value you get from the line sensor
int sMax = 1000; // set this to the maximal value you get from the line sensor
int sM = sMin + sMax / 2; // calculate the midpoint.

void setup() {
  Serial.begin( 9600 ); // set up Serial library at 9600 bps for debugging
  Serial.println( "Motor test!" ); // start message.

  // turn on motor
  steer.setSpeed( 255 ); 
  steer.run( NEUTRAL ); 

  motor.setSpeed( 255 );
  motor.run( RELEASE );
}

void loop() {
  int cm = pulseToCm( getDistance() );

  if ( cm > 15 ) { // there doesn't seem to be an obstacle in front of the car

    motor.setSpeed( 180 );
    motor.run( FORWARD );

    int sVal = analogRead( LINE_SENSOR );
    int error = sVal - sM;
    
    Serial.println( error );
    
    int t;
    if ( error < - 50 ) {
      steer.run(LEFT);
      t = error * -1;
    } else if ( error > 50 ) {
      steer.run(RIGHT);
      t = error;
    } else {
      steer.run(NEUTRAL);
    }
  } else { // less then 15cm = stop the car
    motor.run(RELEASE);
  }
}

/**
 * Take a look at the SDC_HCSR04 sketch for details on these functions
 */
int getDistance(){
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  pinMode(ECHO_PIN, INPUT);
  int duration = pulseIn(ECHO_PIN, HIGH);
  return duration;
}

int pulseToCm( int uS ){
  return ( uS / 2 ) / 29.4;
}
