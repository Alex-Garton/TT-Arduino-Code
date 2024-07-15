//Jacks June 3, 2024
// changing the output -- wanting each line that is printed to have readings, step size, direction, and displacement! 

//combined stepper motor and load cell code
// load cell calibration separate
//may use Rob Tillart's load cell library

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
int step_delay; //sets stepper motor speed
int num_steps;
int step_size;

///////////////////////////////////
//switch preliminary

//defines switch pin
const int switchPin = 13;
const int buttonPin = 12;

////////////////////////////////

void setup() {
  //////////////////////////////
  //load cell
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

////////////////////////
//User Inputs

 Serial.print("Enter calibration factor: ");
  

 while (Serial.available() == 0) {}  //holds here until data is entered to the serial monitor (values, then ENTER key)
    float calibration_factor = Serial.parseFloat();

    while (Serial.available() > 0) {  //clears the serial monitor of extraneous data in the serial input
      Serial.read();
    }

   Serial.println(calibration_factor, 4);

   delay(200);


 Serial.print("Enter sample number: ");
 
 while (Serial.available() == 0) {}  //holds here until data is entered to the serial monitor (values, then ENTER key)
    int sample_number = Serial.parseInt();

    while (Serial.available() > 0) {  //clears the serial monitor of extraneous data in the serial input
      Serial.read();
    }

   Serial.println(sample_number);

   delay(200);
    

 Serial.print("Enter num_steps: ");

 while (Serial.available() == 0) {}  //holds here until data is entered to the serial monitor (values, then ENTER key)
    num_steps = Serial.parseInt();

 while (Serial.available() > 0) {  //clears the serial monitor of extraneous data in the serial input
      Serial.read();}

  Serial.println(num_steps);

  delay(200);
  

Serial.print("Enter step_size: ");

while (Serial.available() == 0) {}  //holds here until data is entered to the serial monitor (values, then ENTER key)
    step_size = Serial.parseInt();

 while (Serial.available() > 0) {  //clears the serial monitor of extraneous data in the serial input
      Serial.read();}

Serial.println(step_size);

delay(200);

Serial.print("Enter step_delay: ");

while (Serial.available() == 0) {}  //holds here until data is entered to the serial monitor (values, then ENTER key)
    step_delay = Serial.parseInt();

 while (Serial.available() > 0) {  //clears the serial monitor of extraneous data in the serial input
      Serial.read();}

  Serial.println(step_delay);

  //////////////////////////////
  //Force Sensor initialization

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
  //switch
  pinMode(switchPin,INPUT);

 

  Serial.print("Flip switch to begin program... \n");
 }



void loop() {
 
  ///////////////////////////
  //turn switch to the on position to start code
  while (digitalRead(switchPin) == 0) {}


  
  ///////////////////////////
  //first move stepper motor and record how many steps and in what direction
  

  int dir_var = LOW;  //dir_var = HIGH -> clockwise, up; dir_var = LOW -> counterclockwise, down
  digitalWrite(dirPin,dir_var); // Enables the motor to move according to dir_var value

  
  //200 pulses is one full cycle rotation
  //step size is number of pulses between readings

  ////////////////////////////
  //stepper motor moves, then reading is taken until i = num_steps


  

  //int num_steps = 40; //represents number of steps before changing direction and number of readings per direction
  //int step_size = 10; //sets the step size

  Serial.print("\n");
  Serial.print("\t| step size: \t");
  Serial.print(step_size);  //step_size is set by use input in serial terminal
  Serial.print("\t| step direction: \t");
  Serial.println("down");
  
  
  for (int i = 0; i < num_steps; i++) {
    
    //this loop executes a single step

    for(int x = 0; x < step_size; x++) {  
        
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(step_delay); //this sets rotational speed; if too low, motor doesn't have enough torque
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(step_delay); 
      
    }
  
    //delay(50); //One second delay

    //Reading is taken
    Serial.print("\t| one reading:\t");
    Serial.println(scale.get_units(),1); //force sensor reading

    
    //delay(50); // One second delay
    
  }

delay(2000); //Two second delay between direction changes


dir_var = HIGH; //dir_var = HIGH -> clockwise, up; dir_var = LOW -> counterclockwise, down
digitalWrite(dirPin,dir_var); // Enables the motor to move according to dir_var value

//num_steps = 40; //represents number of steps before changing direction
//step_size = 10; //sets the step size

    Serial.print("\n");
    Serial.print("\t| step size: \t");
    Serial.print(step_size);
    Serial.print("\t| step direction: \t");
    Serial.println("up");

 for (int i = 0; i < num_steps; i++) {

   //this loop executes a single step
    
    for(int x = 0; x < step_size; x++) {
          
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(step_delay); //this sets rotational speed; if too low, motor doesn't have enough torque
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(step_delay); 
            
  }

  //delay(50);

   Serial.print("\t| one reading:\t");
   Serial.println(scale.get_units(),1);
    
  //delay(50);

  }

 delay(2000);
 }
