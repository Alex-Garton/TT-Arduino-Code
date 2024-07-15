#include "HX711.h"

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
const int switchPin = 13;
const int buttonPin = 12;
bool tare_done = false;

const float calibration_factor = -1122.45; // Enter calibration factor from calibration

HX711 scale;

void setup() {
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  
  pinMode(switchPin, INPUT);
  pinMode(buttonPin, INPUT);
  
  Serial.println("Turn on the switch to start...");
}

void loop() {
  if (digitalRead(switchPin) == HIGH) {

    ///////////////////////////////
    //Tare step; will only run once
    if (!tare_done) {
  Serial.println("Remove weight from force sensor...");
  Serial.println("Press button to tare...");
      
  while (digitalRead(buttonPin) == 0) {} //holds until button is pressed
      
  delay(100);
  scale.tare();
  Serial.println("Tare complete.");
  delay(500);
  tare_done = true;
  Serial.println("Ready for weight measurements.");
  Serial.println("Enter true weight to be measured: ");

  while (Serial.available() == 0) {}
  float weight = Serial.parseFloat();

  while (Serial.available() > 0) {
    Serial.read();}

   Serial.print("True weight: ");
   Serial.print(weight, 4);
   Serial.println(" g");
   
  delay(500);
}

  //////////////////////////////
  //Measurement step
   else {
  Serial.println("Place known weight on scale...");
  delay(400);
  Serial.println("Press button to obtain reading...");
  delay(400);
  
    while (digitalRead(buttonPin) == 0) {}
      // Wait for button press
        
    delay(50);    
  
    float reading = scale.get_units(10);  // Force sensor reading is taken (average of 10 readings)
    Serial.print("Reading: ");
    Serial.print(reading, 4);  // Print with 2 decimal places
    Serial.println(" g");
    
    delay(1000);  
  }
  }
  }
