/*TEMP
 * Copyright (C) 2014 Velleman nv
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 */
 
#include <Servo.h> 
#include <ALLBOT.h>

ALLBOT BOT(8);  //number of motors

enum MotorName {
  hipFrontLeft,
  hipFrontRight,
  hipRearLeft,
  hipRearRight,
  wheelFrontLeft,
  wheelFrontRight,
  wheelRearLeft,
  wheelRearRight
};

long randNumber0;
long randNumber1;
int sounderPin = 13;
int white = 5;
int blue1 = 6;
int blue2 = 11;
int trimmer = A4;
int soundsens = A3;
int lightsens = A5;

String rawcommand;
String command;
int times;
int speedms;

void setup() 
{ 
  //BOT.attach(motorname, pin, init. angle, flipped, offset);
  BOT.attach(hipFrontLeft,    A1,  80, 0, 0);   //ORANGE = -5 0 -5 0 0 0 0 5
  BOT.attach(hipFrontRight,   A0,  80, 1, 0);   //BLUE = -5 0 -5 0 0 0 0 5
  BOT.attach(hipRearLeft,     10,  80, 1, 0);   //GREEN = 0 0 0 0 -5 -5 0 0
  BOT.attach(hipRearRight,     3,  80, 0, -5);
 
  BOT.attach(wheelFrontLeft,  12,  90, 1, 2);
  BOT.attach(wheelFrontRight, A2,  90, 0, 0);
  BOT.attach(wheelRearLeft,    9,  90, 1, 1);
  BOT.attach(wheelRearRight,   4,  90, 0, 1);

  //INIT sounder
  pinMode(sounderPin, OUTPUT);

  //wait for joints to be initialized
  delay(500);

  //starting the hardware UART
  Serial.begin(2400);
  Serial.setTimeout(100);
  Serial.println("serial communication started");
  
  //INIT the random seed
  randomSeed(analogRead(5));

  //chirp for ready
  chirp(1, 50);
  chirp(1, 255);
  chirp(3, 0);

}

