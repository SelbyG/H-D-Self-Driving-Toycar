/**
 *  TCRT5000 line sensor test for the Self-driving Toy Car – Hack Night
 * 
 * The sensor we're using to follow the line is a very simple IR Emitter and an IR PhotoTransistor packaged together.
 * It outputs a voltage that we can use to determine the brightness/darkness of the object it is looking at.
 * We can measure this voltage with the Arduinos analog input pins.
 *
 * We need to do a little soldering to be able to connect the sensor to the necessary pins though.
 * Next to the analogue input pins there are three rows of holes, marked A0-5, GND and +5
 *
 * Connect the sensor like this:
 * 
 * Sensor -> Arduino
 * VCC  -> 5+ next to A0
 * GND  -> GND next to A0
 * A0   -> A0
 * D0   -> Not needed. You can leave it unconnected.
 * 
 * Connect the sensor, upload the sketch and open the serial monitor.
 * You should see a string of numbers being printer to the serial monitor. 
 * Small numbers for a light underground and higher numbers for darker undergrounds.
 * 
 * created 23 Feb 2017
 * by Heerko van der Kooij
 * 
 *  This example is in the public domain
*/

int LINE_SENSOR = A0;

void setup() {
  Serial.begin( 9600 ); // set up Serial library at 9600 bps
}

void loop() {
  int colorVal = analogRead( LINE_SENSOR );
  Serial.println( colorVal );
}
