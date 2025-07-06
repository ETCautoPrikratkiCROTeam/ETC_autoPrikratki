#include <Motors.h>
#include <PID.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <EEPROM.h>
#include "SparkFun_Qwiic_OTOS_Arduino_Library.h"
#include <Arduino.h>
#include <math.h>

#define RAD_TO_DEG 57.2958  // Conversion factor from radians to degrees

Motors motors(true, &Serial1);
QwiicOTOS myOtos;
#define SENSOR_COUNT 48
void go(float speed, float angle, float rotation, int speedLimit);
void holdLineAndSlideSafe(float direction, float KpLine = 0.4, int maxSideSpeed = 25, int maxRotation = 30);
void followBall(float baseSpeed, float deadZone = 1);
void motorSetSpeed(int n, int speed);
void setupMotors();
void motorsOff();
void motorsOn();
int k;
const int NUM_SENSORS = 48;
int treshold[NUM_SENSORS];
bool Blijevo,Bdesno,Bnaprijed,Bnazad;
const int ADDITION_VALUE = 900;
bool found;
float rotationToMaintainHeading(float headingToMaintain);
int headingToMaintain = 0;
int lin[NUM_SENSORS];
int minValues[SENSOR_COUNT];
int maxValues[SENSOR_COUNT];
const int LINI = 850;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
float n = 0.889;
float n2 = 0.937;
enum State {
  PAUSED,
  LEFT,
  ATTACK,
  RIGHT
};
double setpoint = 0;  // Desired heading
double input = 0, output = 0;
double greska = 0, lastError = 0, integral = 0, derivative = 0;
double Kp = 0.7, Ki = 0.0, Kd = 0.046; // Tune these values
unsigned long lastTime = 0;
State state = ATTACK;
int BRZINA = 36;

void setup() {
  // put your setup code here, to run once:
  Setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  Loop();
  
}
