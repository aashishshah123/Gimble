#include <I2Cdev.h>

#include <MPU6050.h>

#include <Wire.h>

#include <Servo.h>

#include <stdlib.h>




MPU6050 accelgyro;

//axis
int x = 0;
int y = 0;
int z = 0;



//state
int state = 0;


//config

Servo zservo;
Servo yservo;
Servo xservo;

void setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  #else
  if I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
  #endif;

  Serial.begin(115200);

  // initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
zservo.attach(6);
yservo.attach(5);
xservo.attach(4);
  x = accelgyro.getXGyroOffset();
  y = accelgyro.getYGyroOffset();
  z = accelgyro.getZGyroOffset();
}

//allowed attachment ports are 11,10,9,6,5,3

// Run the motor
void runMotor() {
  delay(100);
zservo.write(-z);
  delay(100);
 yservo.write(-y);
  delay(100);
 yservo.write(-x);

}

void loop() {
  //gets all raw data
  //accelgyro.getMotion6(&ax, &ay, &az, &x, &y, &z);
  accelgyro.getRotation(&x, &y, &z);
  Serial.print("a/g:\t");
  Serial.print(x); // x axis
  Serial.print("\t");
  Serial.print(y); // y axis
  Serial.print("\t");
  Serial.println(z); // z axis

  //checking if motor works

  runMotor();
}
