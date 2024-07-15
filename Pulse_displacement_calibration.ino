const int stepPin = 9; 
const int dirPin = 8;
const int switchPin = 13;
const int buttonPin = 12;

int step_size; //user input
int num_steps; //user input
int step_delay; //user input, usets stepper motor speed
float displacement; //user input

void setup() {
  Serial.begin(9600);
  
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);

  pinMode(switchPin,INPUT);
  pinMode(buttonPin, INPUT);

  Serial.print("\n");
  Serial.print("\n");

  /*Serial.print("Enter step size: ");

  while(Serial.available() == 0){}
  step_size = Serial.parseInt();
  
  Serial.println(step_size); */
  
  while(Serial.available() > 0){
  Serial.read(); }

  Serial.print("Enter number of steps: ");

  while(Serial.available() == 0){}
  num_steps = Serial.parseInt();

  Serial.println(num_steps);

  while(Serial.available() > 0){
  Serial.read();}

 /* Serial.print("Enter step delay: ");
  
  while(Serial.available() == 0){}
  step_delay = Serial.parseInt();

  Serial.println(step_delay);

  while(Serial.available() > 0){
  Serial.read();}*/
}


void loop() {

 while(digitalRead(buttonPin) == 0) {}
 
 int step_size = 10;
 int step_delay = 3000;
 int dir_var = HIGH;  //dir_var = HIGH -> clockwise, up; dir_var = LOW -> counterclockwise, down
 digitalWrite(dirPin,dir_var); // Enables the motor to move according to dir_var value


  for (int i = 0; i < num_steps; i++) {
    
    //this loop executes a single step

    for(int x = 0; x < step_size; x++) {  
        
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(step_delay); //this sets rotational speed; if too low, motor doesn't have enough torque
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(step_delay); 
      
    }

  }
 Serial.print("Enter displacement (cm): ");

 while(Serial.available() == 0){}
 displacement = Serial.parseFloat();

 Serial.println(displacement);
 

  }
 
