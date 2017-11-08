/**
 * Motorshield test for the Self-driving Toy Car – Hack Night
 *
 * If the sensor and motor tests both work for you, you're now
 * ready to test your Self Driving Toycar!
 *
 * Make sure you setup the min and max values for your line sensor
 * correctly below.
 *
 * The line following code is actually really simple.
 * First we calcalate the average value of the sensor (so the middle).
 * Assuming the car is on the left hand side of the line:
 * If the value is higher (brighter) than the average we steer left,
 * otherwise we steer right.
 */


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
int sMin = 270; // set this to the minimal value you get from the line sensor
int sMax = 1000; // set this to the maximal value you get from the line sensor

int sMid = ( sMin + sMax ) / 2; // calculate the midpoint.

/**
 * One sixth of the range on both sides off the middle for driving straight
 * that makes 1/3 left, 1/3 straight, 1/3 right.
 */
int center = sMid / 6;

void setup() {
  steer.setSpeed( 255 );
  steer.run( NEUTRAL );

  motor.setSpeed( 180 );
  motor.run( FORWARD );
}

void loop() {
  // read the line sensor.
  int sVal = analogRead( LINE_SENSOR );
  // the error is the difference between the perfect middle of our range
  // and the sensor value.
  int error = sVal - sMid;

  int t;
  if ( error < -center ) {
    steer.run( LEFT );
  } else if ( error > center ) {
    steer.run( RIGHT );
  } else {
    steer.run( NEUTRAL );
  }
}