void loop() 
{


  forward(2, 0);
  delay(500);
  spinleft(5, 0);
  delay(500);
  backward(2, 0);
  delay(500);
  spinright(2, 0);
  delay(500);

}
//--------------------------------------------------------------
void spinright(int distance, int speedms){
  for (int i=0; i < 255; i++){
    analogWrite(blue1,i);
    analogWrite(blue2,i);
    delay(1);
  }

  BOT.move(hipRearRight, 45);
  BOT.move(hipRearLeft, 45);
  BOT.move(hipFrontRight, 45);
  BOT.move(hipFrontLeft, 45);
  BOT.animate(100);

  for (int i = 0; i < distance; i++){
    int x = map(analogRead(trimmer), 0, 1023, 90, 135);
    int y = map(analogRead(trimmer), 0, 1023, 90, 45);
    BOT.move(wheelRearRight, x);
    BOT.move(wheelRearLeft, y);
    BOT.move(wheelFrontRight, x);
    BOT.move(wheelFrontLeft, y);
    BOT.animate(100);
    delay(200);
  }

  BOT.move(wheelRearRight, 90);
  BOT.move(wheelRearLeft, 90);
  BOT.move(wheelFrontRight, 90);
  BOT.move(wheelFrontLeft, 90);

  BOT.move(hipRearRight, 80);
  BOT.move(hipRearLeft, 80);
  BOT.move(hipFrontRight, 80);
  BOT.move(hipFrontLeft, 80);
  BOT.animate(100);

  
  for (int i=255 ; i > 0; i--){
    analogWrite(blue1,i);
    analogWrite(blue2,i);
    delay(1);
  }
  analogWrite(blue1,0);
  analogWrite(blue2,0);

}
//--------------------------------------------------------------
void spinleft(int distance, int speedms){
  for (int i=0; i < 255; i++){
    analogWrite(blue1,i);
    analogWrite(blue2,i);
    delay(1);
  }

  BOT.move(hipRearRight, 45);
  BOT.move(hipRearLeft, 45);
  BOT.move(hipFrontRight, 45);
  BOT.move(hipFrontLeft, 45);
  BOT.animate(100);

  for (int i = 0; i < distance; i++){
    int x = map(analogRead(trimmer), 0, 1023, 90, 135);
    int y = map(analogRead(trimmer), 0, 1023, 90, 45);
    BOT.move(wheelRearRight, y);
    BOT.move(wheelRearLeft, x);
    BOT.move(wheelFrontRight, y);
    BOT.move(wheelFrontLeft, x);
    BOT.animate(100);
    delay(200);
  }

  BOT.move(wheelRearRight, 90);
  BOT.move(wheelRearLeft, 90);
  BOT.move(wheelFrontRight, 90);
  BOT.move(wheelFrontLeft, 90);

  BOT.move(hipRearRight, 80);
  BOT.move(hipRearLeft, 80);
  BOT.move(hipFrontRight, 80);
  BOT.move(hipFrontLeft, 80);
  BOT.animate(100);

  
  for (int i=255 ; i > 0; i--){
    analogWrite(blue1,i);
    analogWrite(blue2,i);
    delay(1);
  }
  analogWrite(blue1,0);
  analogWrite(blue2,0);

}
//--------------------------------------------------------------
void backward(int distance, int speedms){
  for (int i=0; i < 255; i++){
    analogWrite(white,i);
    delay(1);
  }
  
  BOT.move(hipRearRight, 100);
  BOT.move(hipRearLeft, 100);
  BOT.move(hipFrontRight, 100);
  BOT.move(hipFrontLeft, 100);
  BOT.animate(100);

  for (int i = 0; i < distance; i++){
    int x = map(analogRead(trimmer), 0, 1023, 90, 135);
    BOT.move(wheelRearRight, x);
    BOT.move(wheelRearLeft, x);
    BOT.move(wheelFrontRight, x);
    BOT.move(wheelFrontLeft, x);
    BOT.animate(100);
    delay(200);
  }

  BOT.move(wheelRearRight, 90);
  BOT.move(wheelRearLeft, 90);
  BOT.move(wheelFrontRight, 90);
  BOT.move(wheelFrontLeft, 90);

  BOT.move(hipRearRight, 80);
  BOT.move(hipRearLeft, 80);
  BOT.move(hipFrontRight, 80);
  BOT.move(hipFrontLeft, 80);
  BOT.animate(100);

  for (int i=255 ; i > 0; i--){
    analogWrite(white,i);
    delay(1);
  }
  analogWrite(white,0);
  
}
//--------------------------------------------------------------
void forward(int distance, int speedms){

  for (int i=0; i < 255; i++){
    analogWrite(white,i);
    delay(1);
  }
  
  BOT.move(hipRearRight, 100);
  BOT.move(hipRearLeft, 100);
  BOT.move(hipFrontRight, 100);
  BOT.move(hipFrontLeft, 100);
  BOT.animate(100);

  for (int i = 0; i < distance; i++){
    int x = map(analogRead(trimmer), 0, 1023, 90, 45);
    BOT.move(wheelRearRight, x);
    BOT.move(wheelRearLeft, x);
    BOT.move(wheelFrontRight, x);
    BOT.move(wheelFrontLeft, x);
    BOT.animate(100);
    delay(200);
  }

  BOT.move(wheelRearRight, 90);
  BOT.move(wheelRearLeft, 90);
  BOT.move(wheelFrontRight, 90);
  BOT.move(wheelFrontLeft, 90);

  BOT.move(hipRearRight, 80);
  BOT.move(hipRearLeft, 80);
  BOT.move(hipFrontRight, 80);
  BOT.move(hipFrontLeft, 80);
  BOT.animate(100);

  for (int i=255 ; i > 0; i--){
    analogWrite(white,i);
    delay(1);
  }
  analogWrite(white,0);
  
}
//--------------------------------------------------------------
void chirp(int beeps, int speedms){

  for (int i = 0; i < beeps; i++){
    for (int i = 0; i < 255; i++){
      digitalWrite(sounderPin, HIGH);
      delayMicroseconds((355-i)+ (speedms*2));
      digitalWrite(sounderPin, LOW);
      delayMicroseconds((355-i)+ (speedms*2));
    }
     delay(30);
  }
}
