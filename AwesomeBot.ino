#include <Servo.h> 

Servo leftServo;
Servo rightServo;
Servo headServo;
#define triggerPin 4
#define echoPin 5
int headPosition = 50;
int collisionCounter = 0;
unsigned long moveAt = 0;

void setup() 
{ 
  leftServo.attach(6);
  rightServo.attach(10);
  headServo.attach(8);
  leftServo.write(0);
  rightServo.write(255);
  
  Serial.begin (9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() 
{
  checkForCollision();

  unsigned long now = millis();
  if (now >= moveAt) {
    headPosition = random(25, 100);
  //  headPosition = 50;
    headServo.write(headPosition);
    
    int delayValue = random(30, 100);
    moveAt = now + delayValue;
    Serial.println("LOOK SOMEWHERE ELSE");
  }
}

void checkForCollision() {
  long duration, distance;
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin, HIGH);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
  if (distance > 0 && distance < 100){
    Serial.println("Evasive action");
    int turnAmount = 500-(distance*5);
    
    if (collisionCounter > 2) {
      backTheFuckOff(turnAmount);
    } else if (headPosition < 55) {
      moveRight(turnAmount);
    } else {
      moveLeft(turnAmount); 
    }
    collisionCounter += 2;
  } else {
    if (collisionCounter > 0) {
      collisionCounter--;
    }
  }
}

void moveLeft(int amount) {
  leftServo.write(255);
  delay(amount);
  leftServo.write(0);
}

void moveRight(int amount) {
  rightServo.write(0);
  delay(amount);
  rightServo.write(255);
}

void backTheFuckOff(int amount) {
  rightServo.write(0);
  leftServo.write(255);
  delay(1000);
  rightServo.write(255);
  delay(250);
  leftServo.write(0);
  collisionCounter = 0;
}
