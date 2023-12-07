/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * @file    MeMegaPiDCMotorTest.ino
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2016/05/17
 * @brief   Description: this file is sample code for MegaPi DC motor device.
 *
 * Function List:
 *    1. void MeMegaPiDCMotorTest::run(int16_t speed)
 *    2. void MeMegaPiDCMotorTest::stop(void)
 *
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 * Mark Yan     2016/05/17    1.0.0          build the new
 * </pre>
 */
#include "MeMegaPi.h"
#include <Wire.h>
#include <MeMegaPi.h>

String value;
int input;

MeMegaPiDCMotor gripper(PORT4A); // Gripper 

MeMegaPiDCMotor motor2(PORT1B);  //RIGHt motor

MeMegaPiDCMotor motor1(PORT3B);

MeMegaPiDCMotor motor4(PORT2B);  //Left motor

uint8_t motorSpee_R = 45;
uint8_t motorSpee_L = 45;



void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
}


void loop() {

  if (Serial3.available()) {
    value = Serial3.readStringUntil('\n');

    if (value.length() > 1) {
      input = value.substring(2, value.length()).toInt();
      value = value[0];
      Serial.print("newDAT  > ");
      Serial.print(value);
      Serial.print(" - ");
      Serial.println(input);
    }else{
      input=0;
      Serial.print("newbot  > ");
      Serial.print(value);
      Serial.print(" - ");
      Serial.println(input);
    }
  } else {
    value = "-1";
  }


  if (value == "5"&& input != 0) {
    motor2.run(input * 0.5);
    motor4.run(-input * 0.5);
  } else if (value == "0" && input > 0) {
    // motor1.run(-motorSpeed);
    motor2.run(-input*0.7);
    // motor3.run(-motorSpeed);
    motor4.run(-input*0.7);
  } else if (value == "0" && input < 0) {
    // motor1.run(-motorSpeed);
    motor2.run(-input*0.7);
    // motor3.run(-motorSpeed);
    motor4.run(-input*0.7);

  } else if (value == "4"&& input != 0) {
    // motor1.run(-motorSpeed);
    motor2.run(-input * 0.5);
    // motor3.run(-motorSpeed);
    motor4.run(input * 0.5);

  } else if (value == "0"&& input==0) {
    motor1.run(50);

  } else if (value == "1"&& input==0) {
    motor1.run(-50);


  } else if (value == "3"&& input==0) {
    gripper.run(-100);

  } else if (value == "2"&& input==0) {
    gripper.run(100);


  }else {

    motor2.stop();
    gripper.stop();
    motor4.stop();
    motor1.stop();
  }


  delay(10);
}
