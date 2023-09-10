#ifndef lib_h
#define lib_h
#include <lib.h>
#include <Servo.h>
Servo Servo1;

long time_stamp = 0;
Motor motor1(5,6); //поменять 
Motor motor2(7,8); //поменять 
Ultrasonic ultra(28,29); 
int lineSensorPin = 51;
int BankaSensorPin = 50;
int servoPin= 53;  //поменять 

void motors_forward(int speed1, int speed2){
    motor1.forward(speed1);
    motor2.forward(speed2);
}
void motors_backward(int speed1, int speed2){
    motor1.backward(speed1);
    motor2.backward(speed2);
}
void motors_stop(){
    motor1.stop();
    motor2.stop();
}
//Повороты
//движение по линии 
void liner(){
    value = digitalRead(lineSensorPin)
      if (lineSensorValue == HIGH) {
        motor1.forward(255);
        motor2.backward(150);
  }
  else {
        motor2.forward(255);
        motor1.backward(230);
  }
}
void Turn_left(int speed1, int speed2, int deltaTime) {
    motor1.forward(speed1);
    motor2.backward(speed2);
    delay(deltaTime);
  }
void Turn_right(int speed1, int speed2, int deltaTime) {
    motor1.backward(speed1);
    motor2.forward(speed2);
    delay(deltaTime);
  }
// выбивание банки
void white_beat(){
    Servo1.write(110);
    motors_stop();
    Turn_right(255,150,600);
    motors_forward(255,255);
    time_stamp = milis();
    wlile (millis - time_stamp>5000){
      liner();
    }
    Servo1.write(0);
    time_stamp = milis();
    wlile (millis - time_stamp>5000){
      liner();
    }
}
void black_beat(){
  motors_forward(255,255)
  delay(1000);
  motors_backward(255,255);
  delay(1000);
}

// условие банок

/* вынесено на LOOP

void check_banki(){
    value1 = ultra.getDistance();
    value2 = digitalRead(BankaSensorPin);
    if (value1 <=1 or value2){
        if (value2==LOW){
          black_beat();
        }
        else{
          white_beat();
        }
    }
}
*/
void setup(){
  Servo1.attach(servoPin);
  motors_forward(255,255)
  delay(700);
  PinMode(lineSensorPin, INPUT);
  PinMode(BankaSensorPin, INPUT);

}
void loop(){
    value1 = ultra.getDistance();
    value2 = digitalRead(BankaSensorPin);
    if (value1 <=1 or value2){
        if (value2==LOW){
          black_beat();
        }
        else{
          white_beat();
        }
    }
    else{
      liner();
    }

}
