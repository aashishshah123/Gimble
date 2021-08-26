#include <I2Cdev.h>

#include <MPU6050.h>

#include <Wire.h>

#include <Stepper.h>

#include <stdlib.h>

#include <fstream>

#include <json/json.h>

MPU6050 accelgyro;

//axis
int x = 0;
int y = 0;
int z = 0;

//config
Json::Value data;
std::ifstream file("info.json", std::ifstream::binary);
file >> data;
cout << "version " += data.version

//state
int state = 0;

// Motor
int stepsPerRevolution = data.rev;
int motorSpeed = data.speed;
int pos = 0;

//config
int serb = data.ser
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  #else
  if I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
  #endif;

  Serial.begin(serb);

  // initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  x = accelgyro.getXGyroOffset();
  y = accelgyro.getYGyroOffset();
  z = accelgyro.getZGyroOffset();
}

// Power down the motor pins
void killSwitch() {
  Serial.println('got kill signal shutting down');
  abort();
}

// Run the motor
void runMotor() {
  if (pos > 360) {
    KillSwitch();
  }
  myStepper.setSpeed(motorSpeed);
  // step pos/360 of a revolution:
  myStepper.step(pos / 360);
}

void loop() {
  //gets all raw data
  //accelgyro.getMotion6(&ax, &ay, &az, &x, &y, &z);
  accelgyro.getRotation( & x, & y, & z);
  Serial.print("a/g:\t");
  Serial.print(x); // x axis
  Serial.print("\t");
  Serial.print(y); // y axis
  Serial.print("\t");
  Serial.println(z); // z axis

  //checking if motor works
  pos = 180;
  runMotor();
  if (Serial.available() > 0) {
    state = Serial.read();
    switch (state) {
    case 'KILL':
      killSwitch();
      break;
    case 1:
      killSwitch();
      break;
    case 'kill':
      killSwitch();
      break;
    case 'stop':
      killSwitch();
      break;
    default:
      cont << 'we didn\'t get that'
      break;
    }
  }
}