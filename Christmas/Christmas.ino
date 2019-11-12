/*
   ChristmasTree

   by Ben Torkington <ben@torkington.com>

   16 December 2016
*/

#include <Arduino.h>

// change the following two lines to match the number of LEDs you have connected
#define PINMIN 2      // the first pin with an LED connected
#define PINMAX 12     // the last pin with an LED connected

// the setup function runs once when you press reset or power the board
void setup() {
  // set up each of the pins in output mode
  for (int i=PINMIN; i<=PINMAX; ++i)
  {
    pinMode(i, OUTPUT);
  }
}

// Now for the utility functions, 

// light each of the LEDs one at a time, starting with the first
void scanUp() {
  for (int i=PINMIN; i<PINMAX + 1; ++i) {
    digitalWrite(i, HIGH);
    delay (100);
    digitalWrite(i, LOW); 
  }
}

// light each of the LEDs one at a time, starting with the last, and working down.
void scanDown() {
  for (int i = PINMAX; i>= PINMIN; --i) {
    digitalWrite(i, HIGH);
    delay (100);
    digitalWrite(i, LOW);     
  }
}

// set all of the Red LEDs at once, either HIGH or LOW
void allRed(int value) {
  digitalWrite(3, value);
  digitalWrite(5, value);
  digitalWrite(7, value);
  digitalWrite(9, value);
  digitalWrite(11, value);
}

// set all of the Green LEDs at once, either HIGH or LOW
void allGreen(int value) {
  digitalWrite(2, value);
  digitalWrite(4, value);
  digitalWrite(6, value);
  digitalWrite(8, value);
  digitalWrite(10, value);
  digitalWrite(12, value);
}

// turn all the Red LEDs on, and the Green LEDs off
void redOnly()
{
  allRed(HIGH);
  allGreen(LOW);
}

// turn all the Green LEDs on, and the Red LEDs off
void greenOnly()
{
  allRed(LOW);
  allGreen(HIGH);
}

void allOn()
{
  allRed(HIGH);
  allGreen(HIGH);
}

void allOff()
{
  allRed(LOW);
  allGreen(LOW);
}

// make 6 LEDs glimmer like stars using PWM. We can only do this for the 6 LEDs connected
// to pins 3, 5, 6, 9, 10 and 11, because those are the only ports on the Arduino Uno
// that support PWM.

void glimmer()
{
  float offsets[6];       // to store different phases for each of 6 
  for(int i=0; i<6; ++i)
  {
    offsets[i] = random(0, 511) * PI / 256;   // calculate a phase at random for each LED between 0 and 2 * PI
  }

  for(int i=0; i<1024; ++i)
  {
    float theta = i * PI / 32;
    
    analogWrite(3, (cos(theta + offsets[0]) + 1) * 128);
    analogWrite(5, (cos(theta + offsets[1]) + 1) * 128);
    analogWrite(6, (cos(theta + offsets[2]) + 1) * 128);
    analogWrite(9, (cos(theta + offsets[3]) + 1) * 128);
    analogWrite(10, (cos(theta + offsets[4]) + 1) * 128);
    analogWrite(11, (cos(theta + offsets[5]) + 1) * 128);

    delay(10);
  }  
}

// Here is where we define the lights routine.
// This where you should start experimenting!

void loop() {
   allOn();
   delay(5000);
   allOff();

  
  for (int i=0; i<3; ++i)   // flash between green and red three times
  {
    // first we turn on all the red LEDs, and wait a second
    redOnly();  
    delay(1000);                       // wait for a second
  
    // now we turn on all the green ones, and wait a second again
  
    greenOnly();  
    delay(1000);                       // wait for a second
  }

  allGreen(LOW);    // turn the green lights off again

  // scan up three times
  scanUp();
  scanUp();
  scanUp();

  // and now scan down three times
  scanDown();
  scanDown();
  scanDown();


  // now glimmer
  glimmer();

  // now flash them all together six times
  for (int i = 0; i<6; ++i)
  {
    allOff();
    delay(500);
    allOn();
    delay(500);
  }

  // now turn them all back off
  allOff();
  
  // now we start all over again!
  // Merry Christmas!
}
