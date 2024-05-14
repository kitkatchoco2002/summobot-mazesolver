#include <IRremote.h>
#include <ir_Lego_PF_BitStreamEncoder.h>




// note ilahi ug inputs ang each infrared sensors
int trig1 = 6;
int echo1 = 7;
int trig2 = 8;
int echo2 = 9; 
int trig3 = 10;
int echo3 = 11;
int cm1 = 0;
int cm2 = 0;
int cm3 = 0;
int irSensor1 = A0;
int irSensor2 = A1;
//FOR MOTOR DRIVER
//speed control
// int enA = A2;
// int enB = A3;
//direction control right motor
int in1 = 2;
int in2 = 3;
//direction control left motor
int in3 = 4;
int in4 = 5;
//remote for switching system
int receiver = 12;
IRrecv irrecv(receiver);
decode_results results;
int currentMode = 0;



void pathFinder(int cm1, int cm2, int cm3) {
  int stop_dis = 20;  // stopping distance
  // cm2=right, cm3 = left

  if (cm1 >= stop_dis && cm2 <= stop_dis && cm3 <= stop_dis) {
    //obstacle in both rear sides
    forward(in1, in2, in3, in4);
   } else if (cm1 <= stop_dis && cm2 >= stop_dis && cm3 <= stop_dis) {
    //obsatcle in front and left
    right(in1, in2, in3, in4);
  } else if (cm1 <= stop_dis && cm2 <= stop_dis && cm3 >= stop_dis) {
    //obstacle in front and right
    left(in1, in2, in3, in4);
  } else if (cm1 <= stop_dis && cm2 <= stop_dis && cm3 <= stop_dis) {
    // obstacle in all direction
    backwards(in1, in2, in3, in4);
    delay(100);
    if (cm3 > cm2) {
      left(in1, in2, in3, in4);
    } else {
      right(in1, in2, in3, in4);
    }
  } else if (cm1 <= stop_dis && cm2 >= stop_dis && cm3 >= stop_dis) {
    //obstacle front
    backwards(in1, in2, in3, in4);
     delay(100);
    if (cm3 > cm2) {
      left(in1, in2, in3, in4);
    } else {
      right(in1, in2, in3, in4);
    }
  } else if (cm1 >= stop_dis && cm2 >= stop_dis && cm3 >= stop_dis) {
    // no obstacle
    forward(in1, in2, in3, in4);
  }
}

void summoBot(int cm1) {
  int opponent = 80;

  irRead(irSensor1, irSensor2);

  if (cm1 <= opponent) {
    forward(in1, in2, in3, in4);
  } else {
    
    right(in1, in2, in3, in4);
    delay(400);
    stop(in1, in2, in3, in4);
    delay(100);
  }
}

//WHEELS
void forward(int in1, int in2, int in3, int in4) {

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void backwards(int in1, int in2, int in3, int in4) {

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void right(int in1, int in2, int in3, int in4) {

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void left(int in1, int in2, int in3, int in4) {

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void stop(int in1, int in2, int in3, int in4) {

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


long ultrasonicRead1(int trig, int echo) {
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  return pulseIn(echo, HIGH);
}
long ultrasonicRead2(int trig, int echo) {
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  return pulseIn(echo, HIGH);
}
long ultrasonicRead3(int trig, int echo) {
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  return pulseIn(echo, HIGH);
}



void irRead(int irSensor1, int irSensor2) {
  pinMode(irSensor1, INPUT);
  pinMode(irSensor2, INPUT);
  pinMode(13, OUTPUT);

  if ((digitalRead(irSensor1) || digitalRead(irSensor2))== HIGH) {
    //IF ONE IS WHITE MUST GO FORWARD
    forward(in1, in2, in3, in4);
  } else if(digitalRead(irSensor1) == HIGH){
    //left sensor
    right(in1, in2, in3, in4);
  } else if(digitalRead(irSensor2) == HIGH){
    //right sensor
    left(in1, in2, in3, in4);
  } else if((digitalRead(irSensor1) && digitalRead(irSensor2)) == LOW) {
    //IF BOTH BLACK PADAYUN SA COMMAND
    //turn on if low
    digitalWrite(13, LOW);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(13, OUTPUT);
}

void loop() {
  int dElay = 0;
  //   //FOR ULTRASONIc CONVERSION
  cm1 = ultrasonicRead1(trig1, echo1) / 29 / 2;
  cm2 = ultrasonicRead2(trig2, echo2) / 29 / 2;
  cm3 = ultrasonicRead3(trig3, echo3) / 29 / 2;


  if (irrecv.decode(&results)) {
      // // Get the infrared code
      // Serial.println(results.value, HEX);
    
      if(results.value == 0xFF6897){
        // number 0
        currentMode = 0;
        digitalWrite(13, LOW);
      }else if(results.value == 0xFF30CF){
        // number 1
        currentMode = 1;
        dElay = 5000;
        digitalWrite(13, HIGH);
      }else if(results.value == 0xFF906F){
        //2
        currentMode = 2;
      }
      // Enable receiving of the next value
      irrecv.resume();
    } 

    if(currentMode == 0){
      pathFinder(cm1, cm2, cm3);
    }else if(currentMode == 1){
      delay(dElay);
      summoBot(cm1);
      // Serial.println("summo");
      // Serial.println(dElay);
    }else if(currentMode == 2){
      stop(in1, in2, in3, in4);
    }
    // Serial.print("cm1 ");
    // Serial.println(cm1);
    // Serial.print("cm2 ");
    // Serial.println(cm2);
    // Serial.print("cm3 ");
    // Serial.println(cm3);
    // delay(1000);

      // // for testing - multimeter
      // // Read the input on analog pin 00
      // int sensorValue = analogRead(A3);
      // // Convert the analog reading to voltage
      // float voltage = sensorValue * (5.0 / 1023.0);
      // // Print the voltage to the Serial Monitor
      // Serial.println(voltage);
      // delay(1000);
    //  irRead(irSensor1,irSensor2);
    // //  right(in1, in2, in3, in4);
  }
