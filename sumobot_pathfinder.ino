
int trig1 = 6;
int echo1 = 7;
int trig2 = 8;
int echo2 = 9;
int trig3 = 10;
int echo3 = 11;
int cm1 = 0;
int cm2 = 0;
int cm3 = 0;
int irSensor = A0;
int switchpin1 = 12;
int switchpin2 = 13;
//FOR MOTOR DRIVER
//speed control
// int enA = 3;
// int enB = 6;
//direction control right motor
int in1 = 2;
int in2 = 3;
//direction control left motor
int in3 = 4;
int in4 = 5;
//function decleration

void forward(int in1, int in2, int in3, int in4);
void backwards(int in1, int in2, int in3, int in4);
void right(int in1, int in2, int in3, int in4);
void left(int in1, int in2, int in3, int in4);
void pathFinder(int cm1, int cm2, int cm3);


void pathFinder(int cm1, int cm2, int cm3) {
  //to be changed to wheels
  int stop_dis = 18;  // stopping distance
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
    delay(1000);
    if (cm3 > cm2) {
      left(in1, in2, in3, in4);
    } else {
      right(in1, in2, in3, in4);
    }
  } else if (cm1 <= stop_dis && cm2 >= stop_dis && cm3 >= stop_dis) {
    //obstacle front
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
  int opponent = 50;

  if (cm1 <= opponent) {
    forward(in1, in2, in3, in4);
  } else {
    right(in1, in2, in3, in4);
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
void left(int in1, int in2, int in3, int in4) {

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void right(int in1, int in2, int in3, int in4) {

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
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



void irRead(int irSensor) {
  pinMode(irSensor, INPUT);
  pinMode(13, OUTPUT);
  if (digitalRead(irSensor) == HIGH) {
    // turn off if white
    digitalWrite(13, HIGH);
  } else {
    //turn on if low
    digitalWrite(13, LOW);
  }
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(irSensor, INPUT);
}

void loop() {
  //   //FOR ULTRASONIc CONVERSION
  cm1 = ultrasonicRead1(trig1, echo1) / 29 / 2;
  cm2 = ultrasonicRead2(trig2, echo2) / 29 / 2;
  cm3 = ultrasonicRead3(trig3, echo3) / 29 / 2;

  // i used toogle switch for this, this is to change the system from summobot to pathfinder and vice versa
//GI COMMENT SA NA NAKO KAY WAPA KO KA ATTACHED SA SWITCH
  // if (digitalRead(switchpin1) == HIGH) {
  //   pathFinder(cm1, cm2, cm3);
  // } else if (digitalRead(switchpin2) == HIGH) {
  //   summobot(cm1);
  // }

    summoBot(cm1);
    Serial.print("cm1 ");
    Serial.println(cm1);
    Serial.print("cm2 ");
    Serial.println(cm2);
    Serial.print("cm3 ");
    Serial.println(cm3);

    //   // for testing - multimeter
    //   // Read the input on analog pin 0
    //   int sensorValue = analogRead(A0);
    //   // Convert the analog reading to voltage
    //   float voltage = sensorValue * (5.0 / 1023.0);
    //   // Print the voltage to the Serial Monitor
    //   Serial.println(voltage);
    //   delay(1000);
    //  //irRead(irSensor);
    //  right(in1, in2, in3, in4);
  }
