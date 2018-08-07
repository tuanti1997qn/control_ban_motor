#include <Stepper.h>

int DIR=6; //define Direction pin
int ENA=5; //define Enable Pin
int sw1 = 3;
int sw2 = 4;
int mystep = 250;
int curr_dir=1;
int current_speed=0;
const int stepsPerRevolution = 700;  // change this to fit the number of steps per revolution
// for your motor


// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8,9 );

int stepCount = 0;  // number of steps the motor has taken

void setup() {
  // nothing to do inside the setup
  pinMode (DIR, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  digitalWrite(ENA,HIGH);
  Serial.begin(9600);
}

void loop() {
  // read the sensor value:
  int sensorReading = analogRead(A0);
  // map it to a range from 0 to 100:
  int motorSpeed = map(sensorReading, 0, 1023, 0, 2500);

  if(digitalRead(sw1) ==0)
  {
    control_speed_1(motorSpeed);
  }
  if(digitalRead(sw2) ==0)
  {
    control_speed_2(motorSpeed);
  }
  if((digitalRead(sw2)&digitalRead(sw1)) == 1)
  {
    current_speed -= mystep;
    if(current_speed<=0)
    {
      current_speed = 0;
    }
    myStepper.setSpeed(current_speed);
    // step 1/100 of a revolution:
    myStepper.step(current_speed );
  }
  Serial.println("current_speed");
  Serial.println(current_speed);
  Serial.println("motorSpeed");
  Serial.println(motorSpeed);
  Serial.println("curr_dir");
  Serial.println(curr_dir);
 // Serial.println(digitalRead(sw1));
 /* Serial.println(analogRead(A0));
  Serial.println(digitalRead(sw1));
  Serial.println(digitalRead(sw2));*/
}

void control_speed_1(int ref)
{
  if(curr_dir==1)
  {
    digitalWrite(DIR,HIGH);
    current_speed -= mystep;
    if(current_speed<=0)
    {
      curr_dir = -1;
      current_speed = 0;
    }
  }
  if(curr_dir==-1)
  {
    digitalWrite(DIR,LOW);
    if(current_speed<ref)
    {
      current_speed += mystep;
    }
    else
    {
      current_speed = ref;
    }
  }
    myStepper.setSpeed(current_speed);
    // step 1/100 of a revolution:
    myStepper.step(current_speed );
}
void control_speed_2(int ref)
{
  if(curr_dir == -1)
  {
    digitalWrite(DIR,LOW);
    current_speed -= mystep;
    if(current_speed<=0)
    {
      curr_dir = 1;
      current_speed = 0;
    }
  }
  if(curr_dir == 1)
  {
    digitalWrite(DIR,HIGH);
    if(current_speed<ref)
    {
      current_speed += mystep;
    }
    else
    {
      current_speed = ref;
    }
  }
    myStepper.setSpeed(current_speed);
    // step 1/100 of a revolution:
    myStepper.step(current_speed );
}
