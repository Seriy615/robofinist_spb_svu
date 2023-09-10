#ifndef lib_h
#define lib_h
#include <lib.h>

long time_stamp = 0;
Motor motor1(5,6); //поменять 
Motor motor2(7,8); //поменять 
Ultrasonic ultra(28,29); 
int lineSensorPin = 51;
int BankaSensorPin = 50;

void motors_forward(int speed1, int speed2){
    motor1.forward(speed1);
    motor2.forward(speed2);
}
void motors_backward(int speed1, int speed2){
    motor1.backward(speed1);
    motor2.backward(speed2);
}
//Повороты
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
void beat(){
    Turn_right(255,100,400);
    motors_forward(255,255);
    

}
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
// условие банок
void check_banki(){
    value1 = ultra.getDistance();
    value2 = digitalRead(BankaSensorPin);
    if (value1 <=1 or value2){
        // дописать 
    }
}


        switch (value2)
        {
        case LOW:
            motors_forward(255,255);
            delay(1000);
            motors_backward(255,255);
            break;
        
        case HIGH:
            beat();
            break;
        }