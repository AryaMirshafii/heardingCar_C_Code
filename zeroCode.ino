#include <AudioFrequencyMeter.h>
//CODE FOR THE ARDUINO ZERO
//Authors:
//Arya Mirshafii
//Sidd Gahrg
AudioFrequencyMeter meter;
//Pin 10 = hearing from the left
//Pin 9 = hearing from right
int Horn_LED = 1;
int Siren_LED = 2;
//int leftHearing;
//int rightHearing;
void setup() {
  Serial.begin(115200);
  Serial.println("Microphones are enabled!");
  
  pinMode(Horn_LED, OUTPUT);
  pinMode(Siren_LED, OUTPUT);
  
  meter.setBandwidth(70.00, 1500);    // Ignore frequency out of this range
  meter.begin(A0, 45000);             // Intialize A0 at sample rate of 45kHz
//  pinMode(10, INPUT);
//  pinMode(9, INPUT);
}
void loop() {
 
  
  float frequency = meter.getFrequency();
  
  
  if ((frequency > 375) && (frequency < 525))
  {
  digitalWrite(Horn_LED, HIGH);
  digitalWrite(Siren_LED, LOW);
  }
  else if ((frequency > 600) && (frequency < 900))
  {
  digitalWrite(Horn_LED, LOW);
  digitalWrite(Siren_LED, HIGH);
  }
  else
  {
  digitalWrite(Horn_LED, LOW);
  digitalWrite(Siren_LED, LOW);
  }
  Serial.print(frequency);
}