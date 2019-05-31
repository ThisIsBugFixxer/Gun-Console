#include <Mouse.h>
#include<Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
int16_t x,y,z,ax,ay,az;
int fx,fy;




void setup() {
  // put your setup code here, to run once:
  Mouse.begin();
  Wire.begin();
  Serial.begin(9600);

  pinMode(LED_BUILTIN,OUTPUT);

  if(!mpu.testConnection()) {
    while (1) {
      /* code */
      Serial.println("connecting to MPU6050");

      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN,LOW);
      delay(500);


    }
  }


}

void loop() {
  // put your main code here, to run repeatedly:
  mpu.getMotion6(&x,&y,&z,&ax,&ay,&az);

  fx = (x+300)/200;  // "+300" because the x axis of gyroscope give values about -350 while it's not moving. Change this value if you get something different using the TEST code, chacking if there are values far from zero.
  fy = -(z-100)/200; // same here about "-100"

  Mouse.move(fx,fy);
  delay(20);
}
