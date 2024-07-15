#include "HX711.h"

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
const int buttonPin = 12;
const int switchPin = 13;
bool tare_done = false;

HX711 scale; 


void setup() {
  
 Serial.begin(9600);

 scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); //configuring the scale pins
 pinMode(buttonPin, INPUT);
 pinMode(switchPin, INPUT);

 Serial.println("Turn on switch to start...");
}

void loop() {

  if (digitalRead(switchPin) == 1) {
  
  while (digitalRead(switchPin) == 0) {} //holds here until button is pressed
  
  if (scale.is_ready()){
    scale.set_scale();
    if (!tare_done){
    Serial.println("Press button to tare... remove any weights from weight carriage.");
    
    while (digitalRead(buttonPin) == 0) {}  //holds here until button is pressed
   
    scale.tare();  //tare the scale
    Serial.println("Tare complete...");
    tare_done = true;
    delay(300);
    }

    else {

    Serial.println("Place a known weight on the scale...");
    delay(1000);
    Serial.println("Enter weight value: ");

    
    while (Serial.available() == 0) {}  //holds here until data is entered to the serial monitor (values, then ENTER key)
    float weight = Serial.parseFloat();

    while (Serial.available() > 0) {  //clears the serial monitor of extraneous data in the serial input
      Serial.read();
    }
    
    
    Serial.print("Weight: ");  //prints known weight to the serial monitor
    Serial.print(weight, 4);
    Serial.println(" g");
    
    Serial.println("Press button to obtain reading...");
    

    while (digitalRead(buttonPin) == 0) {}  //holds here until button is pressed


    float reading = scale.get_units(10);  //force sensor reading is taken
    Serial.print("Reading: ");
    Serial.println(reading);
    delay(1000);
    }
    
  }
   

  else {
    Serial.println("HX711 not found.");
  }
  delay(1000);
}
}

//calibration factor will be the (reading)/(known weight)
