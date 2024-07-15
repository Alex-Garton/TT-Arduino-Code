const int stepPin = 9; 
const int dirPin = 8;
const int step_delay = 700; //sets stepper motor speed
const int switchPin = 13;
const int buttonPin = 12;

void setup() {
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);

  pinMode(switchPin,INPUT);

}

void loop() {
  
 while (digitalRead(switchPin) == 0) {}

 int dir_var = LOW;  //dir_var = HIGH -> clockwise, up; dir_var = LOW -> counterclockwise, down
 digitalWrite(dirPin,dir_var); // Enables the motor to move according to dir_var value

 int num_steps = 2; //represents number of steps before changing direction and number of readings per direction
 int step_size = 10; //sets the step size

  for (int i = 0; i < num_steps; i++) {
    
    //this loop executes a single step

    for(int x = 0; x < step_size; x++) {  
        
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(step_delay); //this sets rotational speed; if too low, motor doesn't have enough torque
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(step_delay); 
      
    }

  }
//while(digitalRead(switchPin) == 1) {}
}
