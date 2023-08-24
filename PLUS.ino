/*
 * copyright (c) 2023, TEAM RAW
 * Divyanshu-Modi <divyan.m05@student.sfit.ac.in>
 */

#include "analogWrite.h"
#include "PS4Controller.h"

typedef struct motor {
  int id; // Useless ?
  int dir_pin;
  int pwm_pin;
  int state;
  int speed;
} mot;

#define MT_CTRL(num, pin1, pin2) \
{ \
  .id = num, \
  .dir_pin = pin1, \
  .pwm_pin = pin2, \
  .state = LOW, \
  .speed = 100, \
}

mot mot1 MT_CTRL(1, 32, 33);
mot mot2 MT_CTRL(2, 17, 16);
mot mot3 MT_CTRL(2, 27, 5);
mot mot4 MT_CTRL(2, 25, 26);

void __motor_activate(struct motor mot)
{
//  Serial.printf("state: %d\t speed: %d\n", mot.state, mot.speed);
  digitalWrite(mot.dir_pin, mot.state);
  analogWrite(mot.pwm_pin, mot.speed);
}

void forward(int speed)
{
  mot1.state = HIGH;
  mot4.state = HIGH;
  Serial.println("forward");

  mot1.speed = speed;
  mot4.speed = speed;

  __motor_activate(mot1);
  __motor_activate(mot4);
}

void backward(int speed)
{
  mot1.state = LOW;
  mot4.state = LOW;
  Serial.println("backward");

  mot1.speed = speed;
  mot4.speed = speed;

  __motor_activate(mot1);
  __motor_activate(mot4);
}

void left(int speed)
{
  mot2.state = HIGH;
  mot3.state = HIGH;
  Serial.println("left");

  mot2.speed = speed;
  mot3.speed = speed;

  __motor_activate(mot2);
  __motor_activate(mot3);
}

void right(int speed)
{
  mot2.state = LOW;
  mot3.state = LOW;
  Serial.println("right");

  mot2.speed = speed;
  mot3.speed = speed;

  __motor_activate(mot2);
  __motor_activate(mot3);
}

void clockwise(int speed)
{
  mot1.state = LOW;
  mot2.state = HIGH;
  mot3.state = LOW;
  mot4.state = HIGH;

  mot1.speed = speed;
  mot2.speed = speed;
  mot3.speed = speed;
  mot4.speed = speed;
  Serial.println("clk");

  __motor_activate(mot1);
  __motor_activate(mot2);
  __motor_activate(mot3);
  __motor_activate(mot4);
}

void anticlockwise(int speed)
{
  mot1.state = HIGH;
  mot2.state = LOW;
  mot3.state = HIGH;
  mot4.state = LOW;
  Serial.println("aclk");

  mot1.speed = speed;
  mot2.speed = speed;
  mot3.speed = speed;
  mot4.speed = speed;

  __motor_activate(mot1);
  __motor_activate(mot2);
  __motor_activate(mot3);
  __motor_activate(mot4);
}

void stop()
{
  mot1.state = LOW;
  mot2.state = LOW;
  mot3.state = LOW;
  mot4.state = LOW;
  Serial.println("stop");

  mot1.speed = 0;
  mot2.speed = 0;
  mot3.speed = 0;
  mot4.speed = 0;

  __motor_activate(mot1);
  __motor_activate(mot2);
  __motor_activate(mot3);
  __motor_activate(mot4);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(mot1.dir_pin, OUTPUT);
  pinMode(mot2.dir_pin, OUTPUT);
  pinMode(mot3.dir_pin, OUTPUT);
  pinMode(mot4.dir_pin, OUTPUT);
  Serial.begin(9600);
  PS4.begin("78:21:84:DF:23:E8");
//  PS4.begin("");
}

void loop() {
  // put your main code here, to run repeatedly:
  int LX = PS4.LStickX();
  int LY = PS4.LStickY();
  int RX = PS4.RStickX();
  int RY = PS4.RStickY();

  if (LX > 20) {
    forward(map(LX, 20, 128, 0, 200));
  } else if (LX < -20) {
    backward(map(LX,-20, -128, 0, 200));
  } else if (LY > 20) {
    left(map(LY, 20, 128, 0, 200));
  } else if (LY < -20) {
    right(map(LY,-20, -128, 0, 200));
  } else if (RX > 20) {
    clockwise(map(RX, 20, 128, 0, 200));
  } else if (RX < -20) {
    anticlockwise(map(RX, -20, -128, 0, 200));
  } else {
    stop();
  }
}
