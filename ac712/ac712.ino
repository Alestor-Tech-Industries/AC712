//This was coded by Alestor Aldous/Alestor-Tech-Industries 
//You have the right to change or modify the code 
// include the library code:
#include <LiquidCrystal.h> //library for LCD
const int numReadings = 200;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

//Measuring Current Using ACS712

const int analogIn = 0; //Connect current sensor with A0 of Arduino
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int ACSoffset = 2500; 
double Voltage = 0; //voltage measuring
double Amps = 0;// Current measuring

void setup() {
   for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  //baud rate
  Serial.begin(9600);//baud rate at which arduino communicates with Laptop/PC
  // set up the LCD's number of columns and rows:
  // Print a message to 
 
  
  delay(2000);//delay for 2 sec
}

void loop() //method to run the source code repeatedly
{
 
 RawValue = analogRead(analogIn);//reading the value from the analog pin
 Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
 Amps = ((Voltage - ACSoffset) / mVperAmp);
 

 Serial.println(Amps);// the '3' after voltage allows you to display 3 digits after decimal point
 delay(100);
 
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = (Amps,3);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  //Serial.println(average);
  delay(1);        // delay in between reads
}
