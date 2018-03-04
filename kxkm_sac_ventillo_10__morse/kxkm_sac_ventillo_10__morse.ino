// ConstantSpeed.pde
// -*- mode: C++ -*-
//
// Shows how to run AccelStepper in the simplest,
// fixed speed mode with no accelerations
// Requires the Adafruit_Motorshield v2 library
//   https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library
// And AccelStepper with AFMotor support
//   https://github.com/adafruit/AccelStepper

// This tutorial is for Adafruit Motorshield v2 only!
// Will not work with v1 shields
#include <Scheduler.h>

#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x60);

// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);




void setup()
{
  Serial.begin(9600);


  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  myMotor1->setSpeed(255);
  myMotor2->setSpeed(255);
  myMotor3->setSpeed(255);
  myMotor4->setSpeed(255);

}

void loop()


{

  myMotor1->setSpeed(255);//ventil1
  myMotor2->setSpeed(255);//ventil2
  myMotor3->setSpeed(255);//ventil3
  myMotor4->setSpeed(255);//lulu

  myMotor1->run(FORWARD);
  myMotor2->run(RELEASE);
  myMotor3->run(RELEASE);

  myMotor4->run(FORWARD);
  delay (200);//cour
  myMotor4->run(RELEASE);
  delay (200);//cour
  myMotor4->run(FORWARD);
  delay (1000);//long
  myMotor4->run(RELEASE);
  delay (200);//cour
  myMotor4->run(FORWARD);
  delay (1000);//long
  myMotor4->run(RELEASE);
  delay (200);//cour
  myMotor4->run(FORWARD);
  delay (200);//cour
  myMotor4->run(RELEASE);
  delay (2000);//espace

  myMotor1->run(RELEASE);
  myMotor2->run(FORWARD);
  myMotor3->run(RELEASE);

  myMotor4->run(FORWARD);
  delay (200);//cour
  myMotor4->run(RELEASE);
  delay (200);//cour
  myMotor4->run(FORWARD);
  delay (1000);//long
  myMotor4->run(RELEASE);
  delay (200);//cour
  myMotor4->run(FORWARD);
  delay (200);//cour
  myMotor4->run(RELEASE);
  delay (200);//cour
  myMotor4->run(FORWARD);
  delay (200);//cour
  myMotor4->run(RELEASE);
  delay (2000);//espace

  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
  myMotor3->run(FORWARD);

  myMotor4->run(FORWARD);
  delay (200);//cour
  myMotor4->run(RELEASE);
  delay (200);//cour
  myMotor4->run(FORWARD);
  delay (1000);//long
  myMotor4->run(RELEASE);
  delay (2000);//espace

  myMotor1->run(FORWARD);
  myMotor2->run(RELEASE);
  myMotor3->run(FORWARD);

  myMotor4->run(FORWARD);
  delay (200);//cour
  myMotor4->run(RELEASE);
  delay (200);//cour
  myMotor4->run(FORWARD);
  delay (200);//cour
  myMotor4->run(RELEASE);
  delay (200);//cour
  myMotor4->run(FORWARD);
  delay (200);//cour
  myMotor4->run(RELEASE);
  delay (2000);//espace

  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
  myMotor3->run(RELEASE);

  myMotor4->run(FORWARD);
  delay (1000);//long
  myMotor4->run(RELEASE);
  delay (2000);//espace

  myMotor4->run(FORWARD);
  delay (200);//cour
  myMotor4->run(RELEASE);
  delay (200);//cour
  myMotor4->run(FORWARD);
  delay (200);//cour
  myMotor4->run(RELEASE);
  delay (2000);//espace

  myMotor1->run(RELEASE);
  myMotor2->run(FORWARD);
  myMotor3->run(FORWARD);

  myMotor4->run(FORWARD);
  delay (1000);//long
  myMotor4->run(RELEASE);
  delay (200);//cour
  myMotor4->run(FORWARD);
  delay (200);//cour
  myMotor4->run(RELEASE);
  delay (200);//cour
  myMotor4->run(FORWARD);
  delay (1000);//long
  myMotor4->run(RELEASE);
  delay (200);//cour
  myMotor4->run(FORWARD);
  delay (200);//cour
  myMotor4->run(RELEASE);
  delay (2000);//espace

  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
  myMotor3->run(FORWARD);

  delay (2000);//espace

  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
  myMotor3->run(RELEASE);


}

