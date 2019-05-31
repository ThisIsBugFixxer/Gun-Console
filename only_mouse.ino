#include <Wire.h>

#include <Mouse.h>

//#include <Keyboard.h>

#include <MPU6050.h>


MPU6050 pos;  // definig the mpu6050 as pos ( as it determines the position )
int16_t ax,ay,az,gx,gy,gz;
int vx,vy;

const int leftClick=2;
const int rightClick=4;
int stateL,stateR;


void setup() {
  Serial.begin(9600);
  Wire.begin();

  if(!pos.testConnection()) {  // this checks if the mpu is conneccted
    while(1);                 // keeps checking till it connects, thus if it isnt connected the code wont exit this loop
    Serial.println("connecting to MPU6050 ");
  }

  Mouse.begin();
 // Keyboard.begin();

  pinMode(leftClick, INPUT);
  pinMode(rightClick,OUTPUT);

}

void loop() {
  pos.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);  // this starts accepting the values.

  //converting the raw values

   vx = (gx+300)/200;  // "+300" because the x axis of gyroscope give values about -350 while it's not moving. Change this value if you get something different using the TEST code, chacking if there are values far from zero.
   vy = -(gz-100)/200; // same here about "-100"

   Mouse.move(vx,vy) ;
   delay(20);

   stateL=digitalRead(leftClick);
   stateR=digitalRead(rightClick);

   if(stateL==HIGH){
      if (!Mouse.isPressed(MOUSE_LEFT)) {
       Mouse.click(MOUSE_LEFT);
       Serial.println("L");
         Mouse.move(vx,vy) ;

    }

   }

  if(stateR==LOW){
    if (!Mouse.isPressed(MOUSE_RIGHT)) {
       Mouse.click(MOUSE_RIGHT);
       Serial.println("right");
         Mouse.move(vx,vy) ;

    }
   }
 }
