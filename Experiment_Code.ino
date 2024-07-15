
/////////////////////////////
//load cell preliminaries
#include "HX711.h"

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
const int grams_calibration_factor = 1; //placeholder value

//const int newtons_calibration_factor = grams_calibration_factor * 9800


HX711 scale; 


///////////////////////////////////
//stepper motor preliminaries

// defines pins numbers
const int stepPin = 9; 
const int dirPin = 8;

///////////////////////////////////
//switch and button preliminaries

//defines switch and button pins
const int switchPin = 13;
const int buttonPin = 12;

////////////////////////////////

void setup() {
  //////////////////////////////
  //load cell
  Serial.begin(9600); //initializes serial data communication
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);  //configures force sensor

////////////////////////
//////User Inputs///////

//Calibration Factor (CF)
 Serial.print("Enter calibration factor: ");
  

 while (Serial.available() == 0) {}  //holds here until data is entered to the serial monitor (values, then ENTER key)
    float calibration_factor = Serial.parseFloat();

    while (Serial.available() > 0) {  //clears the serial monitor of extraneous data in the serial input
      Serial.read();
    }

   Serial.println(calibration_factor, 4);

   delay(200);

//Sample Number
 Serial.print("Enter sample number: ");
 
 while (Serial.available() == 0) {}  //holds here until data is entered to the serial monitor (values, then ENTER key)
    int sample_number = Serial.parseInt();

    while (Serial.available() > 0) {  //clears the serial monitor of extraneous data in the serial input
      Serial.read();
    }

   Serial.println(sample_number);

   delay(200);
    
//Number of steps (num_steps)
 Serial.print("Enter num_steps: ");

 while (Serial.available() == 0) {}  //holds here until data is entered to the serial monitor (values, then ENTER key)
    int num_steps = Serial.parseInt();

 while (Serial.available() > 0) {  //clears the serial monitor of extraneous data in the serial input
      Serial.read();}

  Serial.println(num_steps);

  delay(200);
  
//Step size (step_size)
Serial.print("Enter step_size: ");

while (Serial.available() == 0) {}  //holds here until data is entered to the serial monitor (values, then ENTER key)
    int step_size = Serial.parseInt();

 while (Serial.available() > 0) {  //clears the serial monitor of extraneous data in the serial input
      Serial.read();}

Serial.println(step_size);

delay(200);

//Pulse delay (pulse_delay)
Serial.print("Enter pulse_delay: ");

while (Serial.available() == 0) {}  //holds here until data is entered to the serial monitor (values, then ENTER key)
    int pulse_delay = Serial.parseInt();

 while (Serial.available() > 0) {  //clears the serial monitor of extraneous data in the serial input
      Serial.read();}

  Serial.println(pulse_delay);

  //////////////////////////////
  //Force Sensor configuration

  Serial.println("Press button to tare force sensor...");
  while(digitalRead(buttonPin) == 0) {}

  if (scale.is_ready()) {
  scale.tare();
  }
  scale.set_scale(calibration_factor);
 
  Serial.println("Force Sensor Tared...");
  delay(500);
  Serial.print("Tare reading...:  ");
  Serial.println(scale.get_units(),1);


    
  /////////////////////////////
  //set stepper motor output pins
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);


  ////////////////////////////
  //switch and button pin configuration
  pinMode(switchPin,INPUT);
  pinMoce(buttonPin, INPUT);


  Serial.print("Flip switch to begin program... \n");

 }



void loop() {
 
  ///////////////////////////
  //turn switch to the on position to start code
  while (digitalRead(switchPin) == 0) {}


  
  ///////////////////////////
  //first move stepper motor and records how many steps and in what direction
  //200 pulses is one full cycle rotation
  //step size is number of pulses between readings
  

  int dir_var = LOW;  //dir_var = HIGH -> clockwise, up; dir_var = LOW -> counterclockwise, down
  digitalWrite(dirPin,dir_var); // Enables the motor to move according to dir_var value


  Serial.print("\n");
  Serial.print("\t| step size: \t");
  Serial.print(step_size);  //step_size is set by use input in serial terminal
  Serial.print("\t| step direction: \t");
  Serial.println("down");
  
  ///////////////////////////
  //stepper motor moves, then reading is taken until i = num_steps

  for (int i = 0; i < num_steps; i++) {
    
   
    for(int x = 0; x < step_size; x++) {  //this loop executes a single step (step_size number of pulses)
        
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(pulse_delay); //pulse_delay sets rotational speed; if too low, motor doesn't have enough torque
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(pulse_delay); 
      
    }
      
    //Reading is taken
    Serial.print("\t| one reading:\t");
    Serial.println(scale.get_units(),1); //force sensor reading is taken
    
  }

delay(2000); //Two second delay between direction changes


dir_var = HIGH; //dir_var = HIGH -> clockwise, up; dir_var = LOW -> counterclockwise, down
digitalWrite(dirPin,dir_var); // Enables the motor to move according to dir_var value

  Serial.print("\n");
  Serial.print("\t| step size: \t");
  Serial.print(step_size);
  Serial.print("\t| step direction: \t");
  Serial.println("up");

 ///////////////////////////
 //stepper motor moves, then reading is taken until i = num_steps

 for (int i = 0; i < num_steps; i++) {

   
      for(int x = 0; x < step_size; x++) {  //this loop executes a single step
          
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(pulse_delay); //pulse_delay sets rotational speed; if too low, motor doesn't have enough torque
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(pulse_delay); 
            
      }

    Serial.print("\t| one reading:\t");
    Serial.println(scale.get_units(),1); //force sensor reading is taken
    
  }

 delay(2000);
 }
