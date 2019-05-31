/* creatied by Priyam Mehta (This_Is_Dexter)
 *  and helped  by Meet Rathod ( MRX)
 */


#include <Keyboard.h>

#include <Mouse.h>

//#include <I2Cdev.h>



#include <Wire.h>
///#include <I2Cdev.h>
#include <MPU6050.h>
#include <Mouse.h>

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy;
const int b1=2; // left click
const int b2=3; // right click
const int b3=10; // keyboard "r" button click to reload

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    while (1);
    }
    
    Mouse.begin();
    Keyboard.begin();
    pinMode(b1, INPUT);
    pinMode(b2, INPUT);
    pinMode(b3,INPUT);
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  vx = (gx+300)/200;  // "+300" because the x axis of gyroscope give values about -350 while it's not moving. Change this value if you get something different using the TEST code, chacking if there are values far from zero.
  vy = -(gz-100)/200; // same here about "-100"
  
  Mouse.move(vx, vy);
  
  delay(20);

int  left=digitalRead(b1);
int  right=digitalRead(b2);
int  reload=digitalRead(b3);

  if(left==HIGH) {
   // if (!Mouse.isPressed(MOUSE_LEFT)) {
       Mouse.click(MOUSE_LEFT);
       Serial.println("left");
      
  //  }
   }

   if(right==HIGH) {
  //  if (!Mouse.isPressed(MOUSE_RIGHT)) {
       Mouse.click(MOUSE_RIGHT);
       Serial.println("right");
      
   // }
   }

  if(reload==HIGH) {
    Keyboard.press("r");
    delay(20);
    Serial.println("r");
    Keyboard.releaseAll();
  }
  
}
