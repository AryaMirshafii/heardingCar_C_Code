#include <SoftwareSerial.h>
//Authors:

//Arya Mirshafii
//Sid Gharg
//Kuo Huang

//THIS IS THE CODE FOR THE ARDUINO UNO
//USED TO DETECT WHIHC MICROPHONE
//Mic left = A0
//Mic right = A1
//Mic Forward = A2
//Pin 10 = hearing from the left
//Pin 9 = hearing from right
SoftwareSerial mySerial(8,11); //RX, TX. 8 Connect TXD on BLE 11 Connect RXD on BLE
int state = 0;
void setup() {

  Serial.begin(9600);
  mySerial.begin(38400); //Can be changed on AT command mode
  Serial.println("started....");
 
  Serial.println("endline2....");
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
 
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
 
 
 
 

}
void loop() {


//The left facing microphone is defined as port 0
float micLeftOutput = checkSoundLevels(0);
//The right facing microphone is defined as port 0
float micRightOutput = checkSoundLevels(1);

//Figures out which microphone is loudest(ie where is the sound coming from and sends it to the zero)
whichMicrophone(micLeftOutput,micRightOutput);


//State Check
//IO 4 = Left Horn
//IO 5 = Left Siren
//IO 6 = Right Siren
//IO 7 = Right Horn

 if  ((digitalRead(4) == HIGH) && (digitalRead(5)==LOW) && (digitalRead(6)==LOW) && (digitalRead(7)==LOW)){
      state = 1;
      mySerial.println(String(state));
      //Serial.println("The State is " + String(state));
      return;
 } else if ((digitalRead(4) == LOW) && (digitalRead(5)==HIGH) && (digitalRead(6)==LOW) && (digitalRead(7)==LOW)) {
      state = 2;
      mySerial.println(String(state));
      //Serial.println("The State is " + String(state));
      return;
 } else if ((digitalRead(4) == LOW) && (digitalRead(5)==LOW) && (digitalRead(6)==HIGH) && (digitalRead(7)==LOW)) {
      state = 3;
      mySerial.println(String(state));
      //Serial.println("The State is " + String(state));
      return;
 } else if ((digitalRead(4) == LOW) && (digitalRead(5)==LOW) && (digitalRead(6)==LOW) && (digitalRead(7)==HIGH)) {
       state = 4;
       mySerial.println(String(state));
       //Serial.println("The State is " + String(state));
       return;
 } else {
   state = 0;
   mySerial.println(String(state));
   //Serial.println("The State is " + String(state));
   return;
 }

 Serial.println("The State is " + String(state));
}


//A simple function that determines which microphone is detecting the loudest noise and writes high and low values to pins 9 and 10 which are connected to the arduino zero.

void whichMicrophone(float micLeft, float micRight){

if (micLeft > micRight) {
    //uncomment the below line if you want to debug
    //Serial.println("Hearing from the left");
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
 
 
} else if(micLeft < micRight){
    //uncomment the below line if you want to debug
    //Serial.print("Hearing from the right");
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
}




}
// a function that returns the "loudness of a microphone"
//input represents a pin to read using analogread
float checkSoundLevels(int pinNumber){
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;  
unsigned long startMillis= millis();  // Start of sample window
 unsigned int peakToPeak = 0;   // peak-to-peak level

 unsigned int signalMax = 0;
 unsigned int signalMin = 1024;

 // collect data for 50 mS
 while (millis() - startMillis < sampleWindow)
 {
    sample = analogRead(pinNumber);
    if (sample < 1024)  // toss out spurious readings
    {
       if (sample > signalMax)
       {
          signalMax = sample;  // save just the max levels
       }
       else if (sample < signalMin)
       {
          signalMin = sample;  // save just the min levels
       }
    }
 }
 peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
 float soundLevel = (peakToPeak * 5.0) / 1024;  // convert to volts

 return soundLevel;

}